#include "Renderable.h"
#include<stdio.h>

Renderable::Renderable(){}
Renderable::Renderable(SDL_Renderer* renderer, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight)
{
    this->renderer = renderer;
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

    destRect.x = x;
    destRect.y = y;
    destRect.w = objectWidth;
    destRect.h = objectHeight;

    sprite = nullptr;
    texture = nullptr;
    // renderer = nullptr;

    anchor = TOP_RIGHT;
    
}



void Renderable::render()
{
    updateDestRect();
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void Renderable::updateDestRect()
{
    destRect.w = objectWidth;
    destRect.h = objectHeight;
    switch(anchor)
    {
        case TOP_RIGHT:
            destRect.x = x;
            destRect.y = y;
            break;
        case BOTTOM_CENTER:
            destRect.x = x - (objectWidth / 2);
            destRect.y = y - objectHeight;
            break;
        case CENTER:
            destRect.x = x - (objectWidth / 2);
            destRect.y = y - (objectHeight / 2);
            break;
        default:
            break;
    }
}

int Renderable::setSprite(const char* filePath)
{
    sprite = SDL_LoadBMP(filePath);
    if(sprite == NULL) return 1;
    setTextureFromSprite();

    return 0;
}

int Renderable::setSprite(SDL_Surface* sprite)
{
    this->sprite = sprite;
    setTextureFromSprite();

    return 0;
}
int Renderable::setRectangleAsSprite(uint8_t red, uint8_t green, uint8_t blue)
{
    sprite = SDL_CreateRGBSurface(0, 10, 10, 32,
                                0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(sprite, NULL, SDL_MapRGB(sprite->format, red, green, blue));
    setTextureFromSprite();
    return 0;
}
void Renderable::setTextureFromSprite()
{
    if(texture != nullptr) SDL_DestroyTexture(texture);
    texture = SDL_CreateTextureFromSurface(renderer, sprite);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    if(texture == nullptr) printf("Texture Creation Error: %s\n", SDL_GetError());
}

void Renderable::setX(double newX)
{
    x = newX;
}

void Renderable::setY(double newY)
{
    y = newY;
}
void Renderable::setPosition(double newX, double newY)
{
    x = newX;
    y = newY;
}
int Renderable::getX()
{
    return x;
}
int Renderable::getY()
{
    return y;
}
void Renderable::setAnchor(RenderAnchor newAnchor)
{
    anchor = newAnchor;
}
void Renderable::setObjectWidth(int newWidth)
{
    objectWidth = newWidth;
}
void Renderable::setSpriteWidth(int newWidth)
{
    spriteWidth = newWidth;
}