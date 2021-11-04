#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

void mainLoop(SDL_Renderer* renderer){	
	SDL_Event evenements; // Événements liés à la fenêtre
	bool terminer = false;
	SDL_Texture* map = NULL;
	SDL_Texture* fond = NULL;
	int textuW, textuH;

	SDL_Rect sizeMap;
	SDL_Rect posEcran;
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
				case SDLK_q:
				terminer = true; break;
			}
		}
		SDL_RenderClear(renderer);

		map = loadImage("./resources/dungeon_tiles.bmp", renderer); 
		if (map == NULL) {
        	fprintf(stderr, "Erreur recuperation de l'image: %s", SDL_GetError());
			SDL_DestroyTexture(map);
			break;
		}

		SDL_QueryTexture(map, NULL, NULL, &textuW, &textuH);	

		sizeMap.x = 0;
		sizeMap.y = 0;
		sizeMap.w = 150;
		sizeMap.h = 150;

		posEcran.x = 20;
		posEcran.y = 50;
		posEcran.w = 300;
		posEcran.h = 300;
	

		if (SDL_RenderCopy(renderer, map, &sizeMap, NULL) != 0) {
        	fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
				
		}
		//SDL_RenderCopy(renderer, map, &sizeMap, NULL);
		SDL_RenderPresent(renderer);
	}
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
//	fenetre = SDL_CreateWindow("Samourai vs Zombies", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
//	SDL_CreateWindowAndRenderer(600, 600, SDL_WINDOWPOS_CENTERED, &fenetre, &renderer);
	
	if (SDL_CreateWindowAndRenderer(600, 600, SDL_WINDOW_RESIZABLE, &fenetre, &renderer)) {	
		printf("Erreur de la creation d’une fenetre et du renderer: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}		

	SDL_SetWindowTitle(fenetre, "Samourai vs Zombies");	

	mainLoop(renderer);

	// Quitter SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
