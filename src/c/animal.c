#include "animal.h"

Animal* initAnimal(int xPos, int yPos, ANIMAL_TYPE animalType, GENDER gender) {
    Animal* animal = (Animal *) malloc (sizeof(Animal));
    if (animal == NULL) {
        printf("Error - can't allocate\n");
        return NULL;
    }

    animal->imagePath = getImagePathStringByAnimalTypeAndGender(animalType,gender);
    printf("animal->imagePath: %s\n", animal->imagePath);
    animal->RectAndTexture = loadImageTextureAndRectAndTexture(animal->imagePath);

    animal->movement.xPos = xPos;
    animal->movement.yPos = yPos;
    animal->movement.xVel = 0;
    animal->movement.yVel = 0;

    animal->toTarget.distance = 0;
    animal->toTarget.deltaX = 0;
    animal->toTarget.deltaY = 0;
    animal->toTarget.targetX = 0;
    animal->toTarget.targetY = 0;
    return animal;
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

void updatePosition(Animal* animal) {
    animal->movement.xPos += animal->movement.xVel / FPS;
    animal->movement.yPos += animal->movement.yVel / FPS;
    animal->toTarget.deltaX = animal->toTarget.targetX - animal->movement.xPos;
    animal->toTarget.deltaY = animal->toTarget.targetY - animal->movement.yPos;
    animal->toTarget.distance = sqrt(animal->toTarget.deltaX * animal->toTarget.deltaX + animal->toTarget.deltaY * animal->toTarget.deltaY);
}

bool stayInBorderCheckTargetCollision(Animal* animal) { 
    //check border collision
    if (animal->movement.xPos <= 0) animal->movement.xPos = 0;
    if (animal->movement.yPos <= 0) animal->movement.yPos = 0;
    if (animal->movement.xPos >= WINDOW_WIDTH - animal->RectAndTexture.rect.w) animal->movement.xPos = WINDOW_WIDTH - animal->RectAndTexture.rect.w;
    if (animal->movement.yPos >= WINDOW_HEIGHT - animal->RectAndTexture.rect.h) animal->movement.yPos = WINDOW_HEIGHT - animal->RectAndTexture.rect.h;
    
    if (animal->toTarget.distance < IMAGE_PIXELS/2) {
            // printf("at target\n");
            animal->movement.xVel = animal->movement.yVel = 0;
            return true;
    }
    return false;
}

void updateRectPosition(Animal* animal) {
    animal->RectAndTexture.rect.y = (int) animal->movement.yPos;
    animal->RectAndTexture.rect.x = (int) animal->movement.xPos;
}

void updateAnimal(Animal* animal) { 
    updatePosition(animal);
    stayInBorderCheckTargetCollision(animal);
    updateRectPosition(animal);
}