#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Player.h"
#include "UI.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define BACKGROUND_SPRITE_WIDTH 1280

#define FLOOR_HEIGHT 80

#define PLAYER_X_TO_MOVE_CAMERA 150

#define PLAYER_START_X 50
#define PLAYER_START_Y SCREEN_HEIGHT-20

#define RESULT_SUCCESS 0
#define RESULT_ERROR 1

#define KEY_QUIT 27
#define KEY_NEW_GAME 'n'

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
    bool quit;
	double delta, worldTime, fpsTimer, fps;
    char textBuffer[128];
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Window *window;
	SDL_Renderer *renderer;
    Renderable *background;
    UI* uiManager;
    Player *player;
    SDL_Rect camera, floor;

    Renderable* txtTime;

    void handleRendering();
    void handleEvents();
    void updateUI();
    void reset();
};
#endif