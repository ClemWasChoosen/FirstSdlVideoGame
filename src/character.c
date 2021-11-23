#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "character.h"
#include "constants.h"


int renderPlayer(SDL_Texture *player, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer){
	if (SDL_RenderCopy(renderer, player, &sizePlayer, &posEcran)) {
		fprintf(stderr, "Erreur SDL_RenderCopy : %s\n", SDL_GetError());		
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int renderAnimePlayer(SDL_Texture *player, SDL_Renderer * renderer, SDL_Rect posEcran, SDL_Rect sizePlayer, int *i, int *statePlayer){
	
	
	sizePlayer.x += 64 * (*statePlayer);
	if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
		return EXIT_FAILURE;		

	if (*i%5 == 0) {
		*statePlayer = *statePlayer+1;
		if (*i == 25) {	
			*i = 0;
			*statePlayer = 0;
		}
	}

//	fprintf(stderr, "%d ", sizePlayer.x);
/*	
	sizePlayer.x += 64;
	if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
		return EXIT_FAILURE;		

	SDL_Delay(10);
	SDL_RenderClear(renderer);

//	fprintf(stderr, "%d ", sizePlayer.x);

	sizePlayer.x += 64;
	if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
		return EXIT_FAILURE;		

	SDL_Delay(10);
	SDL_RenderClear(renderer);

//	fprintf(stderr, "%d ", sizePlayer.x);

	sizePlayer.x += 64;
	if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
		return EXIT_FAILURE;		

	SDL_Delay(10);
*/
	return EXIT_SUCCESS;
}

void init_spritePlayer(character_t *mainCharactere){
	mainCharactere->charac.posSprite.x = SIZE_PIXEL * 1.5;
	mainCharactere->charac.posSprite.y = SIZE_PIXEL * 1.7;
	mainCharactere->charac.posSprite.h = SIZE_PIXEL * 2 ;
	mainCharactere->charac.posSprite.w = SIZE_PIXEL  * 2;
	
	/*
	mainCharactere->charac.posEcran.x = 0;
	mainCharactere->charac.posEcran.y = 0;
	mainCharactere->charac.posEcran.h = SIZE_PIXEL * ZOOM_SCREEN * 2; 
	mainCharactere->charac.posEcran.w = SIZE_PIXEL * ZOOM_SCREEN * 2;
*/


	mainCharactere->charac.posEcran.x = WINDOW_WIDTH / 2 - (mainCharactere->charac.posSprite.w ); 
	mainCharactere->charac.posEcran.y = WINDOW_HEIGHT / 2 - (mainCharactere->charac.posSprite.h * 2.5); 
	mainCharactere->charac.posEcran.h = SIZE_PIXEL * 2 * ZOOM_SCREEN;
	mainCharactere->charac.posEcran.w = SIZE_PIXEL * 2 * ZOOM_SCREEN;

}
