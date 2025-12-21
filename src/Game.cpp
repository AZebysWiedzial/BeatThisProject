#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>

#include "Game.h"
#include "graphics.h"

Game::Game()
{
    frames = 0;
    fpsTimer = 0;
    fps = 0;
    quit = false;
    worldTime = 0;
    // screen = nullptr;
    charset = nullptr;
    window = nullptr;
    renderer = nullptr;
    // scrtex = nullptr;
    background = nullptr;
    
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
    uiManager = new UI(renderer);
    player = new Player(renderer, &camera, PLAYER_START_X, PLAYER_START_Y, 30, 30, 30, 30);
    uiManager->initUI();
    background = new WorldRenderable(renderer, &camera, 0.0, 0.0, BACKGROUND_SPRITE_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
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

    Renderable* uiBackground = new Renderable(renderer, 0, 0, 640, 50, 640, 50);
    uiBackground->setRectangleAsSprite(100, 100, 100);

    txtTime = new Renderable(renderer, 10, 10, 100, 100, 80, 40);
    uiManager->add(uiBackground);
    uiManager->add(txtTime);


    return RESULT_SUCCESS;
}

void Game::reset()
{
    worldTime = 0;

    camera.x = 0;
    camera.y = 0;
    
    player->setX(PLAYER_START_X);
    player->setY(PLAYER_START_Y);

    printf("new game\n");
}

int Game::gameLoop()
{
    // char text[128];

    t1 = SDL_GetTicks();

    while(!quit) {
    t2 = SDL_GetTicks();

    // here t2-t1 is the time in milliseconds since
    // the last screen was drawn
    // delta is the same time in seconds
    delta = (t2 - t1) * 0.001;
    t1 = t2;

    worldTime += delta;

    fpsTimer += delta;
    if(fpsTimer > 0.5) 
    {
        fps = frames * 2;
        frames = 0;
        fpsTimer -= 0.5;
    }
   
    handleEvents();

    player->move(delta);
    player->handleCollisions(&floor);

    updateUI();
    
    handleRendering();

    frames++;
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

    // printf("Camera: x - %d; y - %d\n", camera.x, camera.y);

    background->render();
    player->render();
    uiManager->render();

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
void Game::handleEvents()
{
    while(SDL_PollEvent(&event)) 
        {
            switch(event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == KEY_NEW_GAME) reset();
                    else if(event.key.keysym.sym == KEY_QUIT) quit = true;
                    break;
                }
            player->handleEvents(event);
        }
}
void Game::updateUI()
{
    sprintf(textBuffer, "Time: %.1lf s  fps: %.0lf", worldTime, fps);
    txtTime->DrawText(textBuffer, charset, 1.5);
    
}