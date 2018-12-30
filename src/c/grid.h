#ifndef GRID_H   /* Include guard */
#define GRID_H
#include <stdbool.h>
#include <SDL2/SDL.h>

enum TILE_TYPE {
    soil = 0,
    grass = 1,
    water = 2
};

struct Cell {
    SDL_Rect rect;
    TILE_TYPE type;
};
typedef struct Cell Cell;

struct Grid
{
    // x, y, width, height
    SDL_Rect rect;

    // Grid background color
    SDL_Color backgroundColor;

    // Grid border thickness and color
    unsigned int border;
    SDL_Color borderColor;

    // Number of cells over the x axis
    int xCells;
    // Number of cells over the y axis
    int yCells;

    // Matrix of Cells
    Cell cells[GRID_MAX_X_CELLS][GRID_MAX_Y_CELLS];
};
typedef struct Grid Grid;

int grid_adjustSize(Grid *grid);
void grid_alignCenter(Grid *grid, int screenWidth, int screenHeight);

bool grid_init(Grid *grid);
void grid_initCell(Grid *grid, Cell *cell, int i, int j, SDL_Color color);

void grid_render(Grid *grid, SDL_Renderer *renderer);
void grid_renderCell(Cell *cell, SDL_Renderer *renderer);

#endif