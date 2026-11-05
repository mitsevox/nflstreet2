/* Challenge records and progress: loads a challenge (title, description, stat goals, medal
   thresholds and rewards) from the database and scales it by level, tracks the profile's challenge
   status, medals, points and development points, keeps the 32-team tournament bracket's teams and
   scores, and builds the goal and reward texts the challenge screens show. */

/* 0x80077A24-0x80079CD8. _Chal_aGoalTests points to test functions of the range
   0x800775F0-0x80077A24 (ChalGoal.cpp). */

#include <string.h>
#include "game/Class_8018FD64Inline.h"
#include "game/Class_80297C60.h"
#include "game/DbCursor.h"
#include "game/Challenge.h"
#include "game/Object_8017886C.h"
#include "game/fn_801C3284.h"
#include "game/fn_801FCE10.h"

/* 16-byte entry of the table _Chal_aGoalTypes, indexed by a type number: the tag
   passed to fn_8022B7A4, a flag that selects the other side, a kind (0-4)
   and a printf format. */
struct ChalGoalType_t {
    int mTag;
    unsigned char mFlag;
    int mKind;
    const char *mpFormat;
};

/* Pair of functions of the range 0x800775F0-0x80077A24 selected by ChalGoalType_t::mKind. */
struct ChalGoalTests_t {
    int (*mpRecordTest)(int tag, int side, Challenge_t *pRecord, int index);
    int (*mpInfoTest)(int tag, int side, ChalMedalGoal_t *pInfo);
};

extern "C" {

int ChalCheckNoGoal(int tag, int side, Challenge_t *pRecord, int index);
int ChalRankNoGoal(int tag, int side, ChalMedalGoal_t *pInfo);
int ChalCheckAtMostGoal(int tag, int side, Challenge_t *pRecord, int index);
int ChalRankAtMostGoal(int tag, int side, ChalMedalGoal_t *pInfo);
int ChalCheckAtLeastGoal(int tag, int side, Challenge_t *pRecord, int index);
int ChalRankAtLeastGoal(int tag, int side, ChalMedalGoal_t *pInfo);
int ChalRankStylePoints(int side, ChalMedalGoal_t *pInfo);
void ChalOpenTable(DbCursor *pObject);
void ChalOpenInfo(DbCursor *pObject, int value);
void ChalOpenProgress(DbCursor *pObject, int value);
void ChalReadMedalGoal(int id, ChalMedalGoal_t *pInfo);
int ChalHasMedalGoal(Challenge_t *pRecord);

int fn_8007BB4C(DbCursor *pCursor, int key, int *pResult);
void fn_8007BA48(DbCursor *pCursor);
void fn_8007BB04(DbCursor *pCursor);
void fn_8007BE20(DbCursor *pCursor, char *pBuffer, int size);
int fn_8007C46C(int key);
int fn_8007C538(int id);
int fn_8007C690(DbCursor *pCursor, short *pOut);
void fn_8007F6F8(int a, int b);
int fn_800A2178(void);
int fn_800A7E40(unsigned char side);
int fn_800AD9B4(void);
void fn_800B4A18(int index, char *pDest, int size);
int fn_800B9A90(Class_80297C60 *p);
int fn_800D41F8(int side);
unsigned char fn_800D7528(int side);
unsigned char fn_800D7544(int side);
int fn_80178308(void);
int fn_801787DC(int team);
int fn_80186B38(int a);
void fn_8018787C(int index);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
char *fn_801C2F88(char *pDest, const char *pSource, unsigned int count);
unsigned int fn_801C3180(const char *pText);
int fn_8022B7A4(int handle, int tag, void *pValue);
int fn_8022F358(int index);
int fn_8022F3D4(int handle);
int fn_8022F4BC(void);

extern const unsigned char lbl_802AEF10[];

}

ChalGoalTests_t _Chal_aGoalTests[3] = {
    { ChalCheckNoGoal, ChalRankNoGoal },
    { ChalCheckAtLeastGoal, ChalRankAtLeastGoal },
    { ChalCheckAtMostGoal, ChalRankAtMostGoal },
};
const char *_Chal_aszMedalNames[3] = { "Gold", "Silver", "Bronze" };

static DbCursor _Chal_sTableCursor;
static DbCursor _Chal_sInfoCursor;
static DbCursor _Chal_sProgressCursor;
static Challenge_t _Chal_sCurrent;
static int _Chal_iInfoHandle = 0;
static int _Chal_iProgressHandle = 0;

