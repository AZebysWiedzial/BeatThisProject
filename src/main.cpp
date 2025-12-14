#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

#include "game.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

// main
int main(int argc, char **argv) 
{
	Game game;

	int result = game.init();
	if(result == RESULT_SUCCESS) printf("SUCCESS!\n");
	else printf("FAILED\n");
	

	game.gameLoop();

	game.cleanUp();
	
	return 0;
}
