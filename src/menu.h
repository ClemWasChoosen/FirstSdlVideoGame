#ifndef MENU_H
#define MENU_H

#include "sprite.h"


int renderGameOver(SDL_Texture *gameOver, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizeGameOver);

int renderPause(SDL_Texture *pause, SDL_Renderer *renderer);

#endif /* ifndef MENU_H */