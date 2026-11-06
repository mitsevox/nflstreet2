#include "game/DbCursor.h"
#include "game/Challenge.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"
#include "game/fn_8007F828.h"

extern "C" {
void fn_80004504(unsigned char id);
void fn_8000FCD4(int a);
void ChallengeSetMode(int value);
void ChalCloseCursors(void);
DbCursor *ChalGetTableCursor(void);
void ChalFindRecord(DbCursor *pObject, unsigned char id, int *pResult);
void ChalReadRecord(DbCursor *pObject, Challenge_t *pRecord, int a);
int ChalGetProgress(int id, int *pA, int *pB);
unsigned int ChalGetPoints(void);
int ChalGetTournamentWon();
int ChalCountInGroup(int index);
int ChalGetIdInGroup(int a, signed char index);
void ChalFormatReward(int type, unsigned short value, char *pBuffer, unsigned short size);
void ChalFormatRewards(Challenge_t *pRecord, char *pBuffer, unsigned short size);
int ChalHasMedalGoal(Challenge_t *pRecord);
int ChalHasReward(Challenge_t *pRecord, int id);
int MsgGameGetSetupState(void);
void MsgGameSetFEStarted(int a);
void fn_801834DC(void);
int fn_801835A0(void);
}

static const int lbl_8001EFF0[12] = { 12, 10, 11, 13, 9, 4, 8, 5, 7, 6, 14, 14 };

static int lbl_803EBA70 = 0;
static unsigned char lbl_803EBA74 = 0;
static unsigned char lbl_803EBA75 = 0;
static unsigned char lbl_803EBA76 = 0;
static int lbl_803EBA78 = 2;
static int lbl_803EBA7C = 4;
static int lbl_803EBA80 = 12;
static signed char lbl_803EBA84 = 0;

