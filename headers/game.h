#include <SDL.h>
#include "player.h"
#include "UI.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define BACKGROUND_SPRITE_WIDTH 1280
#define BACKGROUND_SPRITE_HEIGHT 480

#define PLAYER_X_TO_MOVE_CAMERA 150

#define RESULT_SUCCESS 0
#define RESULT_ERROR 1

class Game {
    public:
    Game();
    int init();
    int gameLoop();
    void cleanUp();

    private:
    int t1, t2, quit, frames, rc;
	double delta, worldTime, fpsTimer, fps, distance, etiSpeed;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Window *window;
	SDL_Renderer *renderer;
    Renderable *background;
    UI* uiManager;
    Player *player;
    SDL_Rect camera;

    void render();
};