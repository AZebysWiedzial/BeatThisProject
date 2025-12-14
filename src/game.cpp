#include<math.h>
#include<stdio.h>
#include<string.h>

#include "game.h"
#include "graphics.h"

Game::Game()
{
    frames = 0;
    fpsTimer = 0;
    fps = 0;
    quit = 0;
    worldTime = 0;
    etiSpeed = 1;
    // screen = nullptr;
    charset = nullptr;
    window = nullptr;
    renderer = nullptr;
    // scrtex = nullptr;
    backgroundSprite = nullptr;
    backgroundTexture = nullptr;
}

int Game::init()
{
    printf("wyjscie printfa trafia do tego okienka\n");
    printf("printf output goes here\n");

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return RESULT_ERROR;
    }

    // tryb pe�noekranowy / fullscreen mode
    //	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
    //	                                 &window, &renderer);

    rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    if(rc != 0) 
    {
        SDL_Quit();
        printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
        return RESULT_ERROR;
    }
    uiManager = new UI(renderer);
    uiManager->initUI();
    player = new Player(renderer, 0, 0, 30, 30);

    backgroundSprite = SDL_LoadBMP("../assets/background.bmp");
    if(backgroundSprite == NULL) 
    {
        printf("SDL_LoadBMP(background.bmp) error: %s\n", SDL_GetError());
        cleanUp();
        return RESULT_ERROR;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSprite);


    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2017");


    // screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
                                    // 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    //create a blue surface

    // scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_ShowCursor(SDL_DISABLE);

    // wczytanie obrazka cs8x8.bmp
    // charset = SDL_LoadBMP("./cs8x8.bmp");

    // if(charset == NULL) {
    //     printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
    //     cleanUp();
    //     return RESULT_ERROR;
    // }
    // SDL_SetColorKey(charset, true, 0x000000);


    return RESULT_SUCCESS;
}



int Game::gameLoop()
{
    char text[128];

    t1 = SDL_GetTicks();

    while(!quit) {
    t2 = SDL_GetTicks();

    // w tym momencie t2-t1 to czas w milisekundach,
    // jaki uplyna� od ostatniego narysowania ekranu
    // delta to ten sam czas w sekundach
    // here t2-t1 is the time in milliseconds since
    // the last screen was drawn
    // delta is the same time in seconds
    delta = (t2 - t1) * 0.001;
    t1 = t2;

    worldTime += delta;

    // distance += etiSpeed * delta;

    fpsTimer += delta;
    if(fpsTimer > 0.5) {
        fps = frames * 2;
        frames = 0;
        fpsTimer -= 0.5;
        }

    // // tekst informacyjny / info text
    // DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski);
    // //            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
    // sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
    // DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
    // //	      "Esc - exit, \030 - faster, \031 - slower"
    // sprintf(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
    // DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);
   
        while(SDL_PollEvent(&event)) {
        player->handleEvents(event);

        switch(event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            }
        }

    SDL_Rect backgroundSrcRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect backgroundDestRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, &backgroundSrcRect, &backgroundDestRect);

    player->move();
    player->render();

    uiManager->Render();

    SDL_RenderPresent(renderer);

    // obs�uga zdarze� (o ile jakie� zasz�y) / handling of events (if there were any)
    
    frames++;
    }
    return RESULT_SUCCESS;
}
void Game::render()
{

}
void Game::cleanUp()
{
    SDL_FreeSurface(charset);
    // SDL_FreeSurface(screen);
    // SDL_DestroyTexture(scrtex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
