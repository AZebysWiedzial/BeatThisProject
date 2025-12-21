#include "WorldRenderable.h"

WorldRenderable::WorldRenderable(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight) : Renderable(renderer, x, y, spriteWidth, spriteHeight, objectWidth, objectHeight)
{
    this->camera = camera;
}

void WorldRenderable::updateDestRect()
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

void WorldRenderable::render()
{
    updateDestRect();
    Renderable::render();
}