static const float _Chal_afRewardScale[3] = { 0.85f, 0.92f, 1.0f };
static const float _Chal_afAtLeastScale[3] = { 1.0f, 0.85f, 0.7f };
static const float _Chal_afAtMostScale[3] = { 0.7f, 0.85f, 1.0f };
static const int _Chal_aRecordColumns[37] = {
    0x44494843, 0x45444843, 0x4F434843, 0x504F4843, 0x54474843, 0x54504843, 0x49544843, 0x59444843,
    0x41434843, 0x53554843, 0x53434843, 0x53504843, 0x53504343, 0x4F504843, 0x44464843, 0x4C594843,
    0x4E444843, 0x46554843, 0x47464843, 0x41514843, 0x41505143, 0x41525143, 0x42514843, 0x42505143,
    0x42525143, 0x43514843, 0x43505143, 0x43525143, 0x44514843, 0x44505143, 0x44525143, 0x54524843,
    0x56524843, 0x32524843, 0x32564843, 0x524F4843, 0x44444843,
};
static const ChalGoalType_t _Chal_aGoalTypes[85] = {
    { -1, 0, 0, "" },
    { -1, 0, 4, "" },
    { -1, 0, 4, "" },
    { -1, 0, 4, "Style Points: %d" },
    { 0x50747374, 0, 1, "Style Points One Play Best: %d" },
    { 0x64317374, 0, 1, "First Downs: %d" },
    { -1, 0, 4, "Current Play: %d" },
    { 0x73707374, 0, 4, "Current Drive: %d" },
    { 0x6A737374, 0, 1, "Spins and Jukes: %d" },
    { 0x61737374, 0, 1, "Stiff Arms: %d" },
    { 0x68647374, 0, 1, "Hurdles: %d" },
    { 0x62737374, 0, 1, "Stylin' Style Points: %d" },
    { 0x61707374, 0, 1, "Pass Attempts: %d" },
    { 0x61727374, 0, 1, "Rush Attempts: %d" },
    { 0x63707374, 0, 1, "Completed Passes: %d" },
    { 0x74727374, 0, 1, "Rushing Touchdowns: %d" },
    { 0x74507374, 0, 1, "Passing Touchdowns: %d" },
    { 0x64647374, 0, 1, "Defensive Touchdowns: %d" },
    { 0x7A707374, 0, 1, "Pitches: %d" },
    { 0x4F707374, 0, 1, "Pitches One Play Best: %d" },
    { -1, 0, 4, "" },
    { 0x61677374, 0, 2, "Lost Fumbles and Interceptions: %d" },
    { 0x6B737374, 0, 1, "Team Sacks: %d" },
    { 0x73757374, 0, 1, "User Sacks: %d" },
    { 0x53637374, 0, 1, "Consecutive Team Sacks Best: %d" },
    { 0x55637374, 0, 1, "Consecutive User Sacks Best: %d" },
    { 0x74737374, 0, 1, "Safeties: %d" },
    { 0x69447374, 0, 1, "Team Interceptions: %d" },
    { 0x69757374, 0, 1, "User Interceptions: %d" },
    { 0x66667374, 0, 1, "Forced Fumbles: %d" },
    { 0x72667374, 0, 1, "Fumble Recoveries: %d" },
    { -1, 0, 4, "GameBreakers Awarded: %d" },
    { 0x74757374, 0, 1, "User Tackles: %d" },
    { 0x70737374, 0, 1, "Stylin' Pass Completions: %d" },
    { 0x73737374, 0, 1, "Stylin' Spins And Jukes: %d" },
    { 0x64737374, 0, 1, "Stylin' Dives: %d" },
    { 0x6F667374, 0, 1, "Spin/Juke Fakeouts: %d" },
    { 0x69737374, 0, 1, "Stylin' Pitches: %d" },
    { 0x6B737374, 1, 2, "Sacks Allowed: %d" },
    { 0x69707374, 0, 2, "Interceptions Thrown: %d" },
    { 0x6C667374, 0, 2, "Fumbles Lost: %d" },
    { -1, 0, 4, "Touchdowns: %d" },
    { -1, 0, 4, "Points Scored: %d" },
    { 0x70647374, 0, 1, "User Power Tackles: %d" },
    { 0x64317374, 1, 2, "CPU First Downs: %d" },
    { -1, 1, 4, "CPU Touchdowns: %d" },
    { -1, 1, 4, "CPU Points Scored: %d" },
    { -1, 0, 4, "" },
    { -1, 0, 4, "" },
    { 0x43637374, 0, 1, "" },
    { 0x73707374, 1, 4, "CPU Current Drive: %d" },
    { 0x74767374, 0, 1, "Diving Touchdowns: %d" },
    { 0x73707374, 1, 4, "CPU Current Drive: %d" },
    { -1, 0, 4, "Current Play: %d" },
    { 0x676F7374, 0, 1, "Offensive GameBreaker Touchdowns: %d" },
    { -1, 0, 4, "" },
    { 0x73707374, 0, 4, "Current Drive: %d" },
    { 0x64317374, 0, 2, "First Downs: %d" },
    { -1, 0, 4, "Percent Of Plays Passed On: %d" },
    { 0x70447374, 0, 2, "Dropped Passes: %d" },
    { -1, 0, 4, "" },
    { 0x74537374, 0, 1, "Stylin' Touchdowns: %d" },
    { 0x43737374, 0, 1, "" },
    { 0x76737374, 0, 1, "Stylin' Diving Touchdowns: %d" },
    { 0x73327374, 0, 1, "Signature Stylin' Spins And Jukes: %d" },
    { 0x68327374, 0, 1, "Signature Stylin' Hurdles: %d" },
    { 0x50637374, 0, 1, "" },
    { 0x68737374, 0, 1, "Stylin' Hurdles: %d" },
    { -1, 0, 4, "" },
    { 0x66727374, 0, 1, "Rushing First Downs: %d" },
    { 0x72697374, 0, 1, "Interceptions Returned: %d" },
    { -1, 0, 4, "" },
    { -1, 0, 4, "" },
    { 0x75667374, 0, 2, "Fumbles: %d" },
    { -1, 0, 4, "Incomplete Passes: %d" },
    { 0x63777374, 0, 1, "Wall Catches: %d" },
    { 0x6A777374, 0, 1, "Wall Jukes: %d" },
    { 0x70777374, 0, 1, "Wall Passes: %d" },
    { 0x68777374, 0, 1, "Wall Hurdles: %d" },
    { 0x74777374, 0, 1, "Wall Diving Touchdowns: %d" },
    { -1, 0, 4, "" },
    { 0x63757374, 0, 1, "Stylin' Catches: %d" },
    { 0x73687374, 0, 1, "Hot Spots: %d" },
    { 0x6C627374, 0, 1, "Stripped Balls: %d" },
    { 0x77777374, 0, 1, "Wall To Walls: %d" },
};

