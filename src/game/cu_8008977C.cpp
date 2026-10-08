#include "game/Record_8036B55C.h"
#include "game/Object_8008044C.h"
#include "game/Object_801BBD5C.h"
#include "game/fn_801BA2A8.h"
#include "game/fn_802372EC.h"
#include "game/Table_80089904.h"
#include "game/fn_801BE60C.h"
#include <string.h>

struct Header_8008977C {
    unsigned char mUnknown0[2];
    unsigned short mUnknown2;
};

struct Transition_80089A84 {
    unsigned char mType;
    unsigned char mValue;
};

extern "C" {
void fn_800225F4(int index, unsigned int value);
unsigned char fn_800DA53C(unsigned short index);
Object_8008044C *fn_80182DC8(void);
Object_801BBD5C *fn_801BBD5C(unsigned short a, unsigned short b);
int fn_8008A20C(unsigned int value);
}

static unsigned short sValues[15] = {
    16, 21, 22, 19, 20, 17, 18, 23, 24, 25, 26, 27, 28, 29, 30
};
static unsigned short sCurrent[14] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static int sTop[14] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
static unsigned char sPending[14] = {0};
static Transition_80089A84 sTransitions[14][3];
static unsigned char sWaiting = 0;
static int sCountdown = 0;
static unsigned char sSelect = 1;
static int sLast = -1;

