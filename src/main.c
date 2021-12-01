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
#include "character.h"
#include "map.h"
#include "sprite.h"
#include "constants.h"

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
	bool terminer = false;
	SDL_Texture* map = NULL;
	SDL_Texture* player = NULL;
	FILE* fileToRead = NULL;
	int comptTour = 0;

	float frameTime = 0;
	int prevTime = 0;
	int currentTime = 0;
	int deltaTime = 0;

	//A deplacer
	//int statePlayer = 0;

	carte_t carteJeu;
	character_t mainCharactere;
	init_spriteMap(&carteJeu, &fileToRead);
	init_spritePlayer(&mainCharactere);
	
	if (fileToRead == NULL) {
		SDL_DestroyTexture(map);
		free(carteJeu.allSprite);
		free(carteJeu.allMap);
		return;
	}

	placerCarteCentre(&carteJeu);

	//Utilisé pour aller de haut en bas dans le tableau
	int preOccurSlash = 0;
	for (int r = 0; r < carteJeu.sizeMap; r++) {
			if (carteJeu.allMap[r] == '/') {
				preOccurSlash = r + 1;
				break;	
			}
	}


	// Boucle principale
	while(!terminer){

		Uint32 start_time, tempsBoucle = 0;
		//float fps;

  		start_time = SDL_GetTicks();
		
  		
		/*prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;*/

		SDL_PollEvent( &evenements );
		switch(evenements.type)
		{
			case SDL_QUIT:
			terminer = true; break;
			case SDL_KEYDOWN:
			switch(evenements.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					terminer = true; break;
				case SDLK_n:
					for (int i = 0; i < carteJeu.sizeMap; i++) {
						carteJeu.allSprite[i].posEcran.x += 200.0f * deltaTime;	
					}
				break;
			}
		}
		
		frameTime += deltaTime;
		
		SDL_RenderClear(renderer);

		//Récuperation de l'image permettant de faire la carte
		map = loadImage("./resources/dungeon_tiles.bmp", renderer);
		if (map == NULL) {
        	fprintf(stderr, "Erreur recuperation de la map: %s", SDL_GetError());
			SDL_DestroyTexture(map);
			break;
		}
		//Récuperation de l'image permettant de faire la carte
		if (mainCharactere.direction == 'd') {
			player = loadImage("./resources/16x16-knight-1-v3.bmp", renderer);
			if (player == NULL) {
        		fprintf(stderr, "Erreur recuperation du Joueur principal: %s", SDL_GetError());
				SDL_DestroyTexture(player);
				break;
			}		
		}else {
			player = loadImage("./resources/16x16-knight-1-v3-reverse.bmp", renderer);
			if (player == NULL) {
        		fprintf(stderr, "Erreur recuperation du Joueur principal: %s", SDL_GetError());
				SDL_DestroyTexture(player);
				break;
			}
		}
		

		//mapToRender = loadImage("./resources/neonbrand-OjxsirfohHU-unsplash.bmp", renderer);

		//SDL_QueryTexture(map, NULL, NULL, &textuW, &textuH);	

		//Récupère les clicks du joueur
		if (mainCharactere.state < 10) {
			deplacerCarte((SIZE_PIXEL * ZOOM_SCREEN)/4, &carteJeu, evenements, preOccurSlash, &comptTour, &mainCharactere);
		}

		//Rendu de tous les sprites sur la carte
		for (int i = 0; i < carteJeu.sizeMap;i++) {
			if (renderMap(map, renderer, carteJeu.allSprite[i].posEcran, carteJeu.allSprite[i].posSprite)) {
        		fprintf(stderr, "Erreur SDL_Crstart_timeeateTextureFromSurface : %s", SDL_GetError());
				break;	
			}
		}

		if (renderAnimePlayer(player, renderer, mainCharactere.charac.posEcran, mainCharactere.charac.posSprite, &deltaTime, &mainCharactere, carteJeu.allSprite, carteJeu.sizeMap)) {
			fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
			break;
		}

		//######### Pour debug ###########
		//Affiche un point au centre de l'écran
		if (SDL_RenderDrawPoint(renderer, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2) < 0) {
			fprintf(stderr, "Erreur SDL_RenderDrawPoint : %s", SDL_GetError());
			break;
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(20);
		comptTour ++;

		//fprintf(stderr, " %f + delta : %f", frameTime, deltaTime);


		//SDL_Flip();

  		tempsBoucle = SDL_GetTicks()-start_time;

		deltaTime += tempsBoucle;
		

		//fprintf(stderr, "deltaTime %i\n", deltaTime);					
  		//fps = (tempsBoucle > 0) ? 1000.0f / tempsBoucle : 0.0f;
		//fprintf(stderr, " %d ", fps);
		
	//Fin de la boucle 
	}

	//Libère la mémoire 
	SDL_DestroyTexture(map);
	SDL_DestroyTexture(player);
	free(carteJeu.allSprite);
	free(carteJeu.allMap);
}

int main(int argc, char *argv[])
{
	SDL_Window* fenetre = NULL; // Déclaration de la fenêtre
	SDL_Renderer* renderer = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
	{
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	// Créer la fenêtre
	if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &fenetre, &renderer)) {	
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