extern "C" {

void ChalScaleReward(int level, unsigned short *pValue)
{
    *pValue = *pValue * _Chal_afRewardScale[level] + 0.5f;
}

void ChalScaleGoalValue(int level, int type, unsigned int *pValue)
{
    unsigned int old = *pValue;

    if (type != 0) {
        switch (_Chal_aGoalTypes[type].mKind) {
        case 1:
            *pValue = *pValue * _Chal_afAtLeastScale[level] + 0.5f;
            break;
        case 2:
            *pValue = *pValue * _Chal_afAtMostScale[level] + 0.5f;
            break;
        default:
            switch (type) {
            case 3:
            case 0x1F:
            case 0x29:
                *pValue = *pValue * _Chal_afAtLeastScale[level] + 0.5f;
                break;
            case 6:
            case 7:
            case 0x2D:
            case 0x2E:
            case 0x32:
            case 0x35:
            case 0x38:
            case 0x4A:
            case 0x50:
                *pValue = *pValue * _Chal_afAtMostScale[level] + 0.5f;
                break;
            case 2:
            case 0x2A:
                break;
            }
            break;
        }
    }
    if (old != 0 && *pValue == 0) {
        *pValue = 1;
    }
}

void ChalApplyLevelScaling(Challenge_t *pRecord, int level)
{
    signed char i = 0;
    int kind;

    if (ChalHasMedalGoal(pRecord)) {
        i = 1;
        kind = pRecord->mUnknown20C.mUnknown1C;
    } else {
        kind = pRecord->mUnknown1F4[0].mId;
    }
    switch (kind) {
    case 1:
        if (i) {
            for (i = 0; i <= 2; i++) {
                ChalScaleReward(level, &pRecord->mUnknown20C.mUnknown20[i]);
            }
        } else {
            ChalScaleReward(level, &pRecord->mUnknown1F4[0].mUnknown4);
        }
        break;
    case 2:
    case 4:
    case 8:
        if (i) {
            for (i = 0; i <= 2; i++) {
                ChalScaleGoalValue(level, pRecord->mUnknown20C.mUnknown0, &pRecord->mUnknown20C.mUnknown4[i]);
            }
        }
        {
            int j;

            for (j = 0; j < 4; j++) {
                ChalScaleGoalValue(level, pRecord->mUnknown1C4[j].mType, &pRecord->mUnknown1C4[j].mValue);
            }
        }
        break;
    case 3:
    case 5:
    case 6:
    case 7:
        break;
    }
}

void ChalFormatDevPoints(char *pBuffer, int size, unsigned int value)
{
    char text[16];
    unsigned short ones = value % 1000;
    unsigned short thousands = (unsigned short)(value / 1000) % 1000;

    if (value > 999) {
        fn_801C2D88(text, 16, "%d,%03d", thousands, ones);
    } else {
        fn_801C2D88(text, 16, "%d", value);
    }
    fn_801C2D88(pBuffer, size, "%s Development Points", text);
}

void ChalFormatPlayerChoice(char *pBuffer, int size, int value)
{
    fn_801C3284(pBuffer, "Choose a player from any NFL team.", size);
}

void ChalCloseCursors(void)
{
    if (_Chal_sTableCursor.mUnknown0) {
        DbCursorClose(&_Chal_sTableCursor);
    }
    if (_Chal_sInfoCursor.mUnknown0) {
        DbCursorClose(&_Chal_sInfoCursor);
    }
    if (_Chal_sProgressCursor.mUnknown0) {
        DbCursorClose(&_Chal_sProgressCursor);
    }
    _Chal_iInfoHandle = 0;
    _Chal_iProgressHandle = 0;
}

DbCursor *ChalGetTableCursor(void)
{
    if (!_Chal_sTableCursor.mUnknown0) {
        ChalOpenTable(&_Chal_sTableCursor);
    }
    DbCursorFirst(&_Chal_sTableCursor);
    return &_Chal_sTableCursor;
}

DbCursor *ChalGetInfoCursor(int id)
{
    if (!_Chal_sInfoCursor.mUnknown0 || id != _Chal_iInfoHandle) {
        if (_Chal_sInfoCursor.mUnknown0) {
            DbCursorClose(&_Chal_sInfoCursor);
        }
        ChalOpenInfo(&_Chal_sInfoCursor, id);
        _Chal_iInfoHandle = id;
    }
    DbCursorFirst(&_Chal_sInfoCursor);
    return &_Chal_sInfoCursor;
}

DbCursor *ChalGetProgressCursor(int id)
{
    if (!_Chal_sProgressCursor.mUnknown0 || id != _Chal_iProgressHandle) {
        if (_Chal_sProgressCursor.mUnknown0) {
            DbCursorClose(&_Chal_sProgressCursor);
        }
        ChalOpenProgress(&_Chal_sProgressCursor, id);
        _Chal_iProgressHandle = id;
    }
    DbCursorFirst(&_Chal_sProgressCursor);
    return &_Chal_sProgressCursor;
}

void ChalFindRecord(DbCursor *pObject, unsigned char id, int *pResult)
{
    DbCursorFindInt(pObject, 0x44494843, id, 0, pResult);
}

void ChalReadRecord(DbCursor *pObject, Challenge_t *pRecord, int level)
{
    DbColumnValue columns[38];
    char name[208];
    char number[12];
    char *p;
    char *pRest;
    int i;

    memset(pRecord, 0, sizeof(Challenge_t));
    for (i = 0; i < 37; i++) {
        columns[i].Set(0x4C414843, _Chal_aRecordColumns[i], 0);
    }
    columns[37].SetEnd();
    columns[1].mValue = (int)name;
    pRest = 0;
    pObject->Read(columns);
    pRecord->mUnknown0 = columns[0].mValue;
    pRecord->mUnknown1A4 = columns[6].mValue;
    pRecord->mUnknown196 = columns[2].mValue;
    pRecord->mUnknown198 = columns[3].mValue;
    pRecord->mUnknown19C = columns[4].mValue;
    pRecord->mUnknown1A0 = columns[5].mValue;
    pRecord->mUnknown1A6 = columns[7].mValue;
    pRecord->mUnknown1A7 = columns[8].mValue;
    pRecord->mUnknown1A8 = columns[9].mValue;
    pRecord->mUnknown1AC = columns[10].mValue;
    pRecord->mUnknown1B0 = columns[11].mValue;
    pRecord->mUnknown1B4 = columns[12].mValue;
    pRecord->mUnknown1B8 = columns[13].mValue;
    pRecord->mUnknown1BC = columns[14].mValue;
    pRecord->mUnknown1C0 = columns[15].mValue;
    pRecord->mUnknown1C1 = columns[16].mValue;
    pRecord->mUnknown1C2 = columns[17].mValue;
    pRecord->mUnknown1C3 = columns[18].mValue;
    pRecord->mUnknown1C4[0].mType = columns[19].mValue;
    pRecord->mUnknown1C4[0].mValue = columns[20].mValue;
    pRecord->mUnknown1C4[0].mUnknown8 = columns[21].mValue;
    pRecord->mUnknown1C4[1].mType = columns[22].mValue;
    pRecord->mUnknown1C4[1].mValue = columns[23].mValue;
    pRecord->mUnknown1C4[1].mUnknown8 = columns[24].mValue;
    pRecord->mUnknown1C4[2].mType = columns[25].mValue;
    pRecord->mUnknown1C4[2].mValue = columns[26].mValue;
    pRecord->mUnknown1C4[2].mUnknown8 = columns[27].mValue;
    pRecord->mUnknown1C4[3].mType = columns[28].mValue;
    pRecord->mUnknown1C4[3].mValue = columns[29].mValue;
    pRecord->mUnknown1C4[3].mUnknown8 = columns[30].mValue;
    pRecord->mUnknown1F4[0].mId = columns[31].mValue;
    pRecord->mUnknown1F4[0].mUnknown4 = columns[32].mValue;
    pRecord->mUnknown1F4[1].mId = columns[33].mValue;
    pRecord->mUnknown1F4[1].mUnknown4 = columns[34].mValue;
    pRecord->mUnknown204 = columns[35].mValue;
    pRecord->mUnknown208 = columns[36].mValue;
    ChalReadMedalGoal(pRecord->mUnknown0, &pRecord->mUnknown20C);
    ChalApplyLevelScaling(pRecord, level);
    pRecord->mUnknown1[0] = 0;
    pRecord->mUnknownCB[0] = 0;

    for (p = name; *p != 0; p++) {
        if (*p == ' ' && p[1] == '-' && p[2] == ' ') {
            *p = 0;
            fn_801C3284(pRecord->mUnknown1, name, 201);
            pRest = p + 3;
            *p = ' ';
            break;
        }
    }

    if (pRest) {
        int length = 0;
        int copy = 1;

        p = pRest;
        while (*p != 0 && length < 200) {
            if (*p == '%' && (lbl_802AEF10 + 1)[(unsigned char)p[1]] & 4 && (unsigned int)(p[1] - '1') <= 3) {
                char *q;

                fn_801C2D88(number, 12, "%d", pRecord->mUnknown1C4[p[1] - '1'].mValue);
                for (q = number; *q != 0 && length < 200; q++) {
                    pRecord->mUnknownCB[length++] = *q;
                }
                p += 2;
                copy = 0;
            }
            if (copy) {
                pRecord->mUnknownCB[length++] = *p++;
            }
            copy = 1;
        }
        pRecord->mUnknownCB[length] = 0;
    }

    if (ChalHasMedalGoal(pRecord)) {
        for (p = pRecord->mUnknownCB; *p != 0; p++) {
            if (*p == '_') {
                break;
            }
        }
        if (*p != 0) {
            char *pStart;
            int count;

            *p = 0;
            p++;
            pStart = p;
            count = 0;
            while (count <= 2) {
                if (*p == '_' || *p == 0) {
                    pRecord->mUnknown20C.mUnknown10[count++] = pStart;
                    if (*p != 0) {
                        *p = 0;
                        p++;
                        pStart = p;
                    } else {
                        break;
                    }
                } else {
                    p++;
                }
            }
        }
    }

    for (i = 0; i <= 3 && pRecord->mUnknown1C4[i].mType != 0; i++) {
    }
    if (ChalHasMedalGoal(pRecord)) {
        if (i > 3) {
            i = 3;
        }
        pRecord->mUnknown1C4[i].mType = pRecord->mUnknown20C.mUnknown0;
        pRecord->mUnknown1C4[i].mValue = pRecord->mUnknown20C.mUnknown4[2];
        pRecord->mUnknown1C4[i].mUnknown8 = 1;
        i++;
    }
    for (; i <= 3; i++) {
    }
    for (i = 0; i <= 3; i++) {
        if (pRecord->mUnknown1C4[i].mType == 0x50) {
            pRecord->mUnknown1A4 = pRecord->mUnknown1C4[i].mValue;
            break;
        }
    }
}

Challenge_t *ChalGetCurrent(void)
{
    return &_Chal_sCurrent;
}

void ChalLoadCurrent(unsigned char id, int level)
{
    DbCursor *pObject = ChalGetTableCursor();

    ChalFindRecord(pObject, id, 0);
    ChalReadRecord(pObject, &_Chal_sCurrent, level);
}

int ChalGetProgress(int id, int *pA, int *pB)
{
    int result = 0;
    int index = fn_8022F4BC();
    int handle;

    *pB = 3;
    handle = fn_8022F3D4(index);
    *pA = 7;
    if (handle != -1) {
        DbCursor *pObject = ChalGetProgressCursor(handle);

        if (DbCursorFindInt(pObject, 0x44494843, id, 0, 0)) {
            result = DbCursorGetInt(pObject, 0x534C4843);
            *pA = DbCursorGetValue(pObject, 0x444D4843);
            if (result == 1) {
                Challenge_t record;
                DbCursor *pCursor = ChalGetTableCursor();

                ChalFindRecord(pCursor, id, 0);
                ChalReadRecord(pCursor, &record, 1);
                if (record.mUnknown1F4[0].mId == 8 && !fn_8007C538(record.mUnknown1F4[0].mUnknown4)) {
                    result = 0;
                }
            }
            if (result == 2) {
                int value = DbCursorGetInt(pObject, 0x4C534843);

                if (value != 3) {
                    *pB = value;
                }
            }
        }
    }
    return result;
}

void ChalSetProgress(int id, int a, int b, int c)
{
    int handle = fn_8022F3D4(fn_8022F4BC());

    if (handle != -1) {
        DbCursor *pObject = ChalGetProgressCursor(handle);

        if (DbCursorFindInt(pObject, 0x44494843, id, 0, 0)) {
            fn_8007ABA4(pObject, 0x534C4843, a);
            fn_8007AA90(pObject, 0x444D4843, b);
            if (a == 2) {
                fn_8007ABA4(pObject, 0x4C534843, c);
            } else {
                fn_8007ABA4(pObject, 0x4C534843, 3);
            }
        }
    }
}

unsigned int ChalGetPoints(void)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    unsigned int result;

    if (handle == -1) {
        result = 0;
    } else {
        result = DbCursorGetInt(ChalGetInfoCursor(handle), 0x50434943);
    }
    return result;
}

