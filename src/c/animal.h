#ifndef ANIMAL_H   /* Include guard */
#define ANIMAL_H
#include <stdbool.h>
#include "utils.h"

typedef enum DIET {
    herbivore = 0,
    omnivore = 1, 
    carnivore = 2
} DIET; 

typedef enum GENDER {
    female = 0,
    male = 1
} GENDER;

typedef enum HUNGER {
    staving = 0,
    hungry  = 1,
    full = 2
} HUNGER;

typedef enum THIRST {
    dehydrated = 0,
    thirsty = 1,
    saturation = 2
} THIRST;

typedef enum ANIMAL_TYPE {
    rabbit = 0,
    wolf = 1,
    human = 2,
    neardenthal = 3,
    deer = 4,
    bear = 5,
    smilodon = 6,
    mammoth = 7
} ANIMAL_TYPE;

// typedef enum 

struct Animal {
    RectAndSurface rect_and_surface;
    DistanceFromTarget to_target;
    Movement movement;
    ANIMAL_TYPE type;
    const char* name;
    const char* image_path; 
    int speed;
    int health_points;
    DIET diet;
    GENDER gender;
    bool social;
    HUNGER hunger;
    THIRST thirst;
};
typedef struct Animal Animal;

 Animal *human_player;

Animal init_player(int window_width, int window_height);
void destroy_human_player();

#endif