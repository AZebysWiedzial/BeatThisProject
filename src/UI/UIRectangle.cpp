#include "UI/UIRectangle.h"

UIRectangle::UIRectangle(SDL_Renderer* renderer, double x, double y, int width, int height, uint8_t red, uint8_t green, uint8_t blue) : UIElement(renderer, x, y, width, height)
{
    setRectangleAsSprite(255, 255, 255);
    setColor(red, green, blue);
}