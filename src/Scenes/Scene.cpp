#include "Scenes/Scene.h"

Scene::Scene(SDL_Renderer* renderer, SDL_Surface* charset)
{
    this->renderer = renderer;
    this->charset = charset;
    sceneToSwitch = NONE;
}
void Scene::setSceneToSwitch(SceneToSwitch newSceneToSwitch)
{
    sceneToSwitch = newSceneToSwitch;
}
Scene::SceneToSwitch Scene::getSceneToSwitch()
{
    return sceneToSwitch;
}
