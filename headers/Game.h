#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Player.h"
#include "UI.h"
#include "LinkedList.h"
#include "EnemyManager.h"
#include "RenderManager.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define DESIRED_FPS 60.0
#define FRAME_DELAY 1000.0 / DESIRED_FPS

#define FIXED_DELTA_TIME_MS 1000.0 / DESIRED_FPS
#define FIXED_DELTA_TIME_S FIXED_DELTA_TIME_MS * 0.001

#define BACKGROUND_SPRITE_WIDTH 1280

#define FLOOR_HEIGHT 80

#define PLAYER_X_TO_MOVE_CAMERA 150

#define PLAYER_START_X 50
#define PLAYER_START_Y SCREEN_HEIGHT-20

#define RESULT_SUCCESS 0
#define RESULT_ERROR 1

#define KEY_QUIT 27
#define KEY_NEW_GAME 'n'

#define POINTS_FOR_HIT 10
#define COMBO_DURATION_MS 200

#define RESULT_QUIT 0
#define RESULT_NEW_GAME 1

class Game {
    public:
    Game();
    int init();
    int gameLoop();
    void cleanUp();

    private:
    int t1, t2, frames, rc;
    int currPoints, currCombo;
    int comboDurationMs;
    bool quit;
	double deltaTimeMs, deltaTimeS, worldTime, fpsTimer, fps, updatesTimer;
    char textBuffer[128];
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Window *window;
	SDL_Renderer *renderer;
    WorldRenderable *background;
    UI* uiManager;
    Player *player;
    SDL_Rect camera, floor;

    EnemyManager* enemyManager;
    RenderManager* renderManager;
    

    Renderable* txtTime;

    void handleRendering();
    void handleInput();
    void updateUI();
    void update();
    void reset();
};
#endif