#ifndef map_h
#define map_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

#include "character.h"
#include "sprite.h"

struct carte_s {
	sprite_t* allSprite;
	char* allMap;
	int sizeMap;
	int posJoueur;
};


typedef struct carte_s carte_t;

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

/*
 * \brief Deplace la carte en fonction de la touche enfoncée
 * \param deplacement Constante ajouté a la postition x et y pour déplacer la carte
 * \param *carteJeu Plateau de jeu
 * \param evenements Variable contenant les touches qu'a enfoncé le joueur
 * \preOccurSlash Premiere occurence de Slash dans le tableau pour aller de haut en bas
 */
void deplacerCarte(const int deplacement, carte_t *carteJeu, SDL_Event evenements, int preOccurSlash, character_t *mainCharactere);

/*
 * \brief Fonction d'initialisation de la carte de Jeu
 * \param *carteJeu Carte de Jeu à initialiser
 * \param Pointeur sur le fichier permettant d'initialiser le Jeu (Simplement déclaré à NULL)
 */
void init_spriteMap(carte_t *carteJeu, FILE** fileToGet);

/*
 * \brief Place le plateau de jeu au centre de l'écran, sur la position du joueur
 * \param *carteJeu Plateau de jeu à déplacer
 */
void placerCarteCentre(carte_t *carteJeu);

/*
 * \brief Fixe la postition de la tiles dans la variable carteJeu->allSprite.posEcran
 * \param i Index du tile à changer
 * \param x Position en x
 * \param y Position en y (y * SIZE_PIXEL * ZOOM_SCREEN)
 */
void setPosValue(int i, int x, int y, carte_t *carteJeu);

/*
 * \brief Ajoute le tableau preprésentant la map dans un tableau dans carteJeu
 * \param *carteJeu Carte recevant le tableau
 * \param **fileToGet Fichier source à lire
 */
void fileInArray(FILE** fileToGet, carte_t* carteJeu);

/*
 * \brief Ouverture du fichier source depuis son chemin courant
 * \param path[] Chemin du fichier source (./fichiersCarte/[level-].txt)
 */
FILE* readFile(const char path[]);

void deplacerCarteSansEvenement(int x, int y, sprite_t *allSprite, int sizeMap);

#endif
