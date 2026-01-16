#ifndef SCENE_H
#define SCENE_H
#include <SDL.h>

class Scene
{
    public:
    enum SceneToSwitch
    {
        NONE,
        MAIN_MENU,
        LEVEL,
        QUIT,
    };

    Scene(SDL_Renderer* renderer, SDL_Surface* charset);
    virtual void init() = 0;
    virtual void update(double deltaTimeMs) = 0;
    virtual void render() = 0;
    virtual void handleEvents(SDL_Event* event) = 0;
    virtual void onLoad() = 0;
    void setSceneToSwitch(SceneToSwitch newSceneToSwitch);
    SceneToSwitch getSceneToSwitch();


    protected:
    SDL_Renderer* renderer;
    SceneToSwitch sceneToSwitch;

    SDL_Surface* charset;

    virtual void setupUI() = 0;
};

#endif