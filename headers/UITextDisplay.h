#ifndef UITEXTDISPLAY_H
#define UITEXTDISPLAY_H
#include "UIText.h"

class UITextDisplay : public UIText
{
    public:
    UITextDisplay(SDL_Renderer* renderer, double x, double y, int width, int height, const char* prefix, double* displayValuePtr);
    void update() override;
    

    private:
    double* displayValuePtr;
    const char* prefix;

};
#endif