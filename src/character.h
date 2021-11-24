#ifndef character_h
#define character_h 

#include "sprite.h"

struct character_s {
	sprite_t charac;
	int state;
};

typedef struct character_s character_t;

/*
 * \brief Permet de d'afficher le personnage au centre de la carte
 * \param player Texture contenant les sprites du personnage
 * \param renderer Rendu où ajouter le personnage 
 * \param posEcran position de l'affichage par rapport aux coordonnées de l'écran
 * \param sizePlayer position des sprites dans le fichier bmp
 */
int renderPlayer(SDL_Texture* player, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer);

/**
 * \brief Initialisation des valeurs du mainCharactere
 * \param mainCharactere Personnage principal contenant les positions à initialiser
 */
void init_spritePlayer(character_t *mainCharactere);

int renderAnimePlayer(SDL_Texture *player, SDL_Renderer * renderer, SDL_Rect posEcran, SDL_Rect sizePlayer, int *i, int *state);

#endif /* ifndef character_h */
