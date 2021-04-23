#ifndef PLAYER
#define PLAYER
#include "vector.h"
#include "ray.h"
#define NRAYS 90

struct _Player;
typedef struct _Player Player;

extern Vector* player_getPos(const Player* self);
extern Vector* player_getHeading(const Player* self);
extern int player_getFOV(const Player* self);

extern void player_init(Player* self, Vector* pos);

extern void player_updateFOV(Player* self, int fov);
extern void player_setPos(Player* self, Vector* pos);
extern void player_rotate(Player* self, double angle);
extern void player_move(Player* self, float movement);

extern Player* player_create(Vector* pos);

extern void player_look(float scene[], Player* self, Boundary* walls[], size_t NWALLS, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);

#endif /* PLAYER */
