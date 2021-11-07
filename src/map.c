#include "map.h"
#include "sprite.h"
#include "constants.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>


/*int loadImage(const char path[], SDL_Renderer *renderer, SDL_Texture *texture){
    SDL_Surface *tmp = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
		return EXIT_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}*/


SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(tmp == NULL)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(texture == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

int renderMap(SDL_Texture *map, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizeMap){
	if (SDL_RenderCopy(renderer, map, &sizeMap, &posEcran)) {
		fprintf(stderr, "Erreur SDL_RenderCopy : %s\n", SDL_GetError());		
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


void getSpriteMap(int value, SDL_Rect *sizeMap){
	switch (value) {
		case 1:
		sizeMap->x = 32;
		sizeMap->y = 32;
		sizeMap->w = 80;
		sizeMap->h = 93;
			break;

		case 2:
		sizeMap->x = 116;
		sizeMap->y = 32;
		sizeMap->w = 50;
		sizeMap->h = 61;
			break;

		case 16:
		sizeMap->x = 140;
		sizeMap->y = 134;
		sizeMap->h = 21;
		sizeMap->w = 17;
			break;
	}
}


void deplacerCarte(const int deplacement, carte_t *carteJeu, SDL_Event evenements){
	if (carteJeu != NULL) {
		switch (evenements.type) {
			case SDL_KEYDOWN:
				switch (evenements.key.keysym.sym) {
						case SDLK_d:
							for (int i = 0; i < NUMBER_TILES; i++) {
								carteJeu->allSprite[i].posEcran.x = carteJeu->allSprite[i].posEcran.x + deplacement;	
							}
							break;
						case SDLK_q:
							for (int i = 0; i < NUMBER_TILES; i++) {
								carteJeu->allSprite[i].posEcran.x = carteJeu->allSprite[i].posEcran.x - deplacement;	
							}
//							position->x = position->x - deplacement;	
							break;


						case SDLK_s:
							for (int i = 0; i < NUMBER_TILES; i++) {
								carteJeu->allSprite[i].posEcran.y = carteJeu->allSprite[i].posEcran.y + deplacement;	
							}
							break;
						case SDLK_z:
							for (int i = 0; i < NUMBER_TILES; i++) {
								carteJeu->allSprite[i].posEcran.y = carteJeu->allSprite[i].posEcran.y - deplacement;	
							}
//							position->x = position->x - deplacement;	
							break;

				}	
				break;
		}
	}
}

/*void init_spriteMap(sprite_t *ourMap, sprite_t *ourMap2){
	getSpriteMap(1, &ourMap->posSprite);	

	ourMap->posEcran.x = 20;
	ourMap->posEcran.y = 50;
	ourMap->posEcran.w = 200;
	ourMap->posEcran.h = 200;

	getSpriteMap(2, &ourMap2->posSprite);

	ourMap2->posEcran.x = 250;
	ourMap2->posEcran.y = 260;
	ourMap2->posEcran.w = 100;
	ourMap2->posEcran.h = 100;


}*/

void init_spriteMap(carte_t *carteJeu){

	carteJeu->allSprite = malloc(NUMBER_TILES * sizeof(*carteJeu->allSprite)); 
	getSpriteMap(1, &carteJeu->allSprite[0].posSprite);	

	carteJeu->allSprite[0].posEcran.x = WINDOW_HEIGHT / 2 - carteJeu->allSprite[0].posSprite.h / 2;
	carteJeu->allSprite[0].posEcran.y = WINDOW_WIDTH / 2 - carteJeu->allSprite[0].posSprite.w / 2;
	carteJeu->allSprite[0].posEcran.w = carteJeu->allSprite[0].posSprite.w * 4;
	carteJeu->allSprite[0].posEcran.h = carteJeu->allSprite[0].posSprite.h * 4;

	getSpriteMap(2, &carteJeu->allSprite[1].posSprite);	

	carteJeu->allSprite[1].posEcran.x = 20;
	carteJeu->allSprite[1].posEcran.y = 50;
	carteJeu->allSprite[1].posEcran.w = 100;
	carteJeu->allSprite[1].posEcran.h = 100;

	getSpriteMap(16, &carteJeu->allSprite[2].posSprite);	

	carteJeu->allSprite[2].posEcran.x = 100;
	carteJeu->allSprite[2].posEcran.y = 100;
	carteJeu->allSprite[2].posEcran.w = carteJeu->allSprite[2].posSprite.w * 4;
	carteJeu->allSprite[2].posEcran.h = carteJeu->allSprite[2].posSprite.h * 4;

/*	ourMap->posEcran.x = 20;
	ourMap->posEcran.y = 50;
	ourMap->posEcran.w = 200;
	ourMap->posEcran.h = 200;

	getSpriteMap(2, &ourMap2->posSprite);

	ourMap2->posEcran.x = 250;
	ourMap2->posEcran.y = 260;
	ourMap2->posEcran.w = 100;
	ourMap2->posEcran.h = 100;*/


}
