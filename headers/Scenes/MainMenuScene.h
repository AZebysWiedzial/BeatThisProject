#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H
#include "Scene.h"
#include "UI/UI.h"
#include "UI/UIText.h"
#include "filesFuncs.h"

#include "constants.h"

class MainMenuScene : public Scene
{
    public:
    MainMenuScene(SDL_Renderer* renderer, SDL_Surface* charset);
    void init() override;
    void update(double deltaTimeMs) override;
    void render() override;
    void handleEvents(SDL_Event* event) override;
    void onLoad() override;

    private:
    UI* mainMenuUI;
    UI* rankingUI;

    int numberOfScores, currentPage;

    UIText** txtScores;
    Score scoresToDisplay[SCORES_PER_PAGE];
    Score* allScores;

    void setupUI() override;
    void updateScoreDisplay();
};
#endif

