#include "player.h"
#include "sdl_gfx.h"
#include <math.h>

struct _Player
{
    Vector* pos;
    Ray* rays[NRAYS];
    double heading;
    int fov;
};

Vector* player_getPos(const Player* self){
    return self->pos;
}

Vector* player_getHeading(const Player* self){
    return vector_fromAngle(self->heading);
}

int player_getFOV(const Player* self){
    return self->fov;
}

void player_init(Player* self, Vector* pos){
    self->pos = pos;
    self->fov = 60;
    self->heading = 0;
    int j = 0;
    for(int a = - self->fov / 2; a < self->fov / 2; a++){
        self->rays[j] = ray_create(self->pos, DEG2RAD(a));
        j++;
    }
    
}

void player_updateFOV(Player* self, int fov){
    if(self->fov + fov >= 30 && self->fov + fov <= NRAYS){
        self->fov += fov;
        int j = 0;
        for(int a = - self->fov / 2; a < self->fov / 2; a++){
            self->rays[j] = ray_create(self->pos, DEG2RAD(a) + self->heading);
            j++;
        }
    }
}

void player_setPos(Player* self, Vector* pos){
    self->pos = pos;
    int j = 0;
    for(int a = - self->fov / 2; a < self->fov / 2; a++){
        ray_init(self->rays[j], self->pos, DEG2RAD(a) + self->heading);
        j++;
    }
}

void player_rotate(Player* self, double angle){
    self->heading += angle;
    int j = 0;
    for(int a = - self->fov / 2; a < self->fov / 2; a++){
        ray_setAngle(self->rays[j], DEG2RAD(a) + self->heading);
        j++;
    }
}

void player_move(Player* self, float movement){
    Vector* vel = vector_fromAngle(self->heading);
    vector_setMag(vel, movement);
    vector_add(self->pos, vel);
}

Player* player_create(Vector* pos){
    Player* result = (Player*) malloc(sizeof(Player));
    player_init(result, pos);
    return result;
}

void player_look(float scene[], Player* self, Boundary* walls[], size_t NWALLS, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b){
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillCircle(renderer, vector_getX(self->pos), vector_getY(self->pos), 10);

    for(int i = 0; i < self->fov - 1; i++){
        Ray* ray = self->rays[i];
        Vector* closest = NULL;
        float record = INFINITY;
        for(int j = 0; j < NWALLS; j++){
            Vector* pt = ray_cast(ray, walls[j]);
            if(pt != NULL){
                float d = vector_distance(self->pos, pt);
                double a = vector_getHeading(ray_getDir(ray)) - self->heading;
                d *= cos(a);
                if(d < record){
                    record = d;
                    closest = pt;
                }
            }
        }
        
        if(closest != NULL){
            SDL_SetRenderDrawColor(renderer, r, g, b, 100);
            SDL_RenderDrawLine(renderer, vector_getX(self->pos), vector_getY(self->pos), vector_getX(closest), vector_getY(closest));
        }
        scene[i] = record;
    }
}