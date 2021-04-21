#include "player.h"
#include "sdl_gfx.h"
#include <math.h>

double to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

Vector* player_getPos(const Player* player){
    Vector* vector = malloc(sizeof(Vector));
    vector = &player->pos;
    return vector;
}

Player* player_set(Player* player, const Vector pos){
    player->pos = pos;
    player_rotate(player, 0);
    int j = 0;
    for(int i = 0; i < NRAYS; i++){
        player->rays[j] = *ray_create(player->pos, to_radians(i));
        j++;
    }
    return player;
}

void player_setPos(Player* player, const Vector pos){
    vector_set(&player->pos, vector_getX(&pos), vector_getY(&pos));
    for(int i = 0; i < NRAYS; i++){
        ray_set(&player->rays[i], angle);
    }
}

void player_rotate(Player* player, const double angle){
    player->rotation += angle;
    for(int i = 0; i < NRAYS; i++){
        ray_setAngle(&player->rays[i], angle);
    }
}

Player* player_create(const Vector pos){
    Player* player = malloc(sizeof(Player));
    return player_set(player, pos);
}

void player_look(float scene[], const Player* player, const Boundary walls[], const size_t NWALLS, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b){
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillCircle(renderer, vector_getX(&player->pos), vector_getY(&player->pos), 10);

    for(int i = 0; i < NRAYS; i++){
        Vector* closest = NULL;
        float record = INFINITY;
        for(int j = 0; j < NWALLS; j++){
            const Vector* pt = ray_cast(&player->rays[i], &walls[j]);
            if(pt != NULL){
                const float d = vector_distance(&player->pos, pt);
                if(d < record){
                    record = d;
                    closest = pt;
                }
            }
        }
        
        if(closest != NULL){
            SDL_SetRenderDrawColor(renderer, r, g, b, 100);
            SDL_RenderDrawLine(renderer, vector_getX(&player->pos), vector_getY(&player->pos), vector_getX(closest), vector_getY(closest));
        }
        scene[i] = record;
    }
}