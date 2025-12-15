#include "Renderable.h"

Renderable::Renderable(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight)
{
    this->renderer = renderer;
    this->camera = camera;
    this->x = x;
    this->y = y;
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;
    this->objectWidth = objectWidth;
    this->objectHeight = objectHeight;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = spriteWidth;
    srcRect.h = spriteHeight;

    anchor = TOP_RIGHT;
}

void Renderable::updateDestRect()
{
    destRect.w = spriteWidth;
    destRect.h = spriteHeight;
    switch(anchor)
    {
        case TOP_RIGHT:
            destRect.x = x;
            destRect.y = y;
            break;
        case BOTTOM_CENTER:
            destRect.x = x - (spriteWidth / 2);
            destRect.y = y - spriteHeight;
            break;
        default:
            break;
    }
    destRect.x -= camera->x;
    destRect.y -= camera->y;
}

void Renderable::render()
{
    updateDestRect();
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

int Renderable::setSprite(const char* filePath)
{
    sprite = SDL_LoadBMP("../assets/background.bmp");
    if(sprite == NULL) return 1;
    
    texture = SDL_CreateTextureFromSurface(renderer, sprite);
    return 0;
}
