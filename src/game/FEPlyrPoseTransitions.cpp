/* Selects and queues pose animations for the front-end player models. */

#include "game/FEPlyrModel.h"
#include "game/Object_8008044C.h"
#include "game/Object_801BBD5C.h"
#include "game/AnimChanStartAnim.h"
#include "game/SyncRandGetRange.h"
#include "game/Table_80089904.h"
#include "game/fn_801BE60C.h"
#include <string.h>

struct FEPlyrPoseFileView_t {
    unsigned char unk_0x0[2];
    unsigned short mAnimFileId;
};

struct FEPlyrQueuedPose_t {
    unsigned char mType;
    unsigned char mValue;
};

extern "C" {
void FEPlyrSetPose(int index, unsigned int value);
unsigned char PlayerLocoGetRunCategory(unsigned short index);
Object_8008044C *EditMenuGetPlayerCursor(void);
Object_801BBD5C *AnimFileGetStateData(unsigned short a, unsigned short b);
int FEPlyrIsPresetPose(unsigned int value);
}

static unsigned short _FEPlyrPose_aPresetPoses[15] = {
    16, 21, 22, 19, 20, 17, 18, 23, 24, 25, 26, 27, 28, 29, 30
};
static unsigned short _FEPlyrPose_aCurrentPoses[14] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
static int _FEPlyrPose_aStackTops[14] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
static unsigned char _FEPlyrPose_aPendingFlags[14] = {0};
static FEPlyrQueuedPose_t _FEPlyrPose_aTransitions[14][3];
static unsigned char _FEPlyrPose_bIdleTimerStarted = 0;
static int _FEPlyrPose_iIdleTicks = 0;
static unsigned char _FEPlyrPose_bSelectNew = 1;
static int _FEPlyrPose_iLastSelection = -1;

