#include <SDL.h>
#include "Renderable.h"

#define HITBOX_HEIGHT 15
#define HITBOX_WIDTH 30

class GameEntity : public Renderable
{
    public:
    GameEntity(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight);
    virtual void move(double deltaTime);
    void handleCollisions(SDL_Rect* floor);

    protected:
    int dirX;
    int dirY;
    int prevX;
    int prevY;
    int speed;
    bool hasMoved;

    Renderable* shadow;
    SDL_Rect collider;
};