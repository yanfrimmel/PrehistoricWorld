#ifndef GAME_H   /* Include guard */
#define GAME_H

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_error.h>

#include "grid.h"
#include "utils.h"
#include "animal.h"

#define GAME_NAME ("Prehistoric World")
#define SDL_WINDOW_FULLSCREEN (0x00000001) //1 = yes
#define SPEED (500)
#define FPS (60)

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* screen;

int initialize_sdl(void);
SDL_Window* create_window(int flags);  /* An example function declaration */
SDL_Renderer* create_renderer();
void play();
void quit_sdl();
void fps_counter_loop(Uint32* startclock,  Uint32* deltaclock,  Uint32* currentFPS);

#endif 