extern "C" {
int FEPlyrFindRunPose(FEPlyrModel_t *pRecord, Table_80089904 *pTable, unsigned int value)
{
    unsigned char values[4];
    int best = -1;
    unsigned short id;
    Object_801BBD5C *pObject;

    AnimFileGetStateAnimList(((FEPlyrPoseFileView_t *)pRecord->mUnknown796)->mAnimFileId, 74, pTable);
    memset(values, 255, sizeof(values));
    values[0] = 1;
    id = pTable->mEntries[fn_8009C56C(pTable, values)].mUnknown2 & 0x7FFF;
    AnimFileGetStateAnimList(((FEPlyrPoseFileView_t *)pRecord->mUnknown796)->mAnimFileId, id, pTable);
    memset(values, 255, sizeof(values));
    values[0] = PlayerLocoGetRunCategory(value - 31);
    id = pTable->mEntries[fn_8009C56C(pTable, values)].mUnknown2 & 0x7FFF;
    AnimFileGetStateAnimList(((FEPlyrPoseFileView_t *)pRecord->mUnknown796)->mAnimFileId, id, pTable);
    memset(values, 255, sizeof(values));
    values[0] = 1;
    id = pTable->mEntries[fn_8009C56C(pTable, values)].mUnknown2 & 0x7FFF;
    AnimFileGetStateAnimList(((FEPlyrPoseFileView_t *)pRecord->mUnknown796)->mAnimFileId, id, pTable);
    pObject = AnimFileGetStateData(id, ((FEPlyrPoseFileView_t *)pRecord->mUnknown796)->mAnimFileId);
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

int FEPlyrSelectPoseAnimation(FEPlyrModel_t *pRecord, Table_80089904 *pTable,
                unsigned int value, int type)
{
    int result = -1;
    unsigned short best = 0;
    int category = 7;

    if (_FEPlyrPose_bSelectNew != 0) {
        if (type == 2 && value > 30) {
            result = FEPlyrFindRunPose(pRecord, pTable, value);
            _FEPlyrPose_iLastSelection = result;
        } else {
            int current = PlayerDbGetPybt(EditMenuGetPlayerCursor());
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
                score += SyncRandGetRange(0, 100);
                if (score > best && score >= 2000) {
                    _FEPlyrPose_iLastSelection = i;
                    best = score;
                    result = i;
                }
            }
        }
    } else {
        result = _FEPlyrPose_iLastSelection;
    }
    if (result >= 0 && FEPlyrIsPresetPose(value)) {
        _FEPlyrPose_bSelectNew = !_FEPlyrPose_bSelectNew;
    }
    return result;
}

void FEPlyrQueuePoseTransition(FEPlyrModel_t *pRecord, unsigned int value)
{
    int index = pRecord->mUnknown1;
    FEPlyrQueuedPose_t previous;

    if (_FEPlyrPose_aCurrentPoses[index] == value) {
        if (_FEPlyrPose_aStackTops[index] > -1) {
            previous = _FEPlyrPose_aTransitions[index][_FEPlyrPose_aStackTops[index]];
            if (!FEPlyrIsPresetPose(previous.mValue)) {
                _FEPlyrPose_aTransitions[index][1] = previous;
                _FEPlyrPose_aTransitions[index][0].mType = previous.mType == 3 ? 1 : 3;
                _FEPlyrPose_aTransitions[index][0].mValue = previous.mValue;
                _FEPlyrPose_aStackTops[index] = 1;
            }
        }
    } else if (_FEPlyrPose_aStackTops[index] > -1) {
        if (_FEPlyrPose_aTransitions[index][0].mType == 3 && _FEPlyrPose_aTransitions[index][0].mValue == value) {
            return;
        }
        previous = _FEPlyrPose_aTransitions[index][_FEPlyrPose_aStackTops[index]];
        switch (previous.mType) {
        case 1:
            if (value == 2) {
                _FEPlyrPose_aTransitions[index][0] = previous;
                _FEPlyrPose_aStackTops[index] = 0;
            } else {
                _FEPlyrPose_aTransitions[index][1] = previous;
                _FEPlyrPose_aTransitions[index][0].mType = 3;
                _FEPlyrPose_aTransitions[index][0].mValue = value;
                _FEPlyrPose_aStackTops[index] = 1;
            }
            break;
        case 3:
            if (value == 2) {
                _FEPlyrPose_aTransitions[index][1] = previous;
                _FEPlyrPose_aTransitions[index][0].mType = 1;
                _FEPlyrPose_aTransitions[index][0].mValue = previous.mValue;
                _FEPlyrPose_aStackTops[index] = 1;
            } else if (FEPlyrIsPresetPose(value)) {
                _FEPlyrPose_aTransitions[index][2] = previous;
                _FEPlyrPose_aTransitions[index][1].mType = 1;
                _FEPlyrPose_aTransitions[index][1].mValue = previous.mValue;
                _FEPlyrPose_aTransitions[index][0].mType = 4;
                _FEPlyrPose_aTransitions[index][0].mValue = value;
                _FEPlyrPose_aStackTops[index] = 2;
            } else {
                _FEPlyrPose_aTransitions[index][2] = previous;
                _FEPlyrPose_aTransitions[index][1].mType = 1;
                _FEPlyrPose_aTransitions[index][1].mValue = previous.mValue;
                _FEPlyrPose_aStackTops[index] = 2;
                _FEPlyrPose_aTransitions[index][0].mType = 3;
                _FEPlyrPose_aTransitions[index][0].mValue = value;
            }
            break;
        case 4:
            if (value == 2 || FEPlyrIsPresetPose(value)) {
                _FEPlyrPose_aCurrentPoses[index] = value;
            } else if (value > 31) {
                _FEPlyrPose_aCurrentPoses[index] = value;
                _FEPlyrPose_aPendingFlags[index] = 1;
            } else {
                _FEPlyrPose_aTransitions[index][1] = previous;
                _FEPlyrPose_aTransitions[index][0].mType = 3;
                _FEPlyrPose_aTransitions[index][0].mValue = value;
                _FEPlyrPose_aStackTops[index] = 1;
            }
            break;
        }
    } else {
        if (_FEPlyrPose_aCurrentPoses[index] == 2) {
            if (FEPlyrIsPresetPose(value)) {
                _FEPlyrPose_aCurrentPoses[index] = value;
                _FEPlyrPose_aTransitions[index][0].mType = 4;
                _FEPlyrPose_aStackTops[index] = 0;
                _FEPlyrPose_aTransitions[index][0].mValue = value;
            } else {
                _FEPlyrPose_aStackTops[index] = 0;
                _FEPlyrPose_aTransitions[index][0].mType = 3;
                _FEPlyrPose_aTransitions[index][0].mValue = value;
            }
        } else if (value == 2) {
            _FEPlyrPose_aTransitions[index][0].mType = 1;
            _FEPlyrPose_aTransitions[index][0].mValue = _FEPlyrPose_aCurrentPoses[index];
            _FEPlyrPose_aStackTops[index] = 0;
        } else if (FEPlyrIsPresetPose(value)) {
            _FEPlyrPose_aTransitions[index][1].mType = 1;
            _FEPlyrPose_aTransitions[index][1].mValue = _FEPlyrPose_aCurrentPoses[index];
            _FEPlyrPose_aTransitions[index][0].mType = 4;
            _FEPlyrPose_aTransitions[index][0].mValue = value;
            _FEPlyrPose_aStackTops[index] = 1;
        } else {
            _FEPlyrPose_aTransitions[index][1].mType = 1;
            _FEPlyrPose_aTransitions[index][1].mValue = _FEPlyrPose_aCurrentPoses[index];
            _FEPlyrPose_aTransitions[index][0].mType = 3;
            _FEPlyrPose_aTransitions[index][0].mValue = value;
            _FEPlyrPose_aStackTops[index] = 1;
        }
        fn_801BE068(pRecord->mUnknown792, pRecord->mUnknown796,
                   pRecord->mUnknown800, 214, 1.0f, pRecord);
    }
}

int FEPlyrPoseTransitionCallback(Table_80089904 *pTable, unsigned short event, void *a, void *b,
                FEPlyrModel_t *pRecord, unsigned int phase)
{
    int index = pRecord->mUnknown1;
    signed char choice;

    switch (phase) {
    case 0:
        AnimFileGetStateAnimList(((FEPlyrPoseFileView_t *)pRecord->mUnknown796)->mAnimFileId, 214, pTable);
        fn_801BE760(pRecord->mUnknown792, event, 1);
        if (_FEPlyrPose_aStackTops[index] != -1) {
            choice = FEPlyrSelectPoseAnimation(pRecord, pTable, _FEPlyrPose_aTransitions[index][_FEPlyrPose_aStackTops[index]].mValue,
                                _FEPlyrPose_aTransitions[index][_FEPlyrPose_aStackTops[index]].mType);
            while (choice == -1) {
                _FEPlyrPose_aCurrentPoses[index] = _FEPlyrPose_aTransitions[index][_FEPlyrPose_aStackTops[index]].mType == 1
                    ? 2 : _FEPlyrPose_aTransitions[index][_FEPlyrPose_aStackTops[index]].mValue;
                --_FEPlyrPose_aStackTops[index];
                if (_FEPlyrPose_aStackTops[index] < 0) {
                    break;
                }
                choice = FEPlyrSelectPoseAnimation(pRecord, pTable, _FEPlyrPose_aTransitions[index][_FEPlyrPose_aStackTops[index]].mValue,
                                    _FEPlyrPose_aTransitions[index][_FEPlyrPose_aStackTops[index]].mType);
            }
        }
        if (_FEPlyrPose_aStackTops[index] == -1) {
            choice = FEPlyrSelectPoseAnimation(pRecord, pTable, _FEPlyrPose_aCurrentPoses[index], 2);
        }
        if (choice >= 0) {
            AnimChanStartAnim(a, b, pTable->mEntries[choice].mUnknown0,
                       pTable->mEntries[choice].mUnknown2, event, pRecord, 1.0f);
        }
        break;
    case 2:
        if (_FEPlyrPose_aCurrentPoses[index] == 2) {
            if (_FEPlyrPose_iIdleTicks != 0) {
                --_FEPlyrPose_iIdleTicks;
            } else if (_FEPlyrPose_bIdleTimerStarted != 0) {
                FEPlyrSetPose(0, 16);
                FEPlyrSetPose(1, 16);
            } else {
                _FEPlyrPose_iIdleTicks = (SyncRandGetRange(0, 5) + 10) * 120;
                _FEPlyrPose_bIdleTimerStarted = 1;
            }
        } else if (_FEPlyrPose_aCurrentPoses[index] > 31) {
            if (_FEPlyrPose_bIdleTimerStarted != 0) {
                _FEPlyrPose_bIdleTimerStarted = 0;
            }
            if (_FEPlyrPose_aPendingFlags[index] != 0) {
                _FEPlyrPose_aPendingFlags[index] = 0;
                _FEPlyrPose_aStackTops[index] = -1;
                fn_801BE068(pRecord->mUnknown792, pRecord->mUnknown796,
                           pRecord->mUnknown800, event, 1.0f, pRecord);
            }
        } else if (_FEPlyrPose_bIdleTimerStarted != 0) {
            _FEPlyrPose_bIdleTimerStarted = 0;
        }
        break;
    case 1:
        if (_FEPlyrPose_aStackTops[index] != -1) {
            if (_FEPlyrPose_aTransitions[index][_FEPlyrPose_aStackTops[index]].mType != 4) {
                _FEPlyrPose_aCurrentPoses[index] = _FEPlyrPose_aTransitions[index][_FEPlyrPose_aStackTops[index]].mType == 1
                    ? 2 : _FEPlyrPose_aTransitions[index][_FEPlyrPose_aStackTops[index]].mValue;
                --_FEPlyrPose_aStackTops[index];
                fn_801BE068(pRecord->mUnknown792, pRecord->mUnknown796,
                           pRecord->mUnknown800, event, 1.0f, pRecord);
            } else {
                _FEPlyrPose_aStackTops[index] = -1;
                _FEPlyrPose_aCurrentPoses[index] = 2;
                fn_801BE068(pRecord->mUnknown792, pRecord->mUnknown796,
                           pRecord->mUnknown800, event, 1.0f, pRecord);
                if (_FEPlyrPose_aCurrentPoses[index] == 2) {
                    _FEPlyrPose_bIdleTimerStarted = 0;
                }
            }
        }
        break;
    }
    return 0;
}

int FEPlyrIsPresetPose(unsigned int value)
{
    for (unsigned char i = 0; i < 15; i++) {
        if (_FEPlyrPose_aPresetPoses[i] == value) {
            return 1;
        }
    }
    return 0;
}

void FEPlyrResetPoseTransitions(void)
{
    for (unsigned char i = 0; i < 14; i++) {
        _FEPlyrPose_aStackTops[i] = -1;
    }
}
}
