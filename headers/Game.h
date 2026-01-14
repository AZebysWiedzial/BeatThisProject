#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Player.h"
#include "UI.h"
#include "LinkedList.h"
#include "EnemyManager.h"
#include "RenderManager.h"
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
    int currPoints, currCombo;
    int comboDurationMs;
    bool quit;
	double deltaTimeMs, deltaTimeS, worldTime, fpsTimer, fps, updatesTimer, pauseTimer;
    char textBuffer[128];
    GameState gameState;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Window *window;
	SDL_Renderer *renderer;
    WorldRenderable *background;
    UI* gameUI;
    UI* deathScreenUI;
    UI* victoryScreenUI;
    UI* mainMenuUI;
    UI* rankingUI;

    Player *player;
    SDL_Rect camera, floor;

    EnemyManager* enemyManager;
    RenderManager* renderManager;
    // CollisionManager* collisionManager;

    void setupUI();
    int setupSDL();
    void handleRendering();
    void handleInput();
    void fixedUpdate();
    void gameUpdate();
    void reset();
    void handlePoints();
    void deactivateUI();
    void adjustCamera();
};
#endif