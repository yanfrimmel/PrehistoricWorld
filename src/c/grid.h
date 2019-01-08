#ifndef GRID_H   /* Include guard */
#define GRID_H
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "utils.h"
#include "game.h"

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)
#define IMAGE_PIXELS (32)
#define GRID_WIDTH (WINDOW_WIDTH/IMAGE_PIXELS)
#define GRID_HEIGHT (WINDOW_HEIGHT/IMAGE_PIXELS)

#define SOIL_IMAGE_PATH ("../resources/soil.png")
#define GRASS_IMAGE_PATH ("../resources/grass.png")
#define STONES_IMAGE_PATH ("../resources/stones.png")
//thats the way to define enum in c, hideous.
typedef enum TILE_TYPE {
    soil = 0,
    grass = 1,
    stones = 2,
    water = 3
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

int grid_adjustSize();
void grid_alignCenter();
Grid grid_init();
void grid_init_tile(Tile *tile, int i, int j, TILE_TYPE type);
void grid_render();
void grid_render_tile(Tile *tile);
void destroy_grid_surfaces();
void destroy_grid();
RectAndSurface get_rect_and_surface_by_tile_type(int tile_type);
const char* get_image_path_string_by_tile_type(TILE_TYPE tile_type);

#endif