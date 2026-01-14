#include "Scenes/LevelScene.h"
#include "constants.h"

#include "UI/UIButton.h"
#include "UI/UIRectangle.h"
#include "UI/UIText.h"
#include "UI/UIRectangleDisplay.h"
#include "UI/UITextDisplay.h"
#include "UI/UITextField.h"

#include "filesFuncs.h"

LevelScene::LevelScene(SDL_Renderer* renderer) : Scene(renderer)
{
    frames = 0;
    fpsTimer = 0;
    fps = 0;
    worldTime = 0;
    updatesTimer = 0;
    currPoints = 0;
    currCombo = 0;
    this->renderer = renderer;
    background = nullptr;
    enemyManager = nullptr;
}

void LevelScene::init()
{
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    floor = {0, SCREEN_HEIGHT - FLOOR_HEIGHT, BACKGROUND_SPRITE_WIDTH, FLOOR_HEIGHT};

    gameUI = new UI(renderer, false);
    deathScreenUI = new UI(renderer, false);
    victoryScreenUI = new UI(renderer, false);

    enemyManager = new EnemyManager(renderer, &camera);
    player = new Player(renderer, &camera, PLAYER_START_X, PLAYER_START_Y, 100, 30, 30, 30, 30);

    background = new WorldRenderable(renderer, &camera, 0.0, 0.0, BACKGROUND_SPRITE_WIDTH, SCREEN_HEIGHT, BACKGROUND_SPRITE_WIDTH, SCREEN_HEIGHT);
    if(background->setSprite("../assets/background.bmp") == 1)
    {
        printf("SDL_LoadBMP(background.bmp) error: %s\n", SDL_GetError());
        // cleanUp();
        // return RESULT_ERROR;
    }
    // else printf("ok\n");

    enemyManager->spawnEnemy(300, SCREEN_HEIGHT - 50);


    setupUI();
    gameState = IN_GAME;
}
void LevelScene::update(double deltaTimeMs)
{
    switch (gameState)
    {
    case GAME_WON:
        printf("GAME_WON\n");
        gameUI->setActive(false);
        victoryScreenUI->setActive(true);
        break;

    case GAME_LOST:
        printf("GAME_LOST\n");
        gameUI->setActive(false);
        deathScreenUI->setActive(true);
        break;

    case PAUSED:
        printf("PAUSED\n");
        gameUI->setActive(false);
        //pauseUI->setActive(true);
        break;

    case IN_GAME:
        printf("IN_GAME\n");
        gameUI->setActive(true);
        deathScreenUI->setVisible(false);
        victoryScreenUI->setVisible(false);

        updatesTimer += deltaTimeMs * 0.001;
        worldTime += deltaTimeMs * 0.001;
        fpsTimer += deltaTimeMs * 0.001;
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
        handlePoints(deltaTimeMs);

        if(player->isDead()) gameState = GAME_LOST;
        else if(enemyManager->isEnemiesListEmpty()) gameState = GAME_WON;

        gameUI->update();

        adjustCamera();
        
        frames++;

        if(FRAME_DELAY > deltaTimeMs * 0.001)
        {
            SDL_Delay(FRAME_DELAY - deltaTimeMs * 0.001);
        }
        break;
    
    default:
        break;
    }
    
}
void LevelScene::render()
{
    background->render();
    renderGameEntities();
    if(gameUI->getIsVisible()) gameUI->render();
    if(deathScreenUI->getIsVisible()) deathScreenUI->render();
    if(victoryScreenUI->getIsVisible()) victoryScreenUI->render();
}
void LevelScene::handleEvents(SDL_Event* event)
{
    switch(event->type) {
        case SDL_KEYDOWN:
            if(gameState == IN_GAME && event->key.keysym.sym == KEY_NEW_GAME) reset();
            else if(event->key.keysym.sym == KEY_PAUSE) 
            {
                if(gameState == IN_GAME) gameState = PAUSED;
                else if(gameState == PAUSED) gameState = IN_GAME;
            }
            break;
        default:
            break;
    }
    if(gameState == IN_GAME) 
    {
        player->handleInput(event);
        // printf(" - player events");
    }
    
    gameUI->handleInput(event);
    deathScreenUI->handleInput(event);
    victoryScreenUI->handleInput(event); 
}

void LevelScene::fixedUpdate()
{
    player->move(FIXED_DELTA_TIME_S);
    enemyManager->handleEnemiesMovement(FIXED_DELTA_TIME_S);

    player->handleCollisions(&floor);
    enemyManager->handleEnemiesCollisions();
}

void LevelScene::handlePoints(double deltaTimeMs)
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

void LevelScene::adjustCamera()
{
    if(player->getX() - camera.x < PLAYER_X_TO_MOVE_CAMERA) camera.x = player->getX() - PLAYER_X_TO_MOVE_CAMERA;
    else if(player->getX() - camera.x > SCREEN_WIDTH - PLAYER_X_TO_MOVE_CAMERA) camera.x = player->getX() - (SCREEN_WIDTH - PLAYER_X_TO_MOVE_CAMERA);
    
    if(camera.x < 0) camera.x = 0;
    else if(camera.x > BACKGROUND_SPRITE_WIDTH - camera.w) camera.x = BACKGROUND_SPRITE_WIDTH - camera.w;
}

void LevelScene::setupUI()
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
    btnMenu->setOnClick([&]{sceneToSwitch = MAIN_MENU;});

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

        sceneToSwitch = MAIN_MENU;
    });

    victoryScreenUI->add(staticBackground);
    victoryScreenUI->add(txtYouWin);
    victoryScreenUI->add(txtFieldName);
    victoryScreenUI->add(btnMenu);
    victoryScreenUI->add(btnSaveScore);
}

void LevelScene::reset()
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

void LevelScene::renderGameEntities()
{
    bool hasRenderedPlayer = false;
    LinkedList<Enemy*>* enemies = enemyManager->getEnemiesList();
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

void LevelScene::onLoad()
{
    reset();
}