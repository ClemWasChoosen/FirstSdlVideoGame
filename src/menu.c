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

int renderPause(SDL_Texture *pause, SDL_Renderer *renderer){
  sprite_t sizePauseBtn;
  sizePauseBtn.posSprite.x = 1830;
  sizePauseBtn.posSprite.y = 0;
  sizePauseBtn.posSprite.h = 200;
  sizePauseBtn.posSprite.w = 200;

  sizePauseBtn.posEcran.x = 5;
  sizePauseBtn.posEcran.y = 5;
  sizePauseBtn.posEcran.h = 150;
  sizePauseBtn.posEcran.w = 150;

  if (SDL_RenderCopy(renderer, pause, &sizePauseBtn.posSprite, &sizePauseBtn.posEcran)) {
  fprintf(stderr, "Erreur SDL_RenderCopy : %s\n", SDL_GetError());
  return EXIT_FAILURE;
}
return EXIT_SUCCESS;
}
