#ifndef UITEXT_H
#define UITEXT_H

#include "UIElement.h"

#define CHAR_BITMAP_SIZE 8


class UIText : public UIElement
{
    public:
    UIText(SDL_Renderer* renderer, double x, double y, int width, int height, const char* text);
    virtual void setText(const char* newText);
    const char* getText();

    protected:
    char* text;
    SDL_Surface* charset;
    int fontSize;

    virtual void DrawText();

};
#endif