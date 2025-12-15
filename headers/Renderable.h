#include<SDL.h>

class Renderable
{
    
    public:
    Renderable(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight);
    void render();
    void updateDestRect();
    int setSprite(const char* filePath);

    protected:
    enum RenderAnchor
    {
        CENTER,
        TOP_RIGHT,
        BOTTOM_CENTER
    };
    RenderAnchor anchor;

    double x;
    double y;
    int spriteWidth;
    int spriteHeight;

    int objectWidth;
    int objectHeight;

    SDL_Surface* sprite;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect* camera;
    SDL_Rect srcRect;
    SDL_Rect destRect;
};