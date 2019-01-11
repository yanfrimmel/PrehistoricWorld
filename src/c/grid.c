#include "grid.h"
#include "utils.h"
// #include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
// #include <pthread.h> 

int gridInitSurfaces() {
    numberOfTileSurfaces = 1;
    tileSurfaces = (SDL_Surface *) malloc ( numberOfTileSurfaces * sizeof(SDL_Surface));
    if(tileSurfaces == NULL){ printf("Error - can't allocate\n"); return -1; }
    //Images load
    for(int i = 0; i < numberOfTileSurfaces; i++) { 
        tileSurfaces[i] = *IMG_Load(getImagePathStringByTileType(grass)); ; 
        if(!&tileSurfaces) {
            printf("Error - can't create surface\n"); return -1; 
        }
    }
    return 1;
}  

RectAndSurface getRectAndSurfaceByTileType(int tileType){
    SDL_Surface surface = tileSurfaces[tileType];
    if(!&surface) {
            printf("Error - can't allocate\n"); return; 
    }
    SDL_Rect dest;
    SDL_GetClipRect(&surface, &dest);
    RectAndSurface rectAndSurface = {dest,surface};
    return rectAndSurface;
}

int gridAdjustSize()
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

void gridAlignCenter() {
    grid->rect.x = WINDOW_WIDTH;
    grid->rect.y = WINDOW_HEIGHT;
}

Grid gridInit() {
    grid  = (Grid *) malloc (sizeof(Grid));
    if(grid == NULL){ 
        printf("Error - can't allocate\n"); 
        return;
    }
    grid->rect.w = WINDOW_WIDTH;
    grid->rect.h = WINDOW_HEIGHT;
    gridAlignCenter(grid, WINDOW_WIDTH, WINDOW_HEIGHT);
    if(gridInitSurfaces() == -1) {
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
            gridInitTile(&(grid->tiles[i][j]),i, j, soil);
        }
    }
    return *grid;
}



void gridInitTile(Tile *tile, int i, int j, TILE_TYPE type) {
    printf("gridInitTile \n");
    tile->tileType = type;
    RectAndSurface rectAndSurface = getRectAndSurfaceByTileType(tile->tileType); 
    tile->rectAndSurface = rectAndSurface;
    tile->rectAndSurface.rect.w = IMAGE_PIXELS;
    tile->rectAndSurface.rect.h = IMAGE_PIXELS;
    tile->rectAndSurface.rect.x = tile->rectAndSurface.rect.w * i;
    tile->rectAndSurface.rect.y = tile->rectAndSurface.rect.h * j;
}

void gridRender() {
    // Render all tiles
    if(isEntireGridIsBlit) return;
    printf("gridRender%d, %d\n", grid->xTiles, grid->yTiles);
    for(int i = 0; i < grid->xTiles; ++i) {
        for(int j = 0; j < grid->yTiles; ++j) {
            gridRenderTile(&(grid->tiles[i][j]));
        }
    }
    gridTexture = SDL_CreateTextureFromSurface(renderer,gridSurface);
    isEntireGridIsBlit = true;
}

void gridRenderTile(Tile *tile) {
    RectAndSurface* rectAndSurface = &tile->rectAndSurface;
    SDL_BlitSurface(&rectAndSurface->surface, NULL, gridSurface, &rectAndSurface->rect);
}

void destroyGridSurfaces() {
    for(int i = 0; i < numberOfTileSurfaces; i++) { 
        SDL_FreeSurface(&tileSurfaces[i]);
    }
    free(tileSurfaces);
    free(gridSurface);
}

void destroyGrid() {
    free(grid);
}

const char* getImagePathStringByTileType(TILE_TYPE tileType) {
    switch (tileType) {
        case soil:
            return SOIL_IMAGE_PATH;
        case grass:  
            return GRASS_IMAGE_PATH;
        case stones:  
            return STONES_IMAGE_PATH;
    }
}