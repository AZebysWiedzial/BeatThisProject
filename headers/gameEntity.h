#include <SDL.h>
#include "Renderable.h"

class GameEntity : public Renderable
{
    public:
    GameEntity(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight);
    virtual void move(double deltaTime) = 0;
    virtual void handleEvents(SDL_Event& event) = 0;

    protected:
    int dirX;
    int dirY;
    int speed;
};