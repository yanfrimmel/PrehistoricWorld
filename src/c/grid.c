#include "grid.h"
#include "utils.h"
// #include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
// #include <pthread.h> 

int gridInitTextures() {
    numberOfTileImages = 3;
    tileTextures = (SDL_Texture **) malloc ( numberOfTileImages * sizeof(SDL_Texture*));
    if(tileTextures == NULL){ printf("Error - can't allocate\n"); return -1; }
    //Images load
    for(int i = 0; i < numberOfTileImages; i++) { 
        tileTextures[i] = loadTexture(getImagePathStringByTileType(i));
        if(!tileTextures) {
            printf("Error - can't create texture\n"); return -1; 
        }
    }
    return 1;
}  

RectAndTexture getRectAndTextureByTileType(int tileType){
    SDL_Texture* texture = tileTextures[tileType];
    if(!&texture) {
            printf("Error - can't allocate\n"); return; 
    }
    return createRectAndTexture(texture);
}

void gridAlignCenter() {
    grid->rect.x = WINDOW_WIDTH;
    grid->rect.y = WINDOW_HEIGHT;
}

Grid gridInit() {
    GRID_HEIGHT = ceil(WINDOW_HEIGHT/IMAGE_PIXELS);
    GRID_WIDTH  = ceil(WINDOW_WIDTH/IMAGE_PIXELS);
    gridTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    grid  = (Grid *) malloc (sizeof(Grid));
    if(grid == NULL){ 
        printf("Error - can't allocate\n"); 
        return;
    }
    grid->rect.w = WINDOW_WIDTH;
    grid->rect.h = WINDOW_HEIGHT;
    gridAlignCenter(grid, WINDOW_WIDTH, WINDOW_HEIGHT);

    if(gridInitTextures() == -1) {
        fprintf(stderr, "Error: cant allocate grid textures! !\n");
        return;
    };

    grid->tiles = (Tile **) malloc ( GRID_WIDTH * sizeof(Tile*));

    for (int i = 0; i < GRID_WIDTH; i++) {
        grid->tiles[i] = (Tile *) malloc(GRID_HEIGHT * sizeof(Tile));
    }

    if(!grid->rect.w || !grid->rect.h ) {
        fprintf(stderr, "Grid dimensions or number of tiles not initialised !\n");
        return;
    }

    // Init all tiles
    for(int i = 0; i < GRID_WIDTH; ++i) {
        for(int j = 0; j < GRID_HEIGHT; ++j) {
            gridInitTile(&(grid->tiles[i][j]),i, j, soil);
        }
    }
    return *grid;
}



void gridInitTile(Tile *tile, int i, int j, TILE_TYPE type) {
    // printf("gridInitTile \n");
    tile->tileType = type;
    RectAndTexture RectAndTexture = getRectAndTextureByTileType(tile->tileType); 
    tile->RectAndTexture = RectAndTexture;
    tile->RectAndTexture.rect.w = IMAGE_PIXELS;
    tile->RectAndTexture.rect.h = IMAGE_PIXELS;
    tile->RectAndTexture.rect.x = tile->RectAndTexture.rect.w * i;
    tile->RectAndTexture.rect.y = tile->RectAndTexture.rect.h * j;
}

void gridDraw() {
    // Render all tiles
    if(isEntireGridIsDrawn) return;
   
    SDL_SetRenderTarget(renderer, gridTexture);
    printf("gridRender%d, %d\n", GRID_WIDTH, GRID_HEIGHT);
    for(int i = 0; i < GRID_WIDTH; ++i) {
        for(int j = 0; j < GRID_HEIGHT; ++j) {
            gridDrawTile(&(grid->tiles[i][j]));
        }
    }
    SDL_SetRenderTarget(renderer, NULL);
    isEntireGridIsDrawn = true;
}

void gridDrawTile(Tile *tile) {
    RectAndTexture* RectAndTexture = &tile->RectAndTexture;
    SDL_RenderCopy(renderer, RectAndTexture->texture, NULL, &RectAndTexture->rect);
}

void refreshGrid() {
     isEntireGridIsDrawn = false;
}

void updateTile(Tile tile, TILE_TYPE type) { 
    tile.tileType = type;
    tile.RectAndTexture.texture = tileTextures[tile.tileType];
    gridDrawTile(&tile);
}

void destroyGridTextures() {
    for(int i = 0; i < numberOfTileImages; i++) { 
        SDL_DestroyTexture(tileTextures[i]);
    }
    free(tileTextures);
}

void destroyGrid() {
    for(int i=0;i<GRID_WIDTH;i++){
        free(grid->tiles[i]);
    }
    free(grid->tiles);
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