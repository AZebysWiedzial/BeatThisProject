#include <SDL.h>
#include "Renderable.h"

class GameEntity : public Renderable
{
    public:
    GameEntity(SDL_Renderer* renderer, double x, double y, int spriteWidth, int spriteHeight);
    virtual void move() = 0;
    virtual void handleEvents(SDL_Event& event) = 0;

    protected:
    int dirX;
    int dirY;
    int speed;
};