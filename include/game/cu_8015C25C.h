#ifndef GAME_CU_8015C25C_H
#define GAME_CU_8015C25C_H

struct Object_8003DEC4;

extern "C" {
void fn_8015CBC8(void);
void fn_8015CC1C(void);
unsigned char fn_8015CD9C(void);
void fn_8015D060(int index, const char *pName, unsigned char priority, int force);
void fn_8015D180(int index, unsigned char priority);
void fn_8015D1CC(int index, unsigned char priority);
unsigned char fn_8015D1FC(int index);
unsigned char fn_8015D2E8(Object_8003DEC4 *pPlayer);
void fn_8015D32C(Object_8003DEC4 *pPlayer, float *pScale);
unsigned char fn_8015D38C(unsigned char value);
}

#endif
