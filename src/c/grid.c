#include "grid.h"
#include "utils.h"
// #include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
// #include <pthread.h> 

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
    // grid->rect.x = (screenWidth - grid->rect.w) / 2;
    // grid->rect.y = (screenHeight - grid->rect.h) / 2;
    grid->rect.x = screenWidth;
    grid->rect.y = screenHeight;
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
            grid_init_tile(renderer, grid,
                          &(grid->tiles[i][j]),
                          i, j, soil);
        }
    }

    return true;
}



void grid_init_tile(SDL_Renderer* renderer, Grid *grid, Tile *tile, int i, int j, TILE_TYPE type) {
    RecAndTexture rect_and_texture = load_image_and_get_sprite_rect(renderer, get_image_path_string_by_tile_type(tile->tile_type)); 
    tile->rect_and_texture = rect_and_texture;
    // tile->rect_and_texture.rect.w = (grid->rect.w ) / grid->xTiles;
    // tile->rect_and_texture.rect.h = (grid->rect.h ) / grid->yTiles;
    tile->rect_and_texture.rect.x = tile->rect_and_texture.rect.w * i;
    tile->rect_and_texture.rect.y = tile->rect_and_texture.rect.w * j;
    tile->tile_type = type;
}

void grid_render(Grid *grid, SDL_Renderer *renderer) {
    // Render all tiles
    printf("grid_render %d\n", grid->xTiles);
    for(int i = 0; i < grid->xTiles; ++i) {
        for(int j = 0; j < grid->yTiles; ++j) {
            printf("grid_render %d, %d\n", i, j);
            grid_render_tile(&(grid->tiles[i][j]), renderer);
        }
    }
}

void grid_render_tile(Tile *tile, SDL_Renderer *renderer) {
    // Render filled tile
    RecAndTexture* rect_and_texture = &tile->rect_and_texture;
    SDL_RenderCopy(renderer, rect_and_texture->texture, NULL, &(rect_and_texture->rect)) ;
    // SDL_RenderPresent(renderer);
}