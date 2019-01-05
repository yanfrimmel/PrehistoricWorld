#ifndef GRID_H   /* Include guard */
#define GRID_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "utils.h"
#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define IMAGE_PIXELS (32)
#define GRID_WIDTH (WINDOW_WIDTH/IMAGE_PIXELS)
#define GRID_HEIGHT (WINDOW_HEIGHT/IMAGE_PIXELS)
//thats the way to define enum in c, hideous.
typedef enum TILE_TYPE {
    soil = 0,
    grass = 1,
    water = 2
} TILE_TYPE;

struct Tile {
    RectAndSurface rect_and_surface;
    TILE_TYPE tile_type;
};
typedef struct Tile Tile;

struct Grid {
    // x, y, width, height
    SDL_Rect rect;

    // Number of cells over the x axis
    int xTiles;
    // Number of cells over the y axis
    int yTiles;

    // Matrix of Tiles
    Tile tiles[GRID_WIDTH][GRID_HEIGHT];
};
typedef struct Grid Grid;

Grid *grid;
SDL_Surface* tile_surfaces;
int number_of_tile_surfaces;

int grid_adjustSize(Grid *grid);
void grid_alignCenter(Grid *grid, int screenWidth, int screenHeight);
Grid grid_init(SDL_Renderer* renderer, int screenWidth, int screenHeight);
void grid_init_tile(SDL_Renderer* renderer, Grid *grid, Tile *tile, int i, int j, TILE_TYPE type);
void grid_render(SDL_Surface* screen, Grid *grid, SDL_Renderer *renderer);
void grid_render_tile(SDL_Surface* screen, Tile *tile, SDL_Renderer *renderer);
void destroy_grid_surfaces();
void destroy_grid();
RectAndSurface get_rect_and_surface_by_tile_type(int tile_type);

#endif