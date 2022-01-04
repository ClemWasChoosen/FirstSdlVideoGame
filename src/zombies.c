#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "zombies.h"
#include "constants.h"
#include "time.h"
#include "map.h"


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

void deplacerZombieSansEvenement(int x, int y, zombie_t* zomabiesTab){
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

void init_spriteZombie(zombiesAll_t *zombie, char* mapFromFile, int sizeMap, SDL_Rect posEcranMapHG, int preOccurSlash){
	int xToadd = 0;
	int yToadd = 0;

	zombie->allMapFile = mapFromFile;

  zombie->zombiesTab = (zombie_t*)malloc(NBZOMBIES * sizeof(zombie_t));

	for (int i = 0; i < NBZOMBIES; i++)
	{
		zombie->zombiesTab[i].direction ='d';
		zombie->zombiesTab[i].posZombie = getRandomValueInMap(zombie->allMapFile, sizeMap, preOccurSlash, &xToadd, &yToadd);

		zombie->zombiesTab[i].zmb.posSprite.x = SIZE_PIXEL * 1.5;
		zombie->zombiesTab[i].zmb.posSprite.y = SIZE_PIXEL * 1.7;
		zombie->zombiesTab[i].zmb.posSprite.h = SIZE_PIXEL * 2;
		zombie->zombiesTab[i].zmb.posSprite.w = SIZE_PIXEL * 2;

		zombie->zombiesTab[i].zmb.posEcran.x = posEcranMapHG.x + SIZE_PIXEL * ZOOM_SCREEN * xToadd;
		zombie->zombiesTab[i].zmb.posEcran.y = (posEcranMapHG.y - (zombie->zombiesTab[i].zmb.posSprite.h * 1.5)) + SIZE_PIXEL * ZOOM_SCREEN * yToadd;
		zombie->zombiesTab[i].zmb.posEcran.h = SIZE_PIXEL * ZOOM_SCREEN * 2;
		zombie->zombiesTab[i].zmb.posEcran.w = SIZE_PIXEL * ZOOM_SCREEN * 2;

		zombie->zombiesTab[i].display = 1;
		zombie->zombiesTab[i].state = 1;

		zombie->zombiesTab[i].deltaTime = 0;
		zombie->zombiesTab[i].timeHit = 0;
	}
}

void randMoveZombies(zombie_t *zombie, char* allMap, int sizeMap, int preOccurSlash){
	if (zombie->state < 10) {
		int random = rand() % 1000;
		switch (random) {
			case 1:
				if (preOccurSlash != 0 && allMap[zombie->posZombie - preOccurSlash] != '/' && allMap[zombie->posZombie - preOccurSlash] != '=' && zombie->posZombie - preOccurSlash >= 0 && allMap[zombie->posZombie - preOccurSlash] != '-') {
					zombie->direction = 'z';
					zombie->state = 10;
					zombie->posZombie -= preOccurSlash;
				}
				break;
			case 2:
				if (allMap[zombie->posZombie - 1] != '-' && allMap[zombie->posZombie - 1] != '=' && allMap[zombie->posZombie - 1 ] != '/' && zombie->posZombie - 1 >= 0) {
					zombie->direction = 'q';
					zombie->state = 10;
					zombie->posZombie--;
				}

				break;
			case 3:
				if (preOccurSlash != 0 && allMap[zombie->posZombie + preOccurSlash] != '=' && allMap[zombie->posZombie + preOccurSlash] != '-' && zombie->posZombie + preOccurSlash <= sizeMap && allMap[zombie->posZombie + preOccurSlash] != '/') {
					zombie->direction = 's';
					zombie->state = 10;
					zombie->posZombie += preOccurSlash;
				}

				break;
			case 4:
				if (allMap[zombie->posZombie + 1] != '-' && allMap[zombie->posZombie + 1] != '/' && allMap[zombie->posZombie + 1] != '=' && zombie->posZombie + 1 <= sizeMap) {
					zombie->direction = 'd';
					zombie->state = 10;
					zombie->posZombie++;
				}

				break;
			default:
				zombie->state = 0;
				break;
		}
	}
}

void characterHit(int *life, zombie_t *zombie, int posJoueur, int preOccurSlash){
	if (zombie->display == 1) {
		if (zombie->timeHit != 0) {
			Uint32 diff = SDL_GetTicks() - zombie->timeHit;
			//1000 ms == 1s
			if (diff >= 1000 && (zombie->posZombie - preOccurSlash == posJoueur || zombie->posZombie - 1 == posJoueur || zombie->posZombie + preOccurSlash == posJoueur || zombie->posZombie + 1 == posJoueur)) {
				zombie->timeHit = 0;
				*life = *life - 1;
			}
		}else{

			if (zombie->posZombie == posJoueur) {
				zombie->timeHit = SDL_GetTicks();
			}

			switch (zombie->direction) {
			case 'z':
					if (zombie->posZombie - preOccurSlash == posJoueur) {
						zombie->timeHit = SDL_GetTicks();
					}

				break;
			case 'q':
				if (zombie->posZombie - 1 == posJoueur) {
					zombie->timeHit = SDL_GetTicks();
				}
				break;
			case 's':
				if (zombie->posZombie + preOccurSlash == posJoueur) {
					zombie->timeHit = SDL_GetTicks();
				}
				break;
			case 'd':
				if (zombie->posZombie + 1 == posJoueur) {
					zombie->timeHit = SDL_GetTicks();
				}
				break;
			default:

			break;
			}
		}
	}

	if ((SDL_GetTicks() - zombie->timeHit) >= 2000) {
		zombie->timeHit = 0;
	}
}

int renderAnimeZombie(SDL_Texture *zombieTextu, SDL_Renderer * renderer, SDL_Rect posEcran, SDL_Rect sizeZombie, zombie_t *zombie){
	//250ms = toutes les 1/4 secondes
		if (zombie->state < 10) {
			if (zombie->display == 1) {
				sizeZombie.x += 64 * (zombie->state);
				sizeZombie.y = SIZE_PIXEL * 1.7;
					if (zombie->direction == 'd') {
						if (renderZombie(zombieTextu, renderer, posEcran, sizeZombie) == EXIT_FAILURE)
							return EXIT_FAILURE;
					}else {
						if (renderZombieFlipH(zombieTextu, renderer, posEcran, sizeZombie) == EXIT_FAILURE)
							return EXIT_FAILURE;
					}


				if (zombie->deltaTime >= 150) {
						zombie->state += 1;
						if (zombie->state >= 4) {
							zombie->state = 0;
						}
					zombie->deltaTime = 0;
				}
			}
		}else if(zombie->state >= 10 && zombie->state < 20) {
			if (zombie->display == 1) {
				sizeZombie.x += 64 * (zombie->state%10);
				sizeZombie.y = SIZE_PIXEL * 1.7 + 64;
				if (zombie->direction == 'd') {
					if (renderPlayer(zombieTextu, renderer, posEcran, sizeZombie) == EXIT_FAILURE)
						return EXIT_FAILURE;
				}else {
					if (renderPlayerFlipH(zombieTextu, renderer, posEcran, sizeZombie) == EXIT_FAILURE)
						return EXIT_FAILURE;

				}

				//Ajouter le déplacement des squelettes ici
				if (zombie->deltaTime >= 1000/15) {
					switch (zombie->direction) {
					case 'z':
						zombie->zmb.posEcran.y -= (SIZE_PIXEL * ZOOM_SCREEN)/4;
						break;
					case 'q':
						zombie->zmb.posEcran.x -= (SIZE_PIXEL * ZOOM_SCREEN)/4;
						break;
					case 's':
						zombie->zmb.posEcran.y += (SIZE_PIXEL * ZOOM_SCREEN)/4;
						break;
					case 'd':
						zombie->zmb.posEcran.x += (SIZE_PIXEL * ZOOM_SCREEN)/4;
						break;
					default:

					break;
					}

					zombie->state += 1;
					if (zombie->state >= 14) {
						zombie->state = 0;
					}
					zombie->deltaTime = 0;
				}
			}
			sizeZombie.y = SIZE_PIXEL * 1.7 + 6 * 64;
			if (zombie->direction == 'd') {
				if (renderZombie(zombieTextu, renderer, posEcran, sizeZombie) == EXIT_FAILURE)
					return EXIT_FAILURE;
			}else {
				if (renderZombieFlipH(zombieTextu, renderer, posEcran, sizeZombie) == EXIT_FAILURE)
					return EXIT_FAILURE;

			}

			if (zombie->deltaTime >= 150) {
					zombie->state += 1;
					if (zombie->state >= 77) {
						zombie->state = 0;
						zombie->display = 0;
					}
				zombie->deltaTime = 0;
			}
		}

	return EXIT_SUCCESS;
}
