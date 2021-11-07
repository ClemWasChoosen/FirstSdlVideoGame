#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

struct sprite_s {
	SDL_Rect posSprite;
	SDL_Rect posEcran;
};

typedef struct sprite_s sprite_t;

#endif
