#include "game/Object_80039F5C.h"

struct Args_8018ACBC {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
};

extern "C" {
int fn_8006C854(int index, Vector_80039F5C *pPos);

void fn_8018AC38(void *p);
void fn_8018AC3C(void *p);
void fn_8018AC40(int group, unsigned int index);
void fn_8018ACB8(void *p);
void fn_8018ACBC(void *p, unsigned int message, int a, Args_8018ACBC *pArgs);
}

static int lbl_802EAD64[23] = {
    0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x91,
    0x91, 0x91, 0x91, 0x91, 0x79, 0x7A, 0x7B, 0x7C,
    0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83
};

static int lbl_802EADC0[9] = {
    0x91, 0x91, 0x91, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90
};

extern "C" void fn_8018AC38(void *p)
{
}

extern "C" void fn_8018AC3C(void *p)
{
}

extern "C" void fn_8018AC40(int group, unsigned int index)
{
    int id;

    if (group == 0 || group == 13) {
        if ((group == 0 && index <= 22) || (group == 13 && index <= 8)) {
            if (group == 0) {
                id = lbl_802EAD64[index];
            } else {
                id = lbl_802EADC0[index];
            }
            fn_8006C854(id, 0);
        }
    }
}

extern "C" void fn_8018ACB8(void *p)
{
}

extern "C" void fn_8018ACBC(void *p, unsigned int message, int a, Args_8018ACBC *pArgs)
{
    if (p != 0) {
        switch (message) {
        case -1:
            fn_8018AC38(p);
            break;
        case -2:
            fn_8018AC3C(p);
            break;
        case -3:
            fn_8018ACB8(p);
            break;
        case 0:
            fn_8018AC40(pArgs->mUnknown0, pArgs->mUnknown2);
            break;
        }
    }
}
