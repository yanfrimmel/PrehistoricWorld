#ifndef GRAPHICAL_API_H   /* Include guard */
#define GRAPHICAL_API_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define GAME_NAME ("Prehistoric World")
#
// speed in pixels/second
#define SPEED (300)
#define HELLO_IMAGE_STRING ("../resources/hello.png")

int initialize_sdl(void);
SDL_Window* createWindow(int window_width, int widow_height, int flags);  /* An example function declaration */
SDL_Renderer* createRenderer(SDL_Window* window);
void gameLoop(SDL_Window* window , SDL_Renderer* renderer , int window_width, int window_height);
void quit_sdl(void** textures, void** renderers, void** window);

#endif 