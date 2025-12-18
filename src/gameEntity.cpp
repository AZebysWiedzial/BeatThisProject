#include "gameEntity.h"

GameEntity::GameEntity(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight) : Renderable(renderer, camera, x, y, spriteWidth, spriteHeight, objectWidth, objectHeight)
{
    dirX = 0;
    dirY = 0;

    collider = {(int)(x - (HITBOX_WIDTH / 2)), (int)(y - HITBOX_HEIGHT), HITBOX_WIDTH, HITBOX_HEIGHT};

    anchor = BOTTOM_CENTER;
}

void GameEntity::move(double deltaTime)
{
    prevX = x;
    prevY = y;
}

void GameEntity::handleCollisions(SDL_Rect* floor)
{
    if(x + (collider.w / 2) > (*floor).x + (*floor).w || 
        x - (collider.w / 2) < (*floor).x) 
    {
        x = prevX;
    }

    if(y + (collider.h / 2) > (*floor).y + (*floor).h ||
        y - (collider.h / 2) < (*floor).y) 
    {
        y = prevY;
    }
}