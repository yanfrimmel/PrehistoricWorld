#include "game.h"

int initializeSdl(void) {
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    return 0; 
}

SDL_Window* createWindow(int flags) {

    SDL_Window* window = SDL_CreateWindow(GAME_NAME,
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 
                                       flags);
    if (!window) {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return NULL;
    }
    return window;
}

SDL_Renderer* createRenderer() { 
    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED |
                          SDL_RENDERER_PRESENTVSYNC |
                          SDL_RENDERER_TARGETTEXTURE;
                          
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);
    if (!renderer) {
      printf("error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(window);
      SDL_Quit();
      return NULL;
    }

    return renderer;
}

void fpsCounterLoop(Uint32* startclock,  Uint32* deltaclock,  Uint32* currentFPS) {
    *deltaclock = SDL_GetTicks() - *startclock;
    if ( *deltaclock != 0 ) {
        *currentFPS = 1000 / *deltaclock;
         printf("FPS:%d\n",*currentFPS);
    }

}

void play() {
    int closeRequested = 0;
    printf("Pre initPlayer \n");
    Animal humanPlayer = initAnimal((WINDOW_WIDTH - 32) / 2, (WINDOW_HEIGHT - 32) / 2, human, male);
     SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, &humanPlayer.rectAndSurface.surface);
    printf("Pre gridInit \n");
    Grid grid = gridInit(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    printf("Pre gameLoop while\n");
    //for FPS counter
    Uint32 startclock = 0;
    Uint32 deltaclock = 0;
    Uint32 currentFPS = 0;
    int mouseX, mouseY, buttons;
    int frameRateDelay = 1000.0f/FPS;
    while (!closeRequested) {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                closeRequested = 1;
                printf("closeRequested! quiting\n");
            }
        }

        // get cursor position relative to window
       
        buttons = SDL_GetMouseState(&mouseX, &mouseY);
    
        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            humanPlayer.toTarget.distance = 
            sqrt(humanPlayer.toTarget.deltaX * humanPlayer.toTarget.deltaX + 
            humanPlayer.toTarget.deltaY * humanPlayer.toTarget.deltaY);

            humanPlayer.toTarget.targetX = mouseX - humanPlayer.rectAndSurface.rect.w / 2;
            humanPlayer.toTarget.targetY = mouseY - humanPlayer.rectAndSurface.rect.h / 2;
             if (humanPlayer.toTarget.distance > IMAGE_PIXELS/2) {
                humanPlayer.movement.xVel = humanPlayer.toTarget.deltaX * SPEED / humanPlayer.toTarget.distance;
                humanPlayer.movement.yVel = humanPlayer.toTarget.deltaY * SPEED / humanPlayer.toTarget.distance;
            }
        }
        
        // update positions
        humanPlayer.movement.xPos += humanPlayer.movement.xVel / FPS;
        humanPlayer.movement.yPos += humanPlayer.movement.yVel / FPS;
        humanPlayer.toTarget.deltaX = humanPlayer.toTarget.targetX - humanPlayer.movement.xPos;
        humanPlayer.toTarget.deltaY = humanPlayer.toTarget.targetY - humanPlayer.movement.yPos;
        humanPlayer.toTarget.distance = sqrt(humanPlayer.toTarget.deltaX * humanPlayer.toTarget.deltaX + humanPlayer.toTarget.deltaY * humanPlayer.toTarget.deltaY);
        // collision detection with bounds
        if (humanPlayer.movement.xPos <= 0) humanPlayer.movement.xPos = 0;
        if (humanPlayer.movement.yPos <= 0) humanPlayer.movement.yPos = 0;
        if (humanPlayer.movement.xPos >= WINDOW_WIDTH - humanPlayer.rectAndSurface.rect.w) humanPlayer.movement.xPos = WINDOW_WIDTH - humanPlayer.rectAndSurface.rect.w;
        if (humanPlayer.movement.yPos >= WINDOW_HEIGHT - humanPlayer.rectAndSurface.rect.h) humanPlayer.movement.yPos = WINDOW_HEIGHT - humanPlayer.rectAndSurface.rect.h;
        if (humanPlayer.toTarget.distance < IMAGE_PIXELS/2) {
                printf("at target\n");
                humanPlayer.movement.xVel = humanPlayer.movement.yVel = 0;
        }
        // set the positions in the struct
        humanPlayer.rectAndSurface.rect.y = (int) humanPlayer.movement.yPos;
        humanPlayer.rectAndSurface.rect.x = (int) humanPlayer.movement.xPos;

        printf("Pre gameLoop gridRender\n");
        SDL_RenderClear(renderer);
        gridRender();
       
        SDL_RenderCopy(renderer, gridTexture, NULL, NULL);
        SDL_RenderCopy(renderer, playerTexture, NULL, &humanPlayer.rectAndSurface.rect);
       
        SDL_RenderPresent(renderer);
        fpsCounterLoop(&startclock, &deltaclock, &currentFPS);
        if((FPS) < currentFPS) {
            SDL_Delay((frameRateDelay) - deltaclock);
        }
        startclock = SDL_GetTicks();
    }

    apply_functionToAllSubPointers(&humanPlayer.rectAndSurface.surface, 1, SDL_DestroyTexture);
    SDL_DestroyTexture(playerTexture);
    quitSdl();
    return;
}

void quitSdl() {
    printf("quitSdl called: quiting\n");
    SDL_DestroyTexture(gridTexture);
    destroyHumanPlayer();
    destroyGridSurfaces();
    destroyGrid();
    apply_functionToAllSubPointers(renderer, 1, SDL_DestroyRenderer);
    SDL_DestroyWindow((SDL_Renderer*)window);
    SDL_Quit();
}
