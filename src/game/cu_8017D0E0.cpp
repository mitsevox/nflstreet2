#include <string.h>
#include "game/Object_80039F5C.h"
#include "game/Entry_80219044.h"
#include "game/Object_800785C0.h"
#include "game/cu_80067C10.h"
#include "game/cu_8017DD68.h"
#include "game/fn_8007F828.h"
#include "game/fn_80218FC4.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_800B65A0.h"

extern "C" {
extern void *lbl_803EB688;

int fn_80025708(void);
int fn_8002B5A8(void);
int fn_800A8444(int team);
int fn_800A8488(int team);
Object_80039F5C *fn_800B6544(int index);
int fn_800B6644(int index);
int fn_801486A0(void);
int fn_80156704(void);
int fn_80177F70(void);
int fn_80178308(void);
int fn_80179138(void);
int fn_80188044(int index);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
void fn_8021956C(void *p, int a, int b, int c);

unsigned char fn_8017D0E0(int id);
void fn_8017D670(unsigned char value);
void fn_8017D678(void);
void fn_8017D6B8(int a, int b);
}

static unsigned char lbl_803EB468 = 0;
static char lbl_803EB46C[] = "Mash";
static char lbl_803EB474[] = "Press";
static int lbl_803EB47C = 0;
static int lbl_803EB480 = 0;
static unsigned char lbl_803EB484 = 4;
static unsigned char lbl_803EB485 = 4;
static unsigned char lbl_803EB486 = 0;
static unsigned char lbl_803EB487 = 0;
static unsigned char lbl_803EB488 = 0;

static char lbl_80362964[0x52];
static Entry_80219044 lbl_803629B8;
static Entry_80219044 lbl_803629C4;
static Entry_80219044 lbl_803629D0;
static Entry_80219044 lbl_803629DC;
static char lbl_803ECB3C[4];

extern "C" {

/* Returns the slot of controller id: in modes above 1, controllers whose
   fn_800B6644 value is 1 fill the slots from the front and those with 0 from
   the back; otherwise each controller keeps its own index. */
unsigned char fn_8017D0E0(int id)
{
    char order[4];
    int first = 0;
    int last = 3;
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        order[i] = -1;
    }
    for (i = 0; i <= 3; i++) {
        int index = fn_80188044(i);

        if (index != -1) {
            int side = fn_800B6644(index);
            int mode = fn_801486A0();

            if (mode != 0 && mode != 1) {
                if (side == 1) {
                    order[first++] = i;
                } else if (side == 0) {
                    order[last--] = i;
                }
            } else if (side == 1 || side == 0) {
                order[i] = i;
            }
        }
    }
    for (i = 0; i <= 3; i++) {
        if ((unsigned char)order[i] == id) {
            return i;
        }
    }
    return 0;
}

int fn_8017D1D0(unsigned char id)
{
    return 1;
}

void fn_8017D1D8(unsigned char id)
{
    int args[4];
    Object_80039F5C *p;
    unsigned char own;

    if (fn_80156704()) {
        return;
    }
    p = 0;
    {
        int index = fn_80188044(id);

        if (index != -1) {
            p = fn_800B6544(index);
        }
    }
    if (p == 0) {
        return;
    }
    own = (p->mId >> 8 & 0xFF) == fn_80178308();
    args[2] = lbl_803EB486;
    lbl_803629D0.mpText = lbl_803EB46C;
    args[3] = (int)&lbl_803629D0;
    lbl_803629D0.mLength = strlen(lbl_803629D0.mpText);
    if (p->mUnknown8 != 0xFF) {
        if (!own) {
            if (lbl_803EB480 == p->mId && lbl_803EB485 != id) {
                if (lbl_803EB485 != 4) {
                    args[0] = fn_8017D0E0(lbl_803EB485);
                    args[1] = 0;
                    if (fn_8002B5A8()) {
                        fn_8021D7B8(lbl_803EB688, 0x80000019, 4, args);
                    }
                }
                args[0] = fn_8017D0E0(id);
                args[1] = 1;
                if (fn_8002B5A8() && fn_8017D1D0(id)) {
                    fn_8021D7B8(lbl_803EB688, 0x80000019, 4, args);
                }
                lbl_803EB485 = id;
            }
        }
        if (own) {
            if (lbl_803EB47C == p->mId && lbl_803EB484 != id) {
                if (lbl_803EB484 != 4) {
                    args[0] = fn_8017D0E0(lbl_803EB484);
                    args[1] = 0;
                    if (fn_8002B5A8()) {
                        fn_8021D7B8(lbl_803EB688, 0x80000019, 4, args);
                    }
                }
                args[0] = fn_8017D0E0(id);
                args[1] = 1;
                if (fn_8002B5A8() && fn_8017D1D0(id)) {
                    fn_8021D7B8(lbl_803EB688, 0x80000019, 4, args);
                }
                lbl_803EB484 = id;
            }
        }
    }
    if (!own) {
        if (lbl_803EB485 == id && (lbl_803EB480 == 0 || lbl_803EB480 != p->mId)) {
            args[0] = fn_8017D0E0(id);
            args[1] = 0;
            if (fn_8002B5A8()) {
                fn_8021D7B8(lbl_803EB688, 0x80000019, 4, args);
            }
            lbl_803EB485 = 4;
        }
    }
    if (own) {
        if (lbl_803EB484 == id && (lbl_803EB47C == 0 || lbl_803EB47C != p->mId)) {
            args[0] = fn_8017D0E0(id);
            args[1] = 0;
            if (fn_8002B5A8()) {
                fn_8021D7B8(lbl_803EB688, 0x80000019, 4, args);
            }
            lbl_803EB484 = 4;
        }
    }
}