void ChalAddPoints(int value)
{
    int handle = fn_8022F3D4(fn_8022F4BC());

    if (handle != -1) {
        DbCursor *pObject = ChalGetInfoCursor(handle);

        fn_8007ABA4(pObject, 0x50434943, DbCursorGetInt(pObject, 0x50434943) + value);
    }
}

int ChalGetTournamentSlot(void)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    int result;

    if (handle == -1) {
        result = 0;
    } else {
        result = DbCursorGetInt(ChalGetInfoCursor(handle), 0x54524943);
    }
    return result;
}

void ChalSetTournamentSlot(int value)
{
    int handle = fn_8022F3D4(fn_8022F4BC());

    if (handle != -1) {
        fn_8007ABA4(ChalGetInfoCursor(handle), 0x54524943, value);
    }
}

int ChalGetTournamentWon(void)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    int result;

    if (handle == -1) {
        result = 0;
    } else {
        result = (unsigned char)DbCursorGetInt(ChalGetInfoCursor(handle), 0x4D574943);
    }
    return result;
}

void ChalSetTournamentWon(int value)
{
    int index = fn_8022F4BC();
    int handle = fn_8022F3D4(index);

    if (handle != -1) {
        fn_8007ABA4(ChalGetInfoCursor(handle), 0x4D574943, value);
        if (value) {
            fn_801FCE10(0, "use \x8c update 'TSPU' set 'FNWU' = \x82\n", handle, 1);
            fn_8007F6F8(20, 1);
            fn_8018787C(fn_80186B38(index));
        }
    }
}

