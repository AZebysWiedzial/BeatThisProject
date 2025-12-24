#include "RenderManager.h"
#include <stdio.h>

RenderManager::RenderManager(SDL_Renderer* renderer, SDL_Rect* camera, LinkedList<Enemy*>* enemies, Player* player, WorldRenderable* background, UI* uiManager)
{
    this->renderer = renderer;
    this->camera = camera;
    this->enemies = enemies;
    this->player = player;
    this->background = background;
    this->uiManager = uiManager;
}
void RenderManager::renderGameEntities()
{
    bool hasRenderedPlayer = false;
    // enemies.sort();
    enemies->forEach([&](Enemy* enemy){
        if(!hasRenderedPlayer && player->getY() < enemy->getY())
        {
            hasRenderedPlayer = true;
            player->renderShadow();
        }
        enemy->renderShadow();
    });
    if(!hasRenderedPlayer) player->renderShadow();

    hasRenderedPlayer = false;
    enemies->forEach([&](Enemy* enemy){
        if(!hasRenderedPlayer && player->getY() < enemy->getY())
        {
            hasRenderedPlayer = true;
            player->render();
        }
        enemy->render();
    });
    if(!hasRenderedPlayer) player->render();


    enemies->forEach([](Enemy* enemy){
        enemy->renderHpBar();
    });
}
void RenderManager::renderUI()
{
    uiManager->render();
}
void RenderManager::renderEverything()
{
    if(background == nullptr) printf("Background is null\n");
    background->render();
    renderGameEntities();
    renderUI();
}