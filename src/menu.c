#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include "menu.h"

int renderGameOver(SDL_Texture *gameOver, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizeGameOver){
    if (SDL_RenderCopy(renderer, gameOver, &sizeGameOver, &posEcran)) {
		fprintf(stderr, "Erreur SDL_RenderCopy : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}