#include<SDL.h>

class Renderable
{
    
    public:
    Renderable(SDL_Renderer* renderer, double x, double y, int spriteWidth, int spriteHeight);
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

    SDL_Surface* sprite;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect srcRect;
    SDL_Rect destRect;
};