#include "grid.h"


int grid_adjustSize(Grid *grid)
{
    if(!grid->rect.w || !grid->rect.h || !grid->xCells || !grid->yCells)
    {
        fprintf(stderr, "Grid dimensions or number of cells not initialised !\n");
        return false;
    }

    // Init rect
   
    grid->rect.w -= (grid->rect.w - (grid->border * 2) ) % grid->xCells;
    grid->rect.h -= (grid->rect.h - (grid->border * 2) ) % grid->yCells;

    return true;
}

void grid_alignCenter(Grid *grid, int screenWidth, int screenHeight)
{
    grid->rect.x = (screenWidth - grid->rect.w) / 2;
    grid->rect.y = (screenHeight - grid->rect.h) / 2;
}

bool grid_init(Grid *grid)
{
    if(!grid->rect.w || !grid->rect.h || !grid->xCells || !grid->yCells)
    {
        fprintf(stderr, "Grid dimensions or number of cells not initialised !\n");
        return false;
    }

    if(grid->xCells > GRID_MAX_X_CELLS || grid->yCells > GRID_MAX_Y_CELLS)
    {
        fprintf(stderr, "Grid number of cells (%d,%d) is greater than (%d,%d) !\n",
                grid->xCells, grid->yCells,
                GRID_MAX_X_CELLS, GRID_MAX_Y_CELLS);
        return false;
    }

    // Init all cells
    for(int i = 0; i < grid->xCells; ++i)
    {
        for(int j = 0; j < grid->yCells; ++j)
        {
            grid_initCell(grid,
                          &(grid->cells[i][j]),
                          i, j,
                          grid->backgroundColor);
        }
    }

    return true;
}

void grid_initCell(Grid *grid, Cell *cell, int i, int j, SDL_Color color)
{
    cell->rect.w = (grid->rect.w - (grid->border * 2) ) / grid->xCells;
    cell->rect.h = (grid->rect.h - (grid->border * 2) ) / grid->yCells;
}

void grid_render(Grid *grid, SDL_Renderer *renderer)
{
    if(grid->border != 0) // Grid border thickness different from 0
    {
        // Set renderer color to draw the grid border
        SDL_SetRenderDrawColor(renderer,
                               grid->borderColor.r,
                               grid->borderColor.g,
                               grid->borderColor.b,
                               grid->borderColor.a);

        // Render grid border
        SDL_RenderFillRect(renderer, &(grid->rect));
    }

    // Render all cells
    for(int i = 0; i < grid->xCells; ++i)
    {
        for(int j = 0; j < grid->yCells; ++j)
        {
            Grid_renderCell(&(grid->cells[i][j]), renderer);
        }
    }
}

void grid_renderCell(Cell *cell, SDL_Renderer *renderer)
{
    // Render filled cell
    SDL_RenderFillRect(renderer, &(cell->rect));
}