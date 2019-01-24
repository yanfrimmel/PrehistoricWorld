#ifndef GRID_H   /* Include guard */
#define GRID_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "utils.h"
#include "game.h"

#define SOIL_IMAGE_PATH ("../../resources/soil.png")
#define GRASS_IMAGE_PATH ("../../resources/grass.png")
#define STONES_IMAGE_PATH ("../../resources/stones.png")

int GRID_HEIGHT; 
int GRID_WIDTH;
//thats the way to define enum in c, hideous.
typedef enum TILE_TYPE {
    soil = 0,
    grass = 1,
    stones = 2,
    water = 3
} TILE_TYPE;

struct Tile {
    RectAndTexture RectAndTexture;
    TILE_TYPE tileType;
};
typedef struct Tile Tile;

struct Grid {
    SDL_Rect rect;
    Tile** tiles;
};
typedef struct Grid Grid;

Grid *grid;
SDL_Texture** tileTextures;
int numberOfTileImages;
bool isEntireGridIsDrawn;
SDL_Texture* gridTexture;

void gridAlignCenter();
Grid gridInit();
void gridInitTile(Tile *tile, int i, int j, TILE_TYPE type);
void gridDraw();
void gridDrawTile(Tile *tile);
void destroyGridTextures();
void destroyGrid();
void refreshGrid();
void updateTile(Tile tile, TILE_TYPE type);
RectAndTexture getRectAndTextureByTileType(int tileType);
const char* getImagePathStringByTileType(TILE_TYPE tileType);

#endif