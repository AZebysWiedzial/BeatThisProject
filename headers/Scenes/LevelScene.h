#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include <SDL.h>
#include "Scene.h"
#include "UI/UI.h"
#include "Player.h"
#include "EnemyManager.h"

class LevelScene : public Scene
{
    enum GameState
    {
        IN_GAME,
        PAUSED,
        GAME_WON,
        GAME_LOST,
    };
    public:
    LevelScene(SDL_Renderer* renderer);
    void init() override;
    void update(double deltaTimeMs) override;
    void render() override;
    void handleEvents(SDL_Event* event) override;
    void onLoad() override;

    private:
    GameState gameState;

    WorldRenderable *background;

    UI* gameUI;
    UI* deathScreenUI;
    UI* victoryScreenUI;

    Player *player;
    SDL_Rect camera, floor;

    EnemyManager* enemyManager;

    int frames;
    int currPoints, currCombo;
    int comboDurationMs;
    double worldTime, fpsTimer, fps, updatesTimer;

    void fixedUpdate();
    void reset();
    void setupUI() override;
    void handlePoints(double deltaTimeMs);
    void adjustCamera();
    void renderGameEntities();
};
#endif