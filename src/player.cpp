#include "player.h"
#include "math_funcs.h"

#define KEY_UP SDLK_UP
#define KEY_DOWN SDLK_DOWN
#define KEY_LEFT SDLK_LEFT
#define KEY_RIGHT SDLK_RIGHT


Player::Player(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight) : GameEntity(renderer, camera, x, y, spriteWidth, spriteHeight, objectWidth, objectHeight)
{
    speed = PLAYER_SPEED;

    sprite = SDL_CreateRGBSurface(0, spriteWidth, spriteWidth, 32,
                                0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(sprite, NULL, SDL_MapRGB(sprite->format, 0xFF, 0x00, 0x00));
    texture = SDL_CreateTextureFromSurface(renderer, sprite);
}
void Player::move(double deltaTime)
{
    GameEntity::move(deltaTime);
    
    double dx = speed * dirX * deltaTime;
    double dy = speed * dirY * deltaTime;

    normalizeVector(&dx, &dy);

    x += dx;
    y += dy;

    collider.x = (int)(x - (collider.w / 2));
    collider.y = (int)(y - collider.h);
}
void Player::handleEvents(SDL_Event& event)
{
    switch(event.type) {
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == KEY_RIGHT) dirX = 1;
            else if(event.key.keysym.sym == KEY_LEFT) dirX = -1;
            else if(event.key.keysym.sym == KEY_DOWN) dirY = 1;
            else if(event.key.keysym.sym == KEY_UP) dirY = -1;
            break;

        case SDL_KEYUP:
            if(dirX == 1 && event.key.keysym.sym == KEY_RIGHT) dirX = 0;
            else if(dirX == -1 && event.key.keysym.sym == KEY_LEFT) dirX = 0;
            else if(dirY == 1 && event.key.keysym.sym == KEY_DOWN) dirY = 0;
            else if(dirY == -1 && event.key.keysym.sym == KEY_UP) dirY = 0;
            break;
        }
        
}
int Player::getX()
{
    return x;
}
int Player::getY()
{
    return y;
}