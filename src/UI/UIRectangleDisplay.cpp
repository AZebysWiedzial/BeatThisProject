#include "UI/UIRectangleDisplay.h"

UIRectangleDisplay::UIRectangleDisplay(SDL_Renderer* renderer, double x, double y, int width, int height, uint8_t red, uint8_t green, uint8_t blue, int* displayValuePtr) : UIRectangle(renderer, x, y, width, height, red, green, blue)
{
    displayValue.intPtr = displayValuePtr;
    maxValue = (double)(*displayValuePtr);
    type = INT_PTR;
    initialWidth = width;
}

UIRectangleDisplay::UIRectangleDisplay(SDL_Renderer* renderer, double x, double y, int width, int height, uint8_t red, uint8_t green, uint8_t blue, double* displayValuePtr) : UIRectangle(renderer, x, y, width, height, red, green, blue)
{
    displayValue.doublePtr = displayValuePtr;
    maxValue = *displayValuePtr;
    type = DOUBLE_PTR;
    initialWidth = width;
}

void UIRectangleDisplay::update()
{
    double value = 0.0;
    switch(type)
    {
        case INT_PTR:
            value = (double)(*displayValue.intPtr);
            break;
        case DOUBLE_PTR:
            value = *displayValue.doublePtr;
            break;
        default:
            break;
    }

    double scale = value / maxValue;
    if(scale < 0.0) scale = 0.0;
    else if(scale > 1.0) scale = 1.0;

    setWidth((int)(initialWidth * scale));
}