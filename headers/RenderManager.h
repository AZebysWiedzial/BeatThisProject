#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include <SDL.h>
#include "LinkedList.h"
#include "Enemy.h"
#include "Player.h"
#include "WorldRenderable.h"
#include "UI.h"

class RenderManager
{
    public:
    RenderManager(SDL_Renderer* renderer, SDL_Rect* camera, LinkedList<Enemy*>* enemies, Player* player, WorldRenderable* background, UI* uiManager);
    void renderGameEntities();
    void renderUI();
    void renderEverything();
    
    private:
    SDL_Renderer* renderer;
    SDL_Rect* camera;
    LinkedList<Enemy*>* enemies;
    Player* player;
    WorldRenderable* background;
    UI* uiManager;
};

#endif