#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "character.h"
#include "constants.h"
#include "map.h"
#include "sprite.h"

int renderPlayer(SDL_Texture *player, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer){
	if (SDL_RenderCopy(renderer, player, &sizePlayer, &posEcran)) {
		fprintf(stderr, "Erreur SDL_RenderCopy : %s\n", SDL_GetError());		
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int renderAnimePlayer(SDL_Texture *player, SDL_Renderer * renderer, SDL_Rect posEcran, SDL_Rect sizePlayer, int *deltaTime, character_t *mainCharactere, sprite_t *allSprite, int sizeMap){
	//fprintf(stderr, "%d ", *statePlayer);
	//250ms = toutes les 1/4 secondes
	if (mainCharactere->state < 10) {
		
/*		sizePlayer.x += 64 * (mainCharactere->state);
		sizePlayer.y = SIZE_PIXEL * 1.7;
		if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
			return EXIT_FAILURE;	*/	


		if (mainCharactere->direction == 'd') {
			sizePlayer.x += 64 * (mainCharactere->state);
			sizePlayer.y = SIZE_PIXEL * 1.7;
			if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
				return EXIT_FAILURE;		
		}else {
			sizePlayer.x += 512 - 64 * (mainCharactere->state + 1);
			sizePlayer.y = SIZE_PIXEL * 1.7;
			if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
				return EXIT_FAILURE;		

		}
		fprintf(stderr, "%d\n", sizePlayer.x);

		if (*deltaTime >= 125) {	
			mainCharactere->state = mainCharactere->state + 1;
			if (mainCharactere->state >= 4) {
				mainCharactere->state = 0;			
			}
			*deltaTime = 0;
		//	fprintf(stderr, "Retour à 0 en 250ms\n");					
		}
	}else if (mainCharactere->state >= 10) {
		
		if (mainCharactere->direction == 'd') {
			sizePlayer.x += 64 * (mainCharactere->state%10);
			sizePlayer.y = SIZE_PIXEL * 1.7 + 64;
			if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
				return EXIT_FAILURE;		
		}else {
			sizePlayer.x += 512 - 64 * (mainCharactere->state%10);
			sizePlayer.y = SIZE_PIXEL * 1.7 + 64;
			if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
				return EXIT_FAILURE;		

		}
		
		if (*deltaTime >= 1000/15) {	
			switch (mainCharactere->direction) {
			case 'z':
				deplacerCarteSansEvenement(0, (SIZE_PIXEL * ZOOM_SCREEN)/4, allSprite, sizeMap);
				break;		
			case 'q':
				
				deplacerCarteSansEvenement((SIZE_PIXEL * ZOOM_SCREEN)/4, 0, allSprite, sizeMap);
				break;
			case 's':
				
				deplacerCarteSansEvenement(0, -(SIZE_PIXEL * ZOOM_SCREEN)/4, allSprite, sizeMap);
				break;
			case 'd':
				deplacerCarteSansEvenement(-(SIZE_PIXEL * ZOOM_SCREEN)/4, 0, allSprite, sizeMap);
				break;
			default:
				
			break;
		}

			mainCharactere->state += 1;
			if (mainCharactere->state >= 14) {
				mainCharactere->state = 0;			
			}
			*deltaTime = 0;
		//	fprintf(stderr, "Retour à 0 en 250ms\n");					
		}
	}
	
/*	switch (*statePlayer) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			sizePlayer.x += 64 * (*statePlayer);
			sizePlayer.y = SIZE_PIXEL * 1.7;
			if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
				return EXIT_FAILURE;		

			if (*i%5 == 0) {
				*statePlayer = *statePlayer+1;
				if (*i == 25) {	
					*i = 0;
					*statePlayer = 0;
				}
			}	
			
			break;

		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		//case 15:

			sizePlayer.x += 64 * (*statePlayer%10);
			sizePlayer.y = SIZE_PIXEL * 1.7 + 64;
	
			if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
				return EXIT_FAILURE;		

			*statePlayer = *statePlayer+1;	

			if (*statePlayer == 14) {
				*statePlayer = 1;	
			}

		default:
		*statePlayer = 0;	
			break;
	}

	*/
	/*if (*statePlayer <= 5) {
		
		sizePlayer.x += 64 * (*statePlayer);
		sizePlayer.y = SIZE_PIXEL * 1.7;
		if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
			return EXIT_FAILURE;		

		if (*i%5 == 0) {
			*statePlayer = *statePlayer+1;
			if (*i == 25) {	
				*i = 0;
				*statePlayer = 1;
			}
		}	
	}

	if (*statePlayer >= 10 && *statePlayer <= 13) {
		sizePlayer.x += 64 * (*statePlayer%10);
		sizePlayer.y += 64;
	
		if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
			return EXIT_FAILURE;		

		*statePlayer = *statePlayer+1;	

		if (*statePlayer == 14) {
			*statePlayer = 1;	
		}
	}
*/
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
	
	mainCharactere->direction = 'd';

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

	mainCharactere->state = 1;

}
