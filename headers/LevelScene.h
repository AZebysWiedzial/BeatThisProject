#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include <SDL.h>
#include "Scene.h"

class LevelScene : Scene
{
    public:
    LevelScene();
    void init() override;
    void update() override;
    void handleEvents(SDL_Event* event) override;
};
#endif