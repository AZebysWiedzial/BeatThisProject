#include<SDL.h>

#define PLAYER_HP_BAR_LENGTH 40

class UI
{
    public:
    UI(SDL_Renderer* renderer);
    void initUI();
    void Render();

    private:
    SDL_Rect playerHpBar;
    SDL_Rect actionBar;
    SDL_Rect timeFpsBar;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};