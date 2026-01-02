#ifndef UI_RECTANGLE_DISPLAY_H
#define UI_RECTANGLE_DISPLAY_H

#include "UIRectangle.h"
#include <stdio.h>

class UIRectangleDisplay : public UIRectangle
{
    public:
    UIRectangleDisplay(SDL_Renderer* renderer, double x, double y, int width, int height, uint8_t red, uint8_t green, uint8_t blue, int* displayValuePtr);
    UIRectangleDisplay(SDL_Renderer* renderer, double x, double y, int width, int height, uint8_t red, uint8_t green, uint8_t blue, double* displayValuePtr);
    void update() override;
    
    private:
    typedef enum
    {
        INT_PTR,
        DOUBLE_PTR
    } valueType;
    typedef union 
    {
        int* intPtr;
        double* doublePtr;
    } displayType;

    displayType displayValue;
    double maxValue;
    valueType type;
    int initialWidth;
};

#endif