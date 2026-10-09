#include <string.h>
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80178D18.h"

extern "C" {

int fn_80178308(void);
int fn_80178320(void);

int fn_801641E0(Object_800670B4 *pObject, int index, const char **ppNames);

/* Returns entry index of row 0, first swapping into row 0 the entry of the
   row that ppNames selects. */
Entry_8006719C *fn_80163E94(Object_800670B4 *pObject, unsigned int index, const char **ppNames)
{
    if (index > 6) {
        index = 0;
    }
    if (ppNames) {
        int row = fn_801641E0(pObject, index, ppNames);

        if (row != -1 && row != 0) {
            Entry_8006719C entry = pObject->mUnknown8.mUnknown84[row][index];

            pObject->mUnknown8.mUnknown84[row][index] = pObject->mUnknown8.mUnknown84[0][index];
            pObject->mUnknown8.mUnknown84[0][index] = entry;
        }
    }
    return &pObject->mUnknown8.mUnknown84[0][index];
}

void fn_80164058(Object_800670B4 *pObject, int row, int index)
{
    Entry_8006719C entry = pObject->mUnknown8.mUnknown84[row][index];

    pObject->mUnknown8.mUnknown84[row][index] = pObject->mUnknown8.mUnknown84[0][index];
    pObject->mUnknown8.mUnknown84[0][index] = entry;
}

/* Looks the names of the null-terminated list ppNames up in the name table
   and returns the first row whose entry index carries the id of a name found
   there, or -1. */
int fn_801641E0(Object_800670B4 *pObject, int index, const char **ppNames)
{
    int row = 0;
    int i = 0;
    int found = 0;
    int j;

    if (ppNames && ppNames[0]) {
        do {
            for (j = 0; j <= 12; j++) {
                if (strcmp(pObject->mUnknown8.mUnknown1C[j].mName, ppNames[i]) == 0) {
                    unsigned short id = pObject->mUnknown8.mUnknown1C[j].mId;

                    for (row = 0; row <= 10; row++) {
                        if (pObject->mUnknown8.mUnknown84[row][index].mUnknown6 == id) {
                            found = 1;
                            break;
                        }
                    }
                    break;
                }
            }
            i++;
        } while (ppNames[i] && found != 1);
    }
    return found == 1 ? row : -1;
}

/* Returns the index of the entry whose mUnknown8 follows that of entry
   index, wrapping to 1 after the team's player count. */
int fn_801642DC(Object_800670B4 *pObject, unsigned char index)
{
    unsigned int count;
    unsigned char next;
    unsigned char i;
    Entry_8006719C *pEntry;

    if (pObject->mUnknown4) {
        count = fn_80178D70(fn_80178308());
    } else {
        count = fn_80178D70(fn_80178320());
    }
    pEntry = &pObject->mUnknown8.mUnknown84[0][index];
    next = pEntry->mUnknown8 + 1;
    if (next > count) {
        next = 1;
    }
    for (i = 0; i < count; i++) {
        pEntry = &pObject->mUnknown8.mUnknown84[0][i];
        if (pEntry->mUnknown8 == next) {
            break;
        }
    }
    return i;
}

/* As fn_801642DC, stepping back and wrapping to the player count. */
int fn_80164384(Object_800670B4 *pObject, unsigned char index)
{
    unsigned int count;
    unsigned char previous;
    unsigned char i;
    Entry_8006719C *pEntry;

    if (pObject->mUnknown4) {
        count = fn_80178D70(fn_80178308());
    } else {
        count = fn_80178D70(fn_80178320());
    }
    pEntry = &pObject->mUnknown8.mUnknown84[0][index];
    if (pEntry->mUnknown8 > 1) {
        previous = pEntry->mUnknown8 - 1;
    } else {
        previous = count;
    }
    for (i = 0; i < count; i++) {
        pEntry = &pObject->mUnknown8.mUnknown84[0][i];
        if (pEntry->mUnknown8 == previous) {
            break;
        }
    }
    return i;
}

void fn_80164430(Object_800670B4 *pObject, unsigned char index, unsigned char *pA, unsigned char *pB)
{
    *pA = pObject->mUnknown8.mUnknown84[0][index].mUnknown1;
    *pB = pObject->mUnknown8.mUnknown84[0][index].mUnknown3;
}

Object_80039F5C *fn_8016444C(Object_800670B4 *pObject)
{
    if (fn_8016871C(fn_80178308())->mUnknown18 & 0x20000) {
        return fn_80039F5C(fn_80178308(), 1);
    }
    return fn_80039F5C(fn_80178308(), pObject->mUnknown8.mUnknownE);
}

void fn_801644A0(Object_80039F5C *p)
{
    Message_800F01CC msg;
    int post = 0;

    fn_801C1F94(&msg, 0, 4);
    msg.mId = 84;
    if (p->mUnknown2914 == 0) {
        int i;
        int count = fn_80178D70(p->mIdBytes[2]);

        for (i = 0; i < count; i++) {
            Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);

            if (pOther->mUnknown2914 == 7 || pOther->mUnknown2914 == 24) {
                msg.mUnknown1[0] = i;
                msg.mUnknown1[1] = 18;
                msg.mUnknown1[2] = 1;
                post = 1;
            }
        }
    }
    if (post) {
        fn_800F03D8(0, p->mpState, &msg, p);
    }
}
}
