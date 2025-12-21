#ifndef UI_H
#define UI_H
#include<SDL.h>
#include "LinkedList.h"
#include "Renderable.h"

#define PLAYER_HP_BAR_LENGTH 40

class UI
{
    public:
    UI(SDL_Renderer* renderer);
    void initUI();
    void render();
    void add(Renderable* element);

    private:
    char textBuffer[128];
    
    SDL_Renderer* renderer;
    SDL_Surface* charset;
    LinkedList<Renderable*> uiElements;
};
#endif