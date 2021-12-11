/*
* =================================
*	TODO
*	Changer tous les noms en ENEMY
*
* =================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "zombies.h"
#include "constants.h"


int renderZombie(SDL_Texture *zombie, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizeZombie){
	if (SDL_RenderCopy(renderer, zombie, &sizeZombie, &posEcran)) {
		fprintf(stderr, "Erreur SDL_RenderCopy : %s\n", SDL_GetError());		
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int renderZombieFlipH(SDL_Texture *zombie, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer){
	posEcran.x -= posEcran.w - 64;
	if (SDL_RenderCopyEx(renderer, zombie, &sizePlayer, &posEcran, 0, NULL, SDL_FLIP_HORIZONTAL)) {
		fprintf(stderr, "Erreur SDL_RenderCopy : %s\n", SDL_GetError());		
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void deplacerZombieSansEvenement(int x, int y, zombie_t* zombiesTab){
		int i = 0;
		for (i = 0; i < NBZOMBIES; i++) {
			zombiesTab[i].zmb.posEcran.x += x; 
			zombiesTab[i].zmb.posEcran.y += y; 
		}
}

int getRandomValueInMap(char* map, int sizeMax, int preOccurSlash, int *x, int *y){
	int random = rand() % sizeMax;
	if (map[random] != '-' &&  map[random] != '/' && map[random] != '=')
	{
		int count = 0;
		fprintf(stderr, "map : %s\n", map);
		for (int i = 0; i < random; i++)
		{
			if (map[i] == '/')
			{
				count++;
			}
		}
		*x = random % preOccurSlash;
		*y = count;
		
		return random;
	}else{
		return getRandomValueInMap(map, sizeMax, preOccurSlash, x, y);
	}
}

void init_spriteZombie(zombiesAll_t *zombie, int posInit, char* mapFromFile, int sizeMap, SDL_Rect posEcranMapHG, int preOccurSlash){
	int xToadd = 0;
	int yToadd = 0;

	zombie->allMapFile = mapFromFile;
	
    zombie->zombiesTab = malloc(NBZOMBIES * sizeof(*(zombie->zombiesTab)));
    zombie->zombiesTab[0].direction ='d';
	zombie->zombiesTab[0].posZombie = getRandomValueInMap(zombie->allMapFile, sizeMap, preOccurSlash, &xToadd, &yToadd);
	//fprintf(stderr, "random = %d, x = %d, y = %d\n", zombie->zombiesTab[0].posZombie, xToadd, yToadd);

	zombie->zombiesTab[0].zmb.posSprite.x = SIZE_PIXEL * 1.5;
	zombie->zombiesTab[0].zmb.posSprite.y = SIZE_PIXEL * 1.7;
	zombie->zombiesTab[0].zmb.posSprite.h = SIZE_PIXEL * 2;
	zombie->zombiesTab[0].zmb.posSprite.w = SIZE_PIXEL * 2;

	zombie->zombiesTab[0].zmb.posEcran.x = posEcranMapHG.x + SIZE_PIXEL * ZOOM_SCREEN * xToadd;
	//WINDOW_WIDTH / 3 - (zombie->zombiesTab[1].zmb.posSprite.w ); 
	zombie->zombiesTab[0].zmb.posEcran.y = (posEcranMapHG.y - (zombie->zombiesTab[0].zmb.posSprite.h * 1.5)) + SIZE_PIXEL * ZOOM_SCREEN * yToadd;
	//WINDOW_HEIGHT / 3 - (zombie->zombiesTab[1].zmb.posSprite.h * 2.5); 
	zombie->zombiesTab[0].zmb.posEcran.h = SIZE_PIXEL * ZOOM_SCREEN * 2;
	zombie->zombiesTab[0].zmb.posEcran.w = SIZE_PIXEL * ZOOM_SCREEN * 2;

	zombie->zombiesTab[0].state = 1;

}

int renderAnimeZombie(SDL_Texture *zombieTextu, SDL_Renderer * renderer, SDL_Rect posEcran, SDL_Rect sizeZombie, int *deltaTime, zombie_t *zombie){
	//250ms = toutes les 1/4 secondes
	if (zombie->state < 10) {
		sizeZombie.x += 64 * (zombie->state);
		sizeZombie.y = SIZE_PIXEL * 1.7;
		if (zombie->direction == 'd') {
			if (renderZombie(zombieTextu, renderer, posEcran, sizeZombie) == EXIT_FAILURE) 
				return EXIT_FAILURE;		
		}else {
			if (renderZombieFlipH(zombieTextu, renderer, posEcran, sizeZombie) == EXIT_FAILURE) 
				return EXIT_FAILURE;		

		}

		if (*deltaTime >= 125) {	
			zombie->state = zombie->state + 1;
			if (zombie->state >= 4) {
				zombie->state = 0;			
			}
			*deltaTime = 0;
		//	fprintf(stderr, "Retour à 0 en 250ms\n");					
		}
	}
	/*else if (mainCharactere->state >= 10 && mainCharactere->state < 20) {
		sizePlayer.x += 64 * (mainCharactere->state%10);
		sizePlayer.y = SIZE_PIXEL * 1.7 + 64;
		if (mainCharactere->direction == 'd') {
			if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
				return EXIT_FAILURE;		
		}else {
			if (renderPlayerFlipH(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
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
		}else if (mainCharactere->state >= 20) {
			sizePlayer.x += 64 * (mainCharactere->state%10);
			sizePlayer.y = SIZE_PIXEL * 1.7 + 4 * 64;

			if (mainCharactere->direction == 'd') {
								if (renderPlayer(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
					return EXIT_FAILURE;		
			}else {
				if (renderPlayerFlipH(player, renderer, posEcran, sizePlayer) == EXIT_FAILURE) 
					return EXIT_FAILURE;		

		}

		if (*deltaTime >= 125) {	
			mainCharactere->state = mainCharactere->state + 1;
			if (mainCharactere->state > 25) {
				mainCharactere->state = 0;			
			}
			*deltaTime = 0;
		}
	
		}*/
	
	return EXIT_SUCCESS;
}