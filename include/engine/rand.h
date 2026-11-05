#ifndef ENGINE_RAND_H
#define ENGINE_RAND_H

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
