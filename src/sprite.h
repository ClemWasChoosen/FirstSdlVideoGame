#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

/*
 * Structure contenant les positons sur l'écran et depuis le fichier map (.bmp)
 *
 */
struct sprite_s {
	SDL_Rect posSprite;
	SDL_Rect posEcran;
};

typedef struct sprite_s sprite_t;

/**
 * \brief Permet d'inititaliser + charger une image
 * \param path[] chemin courant de la ressource
 * \param renderer rendu à afficher 
 */
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);


#endif
