#ifndef UITEXTDISPLAY_H
#define UITEXTDISPLAY_H
#include "UIText.h"

class UITextDisplay : public UIText
{
    public:
    UITextDisplay(SDL_Renderer* renderer, SDL_Surface* charset, double x, double y, int width, int height, const char* prefix, double* displayValuePtr);
    UITextDisplay(SDL_Renderer* renderer, SDL_Surface* charset, double x, double y, int width, int height, const char* prefix, int* displayValuePtr);
    void update() override;
    

    private:
    double* displayValueDoublePtr;
    int* displayValueIntPtr;
    const char* prefix;

};
#endif