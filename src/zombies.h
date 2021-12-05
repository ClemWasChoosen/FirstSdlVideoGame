#ifndef zombies_h
#define zombies_h value

#include "sprite.h"

struct zombies_s{
	sprite_t charac;
	int state;
	char direction;
};

typedef struct zombies_s zombies_t;

#endif /* ifndef zombies_h */
