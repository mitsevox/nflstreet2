#ifndef GAME_CU_80026BB0_H
#define GAME_CU_80026BB0_H

/* 34 input values of one port. */
struct InputValues {
    float mValue[34];
};

extern "C" {
float fn_80026BB0(int port);
float fn_80026BE8(float x);
void fn_80026C5C(InputValues *pDst, InputValues *pSrc);
int fn_80026CC4(int handle);
int fn_80026D50(void);
void fn_80026DA8(void);
void fn_80026DD4(int port, InputValues *pPrevious, InputValues *pCurrent);
void fn_80027114(int port, int index);
void fn_800271A4(void);
void fn_800271D4(void **pHandlers);
void fn_80027230(void **pHandlers);
void fn_8002728C(int (*pCallback)());
float fn_80027294(int value);
int fn_800272EC(float x);
void fn_80027358(int port);
char *fn_8002739C(void);
int fn_800273A4(void);
}

#endif
