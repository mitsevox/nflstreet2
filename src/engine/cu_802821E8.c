#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"
#include "engine/cu_802821E8.h"

extern unsigned char lbl_803EC584;
extern unsigned char lbl_803ED420;
extern unsigned char lbl_803ED421;
extern unsigned char lbl_803ED422;
extern int lbl_803ED424;
extern int (*lbl_803ED428)(void);
extern int lbl_803ED430;
extern int (*lbl_803ED434)(void);
extern unsigned short lbl_803ED43C;
extern unsigned short lbl_803ED43E;
extern unsigned char *lbl_803ED440;
extern short lbl_803ED444;
extern short *lbl_803ED448;
extern void *lbl_803ED450;
extern short *lbl_803ED44C;
extern void *lbl_803ED454;
extern void *lbl_803ED458;
extern short lbl_803ED45C;
extern short *lbl_803ED464;
extern Struct_803ED474 *lbl_803ED474;
extern Struct_803ED474 *lbl_803ED478;
extern short lbl_803ED47C;
extern short lbl_803ED47E;
extern unsigned int lbl_803ED480;
extern short lbl_803ED484;
extern short lbl_803ED486;
extern int lbl_803ED488;
extern unsigned char *lbl_803ED48C;
extern int lbl_803ED490;
extern unsigned char *lbl_803ED494;
extern unsigned int lbl_803ED498;
extern short lbl_803ED49C;
extern unsigned int lbl_803ED4A0;
extern int lbl_803ED4A4;
extern unsigned char *lbl_803ED4A8;
extern int lbl_803ED4AC;
extern unsigned char *lbl_803ED4B0;
extern Lock_801F8014 lbl_803B53FC;
extern Lock_801F8014 lbl_803B541C;
extern Lock_801F8014 lbl_803B543C;

int fn_80282800(void);
int fn_802828BC(void);
int fn_8028291C(void);
int fn_802830F0(void);
int fn_80284030(void);
void fn_802851E8(void);
void fn_80285394(short count, unsigned int value);
void fn_80285458(void);
void fn_802854D8(void);
int fn_8028257C(Struct_803ED474 *a, Struct_803ED474 *b);
void fn_80282624(Struct_803ED474 *a, Struct_803ED474 *b, int mode);
int fn_80282740(Struct_803ED474 *a, Struct_803ED474 *b, int mode);

int fn_802821E8(void)
{
    if (lbl_803EC584 == 0) {
        lbl_803EC584 = 1;
        lbl_803ED424 = 0;
        lbl_803ED430 = 0;
        fn_801F7FA8(&lbl_803B53FC);
        fn_801F7FA8(&lbl_803B541C);
        fn_801F7FA8(&lbl_803B543C);
        lbl_803ED440 = 0;
        return 0;
    }
    return 0x150001;
}

int fn_80282260(void)
{
    if (lbl_803EC584 != 0 && lbl_803ED424 == 0 && lbl_803ED430 == 0) {
        fn_801F80D0(&lbl_803B53FC);
        fn_801F80D0(&lbl_803B541C);
        fn_801F80D0(&lbl_803B543C);
        lbl_803EC584 = 0;
        return 0;
    }
    return 0x150002;
}

int fn_802822E0(void)
{
    unsigned short i;
    fn_801F8014(&lbl_803B53FC);
    lbl_803ED424 = 1;
    lbl_803ED440 = fn_801D2BB0(1, 0x8000, 0, 0);
    lbl_803ED448 = fn_801D2BB0(1, 0x7FFA, 0, 0);
    lbl_803ED450 = fn_801D2BB0(1, 0x10000, 0, 0);
    lbl_803ED44C = fn_801D2BB0(1, 0x10002, 0, 0);
    for (i = 0; i <= 0x3FFC; i++) {
        lbl_803ED448[i] = -32768;
    }
    lbl_803ED44C[0x8000] = 0x3FFD;
    lbl_803ED454 = fn_801D2BB0(1, 0x4000, 0, 0);
    lbl_803ED458 = fn_801D2BB0(1, 0x8000, 0, 0);
    lbl_803ED464 = fn_801D2BB0(1, 0x474, 0, 0);
    fn_802851E8();
    lbl_803ED45C = 0;
    lbl_803ED47E = 0;
    lbl_803ED498 = 1;
    lbl_803ED428 = fn_80282800;
    lbl_803ED43C = 0;
    lbl_803ED43E = 0;
    lbl_803ED444 = 0;
    lbl_803ED480 = 0;
    lbl_803ED47C = 0;
    lbl_803ED486 = 0;
    return 0;
}

