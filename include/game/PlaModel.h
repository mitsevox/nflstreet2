#ifndef GAME_PLAMODEL_H
#define GAME_PLAMODEL_H

#include "game/Object_80233EAC.h"

struct PlayerHeadIds_t;
struct Object_8003DEC4;

/* Called with the player by PlaModelLoadHairAsync, PlaModelLoadHatAsync, PlaModelLoadGlassesAsync and
   PlaModelLoadJewelAsync once the loads they start complete (directly when nothing
   needs loading). */
typedef void (*PlaModelLoadCallback_t)(Object_8003DEC4 *pPlayer);

extern "C" {
Object_8023417C *fn_8015E2FC(int type, int index, int a);
void PlaModelInit(unsigned int players, int mode);
void fn_8015E73C(int id);
void fn_8015E908(int a);
void fn_8015F3FC(int a);
int fn_8015F5BC(const char *pName);
void PlaModelLoadHairAsync(int index, PlayerHeadIds_t *pIds, Object_8003DEC4 *pPlayer, PlaModelLoadCallback_t pCallback);
void PlaModelLoadHatAsync(int index, int id, Object_8003DEC4 *pPlayer, PlaModelLoadCallback_t pCallback);
void PlaModelLoadGlassesAsync(int index, int id, Object_8003DEC4 *pPlayer, PlaModelLoadCallback_t pCallback);
void PlaModelLoadJewelAsync(int index, int id, Object_8003DEC4 *pPlayer, PlaModelLoadCallback_t pCallback);
void PlaModelFinishAsyncLoads(void);
}

#endif
