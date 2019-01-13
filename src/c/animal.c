#include "animal.h"

Animal initAnimal(int xPos, int yPos, ANIMAL_TYPE animalType, GENDER gender) {
    humanPlayer = (Animal *)malloc(sizeof(Animal));
    if (humanPlayer == NULL) {
        printf("Error - can't allocate\n");
        return;
    }

    humanPlayer->imagePath = getImagePathStringByAnimalTypeAndGender(animalType,gender);
    humanPlayer->RectAndTexture = loadImageTextureAndRectAndTexture(humanPlayer->imagePath);

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

void onDestinationSelected(int* destX, int* destY, Animal* animal) {
     animal->toTarget.distance = 
            sqrt(animal->toTarget.deltaX * animal->toTarget.deltaX + 
            animal->toTarget.deltaY * animal->toTarget.deltaY);

            animal->toTarget.targetX = *destX - animal->RectAndTexture.rect.w / 2;
            animal->toTarget.targetY = *destY - animal->RectAndTexture.rect.h / 2;
            if (animal->toTarget.distance > IMAGE_PIXELS/2) {
                animal->movement.xVel = animal->toTarget.deltaX * SPEED / animal->toTarget.distance;
                animal->movement.yVel = animal->toTarget.deltaY * SPEED / animal->toTarget.distance;
            }
}