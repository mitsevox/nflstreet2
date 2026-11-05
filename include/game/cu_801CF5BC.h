#ifndef GAME_CU_801CF5BC_H
#define GAME_CU_801CF5BC_H

#ifdef __cplusplus
extern "C" {
#endif

void *MathNewRandomStream(int, int);
int MathCopyRandomStream(void *, void *);
int MathGetRandomStreamSize(void *);
int MathDelRandomStream(void *);
float MathGetRandom(void *);
unsigned int MathGetRandomRange(void *, unsigned int);
int MathGetRandomSeed(void);

#ifdef __cplusplus
}
#endif

#endif
