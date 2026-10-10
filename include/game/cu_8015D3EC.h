#ifndef GAME_CU_8015D3EC_H
#define GAME_CU_8015D3EC_H

#include "game/Object_80233EAC.h"

struct Ids_8015F6E8;
struct Object_8003DEC4;

/* Called with the player by fn_8015F958, fn_8015FB38, fn_8015FC54 and
   fn_8015FD70 once the loads they start complete (directly when nothing
   needs loading). */
typedef void (*Callback_8015F958)(Object_8003DEC4 *pPlayer);

extern "C" {
Object_8023417C *fn_8015E2FC(int type, int index, int a);
void fn_8015E620(unsigned int players, int mode);
void fn_8015E73C(int id);
void fn_8015E908(int a);
void fn_8015F3FC(int a);
int fn_8015F5BC(const char *pName);
void fn_8015F958(int index, Ids_8015F6E8 *pIds, Object_8003DEC4 *pPlayer, Callback_8015F958 pCallback);
void fn_8015FB38(int index, int id, Object_8003DEC4 *pPlayer, Callback_8015F958 pCallback);
void fn_8015FC54(int index, int id, Object_8003DEC4 *pPlayer, Callback_8015F958 pCallback);
void fn_8015FD70(int index, int id, Object_8003DEC4 *pPlayer, Callback_8015F958 pCallback);
void fn_8015FE4C(void);
}

#endif
