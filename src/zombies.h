#ifndef zombies_h
#define zombies_h value

#include "sprite.h"

struct zombie_s{
	sprite_t zmb;
	int posZombie;
	int state;
	char direction;
	int display;
	int deltaTime;
};

typedef struct zombie_s zombie_t;

struct zombiesAll_s{
	zombie_t* zombiesTab;
	char* allMapFile;
};

typedef struct zombiesAll_s zombiesAll_t;


int renderZombie(SDL_Texture *zombie, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer);

void init_spriteZombie(zombiesAll_t *zombie, char* mapFromFile, int sizeMap, SDL_Rect posEcranMapHG, int preOccurSlash);

int renderAnimeZombie(SDL_Texture *zombieTextu, SDL_Renderer * renderer, SDL_Rect posEcran, SDL_Rect sizePlayer, zombie_t *zombie);

int renderZombieFlipH(SDL_Texture *player, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer);

void deplacerZombieSansEvenement(int x, int y, zombie_t* zombiesTab);

int getRandomValueInMap(char* map, int sizeMax, int preOccurSlash, int *x, int *y);

#endif /* ifndef zombies_h */
