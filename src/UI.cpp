#include "UI.h"
#include "graphics.h"
#include<stdio.h>

UI::UI(SDL_Renderer* renderer)
{
    this->renderer = renderer;
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
    uiElements.forEach([](UIElement* element){
        element->update();
    });
}
