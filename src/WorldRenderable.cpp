#include "WorldRenderable.h"

WorldRenderable::WorldRenderable(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight) : Renderable(renderer, x, y, spriteWidth, spriteHeight, objectWidth, objectHeight)
{
    this->camera = camera;
}

void WorldRenderable::updateDestRect()
{
    Renderable::updateDestRect();
    destRect.x -= camera->x;
    destRect.y -= camera->y;
}
