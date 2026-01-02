#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>

#include "Game.h"
#include "graphics.h"
#include "UIElement.h"
#include "UIText.h"
#include "UITextDisplay.h"
#include "UIRectangle.h"
#include "UIRectangleDisplay.h"
#include "UITextField.h"

Game::Game()
{
    frames = 0;
    fpsTimer = 0;
    fps = 0;
    quit = false;
    isPaused = false;
    isGameOver = false;
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


    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    floor = {0, SCREEN_HEIGHT - FLOOR_HEIGHT, BACKGROUND_SPRITE_WIDTH, FLOOR_HEIGHT};

    gameUI = new UI(renderer, true);
    deathScreenUI = new UI(renderer, false);

    enemyManager = new EnemyManager(renderer, &camera);
    player = new Player(renderer, &camera, PLAYER_START_X, PLAYER_START_Y, 100, 30, 30, 30, 30);

    background = new WorldRenderable(renderer, &camera, 0.0, 0.0, BACKGROUND_SPRITE_WIDTH, SCREEN_HEIGHT, BACKGROUND_SPRITE_WIDTH, SCREEN_HEIGHT);
    renderManager = new RenderManager(renderer, enemyManager->getEnemiesList(), player, background, gameUI, deathScreenUI);
    // collisionManager = new CollisionManager(player, enemyManager->getEnemiesList(), &floor);





    enemyManager->spawnEnemy(100, SCREEN_HEIGHT - 20);

    
    if(background->setSprite("../assets/background.bmp") == 1)
    {
        printf("SDL_LoadBMP(background.bmp) error: %s\n", SDL_GetError());
        cleanUp();
        return RESULT_ERROR;
    }
    charset = SDL_LoadBMP("../assets/cs8x8.bmp");
    if(charset == nullptr)
    {
        printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
        cleanUp();
        return RESULT_ERROR;
    }
	SDL_SetColorKey(charset, true, SDL_MapRGB(charset->format, 0, 0, 0));

    UIRectangle* uiBackground = new UIRectangle(renderer, 0, 0, 640, 50, 100, 100, 100);
    UIRectangleDisplay* playerHpBar = new UIRectangleDisplay(renderer, 10, 10, PLAYER_HP_BAR_LENGTH, 20, 255, 0, 0, player->getHp());
    UITextDisplay* txtTime = new UITextDisplay(renderer, 300, 10, 100, 16, "Time:", &worldTime);
    UITextDisplay* txtFPS = new UITextDisplay(renderer, 550, 10, 100, 16, "FPS:", &fps);

    gameUI->add(uiBackground);
    gameUI->add(playerHpBar);
    gameUI->add(txtTime);
    gameUI->add(txtFPS);

    UIRectangle* deathScreenBackground = new UIRectangle(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 100, 100, 100);
    deathScreenBackground->setOpacity(150);
    UITextField* textFieldName = new UITextField(renderer, 100, 100, 100, 16);

    deathScreenUI->add(deathScreenBackground);
    deathScreenUI->add(textFieldName);

    return RESULT_SUCCESS;
}

void Game::reset()
{
    gameUI->setActive(true);
    deathScreenUI->setActive(false);

    worldTime = 0;

    camera.x = 0;
    camera.y = 0;
    
    player->setX(PLAYER_START_X);
    player->setY(PLAYER_START_Y);

    enemyManager->clearEnemies();
    enemyManager->spawnEnemy(100, SCREEN_HEIGHT - 20);


    printf("new game\n");
}

int Game::gameLoop()
{
    // char text[128];

    t1 = SDL_GetTicks();

    while(!quit) 
    {
        t2 = SDL_GetTicks();

        deltaTimeMs = t2 - t1;
        deltaTimeS = deltaTimeMs * 0.001;
        t1 = t2;

        handleInput();   
        if(isPaused)
        {
            handleRendering();
            // printf("Game paused\n");
            continue;
        }
        else if(isGameOver)
        {
            gameUI->setActive(false);
            deathScreenUI->setActive(true);
            deathScreenUI->update();
            handleRendering();
            // printf("Game over\n");
            continue;
        } 

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
            update();
            updatesTimer -= FIXED_DELTA_TIME_S;
        }

        player->handleAttacking(deltaTimeMs);

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

        if(player->isDead()) isGameOver = true;
        
        gameUI->update();
        
        handleRendering();

        

        frames++;

        if(FRAME_DELAY > deltaTimeS)
        {
            SDL_Delay(FRAME_DELAY - deltaTimeS);
        }
    

    }
    if(quit) return RESULT_QUIT;
    
    return RESULT_SUCCESS;
}
void Game::handleRendering()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

    if(player->getX() - camera.x < PLAYER_X_TO_MOVE_CAMERA) camera.x = player->getX() - PLAYER_X_TO_MOVE_CAMERA;
    else if(player->getX() - camera.x > SCREEN_WIDTH - PLAYER_X_TO_MOVE_CAMERA) camera.x = player->getX() - (SCREEN_WIDTH - PLAYER_X_TO_MOVE_CAMERA);
    
    if(camera.x < 0) camera.x = 0;
    else if(camera.x > BACKGROUND_SPRITE_WIDTH - camera.w) camera.x = BACKGROUND_SPRITE_WIDTH - camera.w;

    renderManager->renderEverything();

    if(isPaused)
    {
        UIText pauseText(renderer, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 10, 100, 20, "PAUSED");
        pauseText.setColor(0, 0, 0);
        pauseText.render();
    }
    

    SDL_RenderPresent(renderer);
}
void Game::cleanUp()
{
    SDL_FreeSurface(charset);
    
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
                if(!isPaused && !isGameOver && event.key.keysym.sym == KEY_NEW_GAME) reset();
                else if(event.key.keysym.sym == KEY_QUIT) quit = true;
                else if(!isGameOver && event.key.keysym.sym == KEY_PAUSE) isPaused = !isPaused;
                break;
            }
        if(!isPaused && !isGameOver) player->handleInput(&event);
        gameUI->handleInput(&event);
        deathScreenUI->handleInput(&event);
    }
}


void Game::update()
{
    player->move(FIXED_DELTA_TIME_S);
    enemyManager->handleEnemiesMovement(FIXED_DELTA_TIME_S);

    player->handleCollisions(&floor);
    enemyManager->handleEnemiesCollisions();
    // collisionManager->handleAllCollisions();
}
