#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

#include "Game.h"

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

	loopResult = game.gameLoop();
	

	game.cleanUp();
	
	return 0;
}
