#include "UITextDisplay.h"
#include <stdio.h>

UITextDisplay::UITextDisplay(SDL_Renderer* renderer, double x, double y, int width, int height, const char* prefix, double* displayValuePtr) : UIText(renderer, x, y, width, height, prefix)
{
    this->displayValueDoublePtr = displayValuePtr;
    this->displayValueIntPtr = nullptr;
    this->prefix = prefix;
}
UITextDisplay::UITextDisplay(SDL_Renderer* renderer, double x, double y, int width, int height, const char* prefix, int* displayValuePtr) : UIText(renderer, x, y, width, height, prefix)
{
    this->displayValueIntPtr = displayValuePtr;
    this->displayValueDoublePtr = nullptr;
    this->prefix = prefix;
}


void UITextDisplay::update()
{
    char buffer[128];
    if(displayValueDoublePtr != nullptr) sprintf(buffer, "%s%.2f", prefix, *displayValueDoublePtr);
    else sprintf(buffer, "%s%d", prefix, *displayValueIntPtr);
    setText(buffer);
}