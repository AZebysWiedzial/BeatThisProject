#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include <SDL.h>
#include "LinkedList.h"
#include "Enemy.h"
#include "Player.h"
#include "WorldRenderable.h"
#include "UI/UI.h"

class RenderManager
{
    public:
    RenderManager(SDL_Renderer* renderer, LinkedList<Enemy*>* enemies, Player* player, WorldRenderable* background);
    void renderGameEntities();
    void renderUI();
    void renderEverything();
    void addUILayer(UI* layer);
    
    private:
    SDL_Renderer* renderer;
    LinkedList<Enemy*>* enemies;
    Player* player;
    WorldRenderable* background;
    LinkedList<UI*> UILayers;
    // UI* gameUI;
    // UI* deathScreenUI;
    // UI* victoryScreenUI;
};

#endif