#ifndef ANIMAL_H   /* Include guard */
#define ANIMAL_H
#include <stdbool.h>
#include "utils.h"

#define HUMAN_MALE_IMAGE_PATH ("../resources/human_male.png")
#define HUMAN_FEMALE_IMAGE_PATH ("../resources/human_female.png")

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

Animal init_animal(int x_pos, int y_pos, ANIMAL_TYPE animal_type, GENDER gender);
void destroy_human_player();
void edit_animal_movenet(Movement *movement, float x_pos, float y_pos, float x_vel, float y_vel);
void edit_animal_distance_from_target(DistanceFromTarget *target,
    float distance,
    float delta_x,
    float delta_y,
    int target_x,
    int target_y);
const char* get_image_path_string_by_animal_type_and_gender(ANIMAL_TYPE animal_type, GENDER gender);

#endif