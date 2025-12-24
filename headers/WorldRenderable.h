#ifndef WORLDRENDERABLE_H
#define WORLDRENDERABLE_H
#include "Renderable.h"

class WorldRenderable : public Renderable
{
    public:
    WorldRenderable(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight);
    void updateDestRect();
    void render() override;

    private:
    SDL_Rect* camera;
};
#endif