int ChalCountInGroup(int id)
{
    int count = 0;
    DbCursor *pObject = ChalGetTableCursor();

    if (DbCursorFindInt(pObject, 0x44464843, id, 0, 0)) {
        do {
            count++;
        } while (DbCursorFindInt(pObject, 0x44464843, id, 1, 0));
    }
    return count;
}

int ChalGetIdInGroup(int a, signed char index)
{
    int id = 0;

    if (fn_801FCE10(0, "use 'TATS' select 'DIHC' into \x82 from 'LAHC' where 'DFHC' = \x85 and 'ROHC' = \x80\n", &id, a, index) != 0) {
        return 0;
    }
    return id;
}

int ChalGetGearReward(int id)
{
    int gear = 0;

    if (fn_801FCE10(0, "use 'TATS' select 'GGHC' into \x85 from 'GUHC' where 'IGHC' = \x84\n", &gear, id) == 0) {
        gear = fn_8007C46C(gear);
    } else {
        gear = 0;
    }
    return gear;
}

int ChalGetDevPointsAt(int index)
{
    int result = 0;
    int handle = fn_8022F3D4(index);

    if (handle != -1) {
        result = DbCursorGetInt(ChalGetInfoCursor(handle), 0x50444943);
    }
    return result;
}

int ChalGetDevPoints(void)
{
    return ChalGetDevPointsAt(fn_8022F4BC());
}

