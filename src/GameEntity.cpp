#include "GameEntity.h"

GameEntity::GameEntity(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int hp, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight) : WorldRenderable(renderer, camera, x, y, spriteWidth, spriteHeight, objectWidth, objectHeight)
{
    dirX = 0;
    dirY = 0;

    maxHp = hp;
    currHp = maxHp;
    collider = {(int)(x - (HITBOX_WIDTH / 2)), (int)(y - HITBOX_HEIGHT), HITBOX_WIDTH, HITBOX_HEIGHT};

    anchor = BOTTOM_CENTER;
}

void GameEntity::move(double deltaTime)
{
    prevX = x;
    prevY = y;

    hasMoved = false;
}
void GameEntity::undoMoveX()
{
    x = prevX;
}
void GameEntity::undoMoveY()
{
    y = prevY;
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

void GameEntity::dealDamage(int damage)
{
    currHp -= damage;
}
int GameEntity::getCurrHp()
{
    return currHp;
}
int GameEntity::getMaxHp()
{
    return maxHp;
}
int GameEntity::getDirX()
{
    return  dirX;
}
bool GameEntity::getHasMoved()
{
    return hasMoved;
}
Direction GameEntity::getFacingDirection()
{
    return facingDirection;
}
void GameEntity::renderShadow()
{

}