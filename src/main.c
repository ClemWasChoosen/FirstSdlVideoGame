#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void mainLoop(){	
	SDL_Event evenements; // Événements liés à la fenêtre
	bool terminer = false;
	// Boucle principale
	while(!terminer){
		SDL_PollEvent( &evenements );
		switch(evenements.type)
		{
			case SDL_QUIT:
			terminer = true; break;
			case SDL_KEYDOWN:
			switch(evenements.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				case SDLK_q:
				terminer = true; break;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	SDL_Window* fenetre = NULL; // Déclaration de la fenêtre
	SDL_Renderer* renderer = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
	{
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	// Créer la fenêtre
//	fenetre = SDL_CreateWindow("Samourai vs Zombies", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
//	SDL_CreateWindowAndRenderer(600, 600, SDL_WINDOWPOS_CENTERED, &fenetre, &renderer);
	
	if (SDL_CreateWindowAndRenderer(600, 600, SDL_WINDOW_RESIZABLE, &fenetre, &renderer)) {	
		printf("Erreur de la creation d’une fenetre et du renderer: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}		

	SDL_SetWindowTitle(fenetre, "Samourai vs Zombies");	

	mainLoop();

	// Quitter SDL
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
