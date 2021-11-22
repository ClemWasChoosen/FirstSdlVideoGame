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
	//int textuW, textuH; 
	FILE* fileToRead = NULL;

	carte_t carteJeu;
	init_spriteMap(&carteJeu, &fileToRead);

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


	// Boucle principal
	while(!terminer){
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
			}
		}
		SDL_RenderClear(renderer);

		map = loadImage("./resources/dungeon_tiles.bmp", renderer);

		//mapToRender = loadImage("./resources/neonbrand-OjxsirfohHU-unsplash.bmp", renderer);

		if (map == NULL) {
        	fprintf(stderr, "Erreur recuperation de la map: %s", SDL_GetError());
			SDL_DestroyTexture(map);
			break;
		}


		//SDL_QueryTexture(map, NULL, NULL, &textuW, &textuH);	

		deplacerCarte(SIZE_PIXEL * ZOOM_SCREEN, &carteJeu, evenements, preOccurSlash);


		for (int i = 0; i < carteJeu.sizeMap;i++) {
			
			if (renderMap(map, renderer, carteJeu.allSprite[i].posEcran, carteJeu.allSprite[i].posSprite)) {
        		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
				break;	
			}
		}

		if (SDL_RenderDrawPoint(renderer, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2) < 0) {
			fprintf(stderr, "Erreur SDL_RenderDrawPoint : %s", SDL_GetError());
			break;
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(20);

		
			}

	SDL_DestroyTexture(map);
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
