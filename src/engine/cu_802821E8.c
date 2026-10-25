#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"
#include "engine/cu_802821E8.h"

extern Desc_802C2860 lbl_802C2848;
extern Desc_802C2860 lbl_802C2854;
extern unsigned char lbl_802C2878[];
extern short lbl_802C2894[];
extern unsigned char lbl_802C28D0[];
extern unsigned short lbl_802C28EE[];
extern unsigned char lbl_803B7678[];
extern unsigned char lbl_803B775C[];
extern unsigned char lbl_803B785C[];
extern unsigned char lbl_803B7DD4[];
extern int lbl_803ED42C;
extern short lbl_803ED484;
extern unsigned int (*lbl_803ED460)(short count);
void fn_8028490C(Desc_802C2860 *p);
void fn_80284968(Desc_802C2860 *p);
void fn_80284AEC(Desc_802C2860 *p);
void fn_80284D1C(Desc_802C2860 *p);
void fn_80284DD0(Desc_802C2860 *p);
void fn_80284E70(Desc_802C2860 *p);
void fn_80284F78(Desc_802C2860 *p);
unsigned int fn_80283E48(short count);
int fn_802832CC(void);
int fn_80283660(void);
int fn_80282F24(void);
void fn_80282D70(void);
void fn_80285304(unsigned int *sum, unsigned char *data, unsigned int length);
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
extern unsigned short *lbl_803ED448;
extern unsigned short *lbl_803ED450;
extern unsigned short *lbl_803ED44C;
extern unsigned char *lbl_803ED454;
extern unsigned short *lbl_803ED458;
extern unsigned short lbl_803ED45C;
extern short *lbl_803ED464;
extern Struct_803ED474 *lbl_803ED474;
extern Struct_803ED474 *lbl_803ED478;
extern short lbl_803ED47C;
extern short lbl_803ED47E;
extern unsigned int lbl_803ED480;
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
    lbl_803ED440 = 0;
    lbl_803ED424 = 0;
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
    lbl_803ED430 = 2;
    lbl_803ED49C = lbl_803ED4A0 = 0;
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
            case 0:
                break;
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

int fn_8028291C(void)
{
    unsigned int best;
    unsigned short bestPos = 0;
    unsigned short pos;
    unsigned short head;
    unsigned short hash;
    unsigned short next;
    unsigned short search;
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char length;
    unsigned short scan;
    while (lbl_803ED45C <= 0x3FFF) {
        while (lbl_803ED444 <= 228) {
            if (lbl_803ED488 != 0) {
                lbl_803ED44C[lbl_803ED43E] = 16381;
                lbl_803ED488--;
                lbl_803ED440[lbl_803ED43E++] = *lbl_803ED48C++;
                lbl_803ED444++;
                lbl_803ED43E &= 0x7FFF;
            } else if (lbl_803ED474->mUnknown18 == 0) {
                fn_80285304(&lbl_803ED498, lbl_803ED474->mUnknown00, lbl_803ED474->mUnknown04);
                lbl_803ED474->mUnknown08 = lbl_803ED474->mUnknown04;
                return 1;
            } else {
                break;
            }
        }
        if (lbl_803ED444 == 0) {
            break;
        }
        pos = lbl_803ED43C;
        a = lbl_803ED440[pos];
        b = lbl_803ED440[(pos + 1) & 0x7FFF];
        c = lbl_803ED440[(pos + 2) & 0x7FFF];
        hash = ((a << 16) | (b << 8) | c) % 16381U;
        head = lbl_803ED448[hash];
        best = 0;
        search = 0;
        while (lbl_803ED44C[head] == hash) {
            length = 0;
            scan = head;
            if (lbl_803ED440[head] == lbl_803ED440[pos & 0x7FFF] &&
                (pos & 0x7FFF) != lbl_803ED43E) {
                do {
                    length++;
                    scan = (scan + 1) & 0x7FFF;
                    next = (pos + length) & 0x7FFF;
                } while (lbl_803ED440[scan] == lbl_803ED440[next] && next != lbl_803ED43E);
            }
            if (length > best) {
                best = length;
                bestPos = head;
                if (best > 226) {
                    best = 227;
                    break;
                }
            }
            head = lbl_803ED450[head];
            search++;
            if (search > 15) {
                break;
            }
        }
        bestPos = (pos - bestPos) & 0x7FFF;
        if (best > 3 || (best == 3 && bestPos <= 4096)) {
            lbl_803ED454[lbl_803ED45C] = best;
            lbl_803ED458[lbl_803ED45C++] = bestPos;
            next = pos;
            lbl_803ED43C = (pos + best) & 0x7FFF;
            do {
                lbl_803ED44C[next] = hash;
                lbl_803ED450[next] = lbl_803ED448[hash];
                lbl_803ED448[hash] = next;
                next = (next + 1) & 0x7FFF;
                if (next == lbl_803ED43C) {
                    break;
                }
                a = b;
                b = c;
                c = lbl_803ED440[(next + 2) & 0x7FFF];
                hash = ((a << 16) | (b << 8) | c) % 16381U;
            } while (1);
            lbl_803ED444 -= best;
        } else {
            lbl_803ED44C[pos] = hash;
            lbl_803ED450[pos] = lbl_803ED448[hash];
            lbl_803ED448[hash] = pos;
            lbl_803ED43C = pos + 1;
            lbl_803ED454[lbl_803ED45C] = lbl_803ED440[pos];
            lbl_803ED458[lbl_803ED45C++] = 0;
            lbl_803ED43C &= 0x7FFF;
            lbl_803ED444--;
        }
    }
    if (lbl_803ED488 == 0 && lbl_803ED444 == 0 && lbl_803ED474->mUnknown18 != 0) {
        fn_80285304(&lbl_803ED498, lbl_803ED474->mUnknown00, lbl_803ED474->mUnknown04);
    }
    lbl_803ED474->mUnknown08 = lbl_803ED474->mUnknown04 - lbl_803ED488;
    fn_80282D70();
    return 0;
}

