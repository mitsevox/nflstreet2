#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/Object_8007A334.h"
#include "game/cu_8007C9D4.h"

struct Desc_8021DEFC {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
int fn_80033144(void *p);
int fn_8007A934(Object_8007A334 *pObject, int key);
void fn_80083E1C(Object_8007A334 *pObject, int a);
void *fn_8021DEFC(Desc_8021DEFC *pDesc);
void fn_8021E050(void *pList, int index, const char *pName, int a, int b);
void fn_8021E0B0(void *pList, int index, const char *pName, int a, int b, int c);
int fn_8021E504(void *pList, int index, int value);
void fn_8021EA34(int index, void *p);
void *fn_8021EA44(int index);
}

extern char lbl_802EBE68[];
extern char lbl_802EBE88[];
extern char lbl_802EBE98[];
extern char lbl_802EBEA8[];
extern char lbl_802EBEB8[];
extern char lbl_802EBEC8[];
extern char lbl_802EBED8[];
extern char lbl_802EBEE8[];
extern char lbl_802EBEF8[];
extern char lbl_802EBF08[];
extern char lbl_802EBF18[];
extern char lbl_802EBF28[];
extern char lbl_802EBF38[];
extern char lbl_802EBF48[];
extern char lbl_802EBF58[];
extern char lbl_802EBF68[];
extern char lbl_802EBF78[];
extern char lbl_80306B34[];

extern "C" {
void fn_801A60D8(void)
{
    void *pList = fn_8021EA44(1);

    fn_8021E050(pList, 0, lbl_802EBE68, 1, 16);
    fn_8021E0B0(pList, 3, lbl_802EBEA8, 1, 0, 196);
    fn_8021E0B0(pList, 2, lbl_802EBE98, 1, 0, 200);
    fn_8021E0B0(pList, 5, lbl_802EBEC8, 1, 0, 65);
}

void fn_801A6180(void)
{
    int flag = fn_80033144(lbl_80306B34);
    void *pList = fn_8021EA44(1);

    if (flag == 0) {
        fn_8021E0B0(pList, 1, lbl_802EBE88, 1, 0, 196);
        fn_8021E0B0(pList, 6, lbl_802EBED8, 1, 0, 212);
        fn_8021E0B0(pList, 7, lbl_802EBEE8, 1, 0, 212);
        fn_8021E0B0(pList, 4, lbl_802EBEB8, 1, 0, 84);
    } else {
        fn_8021E0B0(pList, 1, lbl_802EBE88, 1, 0, 132);
        fn_8021E0B0(pList, 6, lbl_802EBED8, 1, 0, 132);
        fn_8021E0B0(pList, 7, lbl_802EBEE8, 1, 0, 132);
        fn_8021E0B0(pList, 4, lbl_802EBEB8, 1, 0, 4);
    }
    fn_8021E0B0(pList, 10, lbl_802EBF08, 1, 0, 52);
    fn_8021E0B0(pList, 8, lbl_802EBEF8, 1, 0, 180);
    fn_8021E0B0(pList, 11, lbl_802EBF18, 1, 0, 132);
    fn_8021E0B0(pList, 12, lbl_802EBF28, 1, 0, 52);
    fn_8021E0B0(pList, 14, lbl_802EBF38, 1, 0, 180);
    fn_8021E0B0(pList, 16, lbl_802EBF48, 1, 0, 180);
    fn_8021E0B0(pList, 17, lbl_802EBF58, 1, 0, 180);
    fn_8021E0B0(pList, 19, lbl_802EBF68, 1, 0, 180);
    fn_8021E0B0(pList, 20, lbl_802EBF78, 1, 0, 180);
}

void fn_801A63E8(void)
{
    Object_8007A334 cursor;
    int first = 0;
    int second = 0;
    void *pList = fn_8021EA44(1);

    fn_8021E0B0(pList, 1, lbl_802EBE88, 1, 0, 180);
    fn_8021E0B0(pList, 6, lbl_802EBED8, 1, 0, 132);
    fn_8021E0B0(pList, 7, lbl_802EBEE8, 1, 0, 132);
    fn_8021E0B0(pList, 4, lbl_802EBEB8, 1, 0, 20);
    fn_8021E0B0(pList, 10, lbl_802EBF08, 1, 0, 52);
    fn_8021E0B0(pList, 8, lbl_802EBEF8, 1, 0, 132);
    fn_8021E0B0(pList, 11, lbl_802EBF18, 1, 0, 196);
    fn_8021E0B0(pList, 12, lbl_802EBF28, 1, 0, 4);
    fn_8021E0B0(pList, 14, lbl_802EBF38, 1, 0, 132);
    fn_8021E0B0(pList, 16, lbl_802EBF48, 1, 0, 132);
    fn_8021E0B0(pList, 17, lbl_802EBF58, 1, 0, 132);
    fn_8021E0B0(pList, 19, lbl_802EBF68, 1, 0, 132);
    fn_8021E0B0(pList, 20, lbl_802EBF78, 1, 0, 132);
    fn_8021E504(pList, 1, 0);
    fn_8021E504(pList, 1, 1);
    fn_8021E504(pList, 1, 2);
    fn_8021E504(pList, 1, 10);
    fn_8021E504(pList, 1, 11);
    fn_8021E504(pList, 1, 12);
    fn_8021E504(pList, 1, 13);
    fn_8021E504(pList, 1, 14);
    fn_8021E504(pList, 1, 15);
    fn_8021E504(pList, 7, 4);
    fn_80083E1C(&cursor, 0);
    if (fn_80084034(&cursor, fn_8007CB6C(0), 0)) {
        first = fn_8007A934(&cursor, 0x4C474C54);
    }
    if (fn_80084034(&cursor, fn_8007CB6C(1), 0)) {
        second = fn_8007A934(&cursor, 0x4C474C54);
    }
    fn_80083F68(&cursor);
    fn_8021E504(pList, 4, first);
    if (second != first) {
        fn_8021E504(pList, 4, second);
    }
    fn_8021E504(pList, 4, 0);
}

void fn_801A6730(void)
{
    Desc_8021DEFC desc;

    desc.mUnknown0 = 21;
    desc.mUnknown4 = 21;
    desc.mUnknown8 = 1;
    fn_8021EA34(1, fn_8021DEFC(&desc));
    fn_801A60D8();
    if (fn_80027DF0()) {
        fn_801A6180();
    } else if (fn_8002894C()) {
        fn_801A63E8();
    }
}
}
