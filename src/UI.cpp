#include "UI.h"

UI::UI(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}
void UI::initUI()
{
    playerHpBar.x = 10;
    playerHpBar.y = 10;
    playerHpBar.w = 10;
    playerHpBar.h = 10;

    timeFpsBar.x = 20;
    timeFpsBar.y = 20;
    timeFpsBar.w = 10;
    timeFpsBar.h = 10;

    actionBar.x = 30;
    actionBar.y = 30;
    actionBar.w = 10;
    actionBar.h = 10;
}
void UI::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    SDL_RenderFillRect(renderer, &playerHpBar);
    SDL_RenderFillRect(renderer, &actionBar);
    SDL_RenderFillRect(renderer, &timeFpsBar);
}