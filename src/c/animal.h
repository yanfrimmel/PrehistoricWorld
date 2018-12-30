#ifndef ANIMAL_H   /* Include guard */
#define ANIMAL_H
#include <stdbool.h>

enum DIET {
    herbivore = 0,
    omnivore = 1, 
    carnivore = 2
}; 

enum GENDER {
    female = 0,
    male = 1
};

enum HUNGER {
    staving = 0,
    hungry  = 1,
    full = 2
};

enum THIRST {
    dehydrated = 0,
    thirsty = 1,
    full = 2
};

enum ANIMAL_TYPE {
    rabbit = 0,
    wolf = 1,
    human = 2,
    neardenthal = 3,
    deer = 4,
    bear = 5,
    smilodon = 6,
    mammoth = 7
};

struct Animal {
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

#endif