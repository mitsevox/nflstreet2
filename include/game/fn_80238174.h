#ifndef GAME_FN_80238174_H
#define GAME_FN_80238174_H

typedef int (*Callback_80238234)(void *p, int value);
typedef int (*Callback1C_80238234)(void *p, void *q);
typedef int (*Callback20_80238248)(void *p, char *pBuffer);
typedef int (*Callback24_80238248)(void *p);
typedef int (*Callback28_80238248)(void *p, char *pBuffer);

#ifdef __cplusplus
extern "C" {
#endif
void *fn_80238174(int a, void **ppData, int size, int b, unsigned int id);
void fn_802381E0(void *pHandle);
void fn_80238234(void *pHandle, Callback_80238234 pCallback10, Callback_80238234 pCallback14, Callback_80238234 pCallback18, Callback1C_80238234 pCallback1C);
void fn_80238248(void *pHandle, Callback28_80238248 pCallback28, Callback24_80238248 pCallback24, Callback20_80238248 pCallback20);
#ifdef __cplusplus
}
#endif

#endif
