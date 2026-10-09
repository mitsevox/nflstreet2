#include <string.h>
#include "game/Object_8007A334.h"
#include "game/cu_80181330.h"
#include "game/fn_8021D7B8.h"

extern void *lbl_803EB688;

static char lbl_802EA934[81] = "";

extern "C" {

int fn_80061C44(void);
int fn_80061CAC(void);
int fn_8005F910(void);
int fn_8005F938(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_80186B38(int a);
int fn_8018F228(int a);
void fn_8018F52C(Object_8007A334 *pObject, int a);
void fn_8018F584(Object_8007A334 *pObject);
int fn_8018F5A4(Object_8007A334 *pObject, int index);
void fn_80183368(int mode, int value);
int fn_801835A0(void);
int fn_80183948(void);
int fn_8022F384(int a);
int fn_8022F4BC(void);

/* Posts message 0x80000006 with the text when it differs from the last
   text posted. */
void fn_80180FA4(const char *pText)
{
    static Params_80005284 sText;

    if (strncmp(pText, lbl_802EA934, 81)) {
        Arg_8018399C args[1];

        strncpy(lbl_802EA934, pText, 81);
        sText.mUnknown0 = 0;
        sText.mLength = 80;
        sText.mpText = lbl_802EA934;
        args[0].pParams = &sText;
        fn_8021D7B8(lbl_803EB688, 0x80000006, 1, args);
    }
}

int fn_80181030(void)
{
    return fn_8018F228(fn_80186B38(fn_8022F4BC())) == 0x3FF;
}

/* Reads sixteen values of the current entry; element 6 is the sum of
   elements 3 to 5. */
void fn_80181064(int *pValues)
{
    Object_8007A334 object;
    int total;

    fn_8018F52C(&object, (signed char)fn_8022F384(fn_8022F4BC()));
    pValues[0] = fn_8018F5A4(&object, 0);
    pValues[1] = fn_8018F5A4(&object, 1);
    pValues[2] = fn_8018F5A4(&object, 14);
    total = pValues[3] = fn_8018F5A4(&object, 3);
    total += pValues[4] = fn_8018F5A4(&object, 4);
    total += pValues[5] = fn_8018F5A4(&object, 5);
    pValues[6] = total;
    pValues[7] = fn_8018F5A4(&object, 13);
    pValues[8] = fn_8018F5A4(&object, 2);
    pValues[9] = fn_8018F5A4(&object, 6);
    pValues[10] = fn_8018F5A4(&object, 7);
    pValues[11] = fn_8018F5A4(&object, 8);
    pValues[12] = fn_8018F5A4(&object, 10);
    pValues[13] = fn_8018F5A4(&object, 9);
    pValues[14] = fn_8018F5A4(&object, 11);
    pValues[15] = fn_8018F5A4(&object, 12);
    fn_8018F584(&object);
}

int fn_801811C8(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x17A:
        *pResult = fn_80181030();
        break;
    case 0x187: {
        int index = pArgs[0].pi[0] + 1;

        fn_80181064(&pArgs[0].pi[index]);
        break;
    }
    default:
        return 0;
    }
    return 1;
}

int fn_80181238(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x173:
        if (fn_8005F910()) {
            *pResult = 1;
            if (!fn_801835A0()) {
                fn_80183368(3, 0x3FF);
            }
        } else if (fn_801835A0() && fn_80183948() == 3) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    case 0x148:
        if (fn_80061C44()) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    case 0x14E:
        if (fn_80061CAC()) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    case 0x146:
    case 0x16E:
        fn_8005F938(id, pArgs, unused, pResult);
        break;
    default:
        return 0;
    }
    return 1;
}
}
