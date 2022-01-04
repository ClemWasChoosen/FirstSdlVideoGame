#ifndef zombies_h
#define zombies_h value

#include "sprite.h"

/**
 * @brief Structure des ennemies
 * Contient le sprite des zombies,
 * l'état pour afficher les déplacements, attaques..
 * la direction permet de savoir vers où se dirigent les enemies
 * display permet de savoir si on affiche ou non l'enemie
 * deltaTime pour le timer de chaque zombie
 * timeHit pour le timer pour les attaques
 */
struct zombie_s{
	sprite_t zmb;
	int posZombie;
	int state;
	char direction;
	int display;
	int deltaTime;
	Uint32 timeHit;
};

typedef struct zombie_s zombie_t;

/**
 * @brief Contient tous les ennemies
 * 
 */
struct zombiesAll_s{
	zombie_t* zombiesTab;
	char* allMapFile;
};

typedef struct zombiesAll_s zombiesAll_t;

/**
 * @brief Permet d'afficher les ennemies sur le renderer
 * 
 * @param zombie texture de l'enemie
 * @param renderer renderer où afficher l'enemie
 * @param posEcran position sur l'écran des ennemies
 * @param sizePlayer taille des joueurs sur la texture
 * @return int retourne EXIT_FAILURE si erreur
 */
int renderZombie(SDL_Texture *zombie, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer);

/**
 * @brief Initialise les structures sur les ennemies
 * 
 * @param zombie tous les ennemies à initialiser
 * @param mapFromFile tableau contenant les informations de la map
 * @param sizeMap taille de la map
 * @param posEcranMapHG position Haut gauche de la map pour afficher les ennemies
 * @param preOccurSlash position du premier slash dans le tableau
 */
void init_spriteZombie(zombiesAll_t *zombie, char* mapFromFile, int sizeMap, SDL_Rect posEcranMapHG, int preOccurSlash);

/**
 * @brief Permet de faire le rendu des ennemies sur le renderer avec les animations lors des *      déplacement 
 * 
 * @param zombieTextu texture des ennemies
 * @param renderer renderer où afficher les ennemies
 * @param posEcran position sur l'écran des ennemies
 * @param sizePlayer position sur la texture des ennemies
 * @param zombie un unique zombie à afficher 
 * @return int EXIT_FAILURE si il y a une erreur 
 */
int renderAnimeZombie(SDL_Texture *zombieTextu, SDL_Renderer * renderer, SDL_Rect posEcran, SDL_Rect sizePlayer, zombie_t *zombie);

/**
 * @brief Permet de faire le rendu des ennemies sur le renderer avec les animations lors des *  déplacement (retournement sur l'axe vertical)
 * 
 * @param zombieTextu texture des ennemies
 * @param renderer renderer où afficher les ennemies
 * @param posEcran position sur l'écran des ennemies
 * @param sizePlayer position sur la texture des ennemies
 * @param zombie un unique zombie à afficher 
 * @return int EXIT_FAILURE si il y a une erreur 
 */
int renderZombieFlipH(SDL_Texture *player, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer);

/**
 * @brief Déplace tous les ennemies sans les evenements
 * 
 * @param x position à ajouter au x déjà existant  
 * @param y position à ajouter au y déjà existant 
 * @param zombiesTab tous les ennemies à déplacer 
 */
void deplacerZombieSansEvenement(int x, int y, zombie_t* zombiesTab);

/**
 * @brief récupère un emplacement aléatoire sur la map
 * 
 * @param map tableau contenant la map
 * @param sizeMax taille maximum pour le nombre random
 * @param preOccurSlash première occurence du slash dans le tableau
 * @param x position en x depuis le tableau
 * @param y position en y depuis le tableau
 * @return int EXIT_FAILURE si il y a une erreur 
 */
int getRandomValueInMap(char* map, int sizeMax, int preOccurSlash, int *x, int *y);

/**
 * @brief déplace les ennemies au hasard
 * 
 * @param zombie zombie à déplacer 
 * @param allMap tableau contenant les sprites de la map 
 * @param sizeMap taille de la map 
 * @param preOccurSlash première occurence d'un slash
 */
void randMoveZombies(zombie_t *zombie, char* allMap, int sizeMap, int preOccurSlash);

/**
 * @brief Met un coup au joueur principal si les ennemies sont proches du joueur 
 * 
 * @param life vie du joueur
 * @param zombie unique ennemie pour vérifier la position
 * @param posJoueur position du joueur
 * @param preOccurSlash première occurence d'un slash dans le tableau 
 */
void characterHit(int *life, zombie_t *zombie, int posJoueur, int preOccurSlash);

#endif /* ifndef zombies_h */
