#include "game/cu_80064864.h"
#include "game/cu_80067C10.h"
#include "game/FELoop.h"
#include "game/InGame.h"

struct Text_80186270 {
    int mUnknown0;
    int mUnknown4;
    char *mpText;
};

union Word_80186324 {
    int mValue;
    Text_80186270 *mpText;
};

struct Params_80186324 {
    int mUnknown0;
    Word_80186324 mUnknown4;
};

extern "C" {
int fn_8006C854(int a, int b);
int fn_801800D0(void);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
int fn_801C6458(int a, int b);
int fn_801E195C(int a);
}

static unsigned char lbl_803EB5D8 = 0;
static unsigned char lbl_803EB5D9 = 0;
static unsigned char lbl_803EB5DA = 0;

extern "C" {

void fn_801861D0(int a, unsigned char b)
{
    lbl_803EB5DA = 0;
    if (lbl_803EB5D8 == 0 && fn_80028310() == 0) {
        fn_80067D4C(0x72, 0);
    } else {
        fn_8006C854(0x78, 0);
    }
    if (lbl_803EB5D9) {
        fn_800652A8();
    }
}

void fn_80186238(int a)
{
}

void fn_8018623C(int index, char *pText)
{
    fn_801C2E18(pText, "%d", index + 1);
}

void fn_80186270(int a, char *pText)
{
    fn_8018623C(fn_801C6458(a, 0), pText);
}

int fn_801862A8(int a)
{
    return a == fn_80065650();
}

int fn_801862E0(int a)
{
    return 0;
}

int fn_801862E8(int a)
{
    return fn_801E195C(fn_801C6458(a, 0)) == 2;
}

unsigned char fn_8018631C(void)
{
    return lbl_803EB5DA;
}

int fn_80186324(unsigned int id, Params_80186324 *pParams, int c, int *pResult)
{
    switch (id) {
    case 0x8000000A:
        lbl_803EB5D9 = pParams->mUnknown0;
        lbl_803EB5DA = 1;
        if (lbl_803EB5D9 == 0) {
            if (fn_80027DF0() != 0 || fn_8006565C() != 0) {
                lbl_803EB5D8 = 1;
                fn_8006C854(0x77, 0);
            } else {
                lbl_803EB5D8 = 0;
                fn_80067D4C(0x71, 0);
            }
        } else {
            lbl_803EB5D8 = 0;
        }
        break;
    case 0x80000001:
        fn_80186270(pParams->mUnknown0, pParams->mUnknown4.mpText->mpText);
        break;
    case 0x80000003:
        fn_801861D0(pParams->mUnknown0, pParams->mUnknown4.mValue);
        break;
    case 0x8000000B:
        fn_80186238(pParams->mUnknown0);
        break;
    case 0x80000002:
        *pResult = fn_801862A8(pParams->mUnknown0);
        break;
    case 0x80000004:
        *pResult = fn_801800D0();
        break;
    case 0x80000005:
        *pResult = fn_801862E0(pParams->mUnknown0);
        break;
    case 0x80000006:
        *pResult = fn_801862E8(pParams->mUnknown0);
        break;
    case 0x80000007:
        *pResult = 0;
        break;
    default:
        return 0;
    }
    return 1;
}

}
