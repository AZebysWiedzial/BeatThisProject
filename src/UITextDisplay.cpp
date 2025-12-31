#include "UITextDisplay.h"
#include <stdio.h>

UITextDisplay::UITextDisplay(SDL_Renderer* renderer, double x, double y, int width, int height, const char* prefix, double* displayValuePtr) : UIText(renderer, x, y, width, height, prefix)
{
    this->displayValuePtr = displayValuePtr;
    this->prefix = prefix;
}



void UITextDisplay::update()
{
    char buffer[128];
    sprintf(buffer, "%s %.2f", prefix, *displayValuePtr);
    setText(buffer);
}