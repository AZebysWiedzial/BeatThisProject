#ifndef UITEXT_H
#define UITEXT_H

#include "UIElement.h"



class UIText : public UIElement
{
    public:
    UIText(SDL_Renderer* renderer, SDL_Surface* charset, double x, double y, int width, int height, const char* text);
    virtual void setText(const char* newText);

    protected:
    char* text;
    SDL_Surface* charset;
    int fontSize;

    virtual void DrawText();

};
#endif