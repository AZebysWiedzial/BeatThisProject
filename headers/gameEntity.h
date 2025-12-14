#include <SDL.h>
class GameEntity
{
    public:
    GameEntity(SDL_Renderer* renderer, double x, double y, int spriteWidth, int spriteHeight);

    public:
    void render();
    virtual void move() = 0;
    virtual void handleEvents(SDL_Event& event) = 0;

    protected:
    double x;
    double y;
    int dirX;
    int dirY;
    int speed;
    int spriteWidth;
    int spriteHeight;
    SDL_Surface* sprite;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect destRect;
    SDL_Rect srcRect;

    
};