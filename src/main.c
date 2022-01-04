#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "character.h"
#include "map.h"
#include "sprite.h"
#include "constants.h"
#include "zombies.h"
#include "time.h"
#include "menu.h"

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, window, renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}


void mainLoop(SDL_Renderer* renderer){
  SDL_Event evenements; // Événements liés à la fenêtre
	SDL_Event eventsPause;
  bool boolPause = false;
	bool terminer = false;
  SDL_Texture* map = NULL;
	SDL_Texture* heart = NULL;
	SDL_Texture* player = NULL;
	SDL_Texture* zombie = NULL;
	SDL_Texture* gameOver = NULL;
  SDL_Texture* menu = NULL;
	FILE* fileMap = NULL;

	sprite_t sizeGameOver;
	sizeGameOver.posSprite.x = 0;
	sizeGameOver.posSprite.y = 0;
	sizeGameOver.posSprite.h = 800;
	sizeGameOver.posSprite.w = 800;

	sizeGameOver.posEcran.x = 0;
	sizeGameOver.posEcran.y = 0;
	sizeGameOver.posEcran.h = 800;
	sizeGameOver.posEcran.w = 800;

	//int comptTour = 0;

	//float frameTime = 0;
	//int prevTime = 0;
	//int currentTime = 0;
  //int deltaTimeWait = 0;
	int deltaTime = 0;
	//int deltaTimeZombies = 0;
  const int frameDelay = 1000/FPS;
  int resRenderHeartLife = 0;


  int waves = NBZOMBIES - 1;
  int timerWaves = 0;
  int endWave = 1;

	//A deplacer
	//int statePlayer = 0;

	carte_t carteJeu;
	character_t mainCharactere;
	zombiesAll_t allZombies;
	init_spriteMap(&carteJeu, &fileMap);
	init_spritePlayer(&mainCharactere);
	placerCarteCentre(&carteJeu);

	//Utilisé pour aller de haut en bas dans le tableau
	int preOccurSlash = 0;
	for (int r = 0; r < carteJeu.sizeMap; r++) {
			if (carteJeu.allMap[r] == '/') {
				preOccurSlash = r + 1;
				break;
			}
	}

  menu = loadImage("./resources/menu.bmp", renderer);
  if (menu == NULL) {
    fprintf(stderr, "Erreur recuperation de la feuille Joueur principal: %s", SDL_GetError());
    SDL_DestroyTexture(menu);
  }

	init_spriteZombie(&allZombies, carteJeu.allMap, carteJeu.sizeMap, carteJeu.allSprite[0].posEcran, preOccurSlash);


	if (fileMap == NULL) {
		SDL_DestroyTexture(map);
		free(carteJeu.allSprite);
		free(carteJeu.allMap);
		free(allZombies.zombiesTab);
		return;
	}




	// Boucle principale
	while(!terminer){

		Uint32 start_time, tempsBoucle = 0;

  		start_time = SDL_GetTicks();

    if (boolPause) {
      do {
        SDL_PollEvent( &eventsPause );
        SDL_Delay(5);
      } while(eventsPause.type != SDL_MOUSEBUTTONDOWN);
      boolPause = false;
    }

		SDL_PollEvent( &evenements );
		switch(evenements.type)
		{
			case SDL_QUIT:
			terminer = true; break;
      case SDL_MOUSEBUTTONDOWN:
				if (evenements.button.button == SDL_BUTTON_LEFT){
          boolPause = true;
        }

      break;
			case SDL_KEYDOWN:
			switch(evenements.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					terminer = true; break;
				/*case SDLK_n:
					for (int i = 0; i < carteJeu.sizeMap; i++) {
						carteJeu.allSprite[i].posEcran.x += 200.0f * deltaTime;
					}
				break;*/

			}
		}

		//frameTime += deltaTime;

		SDL_RenderClear(renderer);


		//Récuperation de l'image permettant de faire la carte
		map = loadImage("./resources/dungeon_tiles.bmp", renderer);
		if (map == NULL) {
      fprintf(stderr, "Erreur recuperation de la map: %s", SDL_GetError());
			SDL_DestroyTexture(map);
			break;
		}

		gameOver = loadImage("./resources/game-over.bmp", renderer);
		if (gameOver == NULL) {
      fprintf(stderr, "Erreur recuperation de la map: %s", SDL_GetError());
			SDL_DestroyTexture(gameOver);
			break;
		}
		//Récuperation de l'image permettant de faire la carte
		player = loadImage("./resources/16x16-knight-2-v3.bmp", renderer);
		if (player == NULL) {
			fprintf(stderr, "Erreur recuperation de la feuille Joueur principal: %s", SDL_GetError());
			SDL_DestroyTexture(player);
			break;
		}

		zombie = loadImage("./resources/16x16-knight-1-v3.bmp", renderer);
		if (zombie == NULL) {
			fprintf(stderr, "Erreur recuperation de la feuille zombies: %s", SDL_GetError());
			SDL_DestroyTexture(zombie);
			break;
		}

    heart = loadImage("./resources/heart.bmp", renderer);
		if (heart == NULL) {
			fprintf(stderr, "Erreur recuperation de la feuille coeur de vie: %s", SDL_GetError());
			SDL_DestroyTexture(heart);
			break;
		}

		//Récupère les clicks du joueur
		if (mainCharactere.state < 10) {
			deplacerCarte((SIZE_PIXEL * ZOOM_SCREEN)/4, &carteJeu, evenements, preOccurSlash, &mainCharactere);
		}

		//Rendu de tous les sprites sur la carte

    for (int i = 0; i < carteJeu.sizeMap;i++) {
			if (renderMap(map, renderer, carteJeu.allSprite[i].posEcran, carteJeu.allSprite[i].posSprite)) {
        		fprintf(stderr, "Erreur SDL_Crstart_timeeateTextureFromSurface : %s", SDL_GetError());
				break;
			}
		}

		for (int i = 0; i < NBZOMBIES - waves; i++)
		{
			if (renderAnimeZombie(zombie, renderer, allZombies.zombiesTab[i].zmb.posEcran, allZombies.zombiesTab[i].zmb.posSprite, &allZombies.zombiesTab[i])){
				fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
				break;
			}

      randMoveZombies(&allZombies.zombiesTab[i], carteJeu.allMap, carteJeu.sizeMap, preOccurSlash);
      characterHit(&mainCharactere.life, &allZombies.zombiesTab[i], carteJeu.posJoueur, preOccurSlash);
		}

		if (renderAnimePlayer(player, renderer, mainCharactere.charac.posEcran, mainCharactere.charac.posSprite, &deltaTime, &mainCharactere, carteJeu.allSprite, carteJeu.sizeMap, &allZombies)) {
			fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
			break;
		}

    resRenderHeartLife = renderHeartLife(&mainCharactere, heart, renderer);
    if (resRenderHeartLife == EXIT_FAILURE) {
      fprintf(stderr, "Erreur Impossible d afficher les coeurs : %s\n", SDL_GetError());
			break;
    }else if(resRenderHeartLife == 2){
      terminer = true;
    }

    attackOnZombies(evenements, &allZombies, carteJeu.posJoueur);
    //attackOnRight(evenements, &allZombies, carteJeu.posJoueur);

		//######### Pour debug ###########
		//Affiche un point au centre de l'écran
		/*if (SDL_RenderDrawPoint(renderer, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2) < 0) {
			fprintf(stderr, "Erreur SDL_RenderDrawPoint : %s", SDL_GetError());
			break;
		}*/
		//Fin du jeu car le joueur a perdu, il ne lui reste plus de vie
	if (resRenderHeartLife == 2) {
		if(renderGameOver(gameOver, renderer, sizeGameOver.posEcran, sizeGameOver.posSprite) == EXIT_FAILURE){
			fprintf(stderr, "Erreur SDL_RenderGameOver : %s", SDL_GetError());
		}
	}

  if (boolPause) {
    renderPause(menu, renderer);
  }

		SDL_RenderPresent(renderer);
		//SDL_Delay(20);
		//comptTour ++;

		if(resRenderHeartLife == 2){
			SDL_Delay(5000);
		}

  	tempsBoucle = SDL_GetTicks()-start_time;

		deltaTime += tempsBoucle;
		//deltaTimeZombies += tempsBoucle;
    //deltaTimeWait += tempsBoucle;

    endWave = 1;
    for (int i = 0; i < NBZOMBIES - waves; i++)
		{
      allZombies.zombiesTab[i].deltaTime += tempsBoucle;


      if (allZombies.zombiesTab[i].display == 1) {
        endWave = 0;
      }
		}

    if (endWave == 1) {
      timerWaves += tempsBoucle;
    }

    if (timerWaves >= 5000) {
      if (waves <= 0) {
        terminer = true;
      }else{
        waves--;
		    //fprintf(stderr, "%d\n", NBZOMBIES - waves);
        for (int i = 0; i < NBZOMBIES - waves; i++)
    		{
          allZombies.zombiesTab[i].display = 1;
    		}
        timerWaves = 0;
      }
    }

    //float elapsedMS = tempsBoucle / (float)SDL_GetPerformanceFrequency() * 1000.0f;

	  // Cap to 60 FPS
    //fprintf(stderr, "%f\n", floor(2.0f - elapsedMS));
	  //SDL_Delay(floor(2.0f - elapsedMS));
    if (frameDelay > tempsBoucle) {
      SDL_Delay(frameDelay - tempsBoucle);
    }


	//Fin de la boucle
	}

	//Libère la mémoire
	SDL_DestroyTexture(map);
	SDL_DestroyTexture(player);
	free(carteJeu.allSprite);
	free(carteJeu.allMap);
	free(allZombies.zombiesTab);
}

int main(/*int argc, char *argv[]*/)
{
	time_t temps = time(NULL);
	srand(temps);

	SDL_Window* fenetre = NULL; // Déclaration de la fenêtre
	SDL_Renderer* renderer = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
	{
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	// Créer la fenêtre
	if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &fenetre, &renderer)) {
		printf("Erreur de la creation d’une fenetre et du renderer: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_SetWindowTitle(fenetre, "Samourai vs Zombies");

	//Boucle du jeu créée dans une fonction
	mainLoop(renderer);

	// Quitter SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
