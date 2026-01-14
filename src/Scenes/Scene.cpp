#include "Scenes/Scene.h"

Scene::Scene(SDL_Renderer* renderer)
{
    this->renderer = renderer;
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