void ChalSetDevPoints(int value)
{
    int handle = fn_8022F3D4(fn_8022F4BC());

    if (handle != -1) {
        fn_8007ABA4(ChalGetInfoCursor(handle), 0x50444943, value);
    }
}

void ChalSetDevPointsForSlot(int index, int value)
{
    int handle = fn_8022F3D4(fn_8022F358(index));

    if (handle != -1) {
        fn_8007ABA4(ChalGetInfoCursor(handle), 0x50444943, value);
    }
}

void ChalFormatGoalProgress(int type, unsigned int value, char *pText, int size)
{
    char text[128];
    unsigned int a;
    unsigned int b;
    unsigned int c;
    int tag = _Chal_aGoalTypes[type].mTag;
    const char *pFormat = _Chal_aGoalTypes[type].mpFormat;

    if (tag != -1 && fn_801C3180(pFormat) != 0) {
        int side = !_Chal_aGoalTypes[type].mFlag;

        fn_8022B7A4(side, tag, &a);
        if (tag == 0x73707374 && (fn_800AD9B4() == 2 || fn_800AD9B4() == 5)) {
            int value2 = fn_80178308();
            Object_8017886C *pPlay = fn_8017886C();

            if (value2 == side && (a == 0 || ((pPlay->mUnknown18 & 8) && fn_800A2178() != 14))) {
                a++;
            }
        }
        fn_801C2D88(text, 128, pFormat, a);
        fn_801C2EF0(pText, text, size);
    } else {
        switch (type) {
        case 3:
            fn_801C2D88(text, 128, pFormat, fn_800D41F8(1));
            fn_801C2EF0(pText, text, size);
            break;
        case 6:
            fn_8022B7A4(1, 0x6E737374, &a);
            fn_8022B7A4(0, 0x6E737374, &b);
            switch (fn_800AD9B4()) {
            case 5:
                fn_801C2D88(text, 128, pFormat, a + b + 1);
                break;
            case 4:
                if ((unsigned char)fn_800B9A90(lbl_803EAB84)) {
                    fn_801C2D88(text, 128, pFormat, a + b);
                    break;
                }
            case 2:
            case 3:
                fn_801C2D88(text, 128, pFormat, a + b + 1);
                break;
            default:
                fn_801C2D88(text, 128, pFormat, a + b);
                break;
            }
            fn_801C2EF0(pText, text, size);
            break;
        case 0x1F:
            fn_801C2D88(text, 128, pFormat, fn_800A7E40(1));
            fn_801C2EF0(pText, text, size);
            break;
        case 0x29:
            fn_8022B7A4(1, 0x74727374, &a);
            fn_8022B7A4(1, 0x74507374, &b);
            fn_8022B7A4(1, 0x64647374, &c);
            fn_801C2D88(text, 128, pFormat, a + b + c);
            fn_801C2EF0(pText, text, size);
            break;
        case 0x2A:
            fn_801C2D88(text, 128, pFormat, fn_801787DC(1));
            fn_801C2EF0(pText, text, size);
            break;
        case 0x2D:
            fn_8022B7A4(0, 0x74727374, &a);
            fn_8022B7A4(0, 0x74507374, &b);
            fn_8022B7A4(0, 0x64647374, &c);
            fn_801C2D88(text, 128, pFormat, a + b + c);
            fn_801C2EF0(pText, text, size);
            break;
        case 0x2E:
            fn_801C2D88(text, 128, pFormat, fn_801787DC(0));
            fn_801C2EF0(pText, text, size);
            break;
        case 0x31:
            fn_8022B7A4(1, 0x43637374, &a);
            if (a >= value) {
                fn_801C2D88(text, 128, "Best Completion Streak: %d", a);
            } else {
                fn_801C2D88(text, 128, "Current Completion Streak: %d", fn_800D7528(1));
            }
            fn_801C2EF0(pText, text, size);
            break;
        case 0x35:
            fn_8022B7A4(1, 0x6E737374, &a);
            fn_8022B7A4(0, 0x6E737374, &b);
            switch (fn_800AD9B4()) {
            case 5:
                fn_801C2D88(text, 128, pFormat, a + b + 1);
                break;
            case 4:
                if ((unsigned char)fn_800B9A90(lbl_803EAB84)) {
                    fn_801C2D88(text, 128, pFormat, a + b);
                    break;
                }
            case 2:
            case 3:
                fn_801C2D88(text, 128, pFormat, a + b + 1);
                break;
            default:
                fn_801C2D88(text, 128, pFormat, a + b);
                break;
            }
            fn_801C2EF0(pText, text, size);
            break;
        case 0x3A:
            fn_8022B7A4(1, 0x61707374, &a);
            fn_8022B7A4(1, 0x6E737374, &b);
            fn_801C2D88(text, 128, pFormat, b != 0 ? (unsigned int)((float)a / (float)b * 100.0f) : 0);
            fn_801C2EF0(pText, text, size);
            break;
        case 0x3E:
            fn_8022B7A4(1, 0x43737374, &a);
            if (a >= value) {
                fn_801C2D88(text, 128, "Best Stylin' Completion Streak: %d", a);
            } else {
                fn_801C2D88(text, 128, "Current Stylin' Completion Streak: %d", fn_800D7544(1));
            }
            fn_801C2EF0(pText, text, size);
            break;
        case 0x42:
            fn_8022B7A4(1, 0x50637374, &a);
            if (a >= value) {
                fn_801C2D88(text, 128, "Consecutive Pitches One Play Best: %d", a);
            } else {
                fn_801C2D88(text, 128, "Consecutive Pitches Last Play: %d", a);
            }
            fn_801C2EF0(pText, text, size);
            break;
        case 0x4A:
            fn_8022B7A4(1, 0x61707374, &a);
            fn_8022B7A4(1, 0x63707374, &b);
            fn_801C2D88(text, 128, "Incomplete Passes: %d", a - b);
            fn_801C2EF0(pText, text, size);
            break;
        }
    }
}

