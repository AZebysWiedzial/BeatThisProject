#include "Scenes/MainMenuScene.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"

#include "constants.h"

#include <stdio.h>

MainMenuScene::MainMenuScene(SDL_Renderer* renderer) : Scene(renderer)
{

}
void MainMenuScene::init()
{
    mainMenuUI = new UI(renderer, true);
    rankingUI = new UI(renderer, false);

    setupUI();
}
void MainMenuScene::update(double deltaTimeMs)
{

}
void MainMenuScene::render()
{
    printf("Is menu UI active: %d\n", mainMenuUI->getIsVisible());
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
    UIText* txtTitle = new UIText(renderer, 100, 200, 100, 40, "BEAT THIS PROJECT!");
    UIButton* btnLevelChoice = new UIButton(renderer, 150, 250, 150, 25, "LEVELS");
    UIButton* btnSandbox = new UIButton(renderer, 150, 300, 150, 25, "SANDBOX");
    btnSandbox->setOnClick([&]{
        sceneToSwitch = LEVEL;    
    });
    UIButton* btnRankings = new UIButton(renderer, 150, 350, 250, 25, "SHOW RANKING");
    btnRankings->setOnClick([&]{});
    UIButton* btnQuit = new UIButton(renderer, 150, 400, 150, 25, "QUIT");
    btnQuit->setOnClick([&]{sceneToSwitch = QUIT;});

    // mainMenuUI->add(staticBackground);
    mainMenuUI->add(txtTitle);
    mainMenuUI->add(btnLevelChoice);
    mainMenuUI->add(btnSandbox);
    mainMenuUI->add(btnRankings);
    mainMenuUI->add(btnQuit);
}

void MainMenuScene::onLoad()
{
    mainMenuUI->setActive(true);
    rankingUI->setVisible(false);
}