void fn_8017D4AC(void)
{
    lbl_803EB468 = 1;
    lbl_803EB47C = 0;
    lbl_803EB480 = 0;
    lbl_803EB484 = 4;
    lbl_803EB485 = 4;
    lbl_803EB487 = 0;
    lbl_803EB488 = 0;
    fn_8017DE54(0, 0.0f, 0, 0);
    fn_8017DE54(1, 0.0f, 0, 0);
    fn_8017E620(0, 0);
    fn_8017E620(1, 0);
    if (fn_80025708()) {
        fn_8017D6B8(0, fn_800785C0()->mUnknown1AC);
        fn_8017D6B8(1, fn_800785C0()->mUnknown1A8);
    } else {
        fn_8017D6B8(0, 0);
        fn_8017D6B8(1, 0);
    }
    fn_8017DE54(1, 0.0f, 0, 0);
    fn_8017DE54(0, 0.0f, 0, 0);
    fn_8017DF6C(0, 0);
    fn_8017DF6C(1, 0);
    fn_8017E380(0);
    fn_8017E380(1);
}

void fn_8017D5D8(void)
{
    fn_8017D4AC();
    switch (fn_801486A0()) {
    case 0:
    case 1:
    case 2:
        fn_80218FC4(lbl_803EB688, 3, 0x10, 0, 0);
        break;
    default:
        fn_80218FC4(lbl_803EB688, 3, 3, 0, 0);
        if (fn_80156704()) {
            fn_80218FC4(lbl_803EB688, 7, 0x10, 0, 0);
        }
        break;
    }
    fn_8017D678();
    fn_8017D670(1);
}

void fn_8017D670(unsigned char value)
{
    lbl_803EB468 = value;
}

void fn_8017D678(void)
{
    if (lbl_803EB468) {
        fn_8017D1D8(lbl_803EB487);
        lbl_803EB487++;
        lbl_803EB487 %= 4;
    }
}

void fn_8017D6B8(int a, int b)
{
    int args[2];

    switch (fn_8007F828(14)) {
    case 1:
    case 2:
        break;
    default:
        args[0] = a != 0;
        fn_801C2E18(lbl_803ECB3C, "%d", b);
        lbl_803629B8.mpText = lbl_803ECB3C;
        args[1] = (int)&lbl_803629B8;
        lbl_803629B8.mLength = strlen(lbl_803629B8.mpText);
        fn_8021D7B8(lbl_803EB688, 0x8000000B, 2, args);
        break;
    }
}

void fn_8017D764(void)
{
    int args[1];
    int count = fn_80177F70();

    if (count > 4) {
        count = fn_80177F70() + fn_80179138();
    }
    args[0] = count;
    fn_8021D7B8(lbl_803EB688, 0x80000010, 1, args);
}

void fn_8017D7C4(const char *pText)
{
    Entry_80219044 *args[1];

    strncpy(lbl_80362964, pText, 0x1D);
    args[0] = &lbl_803629C4;
    args[0]->mpText = lbl_80362964;
    args[0]->mLength = strlen(args[0]->mpText);
    fn_8021D7B8(lbl_803EB688, 0x8000000C, 1, args);
    fn_80067D4C(0x13, 0);
}

void fn_8017D844(const char *pText)
{
    Entry_80219044 *args[1];

    strncpy(lbl_80362964, pText, sizeof(lbl_80362964));
    args[0] = &lbl_803629C4;
    args[0]->mpText = lbl_80362964;
    args[0]->mLength = strlen(args[0]->mpText);
    fn_8021D7B8(lbl_803EB688, 0x80000018, 1, args);
    fn_80067D4C(0x13, 0);
}