void fn_8028243C(void)
{
    fn_801D2BD0(lbl_803ED464);
    fn_801D2BD0(lbl_803ED458);
    fn_801D2BD0(lbl_803ED454);
    fn_801D2BD0(lbl_803ED44C);
    fn_801D2BD0(lbl_803ED450);
    fn_801D2BD0(lbl_803ED448);
    fn_801D2BD0(lbl_803ED440);
    lbl_803ED424 = 0;
    lbl_803ED440 = 0;
    fn_801F809C(&lbl_803B53FC);
}

int fn_802824A8(Struct_803ED474 *a, Struct_803ED474 *b)
{
    if (a->mUnknown18 != 0 && b->mUnknown18 != 0) {
        return fn_8028257C(a, b);
    }
    fn_801F8014(&lbl_803B53FC);
    lbl_803ED47E = 0;
    lbl_803ED424 = 2;
    lbl_803ED43C = 0;
    lbl_803ED43E = 0;
    lbl_803ED444 = 0;
    lbl_803ED45C = 0;
    lbl_803ED480 = 0;
    lbl_803ED47C = 0;
    lbl_803ED486 = 0;
    if (b->mUnknown18 != 0) {
        lbl_803ED422 = 1;
    } else {
        lbl_803ED422 = 0;
        lbl_803ED440 = fn_801D2BB0(1, 0x8000, 0, 0);
    }
    lbl_803ED498 = 1;
    lbl_803ED428 = fn_802830F0;
    return 0;
}

int fn_8028257C(Struct_803ED474 *a, Struct_803ED474 *b)
{
    fn_801F8014(&lbl_803B541C);
    lbl_803ED49C = 0;
    lbl_803ED4A0 = 0;
    lbl_803ED430 = 2;
    lbl_803ED434 = fn_80284030;
    return 1;
}

void fn_802825C8(Struct_803ED474 *a, Struct_803ED474 *b, int mode)
{
    if (mode == 1) {
        fn_80282624(a, b, 1);
    } else {
        if (lbl_803ED440 != 0) {
            fn_801D2BD0(lbl_803ED440);
            lbl_803ED440 = 0;
        }
        lbl_803ED424 = 0;
        fn_801F809C(&lbl_803B53FC);
    }
}

void fn_80282624(Struct_803ED474 *a, Struct_803ED474 *b, int mode)
{
    lbl_803ED430 = 0;
    fn_801F809C(&lbl_803B541C);
}

int fn_80282654(Struct_803ED474 *a, Struct_803ED474 *b, int mode)
{
    if (mode == 1) {
        return fn_80282740(a, b, 1);
    }
    lbl_803ED420 = 1;
    lbl_803ED474 = a;
    lbl_803ED48C = a->mUnknown00 + a->mUnknown08;
    lbl_803ED488 = a->mUnknown04 - a->mUnknown08;
    lbl_803ED490 = b->mUnknown04 - b->mUnknown08;
    lbl_803ED494 = b->mUnknown00 + b->mUnknown08;
    lbl_803ED478 = b;
    if (lbl_803ED428 != 0) {
        do {
            switch ((unsigned char)lbl_803ED428()) {
            case 1:
                lbl_803ED420 = 0;
                return 2;
            case 2:
                lbl_803ED420 = 0;
                return 3;
            }
        } while (lbl_803ED428 != 0);
    }
    lbl_803ED420 = 0;
    return 1;
}

int fn_80282740(Struct_803ED474 *a, Struct_803ED474 *b, int mode)
{
    lbl_803ED421 = 1;
    lbl_803ED4A4 = a->mUnknown04 - a->mUnknown08;
    lbl_803ED4A8 = a->mUnknown00 + a->mUnknown08;
    lbl_803ED4AC = b->mUnknown04 - b->mUnknown08;
    lbl_803ED4B0 = b->mUnknown00 + b->mUnknown08;
    if (lbl_803ED434 != 0) {
        do {
            lbl_803ED434();
        } while (lbl_803ED434 != 0);
    }
    a->mUnknown08 = a->mUnknown04 - lbl_803ED4A4;
    b->mUnknown08 = b->mUnknown04 - lbl_803ED4AC;
    lbl_803ED421 = 0;
    return 1;
}

int fn_80282800(void)
{
    if (lbl_803ED488 == 0 && lbl_803ED474->mUnknown18 != 0 && lbl_803ED444 == 0) {
        fn_80285394(1, 1);
        fn_80285394(32, lbl_803ED498);
        fn_802854D8();
        lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04 - lbl_803ED490;
        lbl_803ED428 = fn_802828BC;
    } else {
        fn_80285394(1, 0);
        lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04 - lbl_803ED490;
        lbl_803ED428 = fn_8028291C;
        lbl_803ED45C = 0;
    }
    return 0;
}

int fn_802828BC(void)
{
    fn_80285458();
    lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04 - lbl_803ED490;
    if (lbl_803ED486 != lbl_803ED47E) {
        return 2;
    }
    lbl_803ED478->mUnknown18 = 1;
    lbl_803ED428 = 0;
    return 0;
}
