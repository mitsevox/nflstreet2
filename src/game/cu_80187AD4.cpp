#include <stdio.h>
#include <string.h>
#include "game/Entry_80219044.h"
#include "game/Object_80039F5C.h"
#include "game/fn_801C3284.h"
#include "game/fn_801FCE10.h"

struct Object_80056584;

extern "C" {
extern unsigned short lbl_802EAB80;
extern unsigned short lbl_802EABB4;
extern char lbl_802EABC0[];
extern char lbl_802EABD0[];
extern char lbl_802EABD8[];
extern int lbl_802EACAC[10];
extern int lbl_803EB5E8;
extern unsigned int lbl_803EB610;
extern unsigned char lbl_803EB615;
extern unsigned char lbl_803EB616;
extern unsigned char lbl_803EB61A;
extern char lbl_803EB628[];
extern void *lbl_803EB68C;
extern char lbl_80362BE0[];
extern Entry_80219044 lbl_80362BBC[3];
extern Entry_80219044 *lbl_80362BB0[3];

int fn_801F95C8(void);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_80180EF8(int id);
void *fn_8021EA44(int index);
int fn_8021E72C(void *pObject, int a, int b);
int fn_8022E558(void);
int fn_8022E560(void);
int fn_80219044(void *p, int a, int b, int c, Entry_80219044 **ppEntries);
void fn_8021956C(void *p, int a, int b, int c);
void fn_801CAF24(void);
void fn_8006CA84(int a);
void fn_8018A7B0(void);
void fn_80023024(int a);
void fn_80187E08(int show, const char *pText, int a, int b);
extern unsigned char lbl_803EB61D;
extern unsigned char lbl_803EB624;
extern unsigned char lbl_803EB61B;

void fn_801F87FC(int a);
int fn_8017F60C(void);
void fn_8002129C(char *pDest, int length);
int fn_801C2D88(char *pDest, int length, const char *pFormat, ...);

void fn_80187AD4(int id)
{
    char text[24];
    char shortText[16];
    char displayText[24];
    int type = -1;
    int database = fn_801F95C8();
    int result = fn_801FCE10(0, "use \x8c select 'PYTT' into \x82 from 'MAET' where 'DIGT' = \x82\n",
                            database, &type, id);
    if ((result == 0 && id != lbl_802EABB4 && (unsigned short)id != 0x3FF
         && (unsigned short)id != 0x3F7 && id != 0x3F9) || type == 5) {
        if (fn_801FCE10(0, "use \x8c select 'ANLT' into \x88 and 'ANST' into \x88 and 'ANDT' into \x88 from 'MAET' where 'DIGT' = \x82\n",
                        database, text, shortText, displayText, id) == 0) {
            lbl_802EABB4 = id;
        }
        strcpy(lbl_802EABC0, text);
        strcpy(lbl_802EABD0, shortText);
        strcpy(lbl_802EABD8, displayText);
    } else if (result == 23 || id == 0x3F9) {
        lbl_802EABB4 = 0x3FF;
    }
}

void fn_80187C0C(void)
{
    if (lbl_802EACAC[0] == 10) {
        for (int i = 9; i >= 0; --i) {
            lbl_802EACAC[i] = i;
        }
    }
    lbl_802EAB80 = 0x7FFF;
    lbl_802EABB4 = 0x3FF;
}

void fn_80187C5C(unsigned char value)
{
    lbl_803EB61A = value;
}

unsigned char fn_80187C64(void)
{
    return lbl_803EB61A;
}

int fn_80187C6C(void)
{
    return fn_8022E560();
}

int fn_80187C8C(void)
{
    return fn_8022E558();
}

void fn_80187CAC(int id, char *pText, int size)
{
    if (id != 0x3FF) {
        fn_80187AD4(id);
        fn_801C2EF0(pText, lbl_802EABD8, size);
    } else {
        fn_801C2EF0(pText, "", size);
    }
}

void fn_80187D10(void)
{
    void *pList = fn_8021EA44(1);
    for (unsigned char team = 0; team < 2; ++team) {
        for (unsigned char index = 0; index < 7; ++index) {
            Object_80039F5C *p = fn_80039F5C(team, index);
            if (p->mUnknown9[2] != 0) {
                int id = fn_80180EF8(p->mUnknown2908);
                if (id > 630) {
                    fn_8021E72C(pList, 10, id);
                }
            }
            if ((unsigned char)(index % 10) == 9) {
                fn_80023024(1);
            }
        }
    }
}

void fn_80187DD0(int value)
{
    lbl_803EB5E8 = value;
}

void fn_80187DD8(int show)
{
    fn_80187E08(show, "Please wait...", 1, 1);
}

void fn_80187E08(int show, const char *pText, int a, int b)
{
    if (show != 0) {
        if (lbl_803EB610 < 0xFFFFFFFFU) {
            ++lbl_803EB610;
        }
        if (lbl_803EB610 == 1) {
            fn_801C3284(lbl_80362BE0, pText, 255);
            lbl_803EB615 = a;
            lbl_80362BBC[0].mUnknown0 = 0;
            lbl_803EB616 = b;
            lbl_80362BBC[0].mpText = lbl_803EB628;
            lbl_80362BBC[0].mLength = strlen(lbl_803EB628) + 1;
            lbl_80362BBC[1].mLength = 255;
            lbl_80362BBC[1].mpText = lbl_80362BE0;
            lbl_80362BBC[2].mUnknown0 = 0;
            lbl_80362BBC[2].mpText = lbl_803EB628;
            lbl_80362BBC[1].mUnknown0 = 0;
            lbl_80362BBC[2].mLength = strlen(lbl_803EB628) + 1;
            lbl_80362BB0[0] = &lbl_80362BBC[0];
            lbl_80362BB0[1] = &lbl_80362BBC[1];
            lbl_80362BB0[2] = &lbl_80362BBC[2];
            fn_80219044(lbl_803EB68C, 1, 3, 3, lbl_80362BB0);
            fn_801CAF24();
            fn_8006CA84(1);
            fn_8018A7B0();
        }
    } else {
        if (lbl_803EB610 != 0) {
            --lbl_803EB610;
            if (lbl_803EB610 != 0) {
                return;
            }
        }
        fn_8021956C(lbl_803EB68C, 1, 3, 1);
    }
}

int fn_80187F44(char *pText0, int length0, char *pText1, int length1,
                char *pText2, int length2, char *pText3, int length3)
{
    fn_801C3284(pText0, "NGC", length0);
    fn_801C3284(pText1, "Memory Card", length1);
    fn_801C3284(pText2, "Memory Card", length2);
    fn_801C3284(pText3, "Memory Card Slot", length3);
    return 2;
}

void fn_80187FD0(void)
{
    lbl_803EB61D = 1;
}

void fn_80187FDC(void)
{
    if (lbl_803EB61D == 1) {
        fn_801F87FC(1);
    }
    lbl_803EB61D = 0;
}

void fn_80188014(int value)
{
    lbl_803EB624 = value;
}

void fn_8018801C(int index, int value)
{
    lbl_802EACAC[index] = value;
}

int fn_80188030(int index)
{
    return lbl_802EACAC[index];
}

int fn_80188044(int value)
{
    for (int i = 0; i < 10; ++i) {
        if (lbl_802EACAC[i] == value) {
            return i;
        }
    }
    return -1;
}

void fn_8018807C(unsigned char value)
{
    if (fn_8017F60C() == 0) {
        lbl_803EB61B = value;
    }
}

void fn_801880B4(char *pText, int length)
{
    fn_8002129C(pText, length);
}

void fn_801880D4(int value, char *pText, int length)
{
    char previous[32];
    int negative = value < 0;
    value = value < 0 ? -value : value;
    pText[0] = 0;
    while (value != 0) {
        int remaining = value / 1000;
        unsigned short group = value % 1000;
        value = remaining;
        if (remaining == 0) {
            if (strlen(pText) != 0) {
                strcpy(previous, pText);
                sprintf(pText, "%d,%s", group, previous);
            } else {
                sprintf(pText, "%d", group);
            }
        } else if (strlen(pText) != 0) {
            strcpy(previous, pText);
            sprintf(pText, "%03d,%s", group, previous);
        } else {
            sprintf(pText, "%03d", group);
        }
    }
    if (strlen(pText) == 0) {
        sprintf(pText, "0");
    }
    if (negative) {
        strcpy(previous, pText);
        sprintf(pText, "-%s", previous);
    }
}

void fn_80188248(Object_80056584 *pObject, char *pText, int length)
{
    Object_80039F5C *p = (Object_80039F5C *)pObject;
    signed char initial = p->mUnknown2927[0];
    if (initial == 0 || initial == ' ') {
        fn_801C2D88(pText, length, "%s", p->mUnknown2927 + 21);
    } else {
        fn_801C2D88(pText, length, "%c. %s", initial, p->mUnknown2927 + 21);
    }
}
}
