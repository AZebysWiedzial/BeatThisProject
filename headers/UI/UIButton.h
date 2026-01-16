#ifndef UIBUTTON_H
#define UIBUTTON_H
#include <SDL.h>
#include <functional>
#include "UIElement.h"
#include "UIText.h"
#include "UIRectangle.h"

class UIButton : public UIElement
{
    public:
    UIButton(SDL_Renderer* renderer, SDL_Surface* charset, double x, double y, int width, int height, const char* text);
    void update() override;
    void render() override;
    void handleInput(SDL_Event* event) override;
    void setOnClick(std::function<void()> func);

    private:
    UIText* textComponent;
    UIRectangle* backgroundComponent;

    std::function<void()> onClick;
    int mouseX, mouseY;
    bool isClicked;

    void onHover();
    bool isHovered();
    
};
#endif