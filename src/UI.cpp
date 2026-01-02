#include "UI.h"
#include "graphics.h"
#include<stdio.h>

UI::UI(SDL_Renderer* renderer, bool isActive)
{
    this->renderer = renderer;
    this->isActive = isActive;
}
// void UI::initUI()
// {
    
// }
void UI::render()
{
    uiElements.forEach([](Renderable* element){
        element->render();
    });
}
void UI::add(UIElement* element)
{
    uiElements.add(element);
}

void UI::update()
{
    if(!isActive) return;
    uiElements.forEach([](UIElement* element){
        element->update();
    });
    // printf("UI active\n");
}
void UI::handleInput(SDL_Event* event)
{
    if(!isActive) return;
    uiElements.forEach([event](UIElement* element){
        element->handleInput(event);
    });
}
void UI::setActive(bool active)
{
    isActive = active;
}

bool UI::getIsActive()
{
    return isActive;
}
