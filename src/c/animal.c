#include "animal.h"

Animal init_player(int window_width, int window_height) {
    human_player = (Animal *) malloc (sizeof(Animal));
    if(human_player == NULL) {
         printf("Error - can't allocate\n"); return; 
    }
    human_player->image_path = HUMAN_MALE_IMAGE_PATH;
    human_player->rect_and_surface = load_image_and_get_sprite_rect(human_player->image_path);

    human_player->movement.x_pos = (window_width - human_player->rect_and_surface.rect.w) / 2;
    human_player->movement.y_pos = (window_height - human_player->rect_and_surface.rect.h) / 2;
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