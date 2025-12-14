#include "gameEntity.h"

#define PLAYER_SPEED 1

class Player : public GameEntity
{
    public:
        Player(SDL_Renderer* renderer, double x, double y, int spriteWidth, int spriteHeight);
        void move() override;
        void handleEvents(SDL_Event& event) override;
};