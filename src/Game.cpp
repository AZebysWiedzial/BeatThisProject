#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>

#include "constants.h"

#include "Game.h"
#include "graphics.h"
#include "UIElement.h"
#include "UIText.h"
#include "UITextDisplay.h"
#include "UIRectangle.h"
#include "UIRectangleDisplay.h"
#include "UITextField.h"
#include "UIButton.h"
#include "filesFuncs.h"

Game::Game()
{
    frames = 0;
    fpsTimer = 0;
    fps = 0;
    quit = false;
    worldTime = 0;
    updatesTimer = 0;
    currPoints = 0;
    currCombo = 0;
    charset = nullptr;
    window = nullptr;
    renderer = nullptr;
    background = nullptr;
    enemyManager = nullptr;
}

int Game::init()
{
    if(setupSDL() == RESULT_ERROR) return RESULT_ERROR;

    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    floor = {0, SCREEN_HEIGHT - FLOOR_HEIGHT, BACKGROUND_SPRITE_WIDTH, FLOOR_HEIGHT};

    gameUI = new UI(renderer, false);
    deathScreenUI = new UI(renderer, false);
    victoryScreenUI = new UI(renderer, false);
    mainMenuUI = new UI(renderer, true);
    rankingUI = new UI(renderer, false);

    

    enemyManager = new EnemyManager(renderer, &camera);
    player = new Player(renderer, &camera, PLAYER_START_X, PLAYER_START_Y, 100, 30, 30, 30, 30);

    background = new WorldRenderable(renderer, &camera, 0.0, 0.0, BACKGROUND_SPRITE_WIDTH, SCREEN_HEIGHT, BACKGROUND_SPRITE_WIDTH, SCREEN_HEIGHT);
    renderManager = new RenderManager(renderer, enemyManager->getEnemiesList(), player, background);
    renderManager->addUILayer(gameUI);
    renderManager->addUILayer(deathScreenUI);
    renderManager->addUILayer(victoryScreenUI);
    renderManager->addUILayer(mainMenuUI);
    renderManager->addUILayer(rankingUI);

    
    // collisionManager = new CollisionManager(player, enemyManager->getEnemiesList(), &floor);

    enemyManager->spawnEnemy(100, SCREEN_HEIGHT - 20);

    if(background->setSprite("../assets/background.bmp") == 1)
    {
        printf("SDL_LoadBMP(background.bmp) error: %s\n", SDL_GetError());
        cleanUp();
        return RESULT_ERROR;
    }
	
    setupUI();

    gameState = MAIN_MENU;

    return RESULT_SUCCESS;
}

