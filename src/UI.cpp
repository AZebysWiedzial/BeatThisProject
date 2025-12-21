#include "UI.h"
#include "graphics.h"
#include<stdio.h>

UI::UI(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    charset = nullptr;
}
void UI::initUI()
{
    charset = SDL_LoadBMP("../assets/cs8x8.bmp");
    if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		}
    else printf("Charset loaded!\n");
	SDL_SetColorKey(charset, true, SDL_MapRGB(charset->format, 0, 0, 0));
	
	// SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255)
}
void UI::render()
{
    uiElements.forEach([](Renderable* element){
        element->render();
    });
}
void UI::add(Renderable* element)
{
    uiElements.add(element);
}
