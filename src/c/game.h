#ifndef GAME_H   /* Include guard */
#define GAME_H

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "grid.h"

#include "utils.h"
#include "animal.h"
#include <SDL2/SDL_error.h>

#define GAME_NAME ("Prehistoric World")
#define SDL_WINDOW_FULLSCREEN (0x00000001) //1 = yes
#define SPEED (500)
#define FPS (60)


int initialize_sdl(void);
SDL_Window* create_window(int window_width, int widow_height, int flags);  /* An example function declaration */
SDL_Renderer* create_renderer(SDL_Window* window);
void play(SDL_Window* window , SDL_Renderer* renderer , int window_width, int window_height);
void quit_sdl(void** renderers, void** window, SDL_Surface* screen);
void fps_counter_loop(Uint32* startclock,  Uint32* deltaclock,  Uint32* currentFPS);

#endif 