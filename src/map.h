#ifndef map_h 
#define map_h 

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "sprite.h"

struct carte_s {
	sprite_t* allSprite;
	char* allMap;
	int sizeMap;
	int posJoueur;
};


typedef struct carte_s carte_t;

/**
 * \brief Permet d'inititaliser + charger une image
 * \param path[] chemin courant de la ressource
 * \param renderer rendu à afficher 
 */
 SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);

 /*
  * \brief Permet d'ajouter la map au rendu 
  * \param map texture de la carte a ajouter au rendu
  * \param renderer rendu sur lequel ajouter la map
  * \param posEcran position sur l'ecran a afficher
  * \param sizeMap taille de la partie de la carte a ajouter
  */
int renderMap(SDL_Texture* map, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizeMap);


/*
 * \brief Permet de retourner la position d'une partie de la carte
 * \param value numéro de la carte a ajouter
 * \param sizeMap retourne la position de la carte
 */
void getSpriteMap(char value, SDL_Rect *sizeMap);

void deplacerCarte(const int deplacement, carte_t *carteJeu, SDL_Event evenements, int preOccurSlash);

//void init_spriteMap(sprite_t *ourMap, sprite_t *ourMap2);

void init_spriteMap(carte_t *carteJeu);

void placerCarteCentre(carte_t *carteJeu);

void setPosValue(int i, int x, int y, carte_t *carteJeu);

#endif 
