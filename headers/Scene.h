#ifndef SCENE_H
#define SCENE_H
#include <SDL.h>
class Scene
{
    public:
    Scene();
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void handleEvents(SDL_Event* event) = 0;
};

#endif