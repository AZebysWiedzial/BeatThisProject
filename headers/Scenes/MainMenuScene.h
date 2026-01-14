#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H
#include "Scene.h"
#include "UI/UI.h"

class MainMenuScene : public Scene
{
    public:
    MainMenuScene(SDL_Renderer* renderer);
    void init() override;
    void update(double deltaTimeMs) override;
    void render() override;
    void handleEvents(SDL_Event* event) override;
    void onLoad() override;

    private:
    UI* mainMenuUI;
    UI* rankingUI;

    void setupUI() override;
};
#endif

