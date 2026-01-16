#include "UI/UIButton.h"
#include <stdio.h>

#include "constants.h"

UIButton::UIButton(SDL_Renderer* renderer, SDL_Surface* charset, double x, double y, int width, int height, const char* text) : UIElement(renderer, x, y, width, height)
{
    backgroundComponent = new UIRectangle(renderer, x, y, width, height, 255, 255, 255);
    backgroundComponent->setColor(0, 255, 0);
    textComponent = new UIText(renderer, charset, x + (width / 2), y + (height / 2), width - (BTN_TEXT_OFFSET * 2), height - (BTN_TEXT_OFFSET * 2), text);
    textComponent->setAnchor(CENTER);

    isClicked = false;
    onClick = []{printf("Function unavaliable\n");};
}

void UIButton::update() 
{

}
void UIButton::render() 
{
    backgroundComponent->render();
    textComponent->render();
}
void UIButton::handleInput(SDL_Event* event) 
{
    switch (event->type)
    {
    case SDL_MOUSEMOTION:
        SDL_GetMouseState(&mouseX, &mouseY);
        if(isHovered()) 
        {
            backgroundComponent->setColor(255, 0, 0);
            // printf("Hover!\n");
        }
        else 
        {
            isClicked = false;
            backgroundComponent->setColor(0, 255, 0);
        }
        break;
    
    case SDL_MOUSEBUTTONDOWN:
        if(event->button.button == SDL_BUTTON_LEFT)
        {
            if(isHovered()) isClicked = true;
        }
        break;

    case SDL_MOUSEBUTTONUP:
        if(event->button.button == SDL_BUTTON_LEFT)
        {
            if(isClicked) onClick();
            isClicked = false;
        }

    default:
    
        break;
    }
    // printf("is button clicked: %d\n", isClicked);
}
bool UIButton::isHovered()
{
    return (mouseX > x && mouseX < x + objectWidth && mouseY > y && mouseY < y + objectHeight);
}

void UIButton::setOnClick(std::function<void()> func)
{
    onClick = std::move(func);
}