void ChalFormatGearReward(char *pBuffer, int size, int id)
{
    char stat[32];
    DbCursor cursor;
    short modifiers[12];
    char name[64] = "";
    int key;
    char number[8];
    int separate = 0;
    int gear;

    fn_801C3284(pBuffer, "", size);
    gear = ChalGetGearReward(id);
    if (gear) {
        fn_8007BA48(&cursor);
        if (fn_8007BB4C(&cursor, gear, &key)) {
            int count;

            fn_8007BE20(&cursor, name, 64);
            count = fn_8007C690(&cursor, modifiers);
            fn_801C2F88(pBuffer, name, size);
            if (count) {
                signed char i;

                fn_801C2F88(pBuffer, ": (", size);
                for (i = 0; i <= 9; i++) {
                    if (modifiers[i] != 0) {
                        if (separate) {
                            fn_801C2F88(pBuffer, ", ", size);
                        } else {
                            separate = 1;
                        }
                        if (modifiers[i] < 0) {
                            fn_801C2D88(number, 8, "%d ", (short)(modifiers[i] / 5));
                        } else {
                            fn_801C2D88(number, 8, "+%d ", (short)(modifiers[i] / 5));
                        }
                        fn_801C2F88(pBuffer, number, size);
                        fn_800B4A18(i, stat, 32);
                        fn_801C2F88(pBuffer, stat, size);
                    }
                }
                fn_801C2F88(pBuffer, ")", size);
            }
        } else {
            fn_801C2F88(pBuffer, "Unknown Gear Type", size);
        }
        fn_8007BB04(&cursor);
    } else {
        fn_801C2F88(pBuffer, "Unknown Gear Type", size);
    }
}

void ChalFormatReward(int type, unsigned short value, char *pBuffer, unsigned short size)
{
    switch (type) {
    case 0:
        *pBuffer = 0;
        break;
    case 1:
        ChalFormatDevPoints(pBuffer, size, value);
        break;
    case 2:
        ChalFormatGearReward(pBuffer, size, value);
        break;
    case 4:
        ChalFormatPlayerChoice(pBuffer, size, value);
        break;
    case 3:
    case 5:
    case 6:
    case 7:
        break;
    case 8:
        fn_801C3284(pBuffer, "Impact Gear Modifier", size);
        break;
    }
}

