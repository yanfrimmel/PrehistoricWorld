#include "grid.h"
#include "utils.h"


int grid_adjustSize(Grid *grid)
{
    if(!grid->rect.w || !grid->rect.h || !grid->xTiles || !grid->yTiles)
    {
        fprintf(stderr, "Grid dimensions or number of tiles not initialised !\n");
        return false;
    }

    // Init rect
   
    grid->rect.w -= grid->rect.w  % grid->xTiles;
    grid->rect.h -= grid->rect.h  % grid->yTiles;

    return true;
}

void grid_alignCenter(Grid *grid, int screenWidth, int screenHeight)
{
    grid->rect.x = (screenWidth - grid->rect.w) / 2;
    grid->rect.y = (screenHeight - grid->rect.h) / 2;
}

bool grid_init(SDL_Renderer* renderer, Grid *grid) {
    if(!grid->rect.w || !grid->rect.h || !grid->xTiles || !grid->yTiles) {
        fprintf(stderr, "Grid dimensions or number of tiles not initialised !\n");
        return false;
    }

    if(grid->xTiles > GRID_MAX_X_CELLS || grid->yTiles > GRID_MAX_Y_CELLS) {
        fprintf(stderr, "Grid number of tiles (%d,%d) is greater than (%d,%d) !\n",
                grid->xTiles, grid->yTiles,
                GRID_MAX_X_CELLS, GRID_MAX_Y_CELLS);
        return false;
    }

    // Init all tiles
    for(int i = 0; i < grid->xTiles; ++i) {
        for(int j = 0; j < grid->yTiles; ++j) {
            grid_initTile(renderer, grid,
                          &(grid->tiles[i][j]),
                          i, j, soil);
        }
    }

    return true;
}



void grid_initTile(SDL_Renderer* renderer, Grid *grid, Tile *tile, int i, int j, TILE_TYPE type) {
    tile->rect.w = (grid->rect.w ) / grid->xTiles;
    tile->rect.h = (grid->rect.h ) / grid->yTiles;
    
    tile->tile_type = type;
}

void grid_render(Grid *grid, SDL_Renderer *renderer) {
    // Render all tiles
    for(int i = 0; i < grid->xTiles; ++i) {
        for(int j = 0; j < grid->yTiles; ++j) {
            grid_renderTile(&(grid->tiles[i][j]), renderer);
        }
    }
}

void grid_renderTile(Tile *tile, SDL_Renderer *renderer) {
    // Render filled tile
    RecAndTexture rect_and_texture = load_image_and_get_sprite_rect(renderer, get_image_path_string_by_tile_type(type)); 
    SDL_RenderCopy(renderer, rect_and_texture.texture, NULL, &tile->rect);
    SDL_RenderPresent(renderer);(renderer, &(tile->rect));
}