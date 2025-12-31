#ifndef RENDERABLE_H
#define RENDERABLE_H
#include<SDL.h>


class Renderable
{
    protected:
    enum RenderAnchor
    {
        CENTER,
        TOP_RIGHT,
        BOTTOM_CENTER
    };


    public:
    Renderable();
    Renderable(SDL_Renderer* renderer, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight);
    virtual void render();
    virtual void updateDestRect();
    int setSprite(const char* filePath);
    int setSprite(SDL_Surface* sprite);
    int setRectangleAsSprite(uint8_t red, uint8_t green, uint8_t blue);
    void setTextureFromSprite();
    int getX();
    int getY();
    void setX(double newX);
    void setY(double newY);
    void setPosition(double newX, double newY);
    void setAnchor(RenderAnchor newAnchor);
    void setObjectWidth(int newWidth);
    void setSpriteWidth(int newWidth);



    protected:
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
    SDL_Rect srcRect;
    SDL_Rect destRect;
};
#endif