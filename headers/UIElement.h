#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Renderable.h"

class UIElement : public Renderable
{
    public:
    UIElement(SDL_Renderer* renderer, double x, double y, int width, int height);
    void setWidth(int width);
    void setHeight(int height);
    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    virtual void update() {};

    private:
    bool preserveScale;
    

};
#endif