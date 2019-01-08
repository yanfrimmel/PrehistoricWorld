#include "animal.h"

Animal initAnimal(int xPos, int yPos, ANIMAL_TYPE animalType, GENDER gender) {
    humanPlayer = (Animal *)malloc(sizeof(Animal));
    if (humanPlayer == NULL) {
        printf("Error - can't allocate\n");
        return;
    }

    humanPlayer->imagePath = getImagePathStringByAnimalTypeAndGender(animalType,gender);
    humanPlayer->rectAndSurface = loadImageAndGetSpriteRect(humanPlayer->imagePath);

    humanPlayer->movement.xPos = xPos;
    humanPlayer->movement.yPos = yPos;
    humanPlayer->movement.xVel = 0;
    humanPlayer->movement.yVel = 0;

    humanPlayer->toTarget.distance = 0;
    humanPlayer->toTarget.deltaX = 0;
    humanPlayer->toTarget.deltaY = 0;
    humanPlayer->toTarget.targetX = 0;
    humanPlayer->toTarget.targetY = 0;
    return *humanPlayer;
}

void destroyHumanPlayer() {
    free(humanPlayer);
}

void editAnimalMovenet(Movement *movement, float xPos, float yPos, float xVel, float yVel) {
    movement->xPos = xPos;
    movement->yPos = yPos;
    movement->xVel = xVel;
    movement->yVel = yVel;
}

void editAnimalDistance_fromTarget(DistanceFromTarget *target,
                                      float distance,
                                      float deltaX,
                                      float deltaY,
                                      int targetX,
                                      int targetY) {
    target->distance = distance;
    target->deltaX = deltaX;
    target->deltaY = deltaY;
    target->targetX = targetX;
    target->targetY = targetY;
}

const char* getImagePathStringByAnimalTypeAndGender(ANIMAL_TYPE animalType, GENDER gender) {
    switch (animalType) {
        case human:
            switch (gender){
                case male:
                    return HUMAN_MALE_IMAGE_PATH;
                case female:
                    return HUMAN_FEMALE_IMAGE_PATH;
                }
    }
}