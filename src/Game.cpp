#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>

#include "constants.h"

#include "Game.h"

Game::Game()
{
    frames = 0;
    quit = false;
    window = nullptr;
    renderer = nullptr;
}

int Game::init()
{
    if(setupSDL() == RESULT_ERROR) return RESULT_ERROR;

    gameState = MAIN_MENU;

    level = new LevelScene(renderer);
    mainMenu = new MainMenuScene(renderer);
    currScene = mainMenu;

    level->init();
    mainMenu->init();

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

int Game::mainLoop()
{
    t1 = SDL_GetTicks();
    while(!quit) 
    {
        t2 = SDL_GetTicks();
        deltaTimeMs = t2 - t1;
        deltaTimeS = deltaTimeMs * 0.001;
        t1 = t2;

        adjustScene();

        handleEvents();
        currScene->update(deltaTimeMs);
        handleRendering();
    }
    if(quit) return RESULT_QUIT;
    
    return RESULT_SUCCESS;
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
                if(event.key.keysym.sym == KEY_QUIT) quit = true;
                break;
            }
        currScene->handleEvents(&event);
    }
}
void Game::handleRendering()
{
	SDL_RenderClear(renderer);
    // renderManager->renderEverything();
    currScene->render();
    
    SDL_RenderPresent(renderer);
}
void Game::cleanUp()
{
    // SDL_FreeSurface(charset);
    
    // delete player;
    // delete background;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Game::adjustScene()
{
    Scene::SceneToSwitch newScene = currScene->getSceneToSwitch();
    currScene->setSceneToSwitch(Scene::NONE);
    switch(newScene)
    {
        case Scene::LEVEL:
            currScene = level;
            break;

        case Scene::MAIN_MENU:
            currScene = mainMenu;
            break;
        
        case Scene::QUIT:
            quit = true;
            break;

        default:
            break;
    }
    if(newScene != Scene::NONE && newScene != Scene::QUIT) currScene->onLoad();
} 