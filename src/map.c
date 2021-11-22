#include "map.h"
#include "sprite.h"
#include "constants.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*int loadImage(const char path[], SDL_Renderer *renderer, SDL_Texture *texture){
    SDL_Surface *tmp = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
		return EXIT_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}*/


SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(tmp == NULL)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(texture == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

int renderMap(SDL_Texture *map, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizeMap){
	if (SDL_RenderCopy(renderer, map, &sizeMap, &posEcran)) {
		fprintf(stderr, "Erreur SDL_RenderCopy : %s\n", SDL_GetError());		
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int renderPlayer(SDL_Texture *player, SDL_Renderer *renderer, SDL_Rect posEcran, SDL_Rect sizeMap){
	if (SDL_RenderCopy(renderer, player, &sizeMap, &posEcran)) {
		fprintf(stderr, "Erreur SDL_RenderCopy : %s\n", SDL_GetError());		
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


void getSpriteMap(char value, SDL_Rect *sizeMap){
	switch (value) {

		//Interieur + caillou
		case '0':
		sizeMap->x = SIZE_PIXEL * 5;
		sizeMap->y = SIZE_PIXEL * 3;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			break;


		//Bordure haut  
		case '1':
		sizeMap->x = SIZE_PIXEL * 3;
		sizeMap->y = SIZE_PIXEL * 2;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			break;

		//Bordure gauche
		case '2':
		sizeMap->x = SIZE_PIXEL * 2;
		sizeMap->y = SIZE_PIXEL * 3;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			
			break;

		//Bordure droite
		case '3':
		sizeMap->x = SIZE_PIXEL * 6;
		sizeMap->y = SIZE_PIXEL * 3;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			
			break;

		//Interieur de la carte
		case '4':
		sizeMap->x = SIZE_PIXEL * 3;
		sizeMap->y = SIZE_PIXEL * 3;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			
			break;

		//Coin en haut à gauche
		case '5':
		sizeMap->x = SIZE_PIXEL * 2;
		sizeMap->y = SIZE_PIXEL * 2;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			
			break;

		//Coin en haut à droite
		case '6':
		sizeMap->x = SIZE_PIXEL * 6;
		sizeMap->y = SIZE_PIXEL * 2;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			
			break;

		//Coin bas gauche
		case '7':
		sizeMap->x = SIZE_PIXEL * 2;
		sizeMap->y = SIZE_PIXEL * 6;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			
			break;

		//Coin bas droit
		case '8':
		sizeMap->x = SIZE_PIXEL * 6;
		sizeMap->y = SIZE_PIXEL * 6;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			
			break;

		//Bordure bas
		case '9':
		sizeMap->x = SIZE_PIXEL * 3;
		sizeMap->y = SIZE_PIXEL * 6;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			
			break;

		//Partie gauche du pont 
		case 'p':
		sizeMap->x = SIZE_PIXEL * 8 + 12;
		sizeMap->y = SIZE_PIXEL * 8 + 4;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			
			break;

		//Partie gauche du pont 
		case 'o':
		sizeMap->x = SIZE_PIXEL * 8 + 16;
		sizeMap->y = SIZE_PIXEL * 8 + 4;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			
			break;

		//Bordure hors map deco
		case '=':
		sizeMap->x = SIZE_PIXEL * 3;
		sizeMap->y = SIZE_PIXEL * 7;
		sizeMap->w = SIZE_PIXEL;
		sizeMap->h = SIZE_PIXEL;		
			
			break;

	}
}


void deplacerCarte(const int deplacement, carte_t *carteJeu, SDL_Event evenements, int preOccurSlash){
	if (carteJeu != NULL) {
		switch (evenements.type) {
			case SDL_KEYDOWN:
				switch (evenements.key.keysym.sym) {
						case SDLK_d:
							if (carteJeu->allMap[carteJeu->posJoueur + 1] != '-' && carteJeu->allMap[carteJeu->posJoueur + 1] != '/' && carteJeu->allMap[carteJeu->posJoueur + 1] != '=' && carteJeu->posJoueur + 1 <= carteJeu->sizeMap) {
								for (int i = 0; i < carteJeu->sizeMap; i++) {
									carteJeu->allSprite[i].posEcran.x = carteJeu->allSprite[i].posEcran.x - deplacement;	
								}
								carteJeu->posJoueur = carteJeu->posJoueur + 1;
							}
							break;
						case SDLK_q:
							if (carteJeu->allMap[carteJeu->posJoueur - 1] != '-' && carteJeu->allMap[carteJeu->posJoueur - 1] != '=' && carteJeu->allMap[carteJeu->posJoueur - 1 ] != '/' && carteJeu->posJoueur - 1 >= 0) {
								for (int i = 0; i < carteJeu->sizeMap; i++) {
									carteJeu->allSprite[i].posEcran.x = carteJeu->allSprite[i].posEcran.x + deplacement;	
								}
								carteJeu->posJoueur = carteJeu->posJoueur - 1;
							}
							break;


						case SDLK_s:
							if (preOccurSlash != 0 && carteJeu->allMap[carteJeu->posJoueur + preOccurSlash] != '=' && carteJeu->allMap[carteJeu->posJoueur + preOccurSlash] != '-' && carteJeu->posJoueur + preOccurSlash <= carteJeu->sizeMap && carteJeu->allMap[carteJeu->posJoueur + preOccurSlash] != '/') {
								for (int i = 0; i < carteJeu->sizeMap; i++) {
									carteJeu->allSprite[i].posEcran.y = carteJeu->allSprite[i].posEcran.y - deplacement;	
								}
								carteJeu->posJoueur = carteJeu->posJoueur + preOccurSlash;
							}
							break;
						case SDLK_z:
							if (preOccurSlash != 0 && carteJeu->allMap[carteJeu->posJoueur - preOccurSlash] != '/' && carteJeu->allMap[carteJeu->posJoueur - preOccurSlash] != '=' && carteJeu->posJoueur - preOccurSlash >= 0 && carteJeu->allMap[carteJeu->posJoueur - preOccurSlash] != '-') {
								for (int i = 0; i < carteJeu->sizeMap; i++) {
									carteJeu->allSprite[i].posEcran.y = carteJeu->allSprite[i].posEcran.y + deplacement;	
								}
								carteJeu->posJoueur = carteJeu->posJoueur - preOccurSlash;
							}
							break;

				}	
				break;

		}

	}
	
}

void placerCarteCentre(carte_t *carteJeu){
	if (carteJeu->allSprite != NULL) {
		for (int i = 0; i < carteJeu->sizeMap; i++) {
			carteJeu->allSprite[i].posEcran.x = ((carteJeu->allSprite[i].posEcran.x + WINDOW_WIDTH / 2) - ZOOM_SCREEN * SIZE_PIXEL / 2) ;	
			carteJeu->allSprite[i].posEcran.y = ((carteJeu->allSprite[i].posEcran.y + WINDOW_HEIGHT / 2) - ZOOM_SCREEN * SIZE_PIXEL / 2);	
		}	
	}	
}


FILE* readFile(const char path[]){
	FILE* fileToOpen = NULL;
	fileToOpen = fopen(path, "r"); 
	return fileToOpen;
}

void fileInArray(FILE** fileToGet, carte_t* carteJeu){
	//On ne fait rien si le fichier est null
	if (fileToGet == NULL) {
			fprintf(stderr, "le Fichier est null\n");			
			return;
	}

	fseek(*fileToGet, 0L, SEEK_SET);

	//Initialisation de la taille de la carte en parcourant le fichier 
	//(retour à la ligne et espace non ajouté)
	int c;
	while((c = fgetc(*fileToGet)) != EOF) {
		if (c != ' ' && c != '\n') {
			carteJeu->sizeMap += 1;
		}
	}

	//Curseur au début du fichier
	fseek(*fileToGet, 0L, SEEK_SET);

	carteJeu->allMap = malloc(carteJeu->sizeMap * sizeof(*carteJeu->allMap));

	//Ajout des caractères du fichier dans allMap après allocation mémoire 
	int i = 0;
	while((c = fgetc(*fileToGet)) != EOF) {
		if (c != ' ' && c != '\n') {
			carteJeu->allMap[i] = c; 
			i++;
		}
	}

	fclose(*fileToGet);
}

void init_spriteMap(carte_t *carteJeu, FILE** fileToGet){

	//Initialisation de la map
	carteJeu->sizeMap = 0;
	
	*fileToGet = readFile("./fichiersCarte/level1.txt");

	if (fileToGet == NULL) {
		fprintf(stderr, "Impossible d'ouvrir le fichier: erreur\n");
		return;		
	}

	//Récuperation du fichier
	fileInArray(fileToGet, carteJeu);

	carteJeu->allSprite = malloc(carteJeu->sizeMap * sizeof(*carteJeu->allSprite)); 

	//Initialisation de la position du joueur (la première case possible tout en haut à gauche) 
	carteJeu->posJoueur = 0;
	for (int i = 0; i < carteJeu->sizeMap; i++) {
		if (carteJeu->allMap[i] != '-' && carteJeu->allMap[i] != '/' && carteJeu->allMap[i] != '=') {
			carteJeu->posJoueur = i;	
			break;
		}		
	}

	//Initialisation des placements et du contenu (en fct du bmp de la carte) de chaque tiles 
	int y = 0;
	int x = 0;
	for (int i = 0; i < carteJeu->sizeMap; i++) {
		switch (carteJeu->allMap[i]) {
			case '-':
				x = x + SIZE_PIXEL * ZOOM_SCREEN;
				break;

			case '0':
			getSpriteMap('0', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;


			case '1':
			getSpriteMap('1', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;

			case '2':
			getSpriteMap('2', &carteJeu->allSprite[i].posSprite);
			
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;

			case '3':
			getSpriteMap('3', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);	
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;

			case '4':
			getSpriteMap('4', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;

			case '5':
			getSpriteMap('5', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;

			case '6':
			getSpriteMap('6', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;

			case '7':
			getSpriteMap('7', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;

			case '8':
			getSpriteMap('8', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;

			case '9':
			getSpriteMap('9', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;

			case 'p':
			getSpriteMap('p', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;

			case 'o':
			getSpriteMap('o', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;
	
	
			case '=':
			getSpriteMap('=', &carteJeu->allSprite[i].posSprite);
			setPosValue(i, x, y, carteJeu);
			x = x + SIZE_PIXEL * ZOOM_SCREEN;	
				break;

			case '/':
				y++;
				x = 0;
				break;	
		}
	}
}


void setPosValue(int i, int x, int y, carte_t *carteJeu){
	carteJeu->allSprite[i].posEcran.x = x; 
	carteJeu->allSprite[i].posEcran.y = y * SIZE_PIXEL * ZOOM_SCREEN; 
	carteJeu->allSprite[i].posEcran.w = SIZE_PIXEL * ZOOM_SCREEN;
	carteJeu->allSprite[i].posEcran.h = SIZE_PIXEL * ZOOM_SCREEN;		
}
