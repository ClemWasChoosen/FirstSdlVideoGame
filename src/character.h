#ifndef character_h
#define character_h

#include "zombies.h"
#include "sprite.h"

/**
 * @brief Structure du personnage principal 
 */
struct character_s {
	sprite_t charac;
	int state;
	char direction;
	int life;
};

typedef struct character_s character_t;

int renderPlayer(SDL_Texture* player, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer);

int renderPlayerFlipH(SDL_Texture* player, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizePlayer);

void init_spritePlayer(character_t *mainCharactere);

int renderAnimePlayer(SDL_Texture *player, SDL_Renderer * renderer, SDL_Rect posEcran, SDL_Rect sizePlayer, int *deltaTime, character_t *mainCharactere, sprite_t *allSprite, int sizeMap, zombiesAll_t *allZombies);

void attackOnZombies(SDL_Event evenements, zombiesAll_t *allZombies, int posJoueur);

int renderHeartLife(character_t *mainCharactere, SDL_Texture *heart, SDL_Renderer *renderer);

#endif /* ifndef character_h */
