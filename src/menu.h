#ifndef MENU_H
#define MENU_H

#include "sprite.h"

/**
 * \brief Déplace la carte sans évenement spécifique
 * \param int x position x à ajouter au x actuel
 * \param int y position x à ajouter au x actuel
 * \param allSprite tous les sprites de la map
 * \param sizeMap taille de la carte
 */
int renderGameOver(SDL_Texture *gameOver, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizeGameOver);

/**
 * \brief affiche le logo pause sur le renderer
 * \param SDL_Texture *pause texture du logo pause
 * \param SDL_Renderer *renderer renderer où afficher le logo
 */
int renderPause(SDL_Texture *pause, SDL_Renderer *renderer);

#endif /* ifndef MENU_H */