extern "C" {
int fn_8001ED88(void);
void fn_8001ED80(int value);
void fn_8001ED90(unsigned char value);

int fn_8001E73C(int value)
{
    int i;

    for (i = 0; i < 12; i++) {
        if (lbl_8001EFF0[i] == value) {
            break;
        }
    }
    if (i == 12) {
        i = 0;
    }
    return i;
}

void fn_8001E780(int *pA, int *pB, int *pC)
{
    *pC = 50;
    *pA = lbl_803EBA78;
    *pB = lbl_803EBA7C;
    ChallengeSetMode(3);
    MsgGameSetFEStarted(1);
    if (fn_801835A0()) {
        fn_801834DC();
    }
    if (fn_8001ED88() == 5) {
        ChalCloseCursors();
        *pA = 3;
        *pB = lbl_8001EFF0[lbl_803EBA80];
    } else {
        lbl_803EBA84 = 0;
    }
    *pC = ChalGetPoints();
    fn_8001ED80(3);
    fn_8001ED90(0);
}

void fn_8001E83C(int a, int b)
{
    if (MsgGameGetSetupState() == 0) {
        lbl_803EBA78 = 2;
        lbl_803EBA7C = 4;
    } else {
        lbl_803EBA78 = a;
        lbl_803EBA7C = b;
    }
    ChalCloseCursors();
}

void fn_8001E894(int value, int *pA, int *pB)
{
    int index = fn_8001E73C(value);

    if (index != lbl_803EBA80) {
        lbl_803EBA80 = index;
        lbl_803EBA84 = 0;
    }
    *pA = ChalCountInGroup(lbl_803EBA80);
    *pB = lbl_803EBA84;
}

void fn_8001E8F4(int index, Arg_8018399C text, int *pA, int *pB)
{
    Challenge_t record;
    int a;
    int b;
    DbCursor *pObject = ChalGetTableCursor();
    int id = ChalGetIdInGroup(lbl_803EBA80, index + 1);

    if (id) {
        int kind;

        ChalFindRecord(pObject, id, 0);
        ChalReadRecord(pObject, &record, fn_8007F828(0));
        kind = ChalGetProgress(record.mUnknown0, &a, &b);
        fn_801C3284(text.pParams->mpText, record.mUnknown1, text.pParams->mLength);
        switch (kind) {
        case 0:
            *pB = 1;
            *pA = 0;
            break;
        case 2:
            *pB = 0;
            *pA = 1;
            break;
        case 1:
        case 3:
            *pB = record.mUnknown196 > ChalGetPoints();
            *pA = 0;
            break;
        default:
            *pB = 1;
            *pA = 0;
            break;
        }
    }
}

int fn_8001EA08(int index, int *pValue, Arg_8018399C textA, int *pFlag, Arg_8018399C textB,
                Arg_8018399C textC, Arg_8018399C *pTexts1, Arg_8018399C *pTexts2)
{
    Challenge_t record;
    int result = 0;
    DbCursor *pObject = ChalGetTableCursor();
    int id = ChalGetIdInGroup(lbl_803EBA80, index + 1);

    lbl_803EBA84 = index;
    if (id) {
        int a;
        int b = 1;
        ChalMedalGoal_t *pInfo;
        int kind;
        signed char i;

        ChalFindRecord(pObject, id, 0);
        kind = ChalGetProgress(id, &a, &b);
        if (kind != 2) {
            b = fn_8007F828(0);
        }
        ChalReadRecord(pObject, &record, b);
        pInfo = &record.mUnknown20C;
        result = ChalHasMedalGoal(&record);
        fn_801C3284(textA.pParams->mpText, record.mUnknown1, textA.pParams->mLength);
        fn_801C3284(textB.pParams->mpText, record.mUnknownCB, textB.pParams->mLength);
        if (result) {
            for (i = 0; i <= 2; i++) {
                if (pInfo->mUnknown10[i]) {
                    fn_801C3284(pTexts2[i].pParams->mpText, pInfo->mUnknown10[i],
                                pTexts2[i].pParams->mLength);
                }
            }
        }
        *pFlag = kind != 2 ? record.mUnknown196 : 0;
        if (record.mUnknown198 == 0) {
            *pValue = 10001;
        } else if (ChalHasReward(&record, 4) || record.mUnknown198 == '?') {
            *pValue = -1;
        } else {
            *pValue = record.mUnknown198;
        }
        if (result) {
            for (i = 0; i <= 2; i++) {
                ChalFormatReward(pInfo->mUnknown1C, pInfo->mUnknown20[i], pTexts1[i].pParams->mpText,
                            pTexts1[i].pParams->mLength);
            }
        } else {
            ChalFormatRewards(&record, pTexts1[0].pParams->mpText, pTexts1[0].pParams->mLength);
        }
        switch (record.mUnknown208) {
        case 0:
            fn_801C3284(textC.pParams->mpText, "No Skills", textC.pParams->mLength);
            break;
        case 1:
            fn_801C3284(textC.pParams->mpText, "Weak Skills", textC.pParams->mLength);
            break;
        case 2:
            fn_801C3284(textC.pParams->mpText, "Got Skills", textC.pParams->mLength);
            break;
        case 3:
            fn_801C3284(textC.pParams->mpText, "Mad Skills", textC.pParams->mLength);
            break;
        case 4:
            fn_801C3284(textC.pParams->mpText, "Legendary Skills", textC.pParams->mLength);
            break;
        default:
            fn_801C3284(textC.pParams->mpText, "It's a Mystery", textC.pParams->mLength);
            break;
        }
    }
    return result;
}

void fn_8001ECBC(int index, int a, int *pResult)
{
    int id;

    lbl_803EBA84 = index;
    id = ChalGetIdInGroup(lbl_803EBA80, index + 1);
    fn_8000FCD4(a);
    fn_80004504(id);
    *pResult = ChalHasReward(ChalGetCurrent(), 4) ? 105 : 107;
}

int fn_8001ED34(void)
{
    int state = ChalGetTournamentWon();
    int result = 0;

    if (state) {
        if (lbl_803EBA76 == 0) {
            lbl_803EBA76 = 1;
            result = 1;
        }
    } else {
        lbl_803EBA76 = 0;
    }
    return result;
}

void fn_8001ED80(int value)
{
    lbl_803EBA70 = value;
}

int fn_8001ED88(void)
{
    return lbl_803EBA70;
}

void fn_8001ED90(unsigned char value)
{
    lbl_803EBA74 = value;
}

int fn_8001ED98(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_8001E780(pArgs[0].pi, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000002:
        fn_8001E83C(pArgs[0].i, pArgs[1].i);
        break;
    case 0x80000003:
        fn_8001E894(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000004:
        fn_8001E8F4(pArgs[0].i, pArgs[1], pArgs[2].pi, pArgs[3].pi);
        break;
    case 0x80000005: {
        Arg_8018399C texts[3] = { pArgs[6], pArgs[7], pArgs[8] };

        *pResult = fn_8001EA08(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3].pi, pArgs[4], pArgs[5],
                               texts, (Arg_8018399C *)(pArgs[9].i + (*pArgs[9].pi + 1) * 4));
        break;
    }
    case 0x80000006:
        fn_8001ECBC(pArgs[0].i, pArgs[1].i, pArgs[2].pi);
        break;
    case 0x80000007:
        *pResult = fn_8001ED34();
        break;
    case 0x8000000A: {
        int state;

        *pResult = 0;
        state = ChalGetTournamentWon();
        if (ChalGetPoints() <= 5) {
            if (lbl_803EBA75 == 0 && state == 0) {
                lbl_803EBA75 = 1;
                *pResult = 1;
            }
        } else {
            lbl_803EBA75 = 0;
        }
        break;
    }
    default:
        return 0;
    }
    return 1;
}
}