int Game::setupSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return RESULT_ERROR;
    }

    rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    if(rc != 0) 
    {
        SDL_Quit();
        printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
        return RESULT_ERROR;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_SetWindowTitle(window, "Beat This Project");

    SDL_ShowCursor(SDL_DISABLE);
    return RESULT_SUCCESS;
}
void Game::setupUI()
{
    UIRectangle* uiBackground = new UIRectangle(renderer, 0, 0, 640, 50, 100, 100, 100);
    UIRectangleDisplay* playerHpBar = new UIRectangleDisplay(renderer, 10, 10, PLAYER_HP_BAR_LENGTH, 20, 255, 0, 0, player->getHp());
    UITextDisplay* txtTime = new UITextDisplay(renderer, 300, 10, 100, 12, "Time: ", &worldTime);
    UITextDisplay* txtScore = new UITextDisplay(renderer, 150, 10, 100, 12, "Score: ", &currPoints);
    UITextDisplay* txtFPS = new UITextDisplay(renderer, 500, 10, 100, 12, "FPS: ", &fps);

    gameUI->add(uiBackground);
    gameUI->add(playerHpBar);
    gameUI->add(txtTime);
    gameUI->add(txtScore);
    gameUI->add(txtFPS);

    UIRectangle* staticBackground = new UIRectangle(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 100, 100, 100);
    // gameOverScreenBackground->setOpacity(150);
    UIText* txtGameOver = new UIText(renderer, 150, 200, 100, 50, "GAME OVER!");
    UIButton* btnRestart = new UIButton(renderer, 150, 300, 200, 30, "Restart");
    btnRestart->setOnClick([&]{reset();});
    UIButton* btnMenu = new UIButton(renderer, 400, 300, 200, 30, "Menu");
    btnMenu->setOnClick([&]{gameState = MAIN_MENU;});

    deathScreenUI->add(staticBackground);
    deathScreenUI->add(txtGameOver);
    deathScreenUI->add(btnRestart);
    deathScreenUI->add(btnMenu);

    UIText* txtYouWin = new UIText(renderer, 200, 200, 100, 50, "YOU WIN!");
    UITextField* txtFieldName = new UITextField(renderer, SCREEN_WIDTH/2 - 150, 300, 300, 26);
    UIButton* btnSaveScore = new UIButton(renderer, 200, 300, 150, 30, "SAVE SCORE");
    btnSaveScore->setOnClick([&]{
        printf("%s\n", txtFieldName->getText());
        Score newScore = {txtFieldName->getText(), currPoints};
        addScore(&newScore);
        // printf("Name: %s; Score: %d\n", newScore.nickname, newScore.score);

        gameState = MAIN_MENU;
    });

    victoryScreenUI->add(staticBackground);
    victoryScreenUI->add(txtYouWin);
    victoryScreenUI->add(txtFieldName);
    victoryScreenUI->add(btnMenu);
    victoryScreenUI->add(btnSaveScore);

    UIText* txtTitle = new UIText(renderer, 100, 200, 100, 40, "BEAT THIS PROJECT!");
    UIButton* btnLevelChoice = new UIButton(renderer, 150, 250, 150, 25, "LEVELS");
    UIButton* btnSandbox = new UIButton(renderer, 150, 300, 150, 25, "SANDBOX");
    btnSandbox->setOnClick([&]{
        gameState = IN_GAME;
        reset();    
    });
    UIButton* btnRankings = new UIButton(renderer, 150, 350, 250, 25, "SHOW RANKING");
    btnRankings->setOnClick([&]{gameState = SHOW_RANKINGS;});
    UIButton* btnQuit = new UIButton(renderer, 150, 400, 150, 25, "QUIT");
    btnQuit->setOnClick([&]{quit = true;});

    mainMenuUI->add(staticBackground);
    mainMenuUI->add(txtTitle);
    mainMenuUI->add(btnLevelChoice);
    mainMenuUI->add(btnSandbox);
    mainMenuUI->add(btnRankings);
    mainMenuUI->add(btnQuit);


}

void Game::reset()
{
    gameState = IN_GAME;

    worldTime = 0;
    currPoints = 0;
    currCombo = 0;

    camera.x = 0;
    camera.y = 0;
    
    player->setX(PLAYER_START_X);
    player->setY(PLAYER_START_Y);
    player->resetCurrHp();

    enemyManager->clearEnemies();
    enemyManager->spawnEnemy(100, SCREEN_HEIGHT - 20);


    printf("new game\n");
}

