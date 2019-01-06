#include "grid.h"
#include "utils.h"
// #include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
// #include <pthread.h> 

int grid_init_surfaces() {
    number_of_tile_surfaces = 1;
    tile_surfaces = (SDL_Surface *) malloc ( number_of_tile_surfaces * sizeof(SDL_Surface));
    if(tile_surfaces == NULL){ printf("Error - can't allocate\n"); return -1; }
    //Images load
    for(int i = 0; i < number_of_tile_surfaces; i++) { 
        tile_surfaces[i] = *IMG_Load(get_image_path_string_by_tile_type(grass)); ; 
        if(!&tile_surfaces) {
            printf("Error - can't create surface\n"); return -1; 
        }
    }
    return 1;
}  

RectAndSurface get_rect_and_surface_by_tile_type(int tile_type){
    SDL_Surface surface = tile_surfaces[tile_type];
    if(!&surface) {
            printf("Error - can't allocate\n"); return; 
    }
    SDL_Rect dest;
    SDL_GetClipRect(&surface, &dest);
    RectAndSurface rect_and_surface = {dest,surface};
    return rect_and_surface;
}

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

void grid_alignCenter(Grid *grid, int window_width, int window_height) {
    grid->rect.x = window_width;
    grid->rect.y = window_height;
}

Grid grid_init(SDL_Renderer* renderer, int window_width, int window_height) {
    grid  = (Grid *) malloc (sizeof(Grid));
    if(grid == NULL){ 
        printf("Error - can't allocate\n"); 
        return;
    }
    grid->rect.w = window_width;
    grid->rect.h = window_height;
    grid_alignCenter(grid, window_width, window_height);
    if(grid_init_surfaces() == -1) {
        fprintf(stderr, "Error: cant allocate grid surfaces! !\n");
        return;
    };
    // Set number of cells
    grid->xTiles = GRID_WIDTH;
    grid->yTiles = GRID_HEIGHT;

    if(!grid->rect.w || !grid->rect.h || !grid->xTiles || !grid->yTiles) {
        fprintf(stderr, "Grid dimensions or number of tiles not initialised !\n");
        return;
    }

    if(grid->xTiles > GRID_WIDTH || grid->yTiles > GRID_HEIGHT) {
        fprintf(stderr, "Grid number of tiles (%d,%d) is greater than (%d,%d) !\n",
                grid->xTiles, grid->yTiles,
                GRID_WIDTH, GRID_HEIGHT);
        return;
    }

    // Init all tiles
    for(int i = 0; i < grid->xTiles; ++i) {
        for(int j = 0; j < grid->yTiles; ++j) {
            grid_init_tile(renderer, grid,
                          &(grid->tiles[i][j]),
                          i, j, soil);
        }
    }
    return *grid;
}



void grid_init_tile(SDL_Renderer* renderer, Grid *grid, Tile *tile, int i, int j, TILE_TYPE type) {
    printf("grid_init_tile \n");
    tile->tile_type = type;
    RectAndSurface rect_and_surface = get_rect_and_surface_by_tile_type(tile->tile_type); 
    tile->rect_and_surface = rect_and_surface;
    tile->rect_and_surface.rect.w = IMAGE_PIXELS;
    tile->rect_and_surface.rect.h = IMAGE_PIXELS;
    tile->rect_and_surface.rect.x = tile->rect_and_surface.rect.w * i;
    tile->rect_and_surface.rect.y = tile->rect_and_surface.rect.h * j;
}

void grid_render(SDL_Surface* screen, Grid *grid, SDL_Renderer *renderer) {
    // Render all tiles
    printf("grid_render%d, %d\n", grid->xTiles, grid->yTiles);
    for(int i = 0; i < grid->xTiles; ++i) {
        for(int j = 0; j < grid->yTiles; ++j) {
            grid_render_tile(screen, &(grid->tiles[i][j]), renderer);
        }
    }
}

void grid_render_tile(SDL_Surface* screen, Tile *tile, SDL_Renderer *renderer) {
    RectAndSurface* rect_and_surface = &tile->rect_and_surface;
    SDL_BlitSurface(&rect_and_surface->surface, NULL, screen, &rect_and_surface->rect);
}

void destroy_grid_surfaces() {
    for(int i = 0; i < number_of_tile_surfaces; i++) { 
        SDL_FreeSurface(&tile_surfaces[i]);
    }
    free(tile_surfaces);
}

void destroy_grid() {
    free(grid);
}

const char* get_image_path_string_by_tile_type(TILE_TYPE tile_type) {
    switch (tile_type) {
        case soil:
            return SOIL_IMAGE_PATH;
        case grass:  
            return GRASS_IMAGE_PATH;
        case stones:  
            return STONES_IMAGE_PATH;
    }
}