void ChalFormatRewards(Challenge_t *pRecord, char *pBuffer, unsigned short size)
{
    char value[200];
    char text[600] = "";
    char *p = text;
    int left = sizeof(text);
    signed char i;

    if (ChalHasMedalGoal(pRecord)) {
        ChalMedalGoal_t *pInfo = &pRecord->mUnknown20C;

        for (i = 0; i <= 2; i++) {
            ChalFormatReward(pInfo->mUnknown1C, pInfo->mUnknown20[i], value, 200);
            fn_801C2D88(p, left, "%s - %s\n", _Chal_aszMedalNames[i], value);
            p += fn_801C3180(p);
            left -= fn_801C3180(p);
        }
    } else {
        for (i = 0; i <= 1 && pRecord->mUnknown1F4[i].mId != 0; i++) {
            ChalFormatReward(pRecord->mUnknown1F4[i].mId, pRecord->mUnknown1F4[i].mUnknown4, value, 200);
            fn_801C2D88(p, left, "%s\n", value);
            p += fn_801C3180(p);
            left -= fn_801C3180(p);
        }
    }
    fn_801C3284(pBuffer, text, size);
}

int ChalCheckGoal(int side, Challenge_t *pRecord, int index, int *pResult)
{
    int type = pRecord->mUnknown1C4[index].mType;
    int result = 0;

    if (_Chal_aGoalTypes[type].mKind != 4) {
        int (*pTest)(int, int, Challenge_t *, int) = _Chal_aGoalTests[_Chal_aGoalTypes[type].mKind].mpRecordTest;

        if (_Chal_aGoalTypes[type].mFlag) {
            side = !side;
        }
        *pResult = pTest(_Chal_aGoalTypes[type].mTag, side, pRecord, index);
        result = 1;
    }
    return result;
}

int ChalCheckMedalGoal(int side, ChalMedalGoal_t *pInfo)
{
    int type = pInfo->mUnknown0;
    int testSide = side;
    int result = 7;

    if (_Chal_aGoalTypes[type].mKind != 4) {
        int (*pTest)(int, int, ChalMedalGoal_t *) = _Chal_aGoalTests[_Chal_aGoalTypes[type].mKind].mpInfoTest;

        if (_Chal_aGoalTypes[type].mFlag) {
            testSide = !side;
        }
        result = pTest(_Chal_aGoalTypes[type].mTag, testSide, pInfo);
    } else if (type == 3) {
        result = ChalRankStylePoints(side, pInfo);
    }
    return result;
}

int ChalFindGoalValue(Challenge_t *pRecord, int type, int *pValue)
{
    int value;
    int i;

    if (pValue == 0) {
        pValue = &value;
    }
    for (i = 0; i < 4; i++) {
        if (pRecord->mUnknown1C4[i].mType == type) {
            *pValue = pRecord->mUnknown1C4[i].mValue;
            return 1;
        }
    }
    return 0;
}

int ChalHasMedalGoal(Challenge_t *pRecord)
{
    return pRecord->mUnknown20C.mUnknown0 != 0;
}

int ChalHasReward(Challenge_t *pRecord, int id)
{
    int i;

    for (i = 0; i <= 1; i++) {
        if (pRecord->mUnknown1F4[i].mId == id) {
            return 1;
        }
    }
    return 0;
}

void ChalSetTournamentScore(int id, int a, int b)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    Class_8018FD64 cursor;

    cursor.fn_8018FDEC(0x47505443, 0x4D475443, 0, 0, handle);
    cursor.fn_8018FF54(0x4D475443, id, 0, 0);
    cursor.fn_80190008(0x31535443, a);
    cursor.fn_80190008(0x32535443, b);
}

void ChalGetTournamentScore(int id, short *pA, short *pB)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    Class_8018FD64 cursor;

    cursor.fn_8018FDEC(0x47505443, 0x4D475443, 0, 0, handle);
    cursor.fn_8018FF54(0x4D475443, id, 0, 0);
    *pA = cursor.fn_8018FF78(0x31535443);
    *pB = cursor.fn_8018FF78(0x32535443);
}

void ChalSaveTournamentTeams(int *pValues, int count)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    Class_8018FD64 cursor;
    int i;

    cursor.fn_8018FDEC(0x4C545443, 0x44524F54, 0, 0, handle);
    for (i = 0; i < count; i++) {
        cursor.fn_8018FF54(0x44524F54, i, 0, 0);
        cursor.fn_80190008(0x44494754, pValues[i]);
    }
}

void ChalLoadTournamentTeams(int *pValues, int count)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    Class_8018FD64 cursor;
    int i;

    cursor.fn_8018FDEC(0x4C545443, 0x44524F54, 0, 0, handle);
    for (i = 0; i < count; i++) {
        cursor.fn_8018FF54(0x44524F54, i, 0, 0);
        pValues[i] = cursor.fn_8018FF78(0x44494754);
    }
}

}
