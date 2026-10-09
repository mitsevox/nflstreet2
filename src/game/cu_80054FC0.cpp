#include "game/cu_80181330.h"
#include "game/cu_8003AEA8.h"

extern "C" {
void fn_8001ED80(int value);
int fn_8001ED88(void);
int fn_8002B70C(void);
void fn_8003AED8(int kind, int index, int value);
int fn_8003B0A0(int a, int kind, int index0, int index1, int unused);
int fn_8003B360(int group);
int fn_8003B3AC(int group);
void fn_80077F24(void);
int fn_80082414(int index);
int fn_80085428(int a, int b, float *pX, float *pY, int *pValue, char *pLabel, int labelSize);
void fn_80183920(int mode, int value);
int fn_8018D720(int a);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_8022F384(int a);
int fn_8022F4BC(void);

void fn_80054FC0(int *pResult)
{
    if (fn_8018D720(fn_8022F384(fn_8022F4BC()))) {
        if (fn_8002B70C() != 0x3FF) {
            *pResult = 401;
        } else if (fn_8001ED88() == 6) {
            fn_8001ED80(4);
            *pResult = 123;
        } else {
            *pResult = 400;
        }
    } else {
        *pResult = 404;
        fn_80183920(0, 0x3FF);
    }
    fn_80077F24();
}

int fn_80055058(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 272:
        *pResult = 0;
        *pArgs[0].pi = 0;
        break;
    case 285:
        *pResult = 0;
        break;
    case 392:
        fn_80054FC0(pArgs[0].pi);
        break;
    case 250:
    case 251:
    case 252:
    case 253:
    case 254:
        break;
    default:
        return 0;
    }
    return 1;
}

int fn_800550E4(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 270:
        fn_8003B360(pArgs[0].i);
        break;
    case 271:
        fn_8003B3AC(pArgs[0].i);
        break;
    case 268: {
        int *pList = pArgs[5].pi;
        int list = pList[0] + 1;

        pList += list;
        fn_8003AF8C(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].i, pArgs[7].i, (Pair_8003AEA8 *)pArgs[4].pParams, pList,
                    pArgs[6].pi);
        break;
    }
    case 267:
        fn_8003AEF4(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[6].i, (Pair_8003AEA8 *)pArgs[3].pParams,
                    (Pair_8003AEA8 *)pArgs[4].pParams, (Pair_8003AEA8 *)pArgs[5].pParams);
        break;
    case 269:
        fn_8003B0A0(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].i, pArgs[4].i);
        break;
    default:
        return 0;
    }
    return 1;
}

int fn_800551D8(unsigned char side)
{
    return 1;
}

void fn_800551E0(unsigned char side, int unused, char *pText, int size)
{
    if (side) {
        fn_801C2EF0(pText, "Offense", size);
    } else {
        fn_801C2EF0(pText, "Defense", size);
    }
}

void fn_80055230(unsigned char side, int unused, int index, float *pX, float *pY, char *pLabel, int labelSize)
{
    int value;

    fn_80085428(side, index, pX, pY, &value, pLabel, labelSize);
    fn_8003AED8(side != 0, index, value);
}

int fn_8005528C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 372:
        *pResult = fn_80082414(0);
        break;
    case 373:
        *pResult = fn_80082414(1);
        break;
    case 374:
        *pResult = fn_80082414(2);
        break;
    case 375:
        *pResult = fn_80082414(3);
        break;
    default:
        return 0;
    }
    return 1;
}
}
