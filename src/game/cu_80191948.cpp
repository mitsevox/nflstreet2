#include <string.h>
#include "game/Callees_801D57E0.h"
#include "game/fn_80191948.h"

extern "C" {
int fn_801D6850(void);
void fn_80029BBC(int value, char *pOut, int size);
unsigned int fn_80029838(int value);
int fn_8002A824(void);
char *fn_801D6918(void);
void fn_80191868(int value, char *pOut, int size, int unused, const char *pText);
int fn_801C2D88(char *pOut, int size, const char *pFormat, ...);
void fn_80191C70(int value, int index, char *pA, char *pB, int flag, char *pC, char *pD, char *pE);
extern unsigned char lbl_803EB720;
extern const char lbl_802ABDB8[];
extern const char lbl_802ABD9C[];
extern const char lbl_802ABDBC[];

void fn_80191948(int value, Object_80191948 *pA, Object_80191948 *pB, Object_80191948 *pC)
{
    char text[32];
    char textB[32];
    char textC[32];
    char textD[32];
    int index = fn_801D671C();
    int flag = 0;
    text[0] = lbl_802ABDB8[0];
    textB[0] = lbl_802ABDB8[0];

    switch (value) {
    case 1: case 5: case 8: case 15: case 50: case 59: case 94: case 119: case 122:
        fn_801D6B24(text, 32);
        if (strcmp(text, lbl_802ABD9C) == 0) {
            fn_80029BBC(fn_801D6850(), text, 32);
        }
        break;
    case 63: {
        int key = fn_801D6850();
        if (key < 1 || key > 3) {
            flag = lbl_803EB720;
        }
    }
    case 2:
        switch (fn_801D6850()) {
        case 1:
            fn_80029BBC(fn_801D6850(), text, 32);
            break;
        case 2: case 3:
            fn_801D6B24(textC, 32);
            if (strcmp(textC, lbl_802ABD9C) == 0) {
                fn_80029BBC(fn_801D6850(), text, 32);
            } else {
                fn_80029BBC(fn_801D6850(), textD, 32);
                fn_801C2D88(text, 32, lbl_802ABDBC, textD, textC);
            }
            break;
        }
        break;
    case 4: case 9: case 10: case 17: case 19: case 23: case 51: case 93: case 98: case 99: case 114: case 117: case 123:
        fn_80029BBC(fn_801D6850(), text, 32);
        break;
    case 6: case 91: case 107: case 111: case 113: case 120:
        strcpy(text, fn_801D6918());
        break;
    case 22: case 64: case 65: case 96: case 97: case 115: case 116:
        fn_80029BBC(fn_801D6850(), text, 32);
        fn_80191868(fn_80029838(fn_801D6850()), textB, 32, 0, 0);
        break;
    case 55:
        fn_80191868(fn_8002A824(), text, 32, 0, 0);
        break;
    }
    fn_80191C70(value, index, text, textB, flag, pA->mpUnknown8, pB->mpUnknown8, pC->mpUnknown8);
}
}
