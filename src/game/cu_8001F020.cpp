#include "game/Class_8018FD64Inline.h"
#include "game/cu_80181330.h"

extern "C" {
int fn_8001E2C0(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8001ED98(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8001FE10(unsigned int id, void *pArgs, int unused, int *pResult);
int fn_80020170(unsigned int id, void *pArgs, int unused, int *pResult);
int fn_80020904(unsigned int id, void *pArgs, int unused, int *pResult);
int fn_80020ADC(unsigned int id, void *pArgs, int unused, int *pResult);
int fn_80063578(unsigned int id, void *pArgs, int unused, int *pResult);
int fn_80063910(unsigned int id, void *pArgs, int unused, int *pResult);
int fn_80186010(unsigned int id, void *pArgs, int unused, int *pResult);
signed char fn_80186B38(int a);
void fn_80186ED8(signed char a);
void fn_80186F30(signed char a, int b);
int fn_8022F3D4(int a);
int fn_8022F4BC(void);
}

static int lbl_803EBA88 = 0;

extern "C" {
void fn_8001F500(int index);

int fn_8001F020(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    if (id == 0x80000001) {
        fn_80186F30(fn_80186B38(fn_8022F4BC()), 1);
        fn_80186F30(-1, 0);
        return 1;
    }
    return 0;
}

int fn_8001F074(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 2:
        return fn_8001F020(id, pArgs, unused, pResult);
    case 0:
        return fn_8001ED98(id, pArgs, unused, pResult);
    case 1:
        return fn_8001E2C0(id, pArgs, unused, pResult);
    case 4:
        return fn_80063578(id, pArgs, unused, pResult);
    }
    return 0;
}

int fn_8001F1D8(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8001F504(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);

int fn_8001F120(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 0:
        return fn_80063910(id, pArgs, unused, pResult);
    case 1:
        return fn_8001FE10(id, pArgs, unused, pResult);
    case 2:
        return fn_80020170(id, pArgs, unused, pResult);
    case 5:
        return fn_80186010(id, pArgs, unused, pResult);
    case 6:
        return fn_80020ADC(id, pArgs, unused, pResult);
    case 7:
        return fn_80020904(id, pArgs, unused, pResult);
    case 4:
        return fn_8001F1D8(id, pArgs, unused, pResult);
    case 3:
        return fn_8001F504(id, pArgs, unused, pResult);
    }
    return 0;
}

int fn_8001F1D8(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000004:
        *pResult = 9;
        break;
    case 0x80000002:
    case 0x80000003:
        break;
    case 0x80000001: {
        int handle = fn_8022F3D4(fn_8022F4BC());
        Class_8018FD64 cursor;
        int *pA;
        int *pB;
        int base;
        unsigned int mask;
        int i;

        cursor.fn_8018FDEC(0x464E4955, 0x44494755, 0, 0, handle);
        pA = (int *)(pArgs[1].i + (*pArgs[1].pi + 1) * 4);
        pB = (int *)(pArgs[2].i + (*pArgs[2].pi + 1) * 4);
        fn_80186ED8(fn_80186B38(fn_8022F4BC()));
        base = pArgs[0].i * 4;
        for (i = 0; i < 12; i++) {
            pA[i] = i + base;
            pB[i] = 0;
        }
        mask = cursor.fn_8018FF9C(0x504C5555);
        for (i = base; i <= 9; i++) {
            if (mask & (1 << i)) {
                pB[i - base] = 0;
            } else {
                pB[i - base] = 1;
            }
        }
        lbl_803EBA88 = 0;
        break;
    }
    case 0x80000006:
        *pArgs[1].pi = pArgs[0].i + 40;
        lbl_803EBA88 = pArgs[0].i;
        break;
    case 0x80000005: {
        if (pArgs[0].i == 1) {
            lbl_803EBA88++;
        } else {
            lbl_803EBA88--;
        }
        if (lbl_803EBA88 > 39) {
            lbl_803EBA88 = 0;
        }
        {
            int handle = fn_8022F3D4(fn_8022F4BC());
            Class_8018FD64 cursor;
            unsigned int mask;
            int index;

            cursor.fn_8018FDEC(0x464E4955, 0x44494755, 0, 0, handle);
            mask = cursor.fn_8018FF9C(0x504C5555);
            index = lbl_803EBA88;
            if (index >= 0 && index <= 9 && !(mask & (1 << index))) {
                do {
                    if (pArgs[0].i == 1) {
                        index++;
                    } else {
                        index--;
                    }
                } while (index >= 0 && index <= 9 && !(mask & (1 << index)));
                lbl_803EBA88 = index;
            }
            if (lbl_803EBA88 < 0) {
                lbl_803EBA88 = 39;
            }
            *pArgs[1].pi = lbl_803EBA88 + 40;
        }
        break;
    }
    case 0x80000007:
        lbl_803EBA88 = 0;
        break;
    default:
        return 0;
    }
    return 1;
}

void fn_8001F500(int index)
{
}

int fn_8001F504(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
    case 0x80000002:
        break;
    case 0x80000003:
        fn_8001F500(pArgs[0].i - 1);
        break;
    default:
        return 0;
    }
    return 1;
}
}
