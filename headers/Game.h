#ifndef GAME_H
#define GAME_H

#include <SDL.h>
// #include "Player.h"
// #include "UI.h"
#include "LinkedList.h"
// #include "EnemyManager.h"
#include "RenderManager.h"
#include "Scenes/Scene.h"
#include "Scenes/LevelScene.h"
#include "Scenes/MainMenuScene.h"
// #include "CollisionManager.h"



class Game {
    enum GameState
    {
        IN_GAME,
        MAIN_MENU,
        SHOW_RANKINGS,
        PAUSED,
        GAME_WON,
        GAME_LOST,
    };

    public:
    Game();
    int init();
    int mainLoop();
    void cleanUp();

    private:
    int t1, t2, frames, rc;
    bool quit;
	double deltaTimeMs, deltaTimeS;
    GameState gameState;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Window *window;
	SDL_Renderer *renderer;
    
    RenderManager* renderManager;
    // CollisionManager* collisionManager;
    
    Scene* currScene;
    LevelScene* level;
    MainMenuScene* mainMenu;

    int setupSDL();
    void handleRendering();
    void handleEvents();
    void adjustScene();
};
#endif