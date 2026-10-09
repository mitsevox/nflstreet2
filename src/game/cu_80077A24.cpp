/* 0x80077A24-0x80079CD8. Probably the back of one source file with the range
   0x800775F0-0x80077A24 (cu_800775F0), whose test functions fill lbl_802D6400. */

#include <string.h>
#include "game/Class_8018FD64Inline.h"
#include "game/Class_80297C60.h"
#include "game/Object_8007A334.h"
#include "game/Object_800785C0.h"
#include "game/Object_8017886C.h"
#include "game/fn_801C3284.h"
#include "game/fn_801FCE10.h"

/* 16-byte entry of the table lbl_80291574, indexed by a type number: the tag
   passed to fn_8022B7A4, a flag that selects the other side, a kind (0-4)
   and a printf format. */
struct Entry_80291574 {
    int mTag;
    unsigned char mFlag;
    int mKind;
    const char *mpFormat;
};

/* Pair of functions of the range 0x800775F0-0x80077A24 selected by Entry_80291574::mKind. */
struct Tests_802D6400 {
    int (*mpRecordTest)(int tag, int side, Object_800785C0 *pRecord, int index);
    int (*mpInfoTest)(int tag, int side, Info_8007984C *pInfo);
};

extern "C" {

int fn_800775F0(int tag, int side, Object_800785C0 *pRecord, int index);
int fn_800775F8(int tag, int side, Info_8007984C *pInfo);
int fn_80077600(int tag, int side, Object_800785C0 *pRecord, int index);
int fn_80077654(int tag, int side, Info_8007984C *pInfo);
int fn_800776DC(int tag, int side, Object_800785C0 *pRecord, int index);
int fn_80077730(int tag, int side, Info_8007984C *pInfo);
int fn_800777B8(int side, Info_8007984C *pInfo);
void fn_80077828(Object_8007A334 *pObject);
void fn_80077854(Object_8007A334 *pObject, int value);
void fn_80077890(Object_8007A334 *pObject, int value);
void fn_800778CC(int id, Info_8007984C *pInfo);
int fn_8007984C(Object_800785C0 *pRecord);

int fn_8007BB4C(Object_8007A334 *pCursor, int key, int *pResult);
void fn_8007BA48(Object_8007A334 *pCursor);
void fn_8007BB04(Object_8007A334 *pCursor);
void fn_8007BE20(Object_8007A334 *pCursor, char *pBuffer, int size);
int fn_8007C46C(int key);
int fn_8007C538(int id);
int fn_8007C690(Object_8007A334 *pCursor, short *pOut);
void fn_8007F6F8(int a, int b);
int fn_800A2178(void);
int fn_800A7E40(unsigned char side);
int fn_800AD9B4(void);
void fn_800B4A18(int index, char *pDest, int size);
int fn_800B9A90(Class_80297C60 *p);
int fn_800D41F8(int side);
int fn_800D7528(int side);
int fn_800D7544(int side);
int fn_80178308(void);
int fn_801787DC(int team);
signed char fn_80186B38(int a);
void fn_8018787C(void);
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

Tests_802D6400 lbl_802D6400[3] = {
    { fn_800775F0, fn_800775F8 },
    { fn_800776DC, fn_80077730 },
    { fn_80077600, fn_80077654 },
};
const char *lbl_802D6418[3] = { "Gold", "Silver", "Bronze" };

static Object_8007A334 lbl_8030ADE0;
static Object_8007A334 lbl_8030AE0C;
static Object_8007A334 lbl_8030AE38;
static Object_800785C0 lbl_8030AE64;
static int lbl_803EA790 = 0;
static int lbl_803EA794 = 0;

static const float lbl_80290EE4[3] = { 0.85f, 0.92f, 1.0f };
static const float lbl_80290EF0[3] = { 1.0f, 0.85f, 0.7f };
static const float lbl_80290EFC[3] = { 0.7f, 0.85f, 1.0f };
static const int lbl_80290F08[37] = {
    0x44494843, 0x45444843, 0x4F434843, 0x504F4843, 0x54474843, 0x54504843, 0x49544843, 0x59444843,
    0x41434843, 0x53554843, 0x53434843, 0x53504843, 0x53504343, 0x4F504843, 0x44464843, 0x4C594843,
    0x4E444843, 0x46554843, 0x47464843, 0x41514843, 0x41505143, 0x41525143, 0x42514843, 0x42505143,
    0x42525143, 0x43514843, 0x43505143, 0x43525143, 0x44514843, 0x44505143, 0x44525143, 0x54524843,
    0x56524843, 0x32524843, 0x32564843, 0x524F4843, 0x44444843,
};
static const Entry_80291574 lbl_80291574[85] = {
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

void fn_80077A24(int level, unsigned short *pValue)
{
    *pValue = *pValue * lbl_80290EE4[level] + 0.5f;
}

void fn_80077A8C(int level, int type, unsigned int *pValue)
{
    unsigned int old = *pValue;

    if (type != 0) {
        switch (lbl_80291574[type].mKind) {
        case 1:
            *pValue = *pValue * lbl_80290EF0[level] + 0.5f;
            break;
        case 2:
            *pValue = *pValue * lbl_80290EFC[level] + 0.5f;
            break;
        default:
            switch (type) {
            case 3:
            case 0x1F:
            case 0x29:
                *pValue = *pValue * lbl_80290EF0[level] + 0.5f;
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
                *pValue = *pValue * lbl_80290EFC[level] + 0.5f;
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

void fn_80077D0C(Object_800785C0 *pRecord, int level)
{
    signed char i = 0;
    int kind;

    if (fn_8007984C(pRecord)) {
        i = 1;
        kind = pRecord->mUnknown20C.mUnknown1C;
    } else {
        kind = pRecord->mUnknown1F4[0].mId;
    }
    switch (kind) {
    case 1:
        if (i) {
            for (i = 0; i <= 2; i++) {
                fn_80077A24(level, &pRecord->mUnknown20C.mUnknown20[i]);
            }
        } else {
            fn_80077A24(level, &pRecord->mUnknown1F4[0].mUnknown4);
        }
        break;
    case 2:
    case 4:
    case 8:
        if (i) {
            for (i = 0; i <= 2; i++) {
                fn_80077A8C(level, pRecord->mUnknown20C.mUnknown0, &pRecord->mUnknown20C.mUnknown4[i]);
            }
        }
        {
            int j;

            for (j = 0; j < 4; j++) {
                fn_80077A8C(level, pRecord->mUnknown1C4[j].mType, (unsigned int *)&pRecord->mUnknown1C4[j].mValue);
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

void fn_80077E38(char *pBuffer, int size, unsigned int value)
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

void fn_80077EF8(char *pBuffer, int size, int value)
{
    fn_801C3284(pBuffer, "Choose a player from any NFL team.", size);
}

void fn_80077F24(void)
{
    if (lbl_8030ADE0.mUnknown0) {
        fn_8007A3C4(&lbl_8030ADE0);
    }
    if (lbl_8030AE0C.mUnknown0) {
        fn_8007A3C4(&lbl_8030AE0C);
    }
    if (lbl_8030AE38.mUnknown0) {
        fn_8007A3C4(&lbl_8030AE38);
    }
    lbl_803EA790 = 0;
    lbl_803EA794 = 0;
}

Object_8007A334 *fn_80077F94(void)
{
    if (!lbl_8030ADE0.mUnknown0) {
        fn_80077828(&lbl_8030ADE0);
    }
    fn_8007A444(&lbl_8030ADE0);
    return &lbl_8030ADE0;
}

Object_8007A334 *fn_80077FE0(int id)
{
    if (!lbl_8030AE0C.mUnknown0 || id != lbl_803EA790) {
        if (lbl_8030AE0C.mUnknown0) {
            fn_8007A3C4(&lbl_8030AE0C);
        }
        fn_80077854(&lbl_8030AE0C, id);
        lbl_803EA790 = id;
    }
    fn_8007A444(&lbl_8030AE0C);
    return &lbl_8030AE0C;
}

Object_8007A334 *fn_80078050(int id)
{
    if (!lbl_8030AE38.mUnknown0 || id != lbl_803EA794) {
        if (lbl_8030AE38.mUnknown0) {
            fn_8007A3C4(&lbl_8030AE38);
        }
        fn_80077890(&lbl_8030AE38, id);
        lbl_803EA794 = id;
    }
    fn_8007A444(&lbl_8030AE38);
    return &lbl_8030AE38;
}

void fn_800780C0(Object_8007A334 *pObject, unsigned char id, int *pResult)
{
    fn_8007A7F4(pObject, 0x44494843, id, 0, pResult);
}

void fn_800780F8(Object_8007A334 *pObject, Object_800785C0 *pRecord, int level)
{
    ColumnValue_802D6424 columns[38];
    char name[208];
    char number[12];
    char *p;
    char *pRest;
    int i;

    memset(pRecord, 0, sizeof(Object_800785C0));
    for (i = 0; i < 37; i++) {
        columns[i].Set(0x4C414843, lbl_80290F08[i], 0);
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
    fn_800778CC(pRecord->mUnknown0, &pRecord->mUnknown20C);
    fn_80077D0C(pRecord, level);
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

    if (fn_8007984C(pRecord)) {
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
    if (fn_8007984C(pRecord)) {
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

Object_800785C0 *fn_800785C0(void)
{
    return &lbl_8030AE64;
}

void fn_800785CC(unsigned char id, int level)
{
    Object_8007A334 *pObject = fn_80077F94();

    fn_800780C0(pObject, id, 0);
    fn_800780F8(pObject, &lbl_8030AE64, level);
}

int fn_80078620(int id, int *pA, int *pB)
{
    int result = 0;
    int team = fn_8022F4BC();
    int handle;

    *pB = 3;
    handle = fn_8022F3D4(team);
    *pA = 7;
    if (handle != -1) {
        Object_8007A334 *pObject = fn_80078050(handle);

        if (fn_8007A7F4(pObject, 0x44494843, id, 0, 0)) {
            result = fn_8007A98C(pObject, 0x534C4843);
            *pA = fn_8007A934(pObject, 0x444D4843);
            if (result == 1) {
                Object_800785C0 record;
                Object_8007A334 *pPlayers = fn_80077F94();

                fn_800780C0(pPlayers, id, 0);
                fn_800780F8(pPlayers, &record, 1);
                if (record.mUnknown1F4[0].mId == 8 && !fn_8007C538(record.mUnknown1F4[0].mUnknown4)) {
                    result = 0;
                }
            }
            if (result == 2) {
                int value = fn_8007A98C(pObject, 0x4C534843);

                if (value != 3) {
                    *pB = value;
                }
            }
        }
    }
    return result;
}

void fn_80078738(int id, int a, int b, int c)
{
    int handle = fn_8022F3D4(fn_8022F4BC());

    if (handle != -1) {
        Object_8007A334 *pObject = fn_80078050(handle);

        if (fn_8007A7F4(pObject, 0x44494843, id, 0, 0)) {
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

unsigned int fn_80078800(void)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    unsigned int result;

    if (handle == -1) {
        result = 0;
    } else {
        result = fn_8007A98C(fn_80077FE0(handle), 0x50434943);
    }
    return result;
}

void fn_80078844(int value)
{
    int handle = fn_8022F3D4(fn_8022F4BC());

    if (handle != -1) {
        Object_8007A334 *pObject = fn_80077FE0(handle);

        fn_8007ABA4(pObject, 0x50434943, fn_8007A98C(pObject, 0x50434943) + value);
    }
}

int fn_800788A4(void)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    int result;

    if (handle == -1) {
        result = 0;
    } else {
        result = fn_8007A98C(fn_80077FE0(handle), 0x54524943);
    }
    return result;
}

void fn_800788E8(int value)
{
    int handle = fn_8022F3D4(fn_8022F4BC());

    if (handle != -1) {
        fn_8007ABA4(fn_80077FE0(handle), 0x54524943, value);
    }
}

int fn_80078934(void)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    int result;

    if (handle == -1) {
        result = 0;
    } else {
        result = (unsigned char)fn_8007A98C(fn_80077FE0(handle), 0x4D574943);
    }
    return result;
}

void fn_8007897C(int value)
{
    int team = fn_8022F4BC();
    int handle = fn_8022F3D4(team);

    if (handle != -1) {
        fn_8007ABA4(fn_80077FE0(handle), 0x4D574943, value);
        if (value) {
            fn_801FCE10(0, "use \x8c update 'TSPU' set 'FNWU' = \x82\n", handle, 1);
            fn_8007F6F8(20, 1);
            fn_80186B38(team);
            fn_8018787C();
        }
    }
}

int fn_80078A0C(int id)
{
    int count = 0;
    Object_8007A334 *pObject = fn_80077F94();

    if (fn_8007A7F4(pObject, 0x44464843, id, 0, 0)) {
        do {
            count++;
        } while (fn_8007A7F4(pObject, 0x44464843, id, 1, 0));
    }
    return count;
}

int fn_80078A8C(int a, signed char index)
{
    int id = 0;

    if (fn_801FCE10(0, "use 'TATS' select 'DIHC' into \x82 from 'LAHC' where 'DFHC' = \x85 and 'ROHC' = \x80\n", &id, a, index) != 0) {
        return 0;
    }
    return id;
}

int fn_80078AE0(int id)
{
    int gear = 0;

    if (fn_801FCE10(0, "use 'TATS' select 'GGHC' into \x85 from 'GUHC' where 'IGHC' = \x84\n", &gear, id) == 0) {
        gear = fn_8007C46C(gear);
    } else {
        gear = 0;
    }
    return gear;
}

int fn_80078B48(int team)
{
    int result = 0;
    int handle = fn_8022F3D4(team);

    if (handle != -1) {
        result = fn_8007A98C(fn_80077FE0(handle), 0x50444943);
    }
    return result;
}

int fn_80078B94(void)
{
    return fn_80078B48(fn_8022F4BC());
}

void fn_80078BB8(int value)
{
    int handle = fn_8022F3D4(fn_8022F4BC());

    if (handle != -1) {
        fn_8007ABA4(fn_80077FE0(handle), 0x50444943, value);
    }
}

void fn_80078C04(int index, int value)
{
    int handle = fn_8022F3D4(fn_8022F358(index));

    if (handle != -1) {
        fn_8007ABA4(fn_80077FE0(handle), 0x50444943, value);
    }
}

void fn_80078C50(int type, int value, char *pText, int size)
{
    char text[128];
    unsigned int a;
    unsigned int b;
    unsigned int c;
    int tag = lbl_80291574[type].mTag;
    const char *pFormat = lbl_80291574[type].mpFormat;

    if (tag != -1 && fn_801C3180(pFormat) != 0) {
        int side = !lbl_80291574[type].mFlag;

        fn_8022B7A4(side, tag, &a);
        if (tag == 0x73707374 && (fn_800AD9B4() == 2 || fn_800AD9B4() == 5)) {
            int team = fn_80178308();
            Object_8017886C *pPlay = fn_8017886C();

            if (team == side && (a == 0 || ((pPlay->mUnknown18 & 8) && fn_800A2178() != 14))) {
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
            case 4:
                if ((unsigned char)fn_800B9A90(lbl_803EAB84)) {
                    fn_801C2D88(text, 128, pFormat, a + b);
                    break;
                }
            case 2:
            case 3:
            case 5:
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
            if (a >= (unsigned int)value) {
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
            case 4:
                if ((unsigned char)fn_800B9A90(lbl_803EAB84)) {
                    fn_801C2D88(text, 128, pFormat, a + b);
                    break;
                }
            case 2:
            case 3:
            case 5:
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
            if (a >= (unsigned int)value) {
                fn_801C2D88(text, 128, "Best Stylin' Completion Streak: %d", a);
            } else {
                fn_801C2D88(text, 128, "Current Stylin' Completion Streak: %d", fn_800D7544(1));
            }
            fn_801C2EF0(pText, text, size);
            break;
        case 0x42:
            fn_8022B7A4(1, 0x50637374, &a);
            if (a >= (unsigned int)value) {
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

void fn_80079248(char *pBuffer, int size, int id)
{
    char stat[32];
    Object_8007A334 cursor;
    short modifiers[12];
    char name[64] = "";
    int key;
    char number[8];
    int separate = 0;
    int gear;

    fn_801C3284(pBuffer, "", size);
    gear = fn_80078AE0(id);
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

void fn_8007947C(int type, unsigned short value, char *pBuffer, unsigned short size)
{
    switch (type) {
    case 0:
        *pBuffer = 0;
        break;
    case 1:
        fn_80077E38(pBuffer, size, value);
        break;
    case 2:
        fn_80079248(pBuffer, size, value);
        break;
    case 4:
        fn_80077EF8(pBuffer, size, value);
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

void fn_80079538(Object_800785C0 *pRecord, char *pBuffer, unsigned short size)
{
    char value[200];
    char text[600] = "";
    char *p = text;
    int left = sizeof(text);
    signed char i;

    if (fn_8007984C(pRecord)) {
        Info_8007984C *pInfo = &pRecord->mUnknown20C;

        for (i = 0; i <= 2; i++) {
            fn_8007947C(pInfo->mUnknown1C, pInfo->mUnknown20[i], value, 200);
            fn_801C2D88(p, left, "%s - %s\n", lbl_802D6418[i], value);
            p += fn_801C3180(p);
            left -= fn_801C3180(p);
        }
    } else {
        for (i = 0; i <= 1 && pRecord->mUnknown1F4[i].mId != 0; i++) {
            fn_8007947C(pRecord->mUnknown1F4[i].mId, pRecord->mUnknown1F4[i].mUnknown4, value, 200);
            fn_801C2D88(p, left, "%s\n", value);
            p += fn_801C3180(p);
            left -= fn_801C3180(p);
        }
    }
    fn_801C3284(pBuffer, text, size);
}

int fn_800796B8(int side, Object_800785C0 *pRecord, int index, int *pResult)
{
    int type = pRecord->mUnknown1C4[index].mType;
    int result = 0;

    if (lbl_80291574[type].mKind != 4) {
        int (*pTest)(int, int, Object_800785C0 *, int) = lbl_802D6400[lbl_80291574[type].mKind].mpRecordTest;

        if (lbl_80291574[type].mFlag) {
            side = !side;
        }
        *pResult = pTest(lbl_80291574[type].mTag, side, pRecord, index);
        result = 1;
    }
    return result;
}

int fn_80079758(int side, Info_8007984C *pInfo)
{
    int type = pInfo->mUnknown0;
    int testSide = side;
    int result = 7;

    if (lbl_80291574[type].mKind != 4) {
        int (*pTest)(int, int, Info_8007984C *) = lbl_802D6400[lbl_80291574[type].mKind].mpInfoTest;

        if (lbl_80291574[type].mFlag) {
            testSide = !side;
        }
        result = pTest(lbl_80291574[type].mTag, testSide, pInfo);
    } else if (type == 3) {
        result = fn_800777B8(side, pInfo);
    }
    return result;
}

int fn_800797F4(Object_800785C0 *pRecord, int type, int *pValue)
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

int fn_8007984C(Object_800785C0 *pRecord)
{
    return pRecord->mUnknown20C.mUnknown0 != 0;
}

int fn_80079864(Object_800785C0 *pRecord, int id)
{
    int i;

    for (i = 0; i <= 1; i++) {
        if (pRecord->mUnknown1F4[i].mId == id) {
            return 1;
        }
    }
    return 0;
}

void fn_80079898(int id, int a, int b)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    Class_8018FD64 cursor;

    cursor.fn_8018FDEC(0x47505443, 0x4D475443, 0, 0, handle);
    cursor.fn_8018FF54(0x4D475443, id, 0, 0);
    cursor.fn_80190008(0x31535443, a);
    cursor.fn_80190008(0x32535443, b);
}

void fn_80079974(int id, short *pA, short *pB)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    Class_8018FD64 cursor;

    cursor.fn_8018FDEC(0x47505443, 0x4D475443, 0, 0, handle);
    cursor.fn_8018FF54(0x4D475443, id, 0, 0);
    *pA = cursor.fn_8018FF78(0x31535443);
    *pB = cursor.fn_8018FF78(0x32535443);
}

void fn_80079A50(int *pValues, int count)
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

void fn_80079B2C(int *pValues, int count)
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
