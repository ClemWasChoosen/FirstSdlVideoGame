/*
* =================================
*	TODO
*	Changer tous les noms en ENEMY
*	- sauvegarde
*   - gestion d'erreurs fichiers entrée
*   - souris
* =================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "zombies.h"
#include "constants.h"
#include "time.h"


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
		//fprintf(stderr, "map : %s\n", map);
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

  zombie->zombiesTab = malloc(NBZOMBIES * sizeof(zombie_t));

	for (int i = 0; i < NBZOMBIES; i++)
	{
		zombie->zombiesTab[i].direction ='d';
		zombie->zombiesTab[i].posZombie = getRandomValueInMap(zombie->allMapFile, sizeMap, preOccurSlash, &xToadd, &yToadd);
		//fprintf(stderr, "random = %d, x = %d, y = %d\n", zombie->zombiesTab[0].posZombie, xToadd, yToadd);

		zombie->zombiesTab[i].zmb.posSprite.x = SIZE_PIXEL * 1.5;
		zombie->zombiesTab[i].zmb.posSprite.y = SIZE_PIXEL * 1.7;
		zombie->zombiesTab[i].zmb.posSprite.h = SIZE_PIXEL * 2;
		zombie->zombiesTab[i].zmb.posSprite.w = SIZE_PIXEL * 2;

		zombie->zombiesTab[i].zmb.posEcran.x = posEcranMapHG.x + SIZE_PIXEL * ZOOM_SCREEN * xToadd;
		//WINDOW_WIDTH / 3 - (zombie->zombiesTab[1].zmb.posSprite.w );
		zombie->zombiesTab[i].zmb.posEcran.y = (posEcranMapHG.y - (zombie->zombiesTab[i].zmb.posSprite.h * 1.5)) + SIZE_PIXEL * ZOOM_SCREEN * yToadd;
		//WINDOW_HEIGHT / 3 - (zombie->zombiesTab[1].zmb.posSprite.h * 2.5);
		zombie->zombiesTab[i].zmb.posEcran.h = SIZE_PIXEL * ZOOM_SCREEN * 2;
		zombie->zombiesTab[i].zmb.posEcran.w = SIZE_PIXEL * ZOOM_SCREEN * 2;

		zombie->zombiesTab[i].display = 1;
		zombie->zombiesTab[i].state = 1;
	}


}

int renderAnimeZombie(SDL_Texture *zombieTextu, SDL_Renderer * renderer, SDL_Rect posEcran, SDL_Rect sizeZombie, int *deltaTime, zombie_t *zombie){
	//250ms = toutes les 1/4 secondes

	if (zombie->state < 10) {
		sizeZombie.x += 64 * (zombie->state);
		sizeZombie.y = SIZE_PIXEL * 1.7;
		if (zombie->display == 1) {
			if (zombie->direction == 'd') {
				if (renderZombie(zombieTextu, renderer, posEcran, sizeZombie) == EXIT_FAILURE)
					return EXIT_FAILURE;
			}else {
				if (renderZombieFlipH(zombieTextu, renderer, posEcran, sizeZombie) == EXIT_FAILURE)
					return EXIT_FAILURE;

			}
		}

		if (*deltaTime >= 125) {
			for (size_t i = 0; i < NBZOMBIES; i++) {
				zombie[i].state += 1;
				if (zombie[i].state >= 4) {
					zombie[i].state = 0;
				}
			}
			*deltaTime = 0;
		}
	}
	return EXIT_SUCCESS;
}
