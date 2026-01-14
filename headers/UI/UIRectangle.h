#ifndef UIRECTANGLE_H
#define UIRECTANGLE_H
#include "UIElement.h"
class UIRectangle : public UIElement
{
    public:
    UIRectangle(SDL_Renderer* renderer, double x, double y, int width, int height, uint8_t red, uint8_t green, uint8_t blue);
};
#endif