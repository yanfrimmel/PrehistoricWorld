#ifndef ANIMAL_H   /* Include guard */
#define ANIMAL_H
#include <stdbool.h>
#include "utils.h"

#define HUMAN_MALE_IMAGE_PATH ("resources/human_male.png")
#define HUMAN_FEMALE_IMAGE_PATH ("resources/human_female.png")

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
    RectAndTexture RectAndTexture;
    DistanceFromTarget toTarget;
    Movement movement;
    ANIMAL_TYPE type;
    const char* name;
    const char* imagePath; 
    int speed;
    int healthPoints;
    DIET diet;
    GENDER gender;
    bool social;
    HUNGER hunger;
    THIRST thirst;
};
typedef struct Animal Animal;

Animal* initAnimal(int xPos, int yPos, ANIMAL_TYPE animalType, GENDER gender);
void destroyHumanPlayer();
void editAnimalMovenet(Movement *movement, float xPos, float yPos, float xVel, float yVel);
void editAnimalDistance_fromTarget(DistanceFromTarget *target,
    float distance,
    float deltaX,
    float deltaY,
    int targetX,
    int targetY);
const char* getImagePathStringByAnimalTypeAndGender(ANIMAL_TYPE animalType, GENDER gender);
void onDestinationSelected(int* destX, int* destY, Animal* animal);
void updatePosition(Animal* animal);
void borderOrTargetCollision(Animal* animal);
void updateRectPosition(Animal* animal);
void updateAnimal(Animal* animal);

Animal *humanPlayer;

#endif