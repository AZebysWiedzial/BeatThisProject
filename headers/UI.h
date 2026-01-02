#ifndef UI_H
#define UI_H
#include<SDL.h>
#include "LinkedList.h"
#include "UIElement.h"

#define PLAYER_HP_BAR_LENGTH 100

class UI
{
    public:
    UI(SDL_Renderer* renderer, bool isActive);
    // void initUI();
    void render();
    void add(UIElement* element);
    void update();
    void handleInput(SDL_Event* event);
    void setActive(bool active);
    bool getIsActive();

    private:
    bool isActive;
    
    SDL_Renderer* renderer;
    LinkedList<UIElement*> uiElements;
};
#endif