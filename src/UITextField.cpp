#include "UITextField.h"
#include <string.h>
#include <stdio.h>

UITextField::UITextField(SDL_Renderer* renderer, double x, double y, int width, int height) : UIElement(renderer, x, y, width, height)
{
    isEditable = true;
    mouseX = mouseY = 0;
    length = 0;
    capacity = 60;
    textBuffer = new char[capacity];
    textBuffer[0] = '\0';

    backgroundComponent = new UIRectangle(renderer, x, y, width, height, 255, 255, 255);
    textComponent = new UIText(renderer, x + 2, y + 2, width - 4, height - 4, "");
    textComponent->setColor(0, 0, 0);
}

void UITextField::update()
{
    printf("Text field active: %d; Text: %s\n", isEditable, textBuffer);
    // printf("Kanapka\n");
    textComponent->setText(textBuffer);
}
void UITextField::render()
{
    backgroundComponent->render();
    textComponent->render();
}

void UITextField::handleInput(SDL_Event* event)
{
    switch (event->type)
    {
    case SDL_MOUSEMOTION:
        SDL_GetMouseState(&mouseX, &mouseY);
        break;
    
    case SDL_MOUSEBUTTONDOWN:
        if(event->button.button == SDL_BUTTON_LEFT)
        {
            if(mouseX > x && mouseX < x + objectWidth && mouseY > y && mouseY < y + objectHeight) isEditable = true;
            else isEditable = false;
        }
        break;

    case SDL_TEXTINPUT:
    {
        const char* input = event->text.text;
        appendText(input);
        break;
    }
    case SDL_KEYDOWN:
    {
        SDL_Keycode keyPressed = event->key.keysym.sym;
        if(keyPressed == '\b') backspace();
    }
    case SDL_KEYUP:
    {
        SDL_Keycode keyPressed = event->key.keysym.sym;
        if(keyPressed == SDLK_LSHIFT) isShiftPressed = false;
    }

    default:
    
        break;
    }
}

void UITextField::appendText(const char* textToAppend)
{
    int textToAppendLength = strlen(textToAppend);
    if(length + textToAppendLength + 1 > capacity) return;

    memcpy(textBuffer + length, textToAppend, textToAppendLength + 1);
    textBuffer[length + 1] = '\0';
    length += textToAppendLength;
}

void UITextField::backspace()
{
    if(length == 0) return;

    textBuffer[length - 1] = '\0';
    length--;
}