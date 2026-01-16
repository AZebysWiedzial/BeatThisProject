#include "Scenes/MainMenuScene.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "UI/UITextDisplay.h"

#include "constants.h"

#include <stdio.h>

MainMenuScene::MainMenuScene(SDL_Renderer* renderer, SDL_Surface* charset) : Scene(renderer, charset)
{
    allScores = nullptr;
    txtScores = nullptr;
    numberOfScores = 0;
    currentPage = 0;
}
void MainMenuScene::init()
{
    mainMenuUI = new UI(renderer, true);
    rankingUI = new UI(renderer, false);

    numberOfScores = getNumberOfScores();
    allScores = getScoresFromFile();

    setupUI();
}
void MainMenuScene::update(double deltaTimeMs)
{

}
void MainMenuScene::render()
{
    // printf("Is menu UI active: %d\n", mainMenuUI->getIsVisible());
    mainMenuUI->render();
    rankingUI->render();
}
void MainMenuScene::handleEvents(SDL_Event* event)
{
    mainMenuUI->handleInput(event);
    rankingUI->handleInput(event);
}

void MainMenuScene::setupUI()
{
    UIRectangle* staticBackground = new UIRectangle(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 50, 50, 50);
    UIText* txtTitle = new UIText(renderer, charset, 100, 200, 100, 40, "BEAT THIS PROJECT!");
    UIButton* btnLevelChoice = new UIButton(renderer, charset, 150, 250, 150, 25, "LEVELS");
    UIButton* btnSandbox = new UIButton(renderer, charset, 150, 300, 150, 25, "SANDBOX");
    btnSandbox->setOnClick([&]{
        sceneToSwitch = LEVEL;    
    });
    UIButton* btnRankings = new UIButton(renderer, charset, 150, 350, 250, 25, "SHOW RANKING");
    btnRankings->setOnClick([&]{
        mainMenuUI->setVisible(false);
        rankingUI->setActive(true);
        currentPage = 0;
        updateScores(scoresToDisplay, currentPage);
        updateScoreDisplay();
    });
    UIButton* btnQuit = new UIButton(renderer, charset, 150, 400, 150, 25, "QUIT");
    btnQuit->setOnClick([&]{sceneToSwitch = QUIT;});

    mainMenuUI->add(staticBackground);
    mainMenuUI->add(txtTitle);
    mainMenuUI->add(btnLevelChoice);
    mainMenuUI->add(btnSandbox);
    mainMenuUI->add(btnRankings);
    mainMenuUI->add(btnQuit);

    UIText* txtAllScores = new UIText(renderer, charset, 200, 50, 100, 20, "ALL SCORES:");
    UIButton* btnNextPage = new UIButton(renderer, charset, 400, 400, 100, 20, "NEXT");
    btnNextPage->setOnClick([&]{
        if((currentPage + 1) * SCORES_PER_PAGE >= numberOfScores) return;
        currentPage++;
        updateScores(scoresToDisplay, currentPage);
        updateScoreDisplay();
        printf("Current page: %d\n", currentPage);
    });
    UIButton* btnPrevPage = new UIButton(renderer, charset, 100, 400, 100, 20, "PREVIOUS");
    btnPrevPage->setOnClick([&]{
        if(currentPage <= 0) 
        {
            currentPage = 0;
            return;
        }
        currentPage--;
        updateScores(scoresToDisplay, currentPage);
        updateScoreDisplay();
        printf("Current page: %d\n", currentPage);
    });

    txtScores = new UIText*[SCORES_PER_PAGE];
    

    rankingUI->add(staticBackground);
    rankingUI->add(txtAllScores);
    rankingUI->add(btnNextPage);
    rankingUI->add(btnPrevPage);
    for(int i = 0; i < SCORES_PER_PAGE; i++)
    {
        txtScores[i] = new UIText(renderer, charset, 200, 100 + (i * 25), 100, 16, "kanapka");
        rankingUI->add(txtScores[i]);
    }
}

void MainMenuScene::onLoad()
{
    mainMenuUI->setActive(true);
    rankingUI->setVisible(false);

}

void MainMenuScene::updateScoreDisplay()
{
    char buffer[128];
    for (int i = 0; i < SCORES_PER_PAGE; i++)
    {
        if((SCORES_PER_PAGE * currentPage) + i >= numberOfScores) 
        {
            txtScores[i]->setText("");
            continue;
        }
        snprintf(buffer, sizeof(buffer), "%s: %d", scoresToDisplay[i].nickname, scoresToDisplay[i].score);
        txtScores[i]->setText(buffer);
    }
}