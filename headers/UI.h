#ifndef UI_H
#define UI_H
#include<SDL.h>
#include "LinkedList.h"
#include "UIElement.h"

#define PLAYER_HP_BAR_LENGTH 100

class UI
{
    public:
    UI(SDL_Renderer* renderer);
    // void initUI();
    void render();
    void add(UIElement* element);
    void update();

    private:
    char textBuffer[128];
    
    SDL_Renderer* renderer;
    LinkedList<UIElement*> uiElements;
};
#endif