extern "C" {
int fn_8008977C(Record_8036B55C *pRecord, Table_80089904 *pTable, unsigned int value)
{
    unsigned char values[4];
    int best = -1;
    unsigned short id;
    Object_801BBD5C *pObject;

    fn_801BBC3C(((Header_8008977C *)pRecord->mUnknown796)->mUnknown2, 74, pTable);
    memset(values, 255, sizeof(values));
    values[0] = 1;
    id = pTable->mEntries[fn_8009C56C(pTable, values)].mUnknown2 & 0x7FFF;
    fn_801BBC3C(((Header_8008977C *)pRecord->mUnknown796)->mUnknown2, id, pTable);
    memset(values, 255, sizeof(values));
    values[0] = fn_800DA53C(value - 31);
    id = pTable->mEntries[fn_8009C56C(pTable, values)].mUnknown2 & 0x7FFF;
    fn_801BBC3C(((Header_8008977C *)pRecord->mUnknown796)->mUnknown2, id, pTable);
    memset(values, 255, sizeof(values));
    values[0] = 1;
    id = pTable->mEntries[fn_8009C56C(pTable, values)].mUnknown2 & 0x7FFF;
    fn_801BBC3C(((Header_8008977C *)pRecord->mUnknown796)->mUnknown2, id, pTable);
    pObject = fn_801BBD5C(id, ((Header_8008977C *)pRecord->mUnknown796)->mUnknown2);
    if (pObject->mCount != 0) {
        best = 0;
        for (unsigned char i = 1; i < pObject->mCount; i++) {
            if (!(pObject->mValues[best].mValue >= pObject->mValues[i].mValue)) {
                best = i;
            }
        }
    }
    return best;
}

int fn_80089904(Record_8036B55C *pRecord, Table_80089904 *pTable,
                unsigned int value, int type)
{
    int result = -1;
    unsigned short best = 0;
    int category = 7;

    if (sSelect != 0) {
        if (type == 2 && value > 30) {
            result = fn_8008977C(pRecord, pTable, value);
            sLast = result;
        } else {
            int current = fn_80080E20(fn_80182DC8());
            for (int i = 0; i < pTable->mCount; i++) {
                unsigned short score = 0;
                Info_80089904 *pInfo = pTable->mEntries[i].mpInfo;
                if (pInfo->mValue == value) {
                    score = 1000;
                }
                if (pInfo->mType == type) {
                    score += 1000;
                }
                int subtype = pInfo->mUnknown6;
                switch (subtype) {
                case 10: category = 0; break;
                case 12: category = 1; break;
                case 13: category = 2; break;
                }
                if (current == category || subtype == 1) {
                    score += 500;
                }
                score += fn_802372EC(0, 100);
                if (score > best && score >= 2000) {
                    sLast = i;
                    best = score;
                    result = i;
                }
            }
        }
    } else {
        result = sLast;
    }
    if (result >= 0 && fn_8008A20C(value)) {
        sSelect = !sSelect;
    }
    return result;
}

void fn_80089A84(Record_8036B55C *pRecord, unsigned int value)
{
    int index = pRecord->mUnknown1;
    Transition_80089A84 previous;

    if (sCurrent[index] == value) {
        if (sTop[index] > -1) {
            previous = sTransitions[index][sTop[index]];
            if (!fn_8008A20C(previous.mValue)) {
                sTransitions[index][1] = previous;
                sTransitions[index][0].mType = previous.mType == 3 ? 1 : 3;
                sTransitions[index][0].mValue = previous.mValue;
                sTop[index] = 1;
            }
        }
    } else if (sTop[index] > -1) {
        if (sTransitions[index][0].mType == 3 && sTransitions[index][0].mValue == value) {
            return;
        }
        previous = sTransitions[index][sTop[index]];
        switch (previous.mType) {
        case 1:
            if (value == 2) {
                sTransitions[index][0] = previous;
                sTop[index] = 0;
            } else {
                sTransitions[index][1] = previous;
                sTransitions[index][0].mValue = value;
                sTop[index] = 1;
                sTransitions[index][0].mType = 3;
            }
            break;
        case 3:
            if (value == 2) {
                sTransitions[index][1] = previous;
                sTransitions[index][0].mValue = previous.mValue;
                sTop[index] = 1;
                sTransitions[index][0].mType = 1;
            } else if (fn_8008A20C(value)) {
                sTransitions[index][2] = previous;
                sTransitions[index][0].mValue = value;
                sTop[index] = 2;
                sTransitions[index][1].mType = 1;
                sTransitions[index][1].mValue = previous.mValue;
                sTransitions[index][0].mType = 4;
            } else {
                sTransitions[index][2] = previous;
                sTransitions[index][0].mValue = value;
                sTop[index] = 2;
                sTransitions[index][1].mType = 1;
                sTransitions[index][1].mValue = previous.mValue;
                sTransitions[index][0].mType = 3;
            }
            break;
        case 4:
            if (value == 2 || fn_8008A20C(value)) {
                sCurrent[index] = value;
            } else if (value > 31) {
                sCurrent[index] = value;
                sPending[index] = 1;
            } else {
                sTransitions[index][1] = previous;
                sTransitions[index][0].mValue = value;
                sTop[index] = 1;
                sTransitions[index][0].mType = 3;
            }
            break;
        }
    } else {
        if (sCurrent[index] == 2) {
            if (fn_8008A20C(value)) {
                sCurrent[index] = value;
                sTop[index] = 0;
                sTransitions[index][0].mValue = value;
                sTransitions[index][0].mType = 4;
            } else {
                sTop[index] = 0;
                sTransitions[index][0].mValue = value;
                sTransitions[index][0].mType = 3;
            }
        } else if (value == 2) {
            sTransitions[index][0].mValue = sCurrent[index];
            sTop[index] = 0;
            sTransitions[index][0].mType = 1;
        } else if (fn_8008A20C(value)) {
            sTransitions[index][0].mValue = value;
            sTop[index] = 1;
            sTransitions[index][1].mType = 1;
            sTransitions[index][1].mValue = sCurrent[index];
            sTransitions[index][0].mType = 4;
        } else {
            sTransitions[index][0].mValue = value;
            sTop[index] = 1;
            sTransitions[index][1].mType = 1;
            sTransitions[index][1].mValue = sCurrent[index];
            sTransitions[index][0].mType = 3;
        }
        fn_801BE068(pRecord->mUnknown792, pRecord->mUnknown796,
                   pRecord->mUnknown800, 214, pRecord, 1.0f);
    }
}

int fn_80089E70(Table_80089904 *pTable, unsigned short event, void *a, void *b,
                Record_8036B55C *pRecord, unsigned int phase)
{
    int index = pRecord->mUnknown1;
    signed char choice;

    switch (phase) {
    case 0:
        fn_801BBC3C(((Header_8008977C *)pRecord->mUnknown796)->mUnknown2, 214, pTable);
        fn_801BE760(pRecord->mUnknown792, event, 1);
        if (sTop[index] != -1) {
            choice = fn_80089904(pRecord, pTable, sTransitions[index][sTop[index]].mValue,
                                sTransitions[index][sTop[index]].mType);
            while (choice == -1) {
                sCurrent[index] = sTransitions[index][sTop[index]].mType == 1
                    ? 2 : sTransitions[index][sTop[index]].mValue;
                --sTop[index];
                if (sTop[index] < 0) {
                    break;
                }
                choice = fn_80089904(pRecord, pTable, sTransitions[index][sTop[index]].mValue,
                                    sTransitions[index][sTop[index]].mType);
            }
        }
        if (sTop[index] == -1) {
            choice = fn_80089904(pRecord, pTable, sCurrent[index], 2);
        }
        if (choice >= 0) {
            fn_801BA2A8(a, b, pTable->mEntries[choice].mUnknown0,
                       pTable->mEntries[choice].mUnknown2, event, pRecord, 1.0f);
        }
        break;
    case 2:
        if (sCurrent[index] == 2) {
            if (sCountdown != 0) {
                --sCountdown;
            } else if (sWaiting != 0) {
                fn_800225F4(0, 16);
                fn_800225F4(1, 16);
            } else {
                sCountdown = (fn_802372EC(0, 5) + 10) * 120;
                sWaiting = 1;
            }
        } else if (sCurrent[index] > 31) {
            if (sWaiting != 0) {
                sWaiting = 0;
            }
            if (sPending[index] != 0) {
                sPending[index] = 0;
                sTop[index] = -1;
                fn_801BE068(pRecord->mUnknown792, pRecord->mUnknown796,
                           pRecord->mUnknown800, event, pRecord, 1.0f);
            }
        } else if (sWaiting != 0) {
            sWaiting = 0;
        }
        break;
    case 1:
        if (sTop[index] != -1) {
            if (sTransitions[index][sTop[index]].mType != 4) {
                sCurrent[index] = sTransitions[index][sTop[index]].mType == 1
                    ? 2 : sTransitions[index][sTop[index]].mValue;
                --sTop[index];
                fn_801BE068(pRecord->mUnknown792, pRecord->mUnknown796,
                           pRecord->mUnknown800, event, pRecord, 1.0f);
            } else {
                sTop[index] = -1;
                sCurrent[index] = 2;
                fn_801BE068(pRecord->mUnknown792, pRecord->mUnknown796,
                           pRecord->mUnknown800, event, pRecord, 1.0f);
                if (sCurrent[index] == 2) {
                    sWaiting = 0;
                }
            }
        }
        break;
    }
    return 0;
}

int fn_8008A20C(unsigned int value)
{
    for (unsigned char i = 0; i < 15; i++) {
        if (sValues[i] == value) {
            return 1;
        }
    }
    return 0;
}

void fn_8008A248(void)
{
    for (unsigned char i = 0; i < 14; i++) {
        sTop[i] = -1;
    }
}
}