void fn_8017D8C4(int a, int b, unsigned char c)
{
    lbl_803EB47C = a;
    lbl_803EB480 = b;
    lbl_803EB486 = c;
}

void fn_8017D8D4(void)
{
    int args[4];

    args[2] = 0;
    lbl_803629D0.mpText = lbl_803EB46C;
    args[3] = (int)&lbl_803629D0;
    lbl_803629D0.mLength = strlen(lbl_803629D0.mpText);
    if (lbl_803EB485 != 4) {
        args[0] = fn_8017D0E0(lbl_803EB485);
        args[1] = 0;
        if (fn_8002B5A8()) {
            fn_8021D7B8(lbl_803EB688, 0x80000019, 4, args);
        }
        lbl_803EB485 = 4;
    }
    if (lbl_803EB484 != 4) {
        args[0] = fn_8017D0E0(lbl_803EB484);
        args[1] = 0;
        if (fn_8002B5A8()) {
            fn_8021D7B8(lbl_803EB688, 0x80000019, 4, args);
        }
        lbl_803EB484 = 4;
    }
}

void fn_8017D9B0(int a, int b)
{
    if (lbl_803EB47C == a && lbl_803EB480 == b) {
        lbl_803EB47C = 0;
        lbl_803EB480 = 0;
    }
}

void fn_8017D9D8(int team)
{
    int args[4];

    if (fn_800B65A0(team) == 0xFF || !fn_800A8488(team) || fn_800A8444(team)) {
        return;
    }
    if (team == 0) {
        args[0] = 3;
    } else if (team == 1) {
        args[0] = 0;
    }
    args[1] = 1;
    args[2] = 1;
    lbl_803629DC.mpText = lbl_803EB474;
    args[3] = (int)&lbl_803629DC;
    lbl_803629DC.mLength = strlen(lbl_803629DC.mpText);
    if (fn_8002B5A8()) {
        fn_8021D7B8(lbl_803EB688, 0x80000019, 4, args);
    }
}

void fn_8017DA9C(int team)
{
    int args[4];

    if (fn_800B65A0(team) == 0xFF) {
        return;
    }
    if (team == 0) {
        args[0] = 3;
    } else if (team == 1) {
        args[0] = 0;
    }
    args[1] = 0;
    args[2] = 1;
    lbl_803629DC.mpText = lbl_803EB474;
    args[3] = (int)&lbl_803629DC;
    lbl_803629DC.mLength = strlen(lbl_803629DC.mpText);
    if (fn_8002B5A8()) {
        fn_8021D7B8(lbl_803EB688, 0x80000019, 4, args);
    }
}

void fn_8017DB44(void)
{
    fn_8017D4AC();
    switch (fn_801486A0()) {
    case 0:
    case 1:
    case 2:
        fn_8021956C(lbl_803EB688, 3, 0x10, 1);
        break;
    default:
        fn_8021956C(lbl_803EB688, 3, 3, 1);
        if (fn_80156704()) {
            fn_8021956C(lbl_803EB688, 7, 0x10, 1);
        }
        break;
    }
    fn_8017D670(0);
}

void fn_8017DBCC(void)
{
    int args[1];

    args[0] = 1;
    fn_8021D7B8(lbl_803EB688, 0x8000003A, 1, args);
}

void fn_8017DC08(void)
{
    int args[1];

    args[0] = 0;
    fn_8021D7B8(lbl_803EB688, 0x8000003A, 1, args);
}

void fn_8017DC44(void)
{
    int args[1];

    lbl_803EB488 = 1;
    args[0] = 0;
    fn_8021D7B8(lbl_803EB688, 0x8000001B, 1, args);
}

void fn_8017DC88(void)
{
    int args[1];

    lbl_803EB488 = 0;
    args[0] = 1;
    fn_8021D7B8(lbl_803EB688, 0x8000001B, 1, args);
}

void fn_8017DCCC(void)
{
    int args[1];

    lbl_803EB488 = 1;
    args[0] = 1;
    if (!fn_80156704()) {
        fn_8021D7B8(lbl_803EB688, 0x80000067, 1, args);
    }
}

void fn_8017DD1C(void)
{
    int args[1];

    lbl_803EB488 = 0;
    args[0] = 0;
    fn_8021D7B8(lbl_803EB688, 0x80000067, 1, args);
}

unsigned char fn_8017DD60(void)
{
    return lbl_803EB488;
}

}