int Game::mainLoop()
{
    t1 = SDL_GetTicks();
    while(!quit) 
    {
        t2 = SDL_GetTicks();
        deltaTimeMs = t2 - t1;
        deltaTimeS = deltaTimeMs * 0.001;
        t1 = t2;

        handleInput();
        deactivateUI();
        switch (gameState)
        {
            case IN_GAME:
                // printf("IN_GAME\n");
                gameUI->setActive(true);
                gameUpdate();
                break;
            
            case PAUSED:
                // printf("PAUSED\n");
                

                break;

            case GAME_WON:
                // printf("GAME_WON\n");
                victoryScreenUI->setActive(true);
                victoryScreenUI->update();
                break;

            case GAME_LOST:
                // printf("GAME_LOST\n");
                deathScreenUI->setActive(true);
                deathScreenUI->update();
                break;

            case MAIN_MENU:
                // printf("MAIN_MENU\n");
                mainMenuUI->setActive(true);
                mainMenuUI->update();
                break;

            case SHOW_RANKINGS:
                // printf("SHOW_RANKINGS\n");
                rankingUI->setActive(true);
                rankingUI->update();
                break;

            default:
                break;
        }
        handleRendering();
        // printf("frame\n");
        // printf("Game state: %d\n", gameState);
    }
    if(quit) return RESULT_QUIT;
    
    return RESULT_SUCCESS;
}
void Game::handleRendering()
{
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
    renderManager->renderEverything();

    if(gameState == PAUSED)
    {
        UIText pauseText(renderer, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 10, 100, 20, "PAUSED");
        pauseText.setColor(0, 0, 0);
        pauseText.render();
    }
    SDL_RenderPresent(renderer);
}
void Game::cleanUp()
{
    // SDL_FreeSurface(charset);
    
    delete player;
    delete background;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
void Game::handleInput()
{
    while(SDL_PollEvent(&event)) 
    {
        switch(event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                if(gameState == IN_GAME && event.key.keysym.sym == KEY_NEW_GAME) reset();
                else if(event.key.keysym.sym == KEY_QUIT) quit = true;
                else if(event.key.keysym.sym == KEY_PAUSE) 
                {
                    if(gameState == IN_GAME) gameState = PAUSED;
                    else if(gameState == PAUSED) gameState = IN_GAME;
                }
                break;
            }
        if(gameState == IN_GAME) player->handleInput(&event);
        gameUI->handleInput(&event);
        deathScreenUI->handleInput(&event);
        victoryScreenUI->handleInput(&event); 
        mainMenuUI->handleInput(&event);
    }
}

void Game::gameUpdate()
{
    updatesTimer += deltaTimeS;
    worldTime += deltaTimeS;
    fpsTimer += deltaTimeS;
    if(fpsTimer > 0.5) 
    {
        fps = frames * 2;
        frames = 0;
        fpsTimer -= 0.5;
    }
    
    while(updatesTimer >= FIXED_DELTA_TIME_S)
    {
        fixedUpdate();
        updatesTimer -= FIXED_DELTA_TIME_S;
    }

    player->handleAttacking(deltaTimeMs);
    handlePoints();

    if(player->isDead()) gameState = GAME_LOST;
    else if(enemyManager->isEnemiesListEmpty()) gameState = GAME_WON;

    gameUI->update();

    adjustCamera();
    
    frames++;

    if(FRAME_DELAY > deltaTimeS)
    {
        SDL_Delay(FRAME_DELAY - deltaTimeS);
    }
}

void Game::fixedUpdate()
{
    player->move(FIXED_DELTA_TIME_S);
    enemyManager->handleEnemiesMovement(FIXED_DELTA_TIME_S);

    player->handleCollisions(&floor);
    enemyManager->handleEnemiesCollisions();
    // collisionManager->handleAllCollisions();
}

void Game::handlePoints()
{
    comboDurationMs -= deltaTimeMs;
    int hitEnemies = 0;
    if(player->getWantsToAttack()) 
        hitEnemies = enemyManager->handlePlayerAttack(player->getX(), player->getY(), player->getFacingDirection(), player->attack());

    if(hitEnemies > 0) 
    {
        comboDurationMs = COMBO_DURATION_MS;
        currCombo += hitEnemies;
    }
    if(comboDurationMs <= 0) 
    {
        comboDurationMs = 0;
        currCombo = 0;
    }
    
    int pointsToAdd = ((2 * currCombo + hitEnemies - 1) * POINTS_FOR_HIT) * hitEnemies / 2;
    currPoints += pointsToAdd;
}

void Game::deactivateUI()
{
    gameUI->setActive(false);
    mainMenuUI->setActive(false);
    deathScreenUI->setActive(false);
    victoryScreenUI->setActive(false);
    rankingUI->setActive(false);
}

void Game::adjustCamera()
{
    if(player->getX() - camera.x < PLAYER_X_TO_MOVE_CAMERA) camera.x = player->getX() - PLAYER_X_TO_MOVE_CAMERA;
    else if(player->getX() - camera.x > SCREEN_WIDTH - PLAYER_X_TO_MOVE_CAMERA) camera.x = player->getX() - (SCREEN_WIDTH - PLAYER_X_TO_MOVE_CAMERA);
    
    if(camera.x < 0) camera.x = 0;
    else if(camera.x > BACKGROUND_SPRITE_WIDTH - camera.w) camera.x = BACKGROUND_SPRITE_WIDTH - camera.w;
}