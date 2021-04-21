#ifndef PLAYER
#define PLAYER
#include "vector.h"
#include "ray.h"
#define NRAYS 45

typedef struct _Player
{
    Vector pos;
    Ray rays[NRAYS];
    double rotation;

} Player;

extern Vector* player_getPos(const Player* player);

extern Player* player_set(Player* player, const Vector pos);
extern void player_setPos(Player* player, const Vector pos);
extern void player_rotate(Player* player, const double angle);

extern Player* player_create(const Vector pos);

extern void player_look(float scene[], const Player* player, const Boundary walls[], const size_t NWALLS, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);

#endif /* PLAYER */
