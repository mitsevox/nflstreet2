#include "game/cu_8007F12C.h"
#include "game/Block_80063910.h"
#include "game/fn_80063A0C.h"
#include "game/FELoop.h"
#include "game/fn_8007F828.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_8017F584.h"
#include "game/Object_80228224.h"

extern "C" {
extern void *lbl_803EB688;

int fn_801C6458(int a, int b);
int fn_801E195C(int a);
void fn_80194C5C(int a, int b, int c);
int fn_800B6644(int a);
void fn_80185F4C(int a, int b);
Object_80228224 *fn_8018A854(void);
void fn_8018A7F8(Object_80228224 *pObject, int mode);

static int lbl_803EA620 = 3;
static int lbl_803EA624 = -1;
static int lbl_802D4F5C[21] = {
    24, 0, 8, 6, 10, 9, 11, 12, 3, 4, 5, 24, 14, 15, 16, 17, 1, 2, 1, 18, 19,
};

void fn_80063650(void)
{
    fn_80027DF0();
    lbl_803EA620 = fn_8007F828(6);
}

void fn_8006367C(void)
{
    int value;

    if (lbl_803EA620 != fn_8007F828(6)) {
        if (fn_8007F828(6) == 0) {
            value = 0;
        } else {
            value = 1;
        }
        fn_8021D7B8(lbl_803EB688, 0x8000000F, 1, &value);
        if (fn_8007F828(6) == 1) {
            fn_8018A7F8(fn_8018A854(), 0);
        } else {
            fn_8018A7F8(fn_8018A854(), fn_8007F828(6));
        }
    }
}

void fn_80063728(int value)
{
    lbl_803EA624 = value;
}

void fn_80063730(int id, int flag)
{
    unsigned int i;

    switch (id) {
    case 5:
        if (flag != 0 && fn_8007F828(9) != 0) {
            if (fn_80027DF0() != 0) {
                for (i = 0; i < 8; i++) {
                    if (fn_801E195C(fn_801C6458(i, 0)) == 2) {
                        fn_80194C5C(i, 127, 20);
                    }
                }
            } else {
                for (i = 0; i < 10; i++) {
                    if (fn_801E195C(fn_801C6458(i, 0)) == 2 && fn_800B6644(i) != 255) {
                        fn_80194C5C(i, 127, 20);
                    }
                }
            }
        }
        break;
    case 8:
    case 9:
    case 10:
        fn_80185F4C(id, flag);
        break;
    }
}

void fn_80063824(int index, int value, int notify)
{
    int flag = 0;

    if (lbl_802D4F5C[index] == 24) {
        return;
    }
    if (fn_8017F584() == 8 && lbl_802D4F5C[index] == 8) {
        return;
    }
    if (fn_8007F828(lbl_802D4F5C[index]) == 0 && value != 0) {
        flag = 1;
    }
    fn_8007F6F8(lbl_802D4F5C[index], value);
    if (notify == 1) {
        fn_80063730(index, flag);
    }
}

int fn_800638D0(unsigned int index)
{
    int result = 0;
    int id = fn_80063A0C(index);

    if (id != 24) {
        result = fn_8007F828(id);
    }
    return result;
}

int fn_80063910(unsigned int id, Block_80063910 *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 0x80000005:
        fn_80063728(pBlock->mUnknown0);
        break;
    case 0x80000004:
        fn_80063824(pBlock->mUnknown0, pBlock->mUnknown4, pBlock->mUnknown8);
        break;
    case 0x80000003:
        *pResult = fn_800638D0(pBlock->mUnknown0);
        break;
    case 0x80000007:
        fn_8007F548();
        fn_80063824(5, 1, 0);
        break;
    case 0x80000001:
        fn_80063650();
        break;
    case 0x80000002:
        fn_8006367C();
        break;
    case 0x80000006:
        break;
    default:
        return 0;
    }
    return 1;
}

int fn_80063A0C(unsigned int index)
{
    int id = 24;

    if (index <= 20) {
        id = lbl_802D4F5C[index];
    }
    return id;
}
}