void fn_80282D70(void)
{
    Code_802C2860 *a = lbl_802C2848.mpCodes;
    Code_802C2860 *b = lbl_802C2854.mpCodes;
    short i;
    unsigned short j;
    unsigned short n;
    unsigned short d;
    for (i = 0; i <= 284; i++) {
        a[i].mUnknown00 = 0;
    }
    a[256].mUnknown00 = 1;
    for (i = 0; i <= 29; i++) {
        b[i].mUnknown00 = 0;
    }
    for (j = 0; j < lbl_803ED45C; j++) {
        n = lbl_803ED454[j];
        d = lbl_803ED458[j];
        if (d != 0) {
            a[lbl_803B7678[n] + 257].mUnknown00++;
            d--;
            if (d <= 255) {
                d = lbl_803B775C[d];
            } else {
                d = lbl_803B785C[d >> 7];
            }
            b[d].mUnknown00++;
        } else {
            a[n].mUnknown00++;
        }
    }
    fn_801F8014(&lbl_803B543C);
    fn_80284968(&lbl_802C2848);
    fn_80284AEC(&lbl_802C2848);
    fn_80284DD0(&lbl_802C2848);
    fn_80284968(&lbl_802C2854);
    fn_80284AEC(&lbl_802C2854);
    fn_80284DD0(&lbl_802C2854);
    fn_801F809C(&lbl_803B543C);
    fn_8028490C(&lbl_802C2848);
    fn_8028490C(&lbl_802C2854);
    lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04 - lbl_803ED490;
    lbl_803ED428 = fn_80282F24;
    lbl_803ED42C = 0;
}

int fn_80282F24(void)
{
    unsigned short d;
    unsigned char n;
    unsigned char code;
    fn_80285458();
    while ((unsigned int)lbl_803ED42C < lbl_803ED45C) {
        if (lbl_803ED490 == 0) {
            lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04;
            return 2;
        }
        d = lbl_803ED458[lbl_803ED42C];
        n = lbl_803ED454[lbl_803ED42C++];
        if (d != 0) {
            code = lbl_803B7678[n];
            fn_80285394(lbl_802C2848.mpCodes[code + 257].mUnknown02,
                         lbl_802C2848.mpCodes[code + 257].mUnknown00);
            if ((unsigned int)(code - 8) <= 18) {
                fn_80285394(lbl_802C2878[code], (short)(n - lbl_802C2894[code]));
            }
            if (d <= 256) {
                code = lbl_803B775C[d - 1];
            } else {
                code = lbl_803B785C[(d - 1) >> 7];
            }
            fn_80285394(lbl_802C2854.mpCodes[code].mUnknown02,
                         lbl_802C2854.mpCodes[code].mUnknown00);
            if (code > 3) {
                fn_80285394(lbl_802C28D0[code], (unsigned short)(d - lbl_802C28EE[code]));
            }
        } else {
            fn_80285394(lbl_802C2848.mpCodes[n].mUnknown02,
                         lbl_802C2848.mpCodes[n].mUnknown00);
        }
    }
    fn_80285394(lbl_802C2848.mpCodes[256].mUnknown02,
                 lbl_802C2848.mpCodes[256].mUnknown00);
    lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04 - lbl_803ED490;
    lbl_803ED428 = fn_80282800;
    return 0;
}

int fn_802830F0(void)
{
    lbl_803ED484 = (lbl_803ED47E + 1) & 0xFF;
    while (lbl_803ED484 != lbl_803ED486 && lbl_803ED488 != 0) {
        lbl_803B7DD4[lbl_803ED47E] = *lbl_803ED48C;
        lbl_803ED48C++;
        lbl_803ED47E = lbl_803ED484;
        lbl_803ED488--;
        lbl_803ED484 = (lbl_803ED484 + 1) & 0xFF;
    }
    if (lbl_803ED488 == 0 && lbl_803ED474->mUnknown18 == 0) {
        lbl_803ED474->mUnknown08 = lbl_803ED474->mUnknown04;
        return 1;
    }
    if ((unsigned char)fn_80283E48(1) == 0) {
        fn_801F8014(&lbl_803B543C);
        lbl_803ED460 = fn_80283E48;
        fn_80284D1C(&lbl_802C2848);
        fn_80284DD0(&lbl_802C2848);
        fn_80284E70(&lbl_802C2848);
        fn_80284F78(&lbl_802C2848);
        fn_80284D1C(&lbl_802C2854);
        fn_80284DD0(&lbl_802C2854);
        fn_80284E70(&lbl_802C2854);
        fn_80284F78(&lbl_802C2854);
        fn_801F809C(&lbl_803B543C);
        lbl_803ED474->mUnknown08 = lbl_803ED474->mUnknown04 - lbl_803ED488;
        if (lbl_803ED422 != 0) {
            lbl_803ED428 = fn_80283660;
        } else {
            lbl_803ED428 = fn_802832CC;
        }
        return 0;
    }
    fn_80283E48(32);
    lbl_803ED47C = 0;
    lbl_803ED480 = 0;
    lbl_803ED474->mUnknown08 = lbl_803ED474->mUnknown04 - lbl_803ED488;
    lbl_803ED478->mUnknown08 = lbl_803ED478->mUnknown04 - lbl_803ED490;
    lbl_803ED478->mUnknown18 = 1;
    lbl_803ED428 = 0;
    return 0;
}
