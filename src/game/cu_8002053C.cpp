#include "game/fn_80020904.h"
#include "game/cu_80190208.h"

static signed char lbl_803EBAA0 = -1;

extern "C" {
int fn_801869F0(void);
int fn_80186DF0(signed char *pIndices, int length);
int fn_80186A10(int index, char *pText);
void fn_80186ED8(signed char index);
void fn_80054964(signed char db, int id);
void fn_80054628(signed char db, int id);

int fn_8002053C(int control)
{
    int result = fn_801869F0();
    int count = result;
    if (lbl_803EBAA0 == -1 && count > 0) {
        signed char indices[2];
        unsigned char auxiliary[2];
        result = fn_80186DF0(indices, 2);
        for (int i = 0; i < 2; ++i) {
            if (indices[i] != -1) {
                auxiliary[i] = 1;
            }
        }
        lbl_803EBAA0 = indices[0];
    }
    if (count > 1) {
        switch (control) {
        case 3:
            --lbl_803EBAA0;
            if (lbl_803EBAA0 < 0) {
                lbl_803EBAA0 = count - 1;
            }
            break;
        case 1:
            lbl_803EBAA0 = (lbl_803EBAA0 + 1) % count;
            break;
        }
    }
    return result;
}

int fn_80020620(int control, char *pText, int c, int *pValue, int *pFlag)
{
    fn_8002053C(control);
    fn_80190280(lbl_803EBAA0);
    fn_80186A10(lbl_803EBAA0, pText);
    *pValue = fn_80190294();
    int result = fn_80190310();
    *pFlag = result;
    return result;
}

int fn_80020680(int value, char *pText, int length, int *pResult)
{
    int count;
    return fn_801905E0(value, &count, pText, length, pResult);
}

int fn_800206B4(const char *pCode, int unused, char *pName, int d)
{
    unsigned int value = fn_80190420(pCode, unused, pName);
    fn_80186ED8(lbl_803EBAA0);
    if (value > 54) {
        return 0;
    }
    if (fn_80190768(value)) {
        return 2;
    }
    fn_80190808(value);
    return 1;
}

void fn_80020718(int value)
{
    switch (value) {
    case 27:
        fn_801909E4(26);
        break;
    case 26:
        fn_801909E4(27);
        break;
    case 30:
        fn_801909E4(44);
        fn_801909E4(31);
        fn_801909E4(34);
        break;
    case 31:
        fn_801909E4(44);
        fn_801909E4(30);
        fn_801909E4(34);
        break;
    case 44:
        fn_801909E4(31);
        fn_801909E4(30);
        fn_801909E4(34);
        break;
    case 34:
        fn_801909E4(31);
        fn_801909E4(30);
        fn_801909E4(44);
        fn_801909E4(33);
        break;
    case 33:
        fn_801909E4(34);
        break;
    case 36:
        fn_801909E4(37);
        break;
    case 37:
        fn_801909E4(36);
        break;
    case 28:
        fn_801909E4(29);
        break;
    case 29:
        fn_801909E4(28);
        break;
    case 23:
        fn_801909E4(24);
        break;
    case 24:
        fn_801909E4(23);
        break;
    }
}

void fn_80020870(int value, int *pResult)
{
    int result = fn_801904E0(value);
    fn_80186ED8(lbl_803EBAA0);
    int changed;
    if (fn_801908A0(result)) {
        fn_801909E4(result);
        fn_80054964(lbl_803EBAA0, result);
        changed = 0;
    } else {
        fn_8019094C(result);
        fn_80054628(lbl_803EBAA0, result);
        fn_80020718(result);
        changed = 1;
    }
    *pResult = changed;
}

int fn_80020904(unsigned int id, Word_80020904 *pArgs, int c, int *pResult)
{
    switch (id) {
    case 0x80000001:
        *pArgs[0].mpUnknown0 = fn_801869F0();
        break;
    case 0x80000002:
        lbl_803EBAA0 = -1;
        fn_80190288();
        break;
    case 0x80000004:
    {
        Record_80021154 *pRecord = pArgs[1].mpRecord;
        fn_80020680(pArgs[0].mUnknown0, pRecord->mUnknown8, pRecord->mUnknown4,
                    pArgs[2].mpUnknown0);
        break;
    }
    case 0x80000003:
    {
        Record_80021154 *pRecord = pArgs[1].mpRecord;
        fn_80020620(pArgs[0].mUnknown0, pRecord->mUnknown8, pRecord->mUnknown4,
                    pArgs[2].mpUnknown0, pArgs[3].mpUnknown0);
        break;
    }
    case 0x80000006:
    {
        Word_80020904 *pFirst = pArgs[0].mpWords;
        Word_80020904 *pSecond = pArgs[1].mpWords;
        *pResult = fn_800206B4(pFirst[2].mpCode, pFirst[1].mUnknown0,
                               pSecond[2].mpText, pSecond[1].mUnknown0);
        break;
    }
    case 0x80000005:
        fn_80020870(pArgs[0].mUnknown0, pArgs[1].mpUnknown0);
        break;
    default:
        return 0;
    }
    return 1;
}
}
