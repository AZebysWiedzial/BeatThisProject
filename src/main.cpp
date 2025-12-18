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

	int initResult, loopResult;


	initResult = game.init();
	if(initResult == RESULT_SUCCESS) printf("SUCCESS!\n");
	else 
	{
		printf("FAILED\n");
	}

	
	do
	{
		
		loopResult = game.gameLoop();
	} while (loopResult != RESULT_QUIT);

	game.cleanUp();
	
	return 0;
}
