#ifndef zombies_h
#define zombies_h value

#include "sprite.h"

struct zombie_s{
	sprite_t zmb;
	int posZombie;
	int state;
	char direction;
};

typedef struct zombie_s zombie_t;

struct zombiesAll_s{
	zombie_t* zombiesTab;
	char* allMapFile;
};

typedef struct zombiesAll_s zombiesAll_t;


int renderZombie(SDL_Texture *zombie, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer);

void init_spriteZombie(zombiesAll_t *zombie, int posInit, char* mapFromFile);
#endif /* ifndef zombies_h */
