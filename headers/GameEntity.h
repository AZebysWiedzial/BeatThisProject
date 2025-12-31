#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <SDL.h>
#include "WorldRenderable.h"

#define HITBOX_HEIGHT 15
#define HITBOX_WIDTH 30

enum Direction
{
    LEFT,
    RIGHT
};

class GameEntity : public WorldRenderable
{
    public:
    GameEntity(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int hp, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight);
    virtual void move(double deltaTime);
    void handleCollisions(SDL_Rect* floor);
    void renderShadow();
    virtual void dealDamage(int damage);
    void undoMoveX();
    void undoMoveY();
    int getCurrHp();
    int getMaxHp();
    int getDirX();
    bool getHasMoved();
    Direction getFacingDirection();

    protected:
    int dirX;
    int dirY;
    int prevX;
    int prevY;
    int speed;
    int maxHp, currHp;
    bool hasMoved;
    Direction facingDirection;

    
    WorldRenderable* shadow;
    SDL_Rect collider;
};
#endif