/* Challenge screen: lists the challenges of the chosen group with their names,
   lock and completion state, shows a challenge's description, rewards, medal
   goals and skill level, starts the chosen challenge, and reports once when
   the tournament has been won or the challenge points run low. */

#include "game/DbCursor.h"
#include "game/Challenge.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"
#include "game/GameOptions.h"

extern "C" {
void fn_80004504(unsigned char id);
void fn_8000FCD4(int a);
void ChallengeSetMode(int value);
void ChalCloseCursors(void);
DbCursor *ChalGetTableCursor(void);
int ChalFindRecord(DbCursor *pObject, unsigned char id, int *pResult);
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

static const int _MsgChallenge_aGroupIds[12] = { 12, 10, 11, 13, 9, 4, 8, 5, 7, 6, 14, 14 };

static int _MsgChallenge_iFlowState = 0;
static unsigned char _MsgChallenge_bResumed = 0;
static unsigned char _MsgChallenge_bLowPointsShown = 0;
static unsigned char _MsgChallenge_bTournamentWonShown = 0;
static int _MsgChallenge_iSaved0 = 2;
static int _MsgChallenge_iSaved1 = 4;
static int _MsgChallenge_iGroup = 12;
static signed char _MsgChallenge_iEntry = 0;

extern "C" {
int MsgChallengeGetFlowState(void);
void MsgChallengeSetFlowState(int value);
void MsgChallengeSetResumed(unsigned char value);

int MsgChallengeFindGroup(int value)
{
    int i;

    for (i = 0; i < 12; i++) {
        if (_MsgChallenge_aGroupIds[i] == value) {
            break;
        }
    }
    if (i == 12) {
        i = 0;
    }
    return i;
}

void MsgChallengeOpen(int *pA, int *pB, int *pC)
{
    *pC = 50;
    *pA = _MsgChallenge_iSaved0;
    *pB = _MsgChallenge_iSaved1;
    ChallengeSetMode(3);
    MsgGameSetFEStarted(1);
    if (fn_801835A0()) {
        fn_801834DC();
    }
    if (MsgChallengeGetFlowState() == 5) {
        ChalCloseCursors();
        *pA = 3;
        *pB = _MsgChallenge_aGroupIds[_MsgChallenge_iGroup];
    } else {
        _MsgChallenge_iEntry = 0;
    }
    *pC = ChalGetPoints();
    MsgChallengeSetFlowState(3);
    MsgChallengeSetResumed(0);
}

void MsgChallengeClose(int a, int b)
{
    if (MsgGameGetSetupState() == 0) {
        _MsgChallenge_iSaved0 = 2;
        _MsgChallenge_iSaved1 = 4;
    } else {
        _MsgChallenge_iSaved0 = a;
        _MsgChallenge_iSaved1 = b;
    }
    ChalCloseCursors();
}

void MsgChallengeSelectGroup(int value, int *pA, int *pB)
{
    int index = MsgChallengeFindGroup(value);

    if (index != _MsgChallenge_iGroup) {
        _MsgChallenge_iGroup = index;
        _MsgChallenge_iEntry = 0;
    }
    *pA = ChalCountInGroup(_MsgChallenge_iGroup);
    *pB = _MsgChallenge_iEntry;
}

void MsgChallengeGetEntryStatus(int index, MenuArg_t text, int *pA, int *pB)
{
    Challenge_t record;
    int a;
    int b;
    DbCursor *pObject = ChalGetTableCursor();
    int id = ChalGetIdInGroup(_MsgChallenge_iGroup, index + 1);

    if (id) {
        int kind;

        ChalFindRecord(pObject, id, 0);
        ChalReadRecord(pObject, &record, GameOptionsGet(0));
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

int MsgChallengeGetEntryInfo(int index, int *pValue, MenuArg_t textA, int *pFlag, MenuArg_t textB,
                MenuArg_t textC, MenuArg_t *pTexts1, MenuArg_t *pTexts2)
{
    Challenge_t record;
    int result = 0;
    DbCursor *pObject = ChalGetTableCursor();
    int id = ChalGetIdInGroup(_MsgChallenge_iGroup, index + 1);

    _MsgChallenge_iEntry = index;
    if (id) {
        int a;
        int b = 1;
        ChalMedalGoal_t *pInfo;
        int kind;
        signed char i;

        ChalFindRecord(pObject, id, 0);
        kind = ChalGetProgress(id, &a, &b);
        if (kind != 2) {
            b = GameOptionsGet(0);
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

void MsgChallengeStartEntry(int index, int a, int *pResult)
{
    int id;

    _MsgChallenge_iEntry = index;
    id = ChalGetIdInGroup(_MsgChallenge_iGroup, index + 1);
    fn_8000FCD4(a);
    fn_80004504(id);
    *pResult = ChalHasReward(ChalGetCurrent(), 4) ? 105 : 107;
}

int MsgChallengeCheckTournamentWon(void)
{
    int state = ChalGetTournamentWon();
    int result = 0;

    if (state) {
        if (_MsgChallenge_bTournamentWonShown == 0) {
            _MsgChallenge_bTournamentWonShown = 1;
            result = 1;
        }
    } else {
        _MsgChallenge_bTournamentWonShown = 0;
    }
    return result;
}

void MsgChallengeSetFlowState(int value)
{
    _MsgChallenge_iFlowState = value;
}

int MsgChallengeGetFlowState(void)
{
    return _MsgChallenge_iFlowState;
}

void MsgChallengeSetResumed(unsigned char value)
{
    _MsgChallenge_bResumed = value;
}

int MsgChallengeHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgChallengeOpen(pArgs[0].pi, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000002:
        MsgChallengeClose(pArgs[0].i, pArgs[1].i);
        break;
    case 0x80000003:
        MsgChallengeSelectGroup(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000004:
        MsgChallengeGetEntryStatus(pArgs[0].i, pArgs[1], pArgs[2].pi, pArgs[3].pi);
        break;
    case 0x80000005: {
        MenuArg_t texts[3] = { pArgs[6], pArgs[7], pArgs[8] };

        *pResult = MsgChallengeGetEntryInfo(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3].pi, pArgs[4], pArgs[5],
                               texts, (MenuArg_t *)(pArgs[9].i + (*pArgs[9].pi + 1) * 4));
        break;
    }
    case 0x80000006:
        MsgChallengeStartEntry(pArgs[0].i, pArgs[1].i, pArgs[2].pi);
        break;
    case 0x80000007:
        *pResult = MsgChallengeCheckTournamentWon();
        break;
    case 0x8000000A: {
        int state;

        *pResult = 0;
        state = ChalGetTournamentWon();
        if (ChalGetPoints() <= 5) {
            if (_MsgChallenge_bLowPointsShown == 0 && state == 0) {
                _MsgChallenge_bLowPointsShown = 1;
                *pResult = 1;
            }
        } else {
            _MsgChallenge_bLowPointsShown = 0;
        }
        break;
    }
    default:
        return 0;
    }
    return 1;
}
}
