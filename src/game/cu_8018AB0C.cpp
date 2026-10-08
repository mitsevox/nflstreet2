#include "game/fn_8018AB0C.h"

struct Block_8018A978 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

struct Desc_8018A978 {
    short mUnknown0;
    short mUnknown2;
    Block_8018A978 mUnknown4;
    Block_8018A978 mUnknown16;
    Block_8018A978 mUnknown28;
    Block_8018A978 mUnknown40;
};

struct View_8018A978 {
    char mUnknown0[464];
    float mUnknown464;
    unsigned char mUnknown468;
};

struct Object_8018A978 {
    short mUnknown0;
    short mUnknown2;
    Block_8018A978 mUnknown4;
    Block_8018A978 mUnknown16;
    Block_8018A978 mUnknown28;
    Block_8018A978 mUnknown40;
    View_8018A978 *mpUnknown52;
};

struct Fade_8021CA3C {
    char mUnknown0[12];
    float mUnknown12;
};

extern "C" {
int fn_80163C30(void *p, int value);
void fn_80163CD0(void);
View_8018A978 *fn_801DD168(int type, int flags, Desc_8018A978 *pDesc);
Fade_8021CA3C *fn_8021CA3C(void);
void fn_8018A8C8(int a);
void fn_801CE9E0(int a);
void fn_801CE95C(void);
void fn_80163D64(View_8018A978 *pView, unsigned char value);
void fn_80163D08(View_8018A978 *pView, int value);
void fn_80228D58(View_8018A978 *pView);

void fn_8018A978(Object_8018A978 *p);
void fn_8018AA44(Object_8018A978 *p, int *pDone);
void fn_8018AAE4(Object_8018A978 *p);
void fn_8018AB08(Object_8018A978 *p, int a, int b);
void fn_8018AB64(Object_8018A978 *p, unsigned int message, int a, int *pArgs);

unsigned char lbl_803EB6B0 = 0;

void fn_8018A978(Object_8018A978 *p)
{
    Desc_8018A978 desc;

    desc.mUnknown0 = p->mUnknown0;
    desc.mUnknown2 = p->mUnknown2;
    desc.mUnknown4 = p->mUnknown4;
    desc.mUnknown16 = p->mUnknown16;
    desc.mUnknown28 = p->mUnknown28;
    desc.mUnknown40 = p->mUnknown40;
    p->mpUnknown52 = fn_801DD168(19, 0, &desc);
}

void fn_8018AA44(Object_8018A978 *p, int *pDone)
{
    Fade_8021CA3C *fade = fn_8021CA3C();

    fn_8018A8C8(4);
    fn_801CE9E0(1);
    if (pDone != 0 && *pDone == 0) {
        fn_801CE95C();
        *pDone = 1;
    }
    fn_80163D64(p->mpUnknown52, (unsigned char)(fade->mUnknown12 * 255.0f));
    fn_80163D08(p->mpUnknown52, 1);
    fn_801CE9E0(0);
}

void fn_8018AAE4(Object_8018A978 *p)
{
    fn_80228D58(p->mpUnknown52);
}

void fn_8018AB08(Object_8018A978 *p, int a, int b)
{
}

int fn_8018AB0C(void)
{
    int result = fn_80163C30(0, 40);
    lbl_803EB6B0 = 1;
    return result;
}

void fn_8018AB3C(void)
{
    fn_80163CD0();
    lbl_803EB6B0 = 0;
}

void fn_8018AB64(Object_8018A978 *p, unsigned int message, int a, int *pArgs)
{
    if (p->mUnknown0 != 9) {
        switch (message) {
        case -1:
            fn_8018A978(p);
            break;
        case -2:
            fn_8018AA44(p, pArgs);
            break;
        case -3:
            fn_8018AAE4(p);
            break;
        case 0:
            fn_8018AB08(p, pArgs[0], pArgs[1]);
            break;
        case 4:
            p->mpUnknown52->mUnknown464 = pArgs[0] * 0.01f;
            p->mpUnknown52->mUnknown468 = 1;
            break;
        }
    }
}
}
