#include "animal.h"

Animal init_animal(int x_pos, int y_pos, ANIMAL_TYPE animal_type, GENDER gender) {
    human_player = (Animal *)malloc(sizeof(Animal));
    if (human_player == NULL) {
        printf("Error - can't allocate\n");
        return;
    }

    human_player->image_path = get_image_path_string_by_animal_type_and_gender(animal_type,gender);
    human_player->rect_and_surface = load_image_and_get_sprite_rect(human_player->image_path);

    human_player->movement.x_pos = x_pos;
    human_player->movement.y_pos = y_pos;
    human_player->movement.x_vel = 0;
    human_player->movement.y_vel = 0;

    human_player->to_target.distance = 0;
    human_player->to_target.delta_x = 0;
    human_player->to_target.delta_y = 0;
    human_player->to_target.target_x = 0;
    human_player->to_target.target_y = 0;
    return *human_player;
}

void destroy_human_player() {
    free(human_player);
}

void edit_animal_movenet(Movement *movement, float x_pos, float y_pos, float x_vel, float y_vel) {
    movement->x_pos = x_pos;
    movement->y_pos = y_pos;
    movement->x_vel = x_vel;
    movement->y_vel = y_vel;
}

void edit_animal_distance_from_target(DistanceFromTarget *target,
                                      float distance,
                                      float delta_x,
                                      float delta_y,
                                      int target_x,
                                      int target_y) {
    target->distance = distance;
    target->delta_x = delta_x;
    target->delta_y = delta_y;
    target->target_x = target_x;
    target->target_y = target_y;
}

const char* get_image_path_string_by_animal_type_and_gender(ANIMAL_TYPE animal_type, GENDER gender) {
    switch (animal_type) {
        case human:
            switch (gender){
                case male:
                    return HUMAN_MALE_IMAGE_PATH;
                case female:
                    return HUMAN_FEMALE_IMAGE_PATH;
                }
    }
}