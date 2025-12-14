#include <SDL.h>
#include "player.h"
#include "UI.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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
	SDL_Surface *screen, *charset, *backgroundSprite;
	SDL_Window *window;
	SDL_Renderer *renderer;
    SDL_Texture *backgroundTexture;
    UI* uiManager;
    Player *player;

    void render();
};