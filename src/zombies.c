#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "zombies.h"
#include "constants.h"


int renderZombie(SDL_Texture *zombie, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer){
	if (SDL_RenderCopy(renderer, zombie, &sizePlayer, &posEcran)) {
		fprintf(stderr, "Erreur SDL_RenderCopy : %s\n", SDL_GetError());		
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void init_spriteZombie(zombiesAll_t *zombie, int posInit, char* mapFrom){
	
	
    zombie->zombiesTab = malloc(NBZOMBIES * sizeof(*zombie->zombiesTab));
    zombie->zombiesTab[1].direction ='d';
    zombie->zombiesTab[1].posZombie = posInit;

    zombie->allMapFile = mapFrom;


    //zombie->zombiesTab[1].zmb.posSprite.x = 

	zombie->zombiesTab[1].zmb.posSprite.x = 0;
	zombie->zombiesTab[1].zmb.posSprite.y = 0;
	zombie->zombiesTab[1].zmb.posSprite.h = SIZE_PIXEL * 2;
	zombie->zombiesTab[1].zmb.posSprite.w = SIZE_PIXEL * 2;
	
	/*
	mainCharactere->charac.posEcran.x = 0;
	mainCharactere->charac.posEcran.y = 0;
	mainCharactere->charac.posEcran.h = SIZE_PIXEL * ZOOM_SCREEN * 2; 
	mainCharactere->charac.posEcran.w = SIZE_PIXEL * ZOOM_SCREEN * 2;
*/

	zombie->zombiesTab[1].zmb.posEcran.x = WINDOW_WIDTH / 2 - (zombie->zombiesTab[1].zmb.posSprite.w ); 
	zombie->zombiesTab[1].zmb.posEcran.y = WINDOW_HEIGHT / 2 - (zombie->zombiesTab[1].zmb.posSprite.h * 2.5); 
	zombie->zombiesTab[1].zmb.posEcran.h = SIZE_PIXEL * ZOOM_SCREEN * 1.5;
	zombie->zombiesTab[1].zmb.posEcran.w = SIZE_PIXEL * ZOOM_SCREEN * 1.5;

	zombie->zombiesTab[1].state = 1;

}