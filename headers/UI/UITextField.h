#ifndef UITEXTFIELD_H
#define UITEXTFIELD_H

#include <SDL.h>

#include "UIElement.h"
#include "UIText.h"
#include "UIRectangle.h"

class UITextField : public UIElement
{
    public:
    UITextField(SDL_Renderer* renderer, SDL_Surface* charset,  double x, double y, int width, int height);
    void update() override;
    void render() override;
    void handleInput(SDL_Event* event) override;
    char* getText();

    private:
    UIText* textComponent;
    UIRectangle* backgroundComponent;

    char* textBuffer;
    int length, capacity;
    bool isEditable;
    int mouseX, mouseY;

    // bool isShiftPressed, isCapsLockOn;

    void appendText(const char* textToAppend);
    void backspace();
    

};
#endif