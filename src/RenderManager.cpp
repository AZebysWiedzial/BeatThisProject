#include "RenderManager.h"
#include <stdio.h>

RenderManager::RenderManager(SDL_Renderer* renderer, LinkedList<Enemy*>* enemies, Player* player, WorldRenderable* background)
{
    this->renderer = renderer;
    this->enemies = enemies;
    this->player = player;
    this->background = background;
    // this->gameUI = gameUI;
    // this->deathScreenUI = deathScreenUI;
    // this->victoryScreenUI = victoryScreenUI;
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
    int currLayer = 0;
    // printf("UI layers active: ");
    UILayers.forEach([&](UI* layer){
        if(layer->getIsActive()) 
        {
            // printf("%d ", currLayer);
            layer->render();
        }
        currLayer++;
    });
    // printf("\n");
}
void RenderManager::addUILayer(UI* layer)
{
    UILayers.add(layer);
}
void RenderManager::renderEverything()
{
    background->render();
    renderGameEntities();
    renderUI();
}