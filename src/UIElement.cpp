#include "UIElement.h"
#include <string.h>

UIElement::UIElement(SDL_Renderer* renderer, double x, double y, int width, int height) : Renderable(renderer, x, y, width, height, width, height)
{
    preserveScale = false;
}

void UIElement::setWidth(int width)
{
    objectWidth = width;
    if(preserveScale)
    {
        double scale = (double)objectWidth / (double)spriteWidth;
        objectHeight = (int)(spriteHeight * scale);
    }
}

void UIElement::setHeight(int height)
{
    objectHeight = height;
    if(preserveScale)
    {
        double scale = (double)objectHeight / (double)spriteHeight;
        objectWidth = (int)(spriteWidth * scale);
    }
}

void UIElement::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    if(texture != nullptr) SDL_SetTextureColorMod(texture, red, green, blue);
}