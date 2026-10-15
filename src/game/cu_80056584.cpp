#include "game/Class_80148A58.h"
#include "game/Object_8008044C.h"
#include "game/Object_8007A334.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80181330.h"
#include "game/cu_8017DD68.h"
#include "game/Object_800785C0.h"
#include "game/fn_801FCE10.h"
#include "game/fn_801D2B7C.h"

#include "game/fn_80218FC4.h"
#include "game/fn_801C1F94.h"
#include <string.h>

/* Filled by fn_80152940 for one index; mpObject points to an object whose
   halfword at 0xB5C is passed to fn_80180EF8. */
struct Object_80056584 {
    char mUnknown0[0xB5C];
    unsigned short mUnknownB5C;
};

struct Info_80152940 {
    Info_80152940() : mpObject(0), mUnknown4(0), mUnknown12(0), mUnknown16(0), mUnknown20(0xFF) {}

    Object_80056584 *mpObject;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
};

struct Pair_803EA58C {
    int mUnknown0;
    int mUnknown4;
};

/* Object returned by fn_80168708; its first word is a handle. */
struct Handle_80168708 {
    int mUnknown0;
};

/* Block filled by fn_8006719C (0xCA8 bytes). */
struct Info_8006719C {
    int mUnknown0;
    char mUnknown4[0xCA4];
};

/* Block filled by fn_80067338 (0x20C bytes); a name string starts at 0x1F3. */
struct Record_80067338 {
    int mUnknown0;
    int mUnknown4;
    char mUnknown8[0x1E8];
    char mUnknown1F0[3];
    char mUnknown1F3[0x19];
};

/* Block filled by fn_800670B4 (0xCE4 bytes). */
struct Object_800670B4 {
    int mUnknown0;
    char mUnknown4[0xCE0];
};

/* One 0xEC0-byte slot of the arrays at State_803EA590 +0x14. */
struct Slot_803EA590 {
    Handle_80168708 *mpHandle;
    int mUnknown4;
    Info_8006719C mUnknown8;
    Record_80067338 mUnknownCB0;
    signed char mUnknownEBC;
};

/* Object returned by fn_80168EBC; only the byte at 0x30 and the word at
   0x40 are read here. */
struct Team_80168EBC {
    char mUnknown0[0x30];
    unsigned char mUnknown30;
    char mUnknown31[0xF];
    int mUnknown40;
};

/* State reached through the .sdata pointer 0x803EA590. */
struct State_803EA590 {
    unsigned char mUnknown0[2];
    unsigned char mUnknown2[2];
    int mUnknown4[2];
    Team_80168EBC *mpTeam[2];
    Slot_803EA590 *mpSlots[2];
    unsigned char mUnknown1C[2];
    unsigned char mUnknown1E;
};

/* One 12-byte entry of the arrays at State_803EA58C +0x30. */
struct Entry_803EA58C {
    int mUnknown0;
    int mUnknown4;
    char *mpText;
};

/* Message arguments sent by fn_80056ED8 (0x80000011). */
struct Args_80056ED8 {
    int mSide;
    int mRow;
    int mColumn;
    Entry_803EA58C *mpEntry;
    int mLocked;
};

/* State reached through the .sdata pointer 0x803EA58C. */
struct State_803EA58C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8[2];
    int mUnknown10[2];
    Pair_803EA58C mUnknown18[2];
    int mUnknown28;
    int mUnknown2C;
    Entry_803EA58C *mpEntries[2];
    char **mpTexts[2];
    unsigned char mUnknown40[2];
    unsigned char mUnknown42[2];
    unsigned char mUnknown44[2];
    unsigned char mUnknown46[2];
    unsigned char mUnknown48[2];
    unsigned char mUnknown4A[2];
    unsigned char mUnknown4C[2];
    unsigned char mUnknown4E;
    unsigned char mUnknown4F;
    unsigned char mUnknown50;
};

/* Table reached through the .sdata pointer 0x803EA594. */
struct Table_803EA594 {
    signed char *mpUnknown0[2][4];
    signed char *mpUnknown20[2][4];
    unsigned char mUnknown40[2][4];
    unsigned char mUnknown48[2][4];
    unsigned char mUnknown50[2][4];
    unsigned char mUnknown58[2][4];
};

extern "C" {
extern char lbl_8031BDD4[];
extern void *lbl_803EB688;

void fn_80152940(char *pObject, int index, Info_80152940 *pInfo);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
void fn_80188248(Object_80056584 *pObject, char *pOut, int b);
int fn_80180EF8(int id);
int fn_8017E570(int key, unsigned char *pRed, unsigned char *pGreen, unsigned char *pBlue);
void fn_80187D10(void);
void fn_800C1CA0(void);
void fn_800652A8(void);
int fn_801486A0(void);
int fn_80178308(void);
int fn_80179138(void);
int fn_80168EA8(int team);
Team_80168EBC *fn_80168EBC(int team);
void fn_80168744(int team, unsigned int a, unsigned int b, unsigned char c);
void fn_80167EA0(int team);
Handle_80168708 *fn_80168708(int team);
void fn_801688E0(unsigned int flags);
void fn_801688F4(unsigned int flags);
void fn_8006719C(int tag, int handle, int index, Team_80168EBC *pOwner, Info_8006719C *pInfo);
int fn_80067338(int tag, int handle, int index, Record_80067338 *pRecord);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
void fn_80167094(int tag, Info_8006719C *pInfo, Record_80067338 *pRecord, int a, int b, signed char c, int team, int index);
void fn_80167128(int tag, Record_80067338 *pRecord, int a, int b, int team, int index);
void fn_80167160(int tag, Record_80067338 *pRecord, int a, int b, int c, int team, int index, int first,
                 unsigned char count, Info_8006719C *pInfo);
void fn_80167794(signed char team, int value, int index);
int fn_801C3180(const char *pString);
void fn_8021D7B8(void *p, int id, int count, void *pArgs);
int fn_80178320(void);
int fn_80177F7C(void);
int fn_80177F70(void);
int fn_800B65A0(int side);
void fn_80177D78(void);
void fn_8009D964(int index, int value);
int fn_8009D990(int index);
int fn_8007CB6C(int index);
void fn_800B4434(void);
void fn_800B3C54(void);
int fn_80188030(int value);
void fn_80168D74(unsigned char team);
int fn_80025708(void);
int fn_801485D4(void);
int fn_80028310(void);
int fn_8006560C(void);
unsigned char fn_8002D060(void *p);
void fn_80179144(int a);
void fn_8017916C(void);
unsigned int fn_802372EC(int stream, int count);
void fn_800B41BC(int a, int b, int c);
int fn_80085A34(int formation, int team);
void fn_800B4184(int a);
int fn_800B65D0(int team);
unsigned char fn_80194F24(void);
void fn_80194F1C(unsigned char enabled);
void fn_80194C5C(int a, int b, int c);
void fn_801678CC(int group);
int fn_800670B4(int tag, int a, int b, Object_800670B4 *pObject);
unsigned short fn_800672BC(int tag, int handle);
void *fn_801D2BB0(int a, int size, int c, int d);
int fn_80186F7C(int index);
int fn_8022F358(int index);
int fn_8022F488(int a);
int fn_801C302C(const char *s1, const char *s2, int n);
int fn_800BA6F8(void);
char *fn_801C3284(char *pDest, const char *pSource, int size);
void fn_800588F8(int a, int b);
int fn_80065650(void);
int fn_801C6458(int a, int b);
int fn_800B6644(int index);
unsigned int fn_8017F584(void);
void fn_8002B5D0(int a, int b);
void fn_80047874(unsigned char enable);
void fn_8004730C(unsigned char enabled);
void fn_800282DC(void);
unsigned char fn_8006569C(void);
void fn_80067DB8(int type, void *pPos, int a, int b, int c);
int fn_8006562C(void);
int fn_800AD9B4(void);
void fn_80025C88(int flag);
void fn_80148154(void);
void fn_801483C8(void);
void fn_80067D4C(int type, void *pPos);
void fn_80072C90(unsigned int delay, int wait);
void fn_8009D8CC(int index);
void fn_800AE988(void);
void fn_800656A4(unsigned char value);
void fn_800655B8(void);
int fn_80025B18(int *pResults, char (*pText)[64]);
void fn_80178B1C(int a);
void fn_80065638(int value);
void fn_8003B8BC(void);
void fn_8003B234(int group, int kind, int *pList);
void fn_8003B0F8(int group, int kind, int slot, int code, char *pText, int length);
void fn_8003B6F0(int reset);
void fn_8003B1F4(int group);
void fn_800656AC(unsigned char value);
void fn_80065664(unsigned char value);
int fn_8002C9A8(void *p, int msg, int value);
int fn_8002D228(void *p);
int fn_80156704(void);
int fn_800551D8(unsigned char a);
void fn_800551E0(unsigned char a, int b, char *pText, int length);
int fn_80178D70(int team);
void fn_80055230(unsigned char a, int b, int c, int *pList0, int *pList1, char *pText, int length);
int fn_80186010(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_80063910(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_80056444(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005A2B8(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005A630(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_80059A24(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005B2BC(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005BCA8(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005B4B0(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005C0C0(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005C338(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005C6EC(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005C994(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005CC50(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005D1E4(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005D2D0(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005BFDC(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_800C8744(int team);
void fn_80187CAC(int id, char *pText, int size);
int fn_8007F828(int a);
int fn_8017881C(int team);
int fn_80188044(unsigned int index);
int fn_8017F60C(void);
extern void *lbl_803EA368;

State_803EA58C *lbl_803EA58C = 0;
State_803EA590 *lbl_803EA590 = 0;
Table_803EA594 *lbl_803EA594 = 0;
static unsigned char lbl_803EA598 = 0;
static unsigned char lbl_803EA599 = 100;
static unsigned short lbl_803EA59A = 15;
static unsigned char lbl_803EA59C = 0;
static unsigned char lbl_803EA59D = 0;
static unsigned char lbl_803EA59E = 0;
static unsigned char lbl_803EA59F = 0;
static int lbl_803EA5A0[2] = {0,0};
static unsigned char lbl_803EA5A8 = 0;
static int lbl_803EA5AC = 4;
static int lbl_803EA5B0 = 3;
static unsigned char lbl_803EA5B4 = 0;
static unsigned char lbl_803EA5B5 = 0;

void fn_80056584(int index, char *pOut, int b, char *pText0, int size0, char *pText1, int size1,
                 char *pText2, int size2, int *pColor, int unused, char *pText, int length, int *pId)
{
    Info_80152940 info;

    fn_80152940(lbl_8031BDD4, index, &info);
    fn_801C2D88(pText0, size0, "%d", info.mUnknown4);
    fn_801C2D88(pText1, size1, "%d", info.mUnknown12);
    fn_801C2D88(pText2, size2, "%d", info.mUnknown16);
    Object_80056584 *pObject = info.mpObject;
    if (pObject) {
        fn_80188248(pObject, pOut, b);
        fn_80148A58()->vfn_18(1, index, pText, length);
        *pId = fn_80180EF8(pObject->mUnknownB5C);
    } else {
        *pOut = 0;
        *pId = 0;
    }
    unsigned char red = 0, green = 0, blue = 0;
    fn_8017E570(info.mUnknown20, &red, &green, &blue);
    pColor[0] = red;
    pColor[1] = green;
    pColor[2] = blue;
}

int fn_800566F0(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80056584(pArgs[0].i, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength, pArgs[3].pParams->mpText,
                    pArgs[3].pParams->mLength, pArgs[5].pParams->mpText, pArgs[5].pParams->mLength,
                    pArgs[7].pParams->mpText, pArgs[7].pParams->mLength,
                    (int *)(pArgs[1].i + (*pArgs[1].pi + 1) * 4), pArgs[1].pi[1], pArgs[8].pParams->mpText,
                    pArgs[8].pParams->mLength, pResult);
        fn_801C2EF0(pArgs[4].pParams->mpText, "Street Balls", pArgs[4].pParams->mLength);
        fn_801C2EF0(pArgs[6].pParams->mpText, "Normal Balls", pArgs[6].pParams->mLength);
        break;
    case 0x80000002:
        *pResult = 4;
        break;
    case 0x80000003:
        fn_80187D10();
        if (pArgs[0].i == 1) {
            fn_800C1CA0();
        }
        fn_800652A8();
        break;
    case 0x80000004:
        break;
    default:
        return 0;
    }
    return 1;
}

int fn_80056848(void)
{
    switch (fn_801486A0()) {
    case 3:
    case 4:
        return 0;
    }
    return 1;
}

int fn_80056880(int team)
{
    int value;
    int count = fn_80179138();

    switch (lbl_803EA58C->mUnknown46[team]) {
    case 0:
        value = 0;
        break;
    case 1:
        if (fn_80178308() == (unsigned char)team) {
            value = 1;
        } else {
            value = 4;
        }
        break;
    case 2:
        if (fn_80178308() == (unsigned char)team) {
            value = 2;
        } else {
            value = 6;
        }
        break;
    case 3:
        if (fn_80178308() == (unsigned char)team) {
            value = 3;
        } else {
            value = 5;
        }
        break;
    default:
        if (fn_80178308() == (unsigned char)team && (count == 1 || count == 2)) {
            if (count == 1) {
                value = 7;
            } else {
                value = 8;
            }
        } else {
            value = -1;
        }
        break;
    }
    return value;
}

void fn_8005697C(int team, int *pA, int *pB, int *pC, int *pD, int *pE)
{
    *pA = lbl_803EA58C->mUnknown8[team];
    *pB = lbl_803EA58C->mUnknown44[team];
    *pC = fn_80056880(team);
    *pD = lbl_803EA58C->mUnknown10[team];
    pE[0] = lbl_803EA58C->mUnknown18[team].mUnknown0;
    pE[1] = lbl_803EA58C->mUnknown18[team].mUnknown4;
}

int fn_80056A10(int side, int a, int b, int c)
{
    int result = 0;
    int team = 1;
    unsigned char limit;

    if (side == 0) {
        team = 0;
    }
    if (lbl_803EA58C->mUnknown46[team] <= 3) {
        if (fn_80178308() == team) {
            limit = lbl_803EA594->mUnknown40[team][lbl_803EA58C->mUnknown46[team]];
        } else {
            limit = lbl_803EA594->mUnknown48[team][lbl_803EA58C->mUnknown46[team]];
        }
        int per = lbl_803EA58C->mUnknown4E;
        c %= per;
        int value = (a * 2 + b) * per + c;
        if (value < limit) {
            result = 1;
            switch (side) {
            case 1:
                lbl_803EA58C->mUnknown40[1] = value;
                lbl_803EA58C->mUnknown48[1] = lbl_803EA58C->mUnknown46[1];
                lbl_803EA58C->mUnknown4C[1] = lbl_803EA58C->mUnknown4A[1];
                break;
            case 0:
                lbl_803EA58C->mUnknown40[0] = value;
                lbl_803EA58C->mUnknown48[0] = lbl_803EA58C->mUnknown46[0];
                lbl_803EA58C->mUnknown4C[0] = lbl_803EA58C->mUnknown4A[0];
                break;
            }
        }
    }
    return result;
}


void fn_80056B2C(int team, unsigned int a, int b)
{
    unsigned char limit;

    if (fn_80178308() == team) {
        limit = lbl_803EA594->mUnknown40[team][lbl_803EA58C->mUnknown46[team]];
    } else {
        limit = lbl_803EA594->mUnknown48[team][lbl_803EA58C->mUnknown46[team]];
    }
    unsigned int index = a + b;
    if (index < limit) {
        lbl_803EA590->mUnknown4[team] = fn_80168EA8(team);
        lbl_803EA590->mpTeam[team] = fn_80168EBC(team);
        if (fn_80178308() == team) {
            lbl_803EA590->mpSlots[team][b].mUnknownEBC =
                lbl_803EA594->mpUnknown0[team][lbl_803EA58C->mUnknown46[team]][index];
        } else {
            lbl_803EA590->mpSlots[team][b].mUnknownEBC =
                lbl_803EA594->mpUnknown20[team][lbl_803EA58C->mUnknown46[team]][index];
        }
        fn_80168744(team, 0, lbl_803EA58C->mUnknown46[team], lbl_803EA590->mpSlots[team][b].mUnknownEBC);
        fn_80167EA0(team);
        lbl_803EA590->mpSlots[team][b].mpHandle = fn_80168708(team);
        fn_801688E0(5);
        fn_8006719C(lbl_803EA590->mUnknown4[team], lbl_803EA590->mpSlots[team][b].mpHandle->mUnknown0,
                    lbl_803EA58C->mUnknown46[team], lbl_803EA590->mpTeam[team],
                    &lbl_803EA590->mpSlots[team][b].mUnknown8);
        fn_801688F4(5);
        fn_801688E0(2);
        lbl_803EA590->mpSlots[team][b].mUnknown4 =
            fn_80067338(lbl_803EA590->mUnknown4[team], lbl_803EA590->mpSlots[team][b].mUnknown8.mUnknown0,
                        lbl_803EA590->mpSlots[team][b].mUnknownEBC, &lbl_803EA590->mpSlots[team][b].mUnknownCB0);
        fn_801688F4(2);
        fn_801C2E18(lbl_803EA58C->mpTexts[team][b], "%s",
                    lbl_803EA590->mpSlots[team][b].mUnknownCB0.mUnknown1F3);
    } else {
        lbl_803EA590->mpSlots[team][b].mUnknownEBC = -1;
        fn_801C2E18(lbl_803EA58C->mpTexts[team][b], "%s", "Locked");
    }
}

void fn_80056DE0(int team, int index)
{
    if (lbl_803EA590->mpSlots[team][index].mUnknownEBC != -1) {
        fn_80167094(lbl_803EA590->mUnknown4[team], &lbl_803EA590->mpSlots[team][index].mUnknown8,
                    &lbl_803EA590->mpSlots[team][index].mUnknownCB0,
                    lbl_803EA590->mpSlots[team][index].mUnknownCB0.mUnknown4,
                    lbl_803EA590->mpSlots[team][index].mUnknown4,
                    lbl_803EA590->mpSlots[team][index].mUnknownEBC, team, index);
        fn_80167128(lbl_803EA590->mUnknown4[team], &lbl_803EA590->mpSlots[team][index].mUnknownCB0,
                    lbl_803EA590->mpSlots[team][index].mUnknownCB0.mUnknown4,
                    lbl_803EA590->mpSlots[team][index].mUnknownCB0.mUnknown0, team, index);
        fn_80167160(lbl_803EA590->mUnknown4[team], &lbl_803EA590->mpSlots[team][index].mUnknownCB0,
                    lbl_803EA590->mpSlots[team][index].mUnknownCB0.mUnknown4,
                    lbl_803EA590->mpSlots[team][index].mUnknown4,
                    lbl_803EA590->mpSlots[team][index].mUnknownCB0.mUnknown0, team, index, 0, 11,
                    &lbl_803EA590->mpSlots[team][index].mUnknown8);
    }
}

void fn_80056ED8(int team, int a, int b)
{
    Args_80056ED8 args;
    unsigned char limit;

    fn_80167794(team, lbl_803EA58C->mUnknown4A[team], b);
    fn_80056B2C(team, a, b);
    fn_80056DE0(team, b);
    args.mSide = team != 0;
    args.mRow = b % (lbl_803EA58C->mUnknown4E * 2) / lbl_803EA58C->mUnknown4E;
    args.mColumn = b % (lbl_803EA58C->mUnknown4E * 2) % lbl_803EA58C->mUnknown4E;
    args.mpEntry = &lbl_803EA58C->mpEntries[team][b];
    args.mpEntry->mpText = lbl_803EA58C->mpTexts[team][b];
    args.mpEntry->mUnknown4 = fn_801C3180(lbl_803EA58C->mpTexts[team][b]);
    if (fn_80178308() == team) {
        limit = lbl_803EA594->mUnknown40[team][lbl_803EA58C->mUnknown46[team]];
    } else {
        limit = lbl_803EA594->mUnknown48[team][lbl_803EA58C->mUnknown46[team]];
    }
    args.mLocked = a + b >= limit;
    fn_8021D7B8(lbl_803EB688, 0x80000011, 5, &args);
}

int fn_80057044(void)
{
    int value = -1;

    if (fn_801486A0() == 3) {
        value = fn_80178320();
        lbl_803EA58C->mUnknown4F = value;
    } else if (lbl_803EA58C->mUnknown4F != 2) {
        value = lbl_803EA58C->mUnknown4F;
    }
    return value;
}


void fn_800570A4(int *pSide, int *pTable, int *pMode, int *pFlag, int *pType, int *pState, int *pIsMode6)
{
    if (fn_80177F7C() == 6 && (fn_800B65A0(0) != 0xFF || fn_800B65A0(1) != 0xFF)) {
        fn_80177D78();
    }
    if (!lbl_803EA598) {
        fn_8009D964(2, 0);
        lbl_803EA598 = 1;
    }
    if (lbl_803EA58C->mUnknown50 == 0) {
        *pFlag = 0;
        lbl_803EA58C->mUnknown2C = fn_8007CB6C(1);
        lbl_803EA58C->mUnknown28 = fn_8007CB6C(0);
        lbl_803EA58C->mUnknown40[1] = 0;
        lbl_803EA58C->mUnknown40[0] = 0;
        lbl_803EA58C->mUnknown42[1] = 0;
        lbl_803EA58C->mUnknown42[0] = 0;
        fn_800B4434();
        int id = fn_800B65A0(1);
        if (id == 0xFF) {
            lbl_803EA58C->mUnknown4 = -1;
        } else {
            lbl_803EA58C->mUnknown4 = fn_80188030(id);
        }
        id = fn_800B65A0(0);
        if (id == 0xFF) {
            lbl_803EA58C->mUnknown0 = -1;
        } else {
            lbl_803EA58C->mUnknown0 = fn_80188030(id);
        }
        lbl_803EA590->mUnknown0[0] = 0;
        lbl_803EA590->mUnknown0[1] = 0;
        lbl_803EA590->mUnknown2[0] = 0;
        lbl_803EA590->mUnknown2[1] = 0;
        lbl_803EA590->mUnknown1C[0] = 0;
        lbl_803EA590->mUnknown1C[1] = 0;
        lbl_803EA58C->mUnknown46[0] = 5;
        lbl_803EA58C->mUnknown46[1] = 5;
        lbl_803EA58C->mUnknown48[0] = 5;
        lbl_803EA58C->mUnknown48[1] = 5;
        lbl_803EA58C->mUnknown4A[0] = 0;
        lbl_803EA58C->mUnknown4A[1] = 0;
        lbl_803EA58C->mUnknown4C[0] = 0;
        lbl_803EA58C->mUnknown4C[1] = 0;
        if (fn_80168EBC(0)->mUnknown30) {
            fn_80168D74(0);
        }
        if (fn_80168EBC(1)->mUnknown30) {
            fn_80168D74(1);
        }
    } else {
        *pFlag = 1;
        lbl_803EA58C->mUnknown50 = 0;
    }
    *pSide = fn_80178308() != 0;
    for (unsigned char i = 0; i <= 7; i++) {
        pTable[i] = -1;
    }
    if (lbl_803EA58C->mUnknown0 != -1) {
        pTable[lbl_803EA58C->mUnknown0] = 0;
    }
    if (lbl_803EA58C->mUnknown4 != -1) {
        pTable[lbl_803EA58C->mUnknown4] = 1;
    }
    fn_800B3C54();
    *pMode = fn_8009D990(3);
    *pType = -1;
    if (fn_80025708() && fn_800B65A0(fn_80178308()) != 0xFF) {
        if (fn_800785C0()->mUnknown1B0 != 0) {
            switch (fn_800785C0()->mUnknown1B0) {
            case 1:
                *pType = 2;
                break;
            case 2:
                *pType = 1;
                break;
            case 3:
                *pType = 3;
                break;
            }
        }
    } else if (fn_801485D4() && fn_800B65A0(fn_80178308()) != 0xFF) {
        switch (fn_80148A58()->vfn_08(0)) {
        case 0:
            break;
        case 1:
            *pType = 1;
            break;
        case 2:
            *pType = 2;
            break;
        }
    }
    *pState = fn_80057044();
    *pIsMode6 = fn_80177F70() == 6;
}


void fn_8005740C(int value1, int *pPair1, int word1, int test1, int value0, int *pPair0, int word0, int test0)
{
    int count = fn_80179138();

    if (fn_80028310() == 0) {
        if (fn_8006560C() == 0 && fn_8002D060(lbl_803EA368) == 0) {
            if (count == 0 && fn_80177F70() == 6) {
                count = 1;
                fn_80179144(1);
            }
            lbl_803EA58C->mUnknown50 = 0;
            if (count == 1 || count == 2) {
                fn_8017916C();
            }
            if (lbl_803EA58C->mUnknown4A[0] != lbl_803EA58C->mUnknown4C[0]) {
                fn_80168D74(0);
            }
            if (lbl_803EA58C->mUnknown4A[1] != lbl_803EA58C->mUnknown4C[1]) {
                fn_80168D74(1);
            }
            if (lbl_803EA58C->mUnknown42[0]) {
                if (fn_80178308() == 0) {
                    fn_80168744(0, 0, lbl_803EA58C->mUnknown48[0],
                                lbl_803EA594->mpUnknown0[0][lbl_803EA58C->mUnknown48[0]][lbl_803EA58C->mUnknown40[0]]);
                } else {
                    fn_80168744(0, 0, lbl_803EA58C->mUnknown48[0],
                                lbl_803EA594->mpUnknown20[0][lbl_803EA58C->mUnknown48[0]][lbl_803EA58C->mUnknown40[0]]);
                }
                fn_80167EA0(0);
                fn_800B41BC(0, 0, 0);
            } else {
                if (fn_80178308() == 0) {
                    fn_80168744(0, 0, 0,
                                lbl_803EA594->mpUnknown0[0][0][(unsigned char)fn_802372EC(0, lbl_803EA594->mUnknown40[0][0])]);
                } else {
                    fn_80168744(0, 0, 0,
                                lbl_803EA594->mpUnknown20[0][0][(unsigned char)fn_802372EC(0, lbl_803EA594->mUnknown48[0][0])]);
                }
                fn_80167EA0(0);
                fn_800B41BC(0, 0, 0);
            }
            fn_80085A34(fn_80168EBC(0)->mUnknown40, 0);
            if (lbl_803EA58C->mUnknown42[1]) {
                if (fn_80178308() == 1) {
                    fn_80168744(1, 0, lbl_803EA58C->mUnknown48[1],
                                lbl_803EA594->mpUnknown0[1][lbl_803EA58C->mUnknown48[1]][lbl_803EA58C->mUnknown40[1]]);
                } else {
                    fn_80168744(1, 0, lbl_803EA58C->mUnknown48[1],
                                lbl_803EA594->mpUnknown20[1][lbl_803EA58C->mUnknown48[1]][lbl_803EA58C->mUnknown40[1]]);
                }
                fn_80167EA0(1);
                fn_800B41BC(1, 0, 0);
            } else {
                if (fn_80178308() == 1) {
                    fn_80168744(1, 0, 0,
                                lbl_803EA594->mpUnknown0[1][0][(unsigned char)fn_802372EC(0, lbl_803EA594->mUnknown40[1][0])]);
                } else {
                    fn_80168744(1, 0, 0,
                                lbl_803EA594->mpUnknown20[1][0][(unsigned char)fn_802372EC(0, lbl_803EA594->mUnknown48[1][0])]);
                }
                fn_80167EA0(1);
                fn_800B41BC(1, 0, 0);
            }
            fn_80085A34(fn_80168EBC(1)->mUnknown40, 1);
        } else {
            lbl_803EA58C->mUnknown50 = 1;
            lbl_803EA58C->mUnknown8[0] = word0;
            lbl_803EA58C->mUnknown8[1] = word1;
            lbl_803EA58C->mUnknown44[0] = test0 == 1;
            lbl_803EA58C->mUnknown44[1] = test1 == 1;
            lbl_803EA58C->mUnknown10[0] = value0;
            lbl_803EA58C->mUnknown10[1] = value1;
            lbl_803EA58C->mUnknown18[0].mUnknown0 = pPair0[0];
            lbl_803EA58C->mUnknown18[0].mUnknown4 = pPair0[1];
            lbl_803EA58C->mUnknown18[1].mUnknown0 = pPair1[0];
            lbl_803EA58C->mUnknown18[1].mUnknown4 = pPair1[1];
        }
        lbl_803EA590->mUnknown1C[0] = 0;
        lbl_803EA590->mUnknown1C[1] = 0;
        fn_800B4184(0);
    }
}


int fn_800577DC(int side, int a, int *pPos)
{
    int ok = fn_80056A10(side, a, pPos[0], pPos[1]);

    if (ok) {
        int pad;
        if (side == 0) {
            lbl_803EA58C->mUnknown42[0] = 1;
            pad = fn_800B65D0(0);
        } else {
            lbl_803EA58C->mUnknown42[1] = 1;
            pad = fn_800B65D0(1);
        }
        if (pad != 0xFF) {
            unsigned char enabled = fn_80194F24();
            fn_80194F1C(1);
            fn_80194C5C(pad, lbl_803EA599, lbl_803EA59A);
            fn_80194F1C(enabled);
        }
    }
    return ok;
}

void fn_80057880(int team)
{
    lbl_803EA58C->mUnknown4A[team] = !lbl_803EA58C->mUnknown4A[team];
    fn_80168D74(team);
}

void fn_800578C0(int side, int a)
{
    int team = 1;

    if (side == 0) {
        team = 0;
    }
    if (lbl_803EA590->mUnknown1C[team]) {
        lbl_803EA590->mUnknown0[team] = (a + a) * lbl_803EA58C->mUnknown4E;
        lbl_803EA590->mUnknown2[team] = 0;
        if (fn_80178308() == team) {
            if (lbl_803EA590->mUnknown0[team] + lbl_803EA58C->mUnknown4E * 2 >
                lbl_803EA594->mUnknown40[team][lbl_803EA58C->mUnknown46[team]]) {
                fn_801678CC(team);
            }
        } else {
            if (lbl_803EA590->mUnknown0[team] + lbl_803EA58C->mUnknown4E * 2 >
                lbl_803EA594->mUnknown48[team][lbl_803EA58C->mUnknown46[team]]) {
                fn_801678CC(team);
            }
        }
    }
}


void fn_800579C4(int side, int mode, int *pPages)
{
    int team = 1;

    if (side == 0) {
        team = 0;
    }
    if (team != lbl_803EA58C->mUnknown4F) {
        lbl_803EA590->mUnknown1C[team] = 1;
    }
    if (side == fn_80178308()) {
        switch (mode) {
        case 0:
            lbl_803EA58C->mUnknown46[team] = mode;
            if (team == fn_80178308()) {
                *pPages = (lbl_803EA594->mUnknown40[team][0] + lbl_803EA58C->mUnknown4E * 2 - 1) / (lbl_803EA58C->mUnknown4E * 2);
            } else {
                *pPages = (lbl_803EA594->mUnknown48[team][0] + lbl_803EA58C->mUnknown4E * 2 - 1) / (lbl_803EA58C->mUnknown4E * 2);
            }
            break;
        case 1:
            lbl_803EA58C->mUnknown46[team] = mode;
            *pPages = (lbl_803EA594->mUnknown40[team][1] + lbl_803EA58C->mUnknown4E * 2 - 1) / (lbl_803EA58C->mUnknown4E * 2);
            break;
        case 2:
            lbl_803EA58C->mUnknown46[team] = mode;
            *pPages = (lbl_803EA594->mUnknown40[team][2] + lbl_803EA58C->mUnknown4E * 2 - 1) / (lbl_803EA58C->mUnknown4E * 2);
            break;
        case 3:
            lbl_803EA58C->mUnknown46[team] = mode;
            *pPages = (lbl_803EA594->mUnknown40[team][3] + lbl_803EA58C->mUnknown4E * 2 - 1) / (lbl_803EA58C->mUnknown4E * 2);
            break;
        case -1:
        default:
            lbl_803EA590->mUnknown1C[team] = 0;
            lbl_803EA58C->mUnknown46[team] = 5;
            *pPages = 1;
            break;
        }
    } else {
        switch (mode) {
        case 0:
            lbl_803EA58C->mUnknown46[team] = mode;
            if (team == fn_80178308()) {
                *pPages = (lbl_803EA594->mUnknown40[team][0] + lbl_803EA58C->mUnknown4E * 2 - 1) / (lbl_803EA58C->mUnknown4E * 2);
            } else {
                *pPages = (lbl_803EA594->mUnknown48[team][0] + lbl_803EA58C->mUnknown4E * 2 - 1) / (lbl_803EA58C->mUnknown4E * 2);
            }
            break;
        case 4:
            lbl_803EA58C->mUnknown46[team] = 1;
            *pPages = (lbl_803EA594->mUnknown48[team][1] + lbl_803EA58C->mUnknown4E * 2 - 1) / (lbl_803EA58C->mUnknown4E * 2);
            break;
        case 5:
            lbl_803EA58C->mUnknown46[team] = 3;
            *pPages = (lbl_803EA594->mUnknown48[team][3] + lbl_803EA58C->mUnknown4E * 2 - 1) / (lbl_803EA58C->mUnknown4E * 2);
            break;
        case 6:
            lbl_803EA58C->mUnknown46[team] = 2;
            *pPages = (lbl_803EA594->mUnknown48[team][2] + lbl_803EA58C->mUnknown4E * 2 - 1) / (lbl_803EA58C->mUnknown4E * 2);
            break;
        case -1:
        default:
            lbl_803EA590->mUnknown1C[team] = 0;
            lbl_803EA58C->mUnknown46[team] = 5;
            *pPages = 1;
            break;
        }
    }
    if (lbl_803EA590->mUnknown1C[team]) {
        fn_801678CC(team);
        lbl_803EA590->mUnknown0[team] = 0;
        lbl_803EA590->mUnknown2[team] = 0;
    }
}


void fn_80057C58(unsigned char team, int index, int flag)
{
    Object_800670B4 object;
    QueryCursor cursor;
    char text[3];
    Record_80067338 record;
    signed char number;
    int handle;
    unsigned char i;
    signed char *pList;
    unsigned char *pFirst;
    unsigned char *pCount;
    int table;
    int kind = flag ? 1 : 11;
    int tag = flag ? 0x31544250 : 0x31444250;

    fn_800670B4(tag, kind, 0, &object);
    fn_801FCE10(0, "use \x8c select 'TSBP' into \x85 from 'TSBP' where '_dro' = \x85 and 'MFBP' = \x85\n", tag,
                &handle, index + 1, object.mUnknown0);
    unsigned short count = fn_800672BC(tag, handle);
    if (flag) {
        pList = (signed char *)fn_801D2BB0(0x40, count, 0, 0);
        table = 0x504F5355;
        lbl_803EA594->mpUnknown0[team][index] = pList;
        pFirst = &lbl_803EA594->mUnknown40[team][index];
        pCount = &lbl_803EA594->mUnknown50[team][index];
    } else {
        pList = (signed char *)fn_801D2BB0(0x40, count, 0, 0);
        table = 0x50445355;
        lbl_803EA594->mpUnknown20[team][index] = pList;
        pFirst = &lbl_803EA594->mUnknown48[team][index];
        pCount = &lbl_803EA594->mUnknown58[team][index];
    }
    if (fn_800B65A0(team) != 0xFF && fn_80056848()) {
        int database;
        int id = fn_80186F7C(team);
        if (id != -1) {
            database = fn_8022F488(fn_8022F358(id));
        } else {
            database = 0x454D4147;
        }
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        fn_801FCE10(0, "use \x8c declare \x8a cursor for select * from \x8c where ('XPSU' >= 0) order by 'XPSU' asc\n",
                    database, &cursor, table);
        i = 0;
        while (i < count && fn_801FCE10(0, "fetch from \x8a 'DPSU' into \x80\n", &cursor, &number) == 0) {
            fn_801C2E18(text, "%02d", number);
            for (unsigned int j = 0; j < count; j++) {
                fn_80067338(tag, handle, j, &record);
                if (fn_801C302C(record.mUnknown1F0, text, 2) == 0) {
                    pList[i] = j;
                    i++;
                    break;
                }
            }
        }
        if (cursor.mUnknown0) {
            fn_801FCFA0(&cursor);
        }
    } else {
        for (i = 0; i < count; i++) {
            pList[i] = i;
        }
    }
    *pFirst = i;
    *pCount = count;
    for (; i < count; i++) {
        pList[i] = -1;
    }
}

int fn_80057F20(void)
{
    return -1;
}


void fn_80057F28(void)
{
    unsigned char i;
    unsigned char team;
    unsigned char index;

    switch (fn_801486A0()) {
    case 0:
    case 1:
        return;
    }
    lbl_803EA58C = (State_803EA58C *)fn_801D2BB0(0x40, sizeof(State_803EA58C), 0, 0);
    memset(lbl_803EA58C, 0, sizeof(State_803EA58C));
    if (fn_800BA6F8() == 0 &&
        (fn_8017F60C() != 0 || fn_800B65A0(0) == 0xFF || fn_800B65A0(1) == 0xFF || fn_801486A0() == 3)) {
        lbl_803EA58C->mUnknown4E = 4;
        if (fn_8017F60C()) {
            if (fn_80057F20()) {
                lbl_803EA58C->mUnknown4F = 1;
            } else {
                lbl_803EA58C->mUnknown4F = 0;
            }
        } else if (fn_800B65A0(0) != 0xFF) {
            lbl_803EA58C->mUnknown4F = 1;
        } else {
            lbl_803EA58C->mUnknown4F = 0;
        }
    } else {
        lbl_803EA58C->mUnknown4E = 2;
        lbl_803EA58C->mUnknown4F = 2;
    }
    lbl_803EA58C->mpEntries[0] =
        (Entry_803EA58C *)fn_801D2BB0(0x40, lbl_803EA58C->mUnknown4E * 2 * sizeof(Entry_803EA58C), 0, 0);
    lbl_803EA58C->mpEntries[1] =
        (Entry_803EA58C *)fn_801D2BB0(0x40, lbl_803EA58C->mUnknown4E * 2 * sizeof(Entry_803EA58C), 0, 0);
    lbl_803EA58C->mpTexts[0] = (char **)fn_801D2BB0(0x40, lbl_803EA58C->mUnknown4E * 2 * sizeof(char *), 0, 0);
    for (i = 0; i < lbl_803EA58C->mUnknown4E * 2; i++) {
        lbl_803EA58C->mpTexts[0][i] = (char *)fn_801D2BB0(0x40, 25, 0, 0);
    }
    lbl_803EA58C->mpTexts[1] = (char **)fn_801D2BB0(0x40, lbl_803EA58C->mUnknown4E * 2 * sizeof(char *), 0, 0);
    for (i = 0; i < lbl_803EA58C->mUnknown4E * 2; i++) {
        lbl_803EA58C->mpTexts[1][i] = (char *)fn_801D2BB0(0x40, 25, 0, 0);
    }
    lbl_803EA58C->mUnknown46[0] = 5;
    lbl_803EA58C->mUnknown46[1] = 5;
    lbl_803EA58C->mUnknown48[0] = 5;
    lbl_803EA58C->mUnknown48[1] = 5;
    lbl_803EA58C->mUnknown8[0] = 0;
    lbl_803EA58C->mUnknown8[1] = 0;
    lbl_803EA590 = (State_803EA590 *)fn_801D2BB0(0x40, sizeof(State_803EA590), 0, 0);
    memset(lbl_803EA590, 0, sizeof(State_803EA590));
    lbl_803EA590->mUnknown1E = 0;
    lbl_803EA590->mpSlots[0] =
        (Slot_803EA590 *)fn_801D2BB0(0x40, lbl_803EA58C->mUnknown4E * 2 * sizeof(Slot_803EA590), 0, 0);
    lbl_803EA590->mpSlots[1] =
        (Slot_803EA590 *)fn_801D2BB0(0x40, lbl_803EA58C->mUnknown4E * 2 * sizeof(Slot_803EA590), 0, 0);
    lbl_803EA594 = (Table_803EA594 *)fn_801D2BB0(0x40, sizeof(Table_803EA594), 0, 0);
    for (team = 0; team <= 1; team++) {
        for (index = 0; index <= 3; index++) {
            lbl_803EA594->mpUnknown20[team][index] = 0;
            lbl_803EA594->mpUnknown0[team][index] = 0;
            lbl_803EA594->mUnknown48[team][index] = 0;
            lbl_803EA594->mUnknown40[team][index] = 0;
        }
    }
    for (team = 0; team <= 1; team++) {
        for (index = 0; index <= 3; index++) {
            fn_80057C58(team, index, 1);
            fn_80057C58(team ^ 1, index, 0);
        }
    }
}


void fn_800582D0(void)
{
    unsigned char i;
    unsigned char team;
    unsigned char index;

    lbl_803EA598 = 0;
    if (lbl_803EA58C) {
        for (team = 0; team <= 1; team++) {
            for (index = 0; index <= 3; index++) {
                if (lbl_803EA594->mpUnknown20[team][index]) {
                    fn_801D2BD0(lbl_803EA594->mpUnknown20[team][index]);
                }
                if (lbl_803EA594->mpUnknown0[team][index]) {
                    fn_801D2BD0(lbl_803EA594->mpUnknown0[team][index]);
                }
            }
        }
        fn_801D2BD0(lbl_803EA594);
        lbl_803EA594 = 0;
        fn_801D2BD0(lbl_803EA590->mpSlots[0]);
        fn_801D2BD0(lbl_803EA590->mpSlots[1]);
        fn_801D2BD0(lbl_803EA590);
        lbl_803EA590 = 0;
        fn_801D2BD0(lbl_803EA58C->mpEntries[0]);
        fn_801D2BD0(lbl_803EA58C->mpEntries[1]);
        for (i = 0; i < lbl_803EA58C->mUnknown4E * 2; i++) {
            fn_801D2BD0(lbl_803EA58C->mpTexts[0][i]);
        }
        fn_801D2BD0(lbl_803EA58C->mpTexts[0]);
        for (i = 0; i < lbl_803EA58C->mUnknown4E * 2; i++) {
            fn_801D2BD0(lbl_803EA58C->mpTexts[1][i]);
        }
        fn_801D2BD0(lbl_803EA58C->mpTexts[1]);
        fn_801D2BD0(lbl_803EA58C);
        lbl_803EA58C = 0;
    }
}

int fn_8005845C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000002:
        fn_8005740C(pArgs[0].i, (int *)(pArgs[1].i + (*pArgs[1].pi + 1) * 4), pArgs[2].i, pArgs[3].i, pArgs[4].i,
                    (int *)(pArgs[5].i + (*pArgs[5].pi + 1) * 4), pArgs[6].i, pArgs[7].i);
        break;
    case 0x80000003:
        *pResult = fn_800577DC(pArgs[0].i, pArgs[1].i, (int *)(pArgs[2].i + (*pArgs[2].pi + 1) * 4));
        break;
    case 0x80000004:
        fn_80057880(pArgs[0].i);
        break;
    case 0x80000005:
        fn_800578C0(pArgs[0].i, pArgs[1].i);
        break;
    case 0x80000001:
        fn_800570A4(pArgs[0].pi, (int *)(pArgs[1].i + (*pArgs[1].pi + 1) * 4), pArgs[2].pi, pArgs[3].pi,
                    pArgs[4].pi, pArgs[5].pi, pArgs[6].pi);
        break;
    case 0x80000008:
        *pResult = fn_800BA6F8();
        break;
    case 0x80000006:
        fn_800579C4(pArgs[0].i, pArgs[1].i, pArgs[2].pi);
        break;
    case 0x80000007:
        fn_8005697C(pArgs[0].i, pArgs[1].pi, pArgs[2].pi, pArgs[3].pi, pArgs[4].pi,
                    (int *)(pArgs[5].i + (*pArgs[5].pi + 1) * 4));
        break;
    case 0x80000009:
        *pResult = fn_80057F20();
        break;
    case 0x8000000A:
        fn_800588F8(pArgs[0].i, pArgs[1].i);
        break;
    default:
        return 0;
    }
    return 1;
}

int fn_80058688(void)
{
    int result = 0;

    if (lbl_803EA590) {
        for (unsigned char pass = 0; pass < 1; pass++) {
            unsigned char team = lbl_803EA590->mUnknown1E;
            unsigned char other = !team;
            if (lbl_803EA590->mUnknown1C[team]) {
                if (lbl_803EA590->mUnknown2[team] < lbl_803EA58C->mUnknown4E * 2) {
                    result = 1;
                    fn_80056ED8(team, lbl_803EA590->mUnknown0[team], lbl_803EA590->mUnknown2[team]);
                    lbl_803EA590->mUnknown2[team]++;
                }
            } else if (lbl_803EA590->mUnknown1C[other]) {
                if (lbl_803EA590->mUnknown2[other] < lbl_803EA58C->mUnknown4E * 2) {
                    result = 1;
                    fn_80056ED8(other, lbl_803EA590->mUnknown0[other], lbl_803EA590->mUnknown2[other]);
                    lbl_803EA590->mUnknown2[other]++;
                }
            }
            lbl_803EA590->mUnknown1E = !lbl_803EA590->mUnknown1E;
        }
    }
    return result;
}

void fn_80058798(char *pDest, int size, int number, int flag)
{
    Object_800670B4 object;
    Record_80067338 record;
    char text[3];
    int handle;
    int found = 0;
    int kind = flag ? 1 : 11;
    int tag = flag ? 0x31544250 : 0x31444250;

    fn_800670B4(tag, kind, 0, &object);
    for (unsigned char index = 0; index <= 3; index++) {
        unsigned int j = 0;
        fn_801FCE10(0, "use \x8c select 'TSBP' into \x85 from 'TSBP' where '_dro' = \x85 and 'MFBP' = \x85\n", tag,
                    &handle, index + 1, object.mUnknown0);
        unsigned short count = fn_800672BC(tag, handle);
        fn_801C2E18(text, "%02d", number);
        for (; j < count; j++) {
            fn_80067338(tag, handle, j, &record);
            if (fn_801C302C(record.mUnknown1F0, text, 2) == 0) {
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    if (found) {
        fn_801C3284(pDest, record.mUnknown1F3, size);
    } else {
        fn_801C3284(pDest, "Unknown Play", size);
    }
}

void fn_800588E0(void)
{
    if (lbl_803EA58C) {
        lbl_803EA58C->mUnknown50 = 0;
    }
}

void fn_800588F8(int a, int b)
{
    if (b == 7) {
        fn_80179144(1);
    } else {
        fn_80179144(2);
    }
}

int fn_80058930(int *pA, int *pB)
{
    int mode = fn_801486A0();
    int active = 1;

    if (mode == 15) {
        active = 0;
    }
    if (!active || mode == 5 || mode == 4 || mode == 3) {
        *pA = 1;
    } else {
        *pA = 0;
    }
    if (!active || mode == 5 || mode == 4 || mode == 3 || mode == 2) {
        *pB = 1;
    } else {
        *pB = 0;
    }
    return active;
}


void fn_800589D8(int *pCount, char *pTitle, int titleSize, char *pLine1, int size1, char *pLine2, int size2,
                 char *pLine3, int size3, char *pLine4, int size4, char *pLine5, int size5, char *pLine6, int size6,
                 char *pLine7, int size7, char *pLine8, int size8)
{
    switch (fn_801486A0()) {
    case 4:
        fn_801C3284(pTitle, "4 on 4", titleSize);
        fn_801C3284(pLine1, "- Ball starts on the 5 yard line", size1);
        fn_801C3284(pLine2, "- First down at midfield", size2);
        fn_801C3284(pLine3, "- Turnovers are worth 3 points", size3);
        fn_801C3284(pLine4, "- Play ends after a turnover", size4);
        fn_801C3284(pLine5, "- QB must pass within 5 seconds", size5);
        fn_801C3284(pLine6, "- QB cannot run with the ball", size6);
        *pCount = 6;
        break;
    case 3:
        fn_801C3284(pTitle, "2 Minute Challenge", titleSize);
        fn_801C3284(pLine1, "- Using only passing plays, score as many times as you can in two minutes", size1);
        fn_801C3284(pLine2, "", size2);
        fn_801C3284(pLine3,
                    "- Interceptions, fumble recoveries and safeties by the defense will cause you to lose points",
                    size3);
        *pCount = 3;
        break;
    case 0:
        fn_801C3284(pTitle, "Crush the Carrier", titleSize);
        fn_801C3284(pLine1, "- Score more points than your opponents to win the game", size1);
        fn_801C3284(pLine2, "- You'll earn the most points by Stylin' and holding onto the ball", size2);
        fn_801C3284(pLine3, "- Keep in mind that tackles are worth big points too", size3);
        *pCount = 3;
        break;
    case 5:
        fn_801C3284(pTitle, "Quick Strike", titleSize);
        fn_801C3284(pLine1, "- Each team puts the ball in play from their opponent's end of the field", size1);
        fn_801C3284(pLine2, "", size2);
        fn_801C3284(pLine3, "- Each team retains the ball until they score or run out of downs", size3);
        fn_801C3284(pLine4, "- The game continues until the tie is broken", size4);
        *pCount = 4;
        break;
    case 1:
        fn_801C3284(pTitle, "Jump Ball Battle", titleSize);
        fn_801C3284(pLine1, "- Catch as many passes as possible", size1);
        fn_801C3284(pLine2, "- The NFL STREET ball is worth double points", size2);
        *pCount = 2;
        break;
    case 2:
        fn_801C3284(pTitle, "Open Field Showdown", titleSize);
        fn_801C3284(pLine1, "- Score against your opponent in an open field situation", size1);
        fn_801C3284(pLine2, "- Try to prevent your opponent from scoring in the very same situation", size2);
        *pCount = 2;
        break;
    }
}


void fn_80058CA0(char *pText, int size, int *pActive, int *pSide)
{
    lbl_803EA59C = 0;
    lbl_803EA59D = 0;
    lbl_803EA59E = 0;
    int pad = fn_80065650();
    int value = 0;
    fn_8021D7B8(lbl_803EB688, 0x8000000E, 1, &value);
    if (pad != -1) {
        fn_801C2E18(pText, "Pause - Controller Socket %d", fn_801C6458(pad, 0) + 1);
        int active = 1;
        if (fn_800B6644(pad) == 0) {
            active = 0;
        }
        *pActive = active;
        if (active == 0) {
            if (fn_80178308()) {
                *pSide = 0;
            } else {
                *pSide = 1;
            }
        } else {
            if (fn_80178308() == 0) {
                *pSide = 0;
            } else {
                *pSide = 1;
            }
        }
    } else {
        fn_801C2E18(pText, "Pause");
    }
}

void fn_80058DA0(void)
{
    fn_800652A8();
    if (lbl_803EA59C) {
        if (fn_8017F584() == 6) {
            fn_8002B5D0(1, 7);
        }
        fn_80047874(0);
        fn_8004730C(0);
        fn_800282DC();
    } else {
        fn_80067DB8(0x72, 0, fn_8006569C(), 0, 0);
        if (fn_8006562C() != 5) {
            int value = 1;
            fn_8021D7B8(lbl_803EB688, 0x8000000E, 1, &value);
        }
        if (fn_8017F584() == 6 && fn_800AD9B4() == 2) {
            fn_80025C88(1);
        }
    }
}

void fn_80058E64(void)
{
}

void fn_80058E68(void)
{
    lbl_803EA59C = 1;
    fn_80148154();
    fn_801483C8();
    fn_80067D4C(0x72, 0);
    fn_80072C90(250, 0);
}

void fn_80058EAC(void)
{
    lbl_803EA59D = 1;
    fn_8009D8CC(4);
    fn_8009D964(4, 0);
    fn_800AE988();
    fn_800656A4(0);
    fn_800655B8();
}

int fn_80058EF4(int a)
{
    return 0;
}

void fn_80058EFC(int *pCount, Params_80005284 *pName, Params_80005284 *pText0, Params_80005284 *pText1,
                 Params_80005284 *pText2, Params_80005284 *pText3, int *pResults, Arg_8018399C team)
{
    Params_80005284 *pTeam = team.pParams;
    Object_800785C0 *pRecord = fn_800785C0();
    Params_80005284 *texts[4] = {pText0, pText1, pText2, pText3};
    int results[4];
    char names[4][64];

    fn_801C2EF0(pName->mpText, pRecord->mUnknownCB, pName->mLength);
    fn_801C2EF0(pTeam->mpText, pRecord->mUnknown1, pTeam->mLength);
    *pCount = fn_80025B18(results, names);
    for (unsigned char i = 0; i <= 3; i++) {
        fn_801C3284(texts[i]->mpText, names[i], texts[i]->mLength);
        pResults[i] = results[i];
    }
    fn_80025C88(0);
}

void fn_80058FDC(int a)
{
    lbl_803EA59E = 1;
    fn_80178B1C(a);
}

unsigned char fn_80059004(void)
{
    return lbl_803EA59D;
}

unsigned char fn_8005900C(void)
{
    return lbl_803EA59E;
}

void fn_80059014(void)
{
    lbl_803EA59D = 0;
}

void fn_80059020(void)
{
    lbl_803EA59E = 0;
}

int fn_8005902C(void)
{
    return 0;
}


int fn_80059034(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80058CA0(pArgs[0].pParams->mpText, pArgs[0].pParams->mLength, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000002:
        fn_80058DA0();
        break;
    case 0x80000003:
        fn_80058E64();
        break;
    case 0x80000004:
        fn_80058E68();
        break;
    case 0x80000008:
        fn_80058EAC();
        break;
    case 0x80000009:
        fn_80058FDC(1);
        break;
    case 0x80000015:
        fn_80065638(1);
        fn_8003B8BC();
        break;
    case 0x8000000A:
        fn_8003B234(pArgs[0].i, pArgs[1].i, (int *)(pArgs[2].i + (*pArgs[2].pi + 1) * 4));
        break;
    case 0x8000000B:
        fn_8003B0F8(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].i, pArgs[4].pParams->mpText,
                    pArgs[4].pParams->mLength);
        break;
    case 0x8000000C:
        fn_8003B6F0(0);
        fn_8003B1F4(pArgs[0].i);
        break;
    case 0x80000012:
        *pResult = fn_80058EF4(pArgs[0].i);
        break;
    case 0x8000000E:
        *pResult = 1;
        break;
    case 0x8000000F:
    case 0x80000010:
        break;
    case 0x80000011:
        *pResult = -1;
        break;
    case 0x80000014:
        *pResult = fn_80025708();
        break;
    case 0x80000005:
        fn_80058EFC(pArgs[0].pi, pArgs[1].pParams, pArgs[2].pParams, pArgs[3].pParams, pArgs[4].pParams,
                    pArgs[5].pParams, (int *)(pArgs[6].i + (*pArgs[6].pi + 1) * 4), pArgs[7]);
        break;
    case 0x8000000D:
    case 0x80000016:
        *pResult = 0;
        break;
    case 0x80000017:
        *pResult = fn_80058930(pArgs[0].pi, pArgs[1].pi);
        break;
    case 0x80000018:
        fn_800589D8(pArgs[0].pi, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength, pArgs[2].pParams->mpText,
                    pArgs[2].pParams->mLength, pArgs[3].pParams->mpText, pArgs[3].pParams->mLength,
                    pArgs[4].pParams->mpText, pArgs[4].pParams->mLength, pArgs[5].pParams->mpText,
                    pArgs[5].pParams->mLength, pArgs[6].pParams->mpText, pArgs[6].pParams->mLength,
                    pArgs[7].pParams->mpText, pArgs[7].pParams->mLength, pArgs[8].pParams->mpText,
                    pArgs[8].pParams->mLength, pArgs[9].pParams->mpText, pArgs[9].pParams->mLength);
        break;
    case 0x80000019:
        fn_800656AC(1);
        break;
    case 0x8000001A: {
        int mode = fn_800AD9B4();
        if (mode == 2 || mode == 4 || mode == 5) {
            fn_80065664(1);
        }
        break;
    }
    case 0x8000001B:
        if (fn_800AD9B4() == 4) {
            fn_8002C9A8(lbl_803EA368, 3, 0);
        } else {
            *pResult = fn_8002D228(lbl_803EA368);
        }
        break;
    case 0x8000001C:
        *pResult = fn_80156704();
        break;
    case 0x147:
        *pResult = fn_800551D8(pArgs[0].i);
        break;
    case 0x149:
        fn_800551E0(pArgs[0].i, pArgs[1].i, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength);
        *pArgs[3].pi = fn_80178D70(pArgs[0].i ? fn_80178308() : fn_80178320());
        break;
    case 0x14A: {
        int *pList = (int *)(pArgs[1].i + (*pArgs[1].pi + 1) * 4);
        fn_80055230(pArgs[0].i, pArgs[4].i, pArgs[3].i, pList, pList + 1, pArgs[2].pParams->mpText,
                    pArgs[2].pParams->mLength);
        break;
    }
    default:
        return 0;
    }
    return 1;
}


int fn_800594F4(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80186010(0x80000001, 0, 0, 0);
        fn_80063910(0x80000001, 0, 0, 0);
        break;
    case 0x80000002:
        fn_80063910(0x80000002, 0, 0, 0);
        fn_80186010(0x80000002, 0, 0, 0);
        break;
    case 0x80000005:
        fn_80186010(0x80000003, pArgs, unused, pResult);
        fn_80063910(0x80000005, pArgs, unused, pResult);
        break;
    case 0x80000006:
        fn_80063910(0x80000003, pArgs, unused, pResult);
        break;
    case 0x80000007:
        fn_80063910(0x80000004, pArgs, unused, pResult);
        break;
    default:
        return 0;
    }
    return 1;
}

int fn_80059664(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 2:
        return fn_8005845C(id, pArgs, unused, pResult);
    case 0:
        return fn_80059034(id, pArgs, unused, pResult);
    case 3:
        return fn_8005A2B8(id, pArgs, unused, pResult);
    case 0x10:
        return fn_8005A630(id, pArgs, unused, pResult);
    case 5:
        return fn_80059A24(id, pArgs, unused, pResult);
    case 6:
        return fn_80056444(id, pArgs, unused, pResult);
    case 7:
        return fn_8005B2BC(id, pArgs, unused, pResult);
    case 0xA:
        return fn_8005BCA8(id, pArgs, unused, pResult);
    case 8:
        return fn_8005B4B0(id, pArgs, unused, pResult);
    case 0xB:
        return fn_800594F4(id, pArgs, unused, pResult);
    case 0xF:
        return fn_8005C0C0(id, pArgs, unused, pResult);
    case 0x13:
        return fn_800566F0(id, pArgs, unused, pResult);
    case 0x14:
        return fn_8005C338(id, pArgs, unused, pResult);
    case 0x12:
        return fn_8005C6EC(id, pArgs, unused, pResult);
    case 0x11:
        return fn_8005C994(id, pArgs, unused, pResult);
    case 0x18:
        return fn_8005CC50(id, pArgs, unused, pResult);
    case 0x19:
        return fn_8005D1E4(id, pArgs, unused, pResult);
    case 0x16:
        return fn_8005D2D0(id, pArgs, unused, pResult);
    case 9:
        return fn_8005BFDC(9, id, pArgs, unused, pResult);
    case 0xC:
        return fn_8005BFDC(0xC, id, pArgs, unused, pResult);
    case 0x17:
        return fn_8005BFDC(0x17, id, pArgs, unused, pResult);
    }
    return 0;
}


int fn_8005993C(int *pId1, int *pId0, char *pName1, int size1, char *pName0, int size0,
                int *pValue1, int *pValue0)
{
    int ok = 1;
    char name1[17];
    char name0[17];
    int id0 = fn_800C8744(0);
    int id1 = fn_800C8744(1);

    fn_80187CAC(id1, name1, 16);
    fn_80187CAC(id0, name0, 16);
    name1[16] = 0;
    name0[16] = 0;
    if (fn_8007F828(14) == 1) {
        ok = 0;
    }
    int value0 = fn_8017881C(0);
    int value1 = fn_8017881C(1);
    *pId1 = id1;
    *pId0 = id0;
    *pValue1 = value1;
    *pValue0 = value0;
    fn_801C2EF0(pName1, name1, size1);
    fn_801C2EF0(pName0, name0, size0);
    return ok;
}

int fn_80059A24(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    if (id == 0x80000001) {
        *pResult = fn_8005993C(pArgs[0].pi, pArgs[1].pi, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength,
                               pArgs[3].pParams->mpText, pArgs[3].pParams->mLength, pArgs[4].pi, pArgs[5].pi);
        return 1;
    }
    return 0;
}

void fn_80059A9C(int *pList)
{
    unsigned int i;
    int high = 3;
    int low = 0;

    for (i = 0; i < 4; i++) {
        pList[i] = -1;
    }
    for (i = 0; i <= 3; i++) {
        int id = fn_80188044(i);
        if (id != -1) {
            unsigned int side = fn_800B6644(id);
            if ((unsigned int)fn_801486A0() > 1) {
                if (side == 1) {
                    pList[low++] = i;
                } else if (side == 0) {
                    pList[high--] = i;
                }
            } else if (side <= 1) {
                pList[i] = i;
            }
        }
    }
}


struct Stats_8005A7EC {
    float mUnknown0;
    int mUnknown4;
    int mStats[12];
    float mValues[11];
    int mIndices[11];
};
struct Weight_8005A8D0 {int mTag;int mColumn;float mWeight;};
struct Category_8005AB04 {char mName[20];unsigned char mEnabled;unsigned int mCount;int mIndices[2];};
extern Object_8008044C lbl_80309F98;
extern Stats_8005A7EC lbl_80309FC4[2];
extern const Weight_8005A8D0 lbl_8028EAE8[12];
extern const Category_8005AB04 lbl_8028EB78[11];
extern int lbl_802D4D0C[4];
extern const char *lbl_802D4D1C[9];
extern const float lbl_803ED6A4,lbl_803ED6A8;
void fn_800D4164(int side,float time,int a);
void fn_800A7B5C(void);
void fn_800B823C(int side);
int fn_80187C8C(void);
int fn_80187C6C(void);
int fn_801787DC(int team);
int fn_800D41F8(int team);
int fn_800A8444(int team);
int fn_800A8740(void);
float fn_800D3F2C(int team);
void fn_8017E328(int team,int mode);
int fn_800CAAC4(int team,unsigned char index);
float fn_800C9CF0(int team,unsigned char index);
int fn_80178C24(void);
unsigned int fn_8009D9F8(int key);
int fn_8009D9C0(int key);
Record_80067338 *fn_8016898C(int team,int index);
int fn_800AEBA0(void);
int fn_80178E4C(void);
int fn_800AF078(int team);
int fn_8002892C(void);
Object_80039F5C *fn_8003AC84(int id);
int fn_8008201C(Object_8008044C *pObject,int a,int b,int *pResult,int *pPosition);
void fn_80080A34(Object_8008044C *pObject,char *pText,int size);
void fn_8017833C(int enabled);
void fn_80178354(int enabled);
void fn_800C1E50(void);
int fn_80025718(void);
int fn_80025508(void);
int fn_80178AE0(void);
void *fn_8022F4BC(void);
void *fn_80186B38(void *p);
int fn_8006270C(void);
void fn_8018F340(void *p,int id);
void fn_8018F4C4(void *p);
int fn_8018F288(void *p,int id);
int fn_8018F3D8(void *p);
int fn_800A3444(void);
void fn_8007B684(int id);
void fn_8007B8A4(char *pText,int size);
void fn_8007B904(char *pText,int size);
void fn_8007B6D4(void);
void fn_80083E1C(Object_8007A334 *pObject,Query_80083E40 *pQuery);
int fn_8008406C(Object_8007A334 *pObject,int id,int *pResult);
int fn_80083FBC(Object_8007A334 *pObject);
void fn_80079248(char *pText,int size,int id);
void fn_80078BB8(int value);
int fn_80078B94(void);
int fn_80078AE0(int id);
void fn_8007E274(int key);
void fn_8007E8A8(int a,int value);
void fn_800C8818(int id);
void fn_8002B714(void);
void fn_8007E738(int value);
void fn_8007BF60(int value);
int fn_8007984C(Object_800785C0 *pRecord);
int fn_8002B5C8(void);
void fn_80077F24(void);

void fn_80059B64(int *pList, int *pValues, Arg_8018399C *pNames, int *pScores, int *pZero, int *pModes, int *pState, int *pFlags, int *pEnabled, int *pLast);
void fn_80059E24(float *pValues);
void fn_80059F54(int *pA, int *pB, int *pC, int *pD);
void fn_80059F80(char *pText, int *pRed, int *pGreen, int *pBlue);
void fn_8005A1C0(unsigned int team, int *pEnabled, Params_80005284 **pNames, int *pMode, Params_80005284 **ppText);
int fn_8005A2B8(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005A630(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005A794(int tag, int column, int id);
void fn_8005A7EC(int team);
int fn_8005A860(int team);
Object_80039F5C *fn_8005A8AC(int team);
void fn_8005A8D0(int team);
void fn_8005AB04(int team, Arg_8018399C *pNames, int *pValues);
void fn_8005AC18(int team,int *pId,char *pFirst,int firstSize,char *pLast,int lastSize);
void fn_8005ACF0(int team);
void fn_8005ACC8(void);
void fn_8005ADCC(int team,int *pId,char *pFirst,int firstSize,char *pLast,int lastSize,Arg_8018399C *pNames,int *pValues);
void fn_8005AE5C(int index);
void fn_8005AEC8(int *pEnabled,int *pCount,Params_80005284 *pFirst,Params_80005284 *pSecond,int *pAllowed);
void fn_8005B128(int *pResult,int *pId,Params_80005284 *pText);
int fn_8005B2BC(unsigned int id,Arg_8018399C *pArgs,int unused,int *pResult);
void fn_8005B3D4(char *pFirst,int firstSize,char *pLast,int lastSize,int *pValue,char *pLabel,int labelSize,int *pResult);
int fn_8005B4B0(unsigned int id,Arg_8018399C *pArgs,int unused,int *pResult);
void fn_8005B55C(int *pResult);
void fn_8005B610(char *pText,int size,int id);
void fn_8005B6AC(char *pText,int size,unsigned char id,int defensive);
int fn_8005B730(char *pText,int size,int kind,int value);
void fn_8005B838(int kind,int value);
int fn_8005B908(Params_80005284 **pText);
void fn_8005B9FC(int *pResult,Params_80005284 **pNames);

void fn_80059B64(int *pList, int *pValues, Arg_8018399C *pNames, int *pScores, int *pZero, int *pModes, int *pState, int *pFlags, int *pEnabled, int *pLast)
{
    if (fn_80025708()) {
        if (fn_800785C0()->mUnknown1C3) { fn_800D4164(0, lbl_803ED6A4, 0); fn_800A7B5C(); }
        if (fn_800785C0()->mUnknown1C2) { fn_800D4164(1, lbl_803ED6A4, 0); fn_800A7B5C(); }
    }
    fn_800B823C(0); fn_800B823C(1);
    fn_80059A9C(pList);
    pValues[0] = fn_80187C8C(); pValues[1] = fn_80187C6C();
    if (fn_8007F828(14) != 1) {
        Params_80005284 *pText = ((Params_80005284 **)pNames[0].pi)[*pNames[0].pi + 1];
        fn_801C2D88(pText->mpText, pText->mLength + 1, "%d", fn_801787DC(0));
        pText = ((Params_80005284 **)pNames[0].pi)[*pNames[0].pi + 2];
        fn_801C2D88(pText->mpText, pText->mLength + 1, "%d", fn_801787DC(1));
    } else {
        ((Params_80005284 **)pNames[0].pi)[*pNames[0].pi + 1]->mpText[0] = 0;
        ((Params_80005284 **)pNames[0].pi)[*pNames[0].pi + 2]->mpText[0] = 0;
    }
    pScores[0] = fn_800D41F8(0); pScores[1] = fn_800D41F8(1);
    pZero[1] = 0; pZero[0] = 0; pModes[1] = 0; pModes[0] = 0;
    *pState = fn_80177F70();
    pFlags[0] = fn_800A8444(0); pFlags[1] = fn_800A8444(1);
    *pEnabled = fn_800A8740() == 0;
    if (*pEnabled == 1) {
        for (int i = 0; i < 2; i++) {
            if (fn_800D3F2C(i) < lbl_803ED6A8) {
                if (fn_800D3F2C(i) < lbl_803ED6A4) pModes[i] = 0;
                else pModes[i] = 1;
            } else pModes[i] = 2;
            fn_8017DF6C((unsigned char)i, (unsigned char)pModes[i]);
            if (fn_800D3F2C(i) < lbl_803ED6A4) fn_8017E328((unsigned char)i, 1);
            else fn_8017E328((unsigned char)i, 2);
        }
    }
    pLast[1] = 0; pLast[0] = 0;
}

void fn_80059E24(float *pValues)
{
    for (int i = 0; i < 4; i++) pValues[i] = 1.0f;
    float *pLow = pValues, *pHigh = pValues + 3;
    int index1 = 0, index0 = 0;
    for (unsigned int i = 0; i < 4; i++) {
        int id = fn_80188044(i);
        if (id != -1) {
            int team = fn_800B6644(id);
            if (team != 255) {
                if ((unsigned int)fn_801486A0() <= 1) {
                    for (unsigned char j = 0; j < 4; j++) {
                        if (fn_800CAAC4(team, j) == id) {pValues[i] = fn_800C9CF0(team, j); break;}
                    }
                } else if (team == 1) *pLow++ = fn_800C9CF0(1, index1++);
                else if (team == 0) *pHigh-- = fn_800C9CF0(0, index0++);
            }
        }
    }
}

void fn_80059F54(int *pA, int *pB, int *pC, int *pD)
{
    *pA = lbl_802D4D0C[0]; *pB = lbl_802D4D0C[1]; *pC = lbl_802D4D0C[2]; *pD = lbl_802D4D0C[3];
}

void fn_80059F80(char *pText, int *pRed, int *pGreen, int *pBlue)
{
    int key;
    int mode = fn_801486A0();
    if (mode == 2 || mode == 4) key = 5;
    else { key = 4; if (fn_80178C24()) key = 1; }
    unsigned int time = fn_8009D990(key);
    unsigned int elapsed = fn_8009D9F8(key);
    int duration = fn_8009D9C0(key);
    float fraction = (float)elapsed / (float)duration;
    if (!(1.0f - fraction > 0.0000001f)) fraction = 1.0f;
    unsigned int remainder = (unsigned int)(fraction * 1000.0f) % 1000;
    unsigned short minutes = time / 60;
    unsigned short seconds = time % 60;
    if (minutes == 0 && seconds == 0) remainder = 0;
    if (remainder) {
        if (!seconds) {seconds = 59; minutes--;}
        else seconds--;
    }
    fn_801C2E18(pText, "%d:%02d.%01d", minutes, seconds, remainder / 100);
    if (pRed && pGreen && pBlue) {
        if (minutes != 0 || (seconds > 9 && (seconds != 10 || remainder != 0))) {
            *pRed = 255; *pGreen = 255; *pBlue = 255;
        } else {*pRed = 200; *pGreen = 0; *pBlue = 0;}
    }
}

void fn_8005A1C0(unsigned int team, int *pEnabled, Params_80005284 **pNames, int *pMode, Params_80005284 **ppText)
{
    Params_80005284 *pText = *ppText;
    for (unsigned int i = 0; i < 4; i++) {
        pEnabled[i] = fn_801486A0() != 2 || i < 2;
        if (pEnabled[i] == 1) {
            Record_80067338 *pRecord = fn_8016898C((unsigned char)team, i);
            fn_801C2EF0(pNames[i]->mpText, pRecord->mUnknown1F3, pNames[i]->mLength);
        }
    }
    if ((unsigned int)fn_80178308() == team) {
        *pMode = fn_800AEBA0() != 0;
        if (*pMode == 1) fn_801C2EF0(pText->mpText, "Max Protect", pText->mLength);
    } else {
        *pMode = fn_80178E4C();
        fn_801C2EF0(pText->mpText, "Prediction", pText->mLength);
    }
}

int fn_8005A2B8(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80059B64((int *)(pArgs[0].i + (*pArgs[0].pi + 1) * 4), (int *)(pArgs[1].i + (*pArgs[1].pi + 1) * 4), &pArgs[2],
                   (int *)(pArgs[3].i + (*pArgs[3].pi + 1) * 4), (int *)(pArgs[4].i + (*pArgs[4].pi + 1) * 4),
                   (int *)(pArgs[5].i + (*pArgs[5].pi + 1) * 4), pArgs[6].pi,
                   (int *)(pArgs[7].i + (*pArgs[7].pi + 1) * 4), pArgs[8].pi,
                   (int *)(pArgs[9].i + (*pArgs[9].pi + 1) * 4));
        break;
    case 0x80000002: fn_80059E24((float *)(pArgs[0].i + (*pArgs[0].pi + 1) * 4)); break;
    case 0x80000003: fn_80059A9C((int *)(pArgs[0].i + (*pArgs[0].pi + 1) * 4)); break;
    case 0x80000005: fn_80059F54(pArgs[0].pi,pArgs[1].pi,pArgs[2].pi,pArgs[3].pi); break;
    case 0x80000006: fn_80059F80(pArgs[0].pParams->mpText,0,0,0); break;
    case 0x80000007:
        if (fn_80025708()) *pResult = fn_800785C0()->mUnknown1A4;
        else {int mode = fn_801486A0(); *pResult = mode == 2 || mode == 4 ? 1 : fn_80178C24();}
        break;
    case 0x80000008:
        ((int *)(pArgs[0].i + (*pArgs[0].pi + 1) * 4))[0] = fn_800AF078(0);
        ((int *)(pArgs[0].i + (*pArgs[0].pi + 1) * 4))[1] = fn_800AF078(1);
        *pArgs[1].pi = fn_8002892C() != 0;
        ((int *)(pArgs[2].i + (*pArgs[2].pi + 1) * 4))[0] = 0;
        ((int *)(pArgs[2].i + (*pArgs[2].pi + 1) * 4))[1] = 0;
        ((float *)(pArgs[3].i + (*pArgs[3].pi + 1) * 4))[0] = 1.0f;
        ((float *)(pArgs[3].i + (*pArgs[3].pi + 1) * 4))[1] = 1.0f;
        ((float *)(pArgs[4].i + (*pArgs[4].pi + 1) * 4))[0] = 1.0f;
        ((float *)(pArgs[4].i + (*pArgs[4].pi + 1) * 4))[1] = 1.0f;
        ((int *)(pArgs[5].i + (*pArgs[5].pi + 1) * 4))[0] = 0;
        ((int *)(pArgs[5].i + (*pArgs[5].pi + 1) * 4))[1] = 0;
        break;
    case 0x80000009:
        {Params_80005284 *pText = pArgs[4].pParams;
        fn_8005A1C0(pArgs[0].i, (int *)(pArgs[1].i + (*pArgs[1].pi + 1) * 4),
                   (Params_80005284 **)(pArgs[2].i + (*pArgs[2].pi + 1) * 4), pArgs[3].pi, &pText);}
        break;
    default: return 0;
    }
    return 1;
}

int fn_8005A630(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch(id) {
    case 0x80000001: break;
    case 0x80000002: {int mode=fn_801486A0(); *pResult=mode==2||mode==4?1:fn_80178C24();} break;
    case 0x80000003: fn_80059A9C((int *)(pArgs[0].i + (*pArgs[0].pi + 1) * 4)); break;
    case 0x80000004: fn_80059F80(pArgs[0].pParams->mpText,pArgs[1].pi,pArgs[2].pi,pArgs[3].pi); break;
    case 0x80000005: fn_80059E24((float *)(pArgs[0].i + (*pArgs[0].pi + 1) * 4)); break;
    case 0x80000006: {Params_80005284 *pText=pArgs[4].pParams;
        fn_8005A1C0(pArgs[0].i,(int *)(pArgs[1].i+(*pArgs[1].pi+1)*4),
                   (Params_80005284 **)(pArgs[2].i+(*pArgs[2].pi+1)*4),pArgs[3].pi,&pText);} break;
    default:return 0;
    }
    return 1;
}

int fn_8005A794(int tag, int column, int id)
{
    int value;
    if (fn_801FCE10(0,"select \x8c into \x82 from \x8c where 'DIGP' = \x82\n",column,&value,tag,id)) value=0;
    return value;
}

void fn_8005A7EC(int team)
{
    int swapped;
    do {
        swapped=0;
        for (int i=0;i<10;i++) {
            if (!(lbl_80309FC4[team].mValues[i]>=lbl_80309FC4[team].mValues[i+1])) {
                float value=lbl_80309FC4[team].mValues[i];
                lbl_80309FC4[team].mValues[i]=lbl_80309FC4[team].mValues[i+1];
                lbl_80309FC4[team].mValues[i+1]=value;
                int index=lbl_80309FC4[team].mIndices[i];
                lbl_80309FC4[team].mIndices[i]=lbl_80309FC4[team].mIndices[i+1];
                lbl_80309FC4[team].mIndices[i+1]=index;
                swapped=1;
            }
        }
    } while(swapped);
}

int fn_8005A860(int team)
{
    fn_8005ACF0(team); fn_8005A8D0(team); fn_8005ACC8();
    return lbl_80309FC4[team].mUnknown4;
}
Object_80039F5C *fn_8005A8AC(int team)
{
    return fn_8003AC84(fn_8005A860(team));
}

void fn_8005A8D0(int team)
{
    int row;
    int values[12];
    float scores[11];
    if (fn_8008201C(&lbl_80309F98,0,team,&row,0)) {
        do {
            for (int i=0;i<12;i++) values[i]=fn_8005A794(lbl_8028EAE8[i].mTag,lbl_8028EAE8[i].mColumn,row);
            float sum=0.0f;
            for (int i=0;i<11;i++) {
                float value=0.0f;
                for (unsigned int j=0;j<lbl_8028EB78[i].mCount;j++) {
                    int index=lbl_8028EB78[i].mIndices[j];
                    if(index!=13) value += values[index]*lbl_8028EAE8[index].mWeight;
                }
                scores[i]=value; sum+=value;
            }
            Object_80039F5C *p=fn_8003AC84(row);
            if(p && p->mUnknown9[2]) sum+=1.0f;
            if(!(sum<=lbl_80309FC4[team].mUnknown0)) {
                lbl_80309FC4[team].mUnknown0=sum;
                lbl_80309FC4[team].mUnknown4=row;
                for(int i=0;i<12;i++) lbl_80309FC4[team].mStats[i]=values[i];
                for(int i=0;i<11;i++) lbl_80309FC4[team].mValues[i]=scores[i];
            }
        } while(fn_8008201C(&lbl_80309F98,1,team,&row,0));
    }
}

void fn_8005AB04(int team, Arg_8018399C *pNames, int *pValues)
{
    fn_8005A7EC(team);
    unsigned int count=0;
    int i=0;
    do {
        const Category_8005AB04 *pCategory=&lbl_8028EB78[lbl_80309FC4[team].mIndices[i++]];
        if(pCategory->mEnabled) {
            Params_80005284 *pText=((Params_80005284 **)pNames[0].pi)[*pNames[0].pi+count+1];
            fn_801C2EF0(pText->mpText,pCategory->mName,pText->mLength);
            int value=0;
            for(unsigned int j=0;j<pCategory->mCount;j++) {
                int index=pCategory->mIndices[j];
                if(index!=13) value+=lbl_80309FC4[team].mStats[index];
            }
            pValues[count++]=value;
        }
    } while(count<4);
}

void fn_8005AC18(int team,int *pId,char *pFirst,int firstSize,char *pLast,int lastSize)
{
    int key;
    fn_800809C4(&lbl_80309F98,lbl_80309FC4[team].mUnknown4,&key);
    *pId=fn_800C8744(team);
    char first[16],last[16];
    fn_80080A34(&lbl_80309F98,first,12); fn_801C2EF0(pFirst,first,firstSize);
    fn_80080A68(&lbl_80309F98,last,15); fn_801C2EF0(pLast,last,lastSize);
}
void fn_8005ACC8(void) {fn_8008056C(&lbl_80309F98);}
void fn_8005ACF0(int team)
{
    Desc_8008044C desc;
    desc.mUnknown4=1; desc.mUnknown8=team;
    fn_8008044C(&lbl_80309F98,&desc,0x454D4147);
    Stats_8005A7EC *p=&lbl_80309FC4[team];
    p->mUnknown4=0; p->mUnknown0=-3.4028234663852886e38f;
    for(int i=11;i>=0;i--) p->mStats[i]=0;
    for(int i=0;i<11;i++) {p->mIndices[i]=i;p->mValues[i]=0.0f;}
}
void fn_8005ADCC(int team,int *pId,char *pFirst,int firstSize,char *pLast,int lastSize,Arg_8018399C *pNames,int *pValues)
{
    team=team!=0;
    fn_8005ACF0(team); fn_8005A8D0(team);
    fn_8005AC18(team,pId,pFirst,firstSize,pLast,lastSize); fn_8005AB04(team,pNames,pValues); fn_8005ACC8();
}

void fn_8005AE5C(int index)
{
    if(lbl_803EA5A0[index]!=1 && lbl_803EA5A0[index]==2) {
        if(fn_8017F584()==8) {fn_800C1CA0();fn_8017833C(1);fn_80178354(1);}
        else fn_800C1CA0();
    }
    lbl_803EA5A0[0]=0; lbl_803EA5A0[1]=0;
}

void fn_8005AEC8(int *pEnabled,int *pCount,Params_80005284 *pFirst,Params_80005284 *pSecond,int *pAllowed)
{
    fn_800C1E50();fn_80059020();
    int enabled=0;
    if(!fn_8017F60C() && (!fn_80025718() || fn_80025508())) {
        enabled=1;
        if(fn_8017F584()==7 || fn_8017F584()==10) {
            if(fn_800B65A0(fn_80178AE0())!=255) enabled=0;
        }
    }
    *pEnabled=enabled;
    unsigned int score1,score0;
    if(fn_8007F828(14)==1) {score1=fn_800D41F8(1);score0=fn_800D41F8(0);}
    else {score1=fn_801787DC(1);score0=fn_801787DC(0);}
    *pAllowed=!((score1<score0 && fn_800B65A0(1)!=255)||(score0<score1 && fn_800B65A0(0)!=255));
    if(fn_8017F584()==8) {
        if(score1>score0) {*pCount=1;fn_801C2EF0(pFirst->mpText,"Continue",pFirst->mLength);lbl_803EA5A0[0]=3;}
        else {*pCount=2;fn_801C2EF0(pFirst->mpText,"Rematch",pFirst->mLength);lbl_803EA5A0[0]=2;
              fn_801C2EF0(pSecond->mpText,"Exit",pSecond->mLength);lbl_803EA5A0[1]=1;}
        return;
    }
    const char *pLabel=fn_8017F584()==11?"Continue":"Exit";
    if(*pEnabled==1) {
        *pCount=2;fn_801C2EF0(pFirst->mpText,"Rematch",pFirst->mLength);lbl_803EA5A0[0]=2;
        fn_801C2EF0(pSecond->mpText,pLabel,pSecond->mLength);lbl_803EA5A0[1]=1;
    } else {
        *pCount=1;fn_801C2EF0(pFirst->mpText,pLabel,pSecond->mLength);lbl_803EA5A0[0]=1;lbl_803EA5A0[1]=0;
    }
}

void fn_8005B128(int *pResult,int *pId,Params_80005284 *pText)
{
    unsigned int score1,score0;
    if(fn_8007F828(14)==1) {score1=fn_800D41F8(1);score0=fn_800D41F8(0);}
    else {score1=fn_801787DC(1);score0=fn_801787DC(0);}
    if(fn_8017F584()==8) {
        if(score1>score0) {
            void *p=fn_80186B38(fn_8022F4BC());
            fn_8018F340(p,fn_8006270C());
            fn_8018F4C4(fn_80186B38(fn_8022F4BC()));
            *pResult=1;
            if(fn_8018F288(fn_80186B38(fn_8022F4BC()),34)) *pResult=3;
            else if(!fn_8018F3D8(fn_80186B38(fn_8022F4BC()))) *pResult=2;
        } else *pResult=0;
        Object_8007A334 query;
        fn_80083E40(&query,0,0x54415453);
        if(fn_80084034(&query,*pId,0)) {char name[36];fn_80083F88(&query,name,32);fn_801C3284(pText->mpText,name,pText->mLength);}
        else fn_801C3284(pText->mpText,"",pText->mLength);
        fn_80083F68(&query);
    } else *pResult=-1;
}
int fn_8005B2BC(unsigned int id,Arg_8018399C *pArgs,int unused,int *pResult)
{
    switch(id) {
    case 0x80000001:lbl_803EA59F=1;fn_8005AEC8(pArgs[0].pi,pArgs[1].pi,pArgs[2].pParams,pArgs[3].pParams,pArgs[4].pi);break;
    case 0x80000002:fn_8005AE5C(pArgs[0].i);lbl_803EA59F=0;break;
    case 0x80000003:fn_8005ADCC(pArgs[0].i,pArgs[1].pi,pArgs[2].pParams->mpText,pArgs[2].pParams->mLength,
        pArgs[3].pParams->mpText,pArgs[3].pParams->mLength,&pArgs[4],(int *)(pArgs[5].i+(*pArgs[5].pi+1)*4));break;
    case 0x80000004:fn_8005B128(pArgs[0].pi,pArgs[1].pi,pArgs[2].pParams);break;
    default:return 0;
    }
    return 1;
}
unsigned char fn_8005B3CC(void) {return lbl_803EA59F;}
void fn_8005B3D4(char *pFirst,int firstSize,char *pLast,int lastSize,int *pValue,char *pLabel,int labelSize,int *pResult)
{
    fn_8007B684(fn_800A3444());fn_8007B8A4(pFirst,firstSize);fn_8007B904(pLast,lastSize);fn_8007B6D4();
    fn_801FCE10(0,"use 'EVAS' select 'KTFH' into \x82 from 'DFSH' where 'DIVE' = \x80\n",pValue,fn_800A3444());
    int mode=fn_8007F828(14);
    if(mode==0) {fn_801C2E18(pLabel,"Touchdowns");*pResult=fn_8007F828(1);}
    else if(mode==1) {fn_801C2E18(pLabel,"Style Points");*pResult=fn_8007F828(2);}
}
int fn_8005B4B0(unsigned int id,Arg_8018399C *pArgs,int unused,int *pResult)
{
    switch(id) {
    case 0x80000001:fn_8005B3D4(pArgs[0].pParams->mpText,pArgs[0].pParams->mLength,pArgs[1].pParams->mpText,
        pArgs[1].pParams->mLength,pArgs[2].pi,pArgs[3].pParams->mpText,pArgs[3].pParams->mLength,pArgs[4].pi);break;
    case 0x80000002:fn_8007B684(fn_800A3444());fn_8007B8A4(pArgs[0].pParams->mpText,pArgs[0].pParams->mLength);fn_8007B6D4();break;
    default:return 0;
    }
    return 1;
}
void fn_8005B55C(int *pResult)
{
    Object_8007A334 query;
    fn_80083E1C(&query,0);fn_8008406C(&query,1,0);*pResult=fn_80083FBC(&query);fn_80083F68(&query);fn_800C1E50();
}
void fn_8005B5D8(int clear) {fn_800652A8();if(clear) fn_800C1CA0();}
void fn_8005B610(char *pText,int size,int id)
{
    Object_8007A334 query;char name[24];
    fn_8007EEFC(&query);fn_8007F0F4(&query,id+45,0);fn_8007F094(&query,name,21);fn_8007F064(&query);
    fn_801C2D88(pText,size,lbl_802D4D1C[5],name);
}
void fn_8005B6AC(char *pText,int size,unsigned char id,int defensive)
{
    char name[68];fn_80058798(name,64,id,defensive);
    fn_801C2D88(pText,size,defensive?lbl_802D4D1C[3]:lbl_802D4D1C[7],name);
}
int fn_8005B730(char *pText,int size,int kind,int value)
{
    int result=0;char text[260];text[0]=0;
    switch(kind) {
    case 1:result=value;break;
    case 2:fn_80079248(text,255,value);break;
    case 3:fn_8005B6AC(text,255,value,1);break;
    case 5:fn_8005B610(text,255,value);break;
    case 7:fn_8005B6AC(text,255,value,0);break;
    default:fn_801C3284(text,lbl_802D4D1C[kind],255);break;
    }
    if(fn_801C3180(text)>0) fn_801C2EF0(pText,text,size);
    return result;
}
void fn_8005B838(int kind,int value)
{
    switch(kind) {
    case 1:fn_80078BB8(fn_80078B94()+value);break;
    case 2:fn_8007E274(fn_80078AE0(value));break;
    case 3:fn_8007E8A8(0,value);break;
    case 4:fn_800C8818(0);fn_8002B714();break;
    case 5:fn_8007E738(value);break;
    case 6:break;
    case 7:fn_8007E8A8(1,value);break;
    case 8:fn_8007BF60(value);break;
    }
}
int fn_8005B908(Params_80005284 **pText)
{
    int result=0;Object_800785C0 *p=fn_800785C0();
    if(!fn_8007984C(p)) {
        for(int i=0;i<2;i++) {
            if(p->mUnknown1F4[i].mId) {
                result+=fn_8005B730((*pText)->mpText,(*pText)->mLength,p->mUnknown1F4[i].mId,p->mUnknown1F4[i].mUnknown4);
                fn_8005B838(p->mUnknown1F4[i].mId,p->mUnknown1F4[i].mUnknown4);
                if(fn_801C3180((*pText)->mpText)) pText++;
            }
        }
    } else {
        int index=fn_8002B5C8();
        if(index<3) {
            result=fn_8005B730((*pText)->mpText,(*pText)->mLength,p->mUnknown20C.mUnknown1C,p->mUnknown20C.mUnknown20[index]);
            fn_8005B838(p->mUnknown20C.mUnknown1C,p->mUnknown20C.mUnknown20[index]);
        }
    }
    return result;
}
void fn_8005B9FC(int *pResult,Params_80005284 **pNames)
{
    for(int i=0;i<4;i++) fn_801C3284(pNames[i]->mpText,"",pNames[i]->mLength);
    *pResult=fn_8005B908(pNames);fn_80077F24();
}

}

/* Shared with the 28-byte records initialized by fn_80156400. */
class Record_8005CE10 {
public:
    Record_8005CE10() : mOrdinal(0), mEvent(11), mPlayer(32767), mConversion(11), mOther(32767), mFlag(0) {}
    virtual ~Record_8005CE10() {}
    unsigned int mOrdinal;
    int mEvent;
    int mPlayer;
    int mConversion;
    int mOther;
    unsigned char mFlag;
};
struct Stats_8005C4A4 {
    Object_80039F5C *mpPlayer;
    int mUnknown4;
    unsigned int mTime;
    int mUnknown12;
    unsigned char mColor;
    Stats_8005C4A4() : mpPlayer(0), mUnknown4(0), mTime(0), mUnknown12(0), mColor(255) {}
};
struct Stats_8005C844 {
    Stats_8005C844() {
        mValues[0]=0; mValues[1]=0; mValues[2]=0; mValues[3]=0;
        fn_801C1F94(mpPlayers,0,sizeof(mpPlayers));
    }
    Object_80039F5C *mpPlayers[3];
    int mValues[4];
};
struct Stats_8005CAE4 {
    Stats_8005CAE4() {
        mValues[0]=0; mValues[1]=0; mValues[2]=0; mValues[3]=0;
        fn_801C1F94(mpPlayers,0,sizeof(mpPlayers));
    }
    Object_80039F5C *mpPlayers[4];
    int mValues[4];
};
struct Args_8005F8B4;
extern "C" {
void fn_8005F8B4(Args_8005F8B4 *p);
void fn_8005F8F0(void);
void fn_8005F900(int *pHome);
int fn_8002568C(void);
int fn_8002B5B0(void);
int fn_800A8F94(void);
int fn_800A8EA4(int team);
struct Args_80055540;
int fn_80055540(int,Args_80055540 *);
void fn_80064F58(unsigned short,unsigned short,int,unsigned int,int *,int);
int fn_80178EE0(int team);
int fn_80178EA0(int team);
int fn_80155130(Class_80148A58 *,int,int);
int fn_80178D70(int team);
int fn_8007CB6C(int team);
void fn_8014F3E4(Class_80148A58 *,int,Stats_8005C4A4 *);
void fn_8014BA20(Class_80148A58 *,int,Stats_8005C844 *);
void fn_8014CCE8(Class_80148A58 *,int,Stats_8005CAE4 *);
void fn_80155CF0(Class_80148A58 *,int,int *,int *);
void fn_80155C44(Class_80148A58 *,int,int,Record_8005CE10 *);
int fn_80155D38(Class_80148A58 *,int);

void fn_8005BA64(Arg_8018399C *p) {fn_801C2EF0(p->pParams->mpText,"Name: FIX ME",p->pParams->mLength);}
void fn_8005BA98(Arg_8018399C *p) {fn_801C2EF0(p->pParams->mpText,"Name: FIX ME",p->pParams->mLength);}
void fn_8005BACC(Arg_8018399C *p,int *pValue,Arg_8018399C *pOther) {fn_8005BA64(p);fn_8005BA98(pOther);*pValue=0;}
void fn_8005BB0C(Arg_8018399C *p,int *a,int *b,int *c) {fn_8005BA64(p);*a=0;*b=0;*c=0;}
void fn_8005BB50(Arg_8018399C *p,int *a,int *b) {fn_8005BA64(p);*a=0;*b=0;}
int fn_8005BB8C(void) {
    int value=0;
    if(!lbl_803EA5A8) {
        if(fn_8007984C(fn_800785C0())) {switch(fn_8002B5C8()) {case 0:value=1;break;case 1:value=2;break;case 2:value=3;break;}}
    }
    return value;
}
void fn_8005BC10(int value) {
    if(!fn_8005900C()) {int a=fn_80025508();int b=fn_8002568C();fn_8002B5D0(a,b);}
    else {fn_8002B5D0(0,0);fn_80059020();}
    int args[2];args[0]=fn_8002B5B0()==0;args[1]=value;
    fn_80064F58(3,10,-1,2,args,0);
}
int fn_8005BCA8(unsigned int id,Arg_8018399C *p,int unused,int *result) {
    switch(id) {
    case 0x80000001:if(!lbl_803EA5A8)fn_8005B55C(p[0].pi);else fn_8005F900(p[0].pi);break;
    case 0x80000002:if(!lbl_803EA5A8)fn_8005B5D8(p[0].i);else fn_8005F8F0();break;
    case 0x80000003:if(!lbl_803EA5A8)fn_8005B9FC(p[0].pi,(Params_80005284 **)(p[1].i+(*p[1].pi+1)*4));break;
    case 0x80000004:if(!lbl_803EA5A8)fn_8005BACC(p,p[1].pi,p+2);break;
    case 0x80000005:if(!lbl_803EA5A8)fn_8005BB0C(p,p[1].pi,p[2].pi,p[3].pi);break;
    case 0x80000006:if(!lbl_803EA5A8)fn_8005BB50(p+1,p[1].pi,p[2].pi);break;
    case 0x80000007:if(lbl_803EA5A8)fn_8005F8B4((Args_8005F8B4 *)p);break;
    case 0x80000008:*result=fn_8005BB8C();break;
    default:return 0;
    }
    return 1;
}
void fn_8005BE54(unsigned char value) {lbl_803EA5A8=value;}
int fn_8005BE5C(int value) {
    if(lbl_803EA5B0==3) {
        lbl_803EA5B0=value;
        switch(value) {
        case 0:fn_80218FC4(lbl_803EB688,3,9,0,0);lbl_803EA5AC=0;return 1;
        case 1:fn_80218FC4(lbl_803EB688,3,12,0,0);lbl_803EA5AC=0;return 1;
        case 2:fn_80218FC4(lbl_803EB688,3,23,0,0);lbl_803EA5AC=0;return 1;
        }
    }
    return 0;
}
void fn_8005BF18(void) {fn_8021D7B8(lbl_803EB688,0x8000001C,0,0);lbl_803EA5AC=4;lbl_803EA5B0=3;}
void fn_8005BF5C(void) {fn_8021D7B8(lbl_803EB688,0x80000029,0,0);lbl_803EA5AC=2;}
void fn_8005BF98(void) {fn_8021D7B8(lbl_803EB688,0x8000002A,0,0);lbl_803EA5AC=0;}
int fn_8005BFD4(void) {return lbl_803EA5AC;}
int fn_8005BFDC(int group,unsigned int id,Arg_8018399C *p,int unused,int *result) {
    if(id==0x80000002) {
        if(lbl_803EA5AC==0) {lbl_803EA5AC=1;return 1;}
        if(lbl_803EA5AC==2) {lbl_803EA5AC=3;return 1;}
    } else {
        switch(group) {
        case 9:return fn_80055540(id,(Args_80055540 *)p);
        case 12:if(id==0x80000003) {*result=fn_800A8EA4(fn_800A8F94())==2;}return 1;
        case 23:return 1;
        }
    }
    return 0;
}
int fn_8005C0C0(unsigned int id,Arg_8018399C *,int,int *) {
    if(id==0x80000001)return 1;
    if(id!=0x80000002)return 0;
    if(lbl_803EA5B4) {
        fn_800C1CA0();if(fn_8017F584()==8) {fn_8017833C(1);fn_80178354(1);}lbl_803EA5B4=0;
    }
    fn_800652A8();return 1;
}
void fn_8005C144(int team,char *text,int size) {int a=fn_80178EE0(team);int b=fn_80178EA0(team);fn_801C2D88(text,size,"%d for %d",a,b);}
void fn_8005C1A4(int team,unsigned char index,int *color) {
    fn_8017E570(fn_80155130(fn_80148A58(),team,index),(unsigned char *)(color+0),(unsigned char *)(color+1),(unsigned char *)(color+2));
}
int fn_8005C1F4(int team,unsigned char index,char *name,int nameSize,char *text,unsigned char size,char *first,char *second,char *third,char *fourth,unsigned char firstSize,unsigned char secondSize) {
    Object_80039F5C *p=fn_80039F5C(team,index);int result=0;
    *name=0;*first=0;*second=0;*third=0;*fourth=0;*text=0;
    if(p && p->mUnknown9[2]) {
        fn_80188248((Object_80056584 *)p,name,nameSize);
        fn_80148A58()->vfn_20(team,index,0,first,firstSize,second,secondSize);
        fn_80148A58()->vfn_20(team,index,1,third,firstSize,fourth,secondSize);
        fn_80148A58()->vfn_18(team,index,text,size);
        result=fn_80180EF8(p->mUnknown2908);
    }
    return result;
}
int fn_8005C338(unsigned int id,Arg_8018399C *p,int unused,int *result) {
    switch(id) {
    case 0x80000001:fn_80187D10();if(p[0].i==1)fn_800C1CA0();fn_800652A8();break;
    case 0x80000002:fn_8005C144((unsigned char)p[0].i,p[1].pParams->mpText,p[1].pParams->mLength);break;
    case 0x80000003:fn_8005C1A4((unsigned char)p[0].i,(unsigned char)p[1].i,(int *)(p[2].i+(*p[2].pi+1)*4));break;
    case 0x80000004:*result=fn_8005C1F4((unsigned char)p[0].i,(unsigned char)p[1].i,p[2].pParams->mpText,p[2].pParams->mLength,p[3].pParams->mpText,(unsigned char)p[3].pParams->mLength,p[4].pParams->mpText,p[5].pParams->mpText,p[6].pParams->mpText,p[7].pParams->mpText,(unsigned char)p[4].pParams->mLength,(unsigned char)p[5].pParams->mLength);break;
    case 0x80000005:*result=fn_80178D70((unsigned char)p[0].i);break;
    case 0x80000006:break;
    default:return 0;
    }return 1;
}
void fn_8005C4A4(int team,char *name,int nameSize,char *first,int firstSize,char *time,int timeSize,char *last,int lastSize,int *color,int unused,char *text,unsigned char textSize,int *result) {
    Stats_8005C4A4 stats;fn_8014F3E4(fn_80148A58(),team,&stats);
    unsigned int minutes=stats.mTime/60,seconds=stats.mTime%60;
    fn_801C2D88(first,firstSize,"%d",stats.mUnknown4);
    if(seconds<10)fn_801C2D88(time,timeSize,"%d:0%d",minutes,seconds);else fn_801C2D88(time,timeSize,"%d:%d",minutes,seconds);
    fn_801C2D88(last,lastSize,"%d",stats.mUnknown12);
    if(!stats.mpPlayer) {*name=0;*result=0;}
    else {
        fn_80188248((Object_80056584 *)stats.mpPlayer,name,nameSize);
        unsigned char foundTeam=0,foundIndex=0;bool found=false;
        for(unsigned char t=0;t<2 && !found;t++)for(unsigned char i=0;i<6 && !found;i++) {
            Object_80039F5C *p=fn_80039F5C(t,i);
            if((short)stats.mpPlayer->mUnknown2908==(short)p->mUnknown2908) {found=true;foundTeam=t;foundIndex=i;}
        }
        fn_80148A58()->vfn_18(foundTeam,foundIndex,text,textSize);
        *result=fn_80180EF8(stats.mpPlayer->mUnknown2908);
    }
    unsigned char r=0,g=0,b=0;fn_8017E570(stats.mColor,&r,&g,&b);color[0]=r;color[2]=b;color[1]=g;
}
int fn_8005C6EC(unsigned int id,Arg_8018399C *p,int unused,int *result) {
    switch(id) {
    case 0x80000001:fn_8005C4A4((unsigned char)p[0].i,p[2].pParams->mpText,p[2].pParams->mLength,p[3].pParams->mpText,p[3].pParams->mLength,p[5].pParams->mpText,p[5].pParams->mLength,p[7].pParams->mpText,p[7].pParams->mLength,(int *)(p[1].i+(*p[1].pi+1)*4),p[1].pi[1],p[8].pParams->mpText,(unsigned char)p[8].pParams->mLength,result);fn_801C2EF0(p[4].pParams->mpText,"Time of Possession",p[4].pParams->mLength);fn_801C2EF0(p[6].pParams->mpText,"Tackles",p[6].pParams->mLength);break;
    case 0x80000002:*result=6;break;
    case 0x80000003:fn_80187D10();if(p[0].i==1)fn_800C1CA0();fn_800652A8();break;
    case 0x80000004:break;
    default:return 0;
    }return 1;
}
void fn_8005C844(int team,int *value,char *score,char *first,char *second,char *third,int *values,unsigned char scoreSize,unsigned char textSize) {
    Stats_8005C844 stats;fn_8014BA20(fn_80148A58(),team,&stats);
    values[2]=stats.mValues[3];values[0]=stats.mValues[1];values[1]=stats.mValues[2];
    fn_801C2D88(score,scoreSize,"%d",stats.mValues[0]);*value=fn_8007CB6C(team!=0);
    fn_80148A58()->vfn_19(team,0,first,textSize);fn_80148A58()->vfn_19(team,1,second,textSize);fn_80148A58()->vfn_19(team,2,third,textSize);
}
int fn_8005C994(unsigned int id,Arg_8018399C *p,int unused,int *result) {
    if(id==0x80000003) {
        int n=*p[3].pi;Params_80005284 **texts=(Params_80005284 **)p[3].pi;
        fn_8005C844((unsigned char)p[0].i,p[1].pi,p[2].pParams->mpText,texts[n+1]->mpText,texts[n+2]->mpText,texts[n+3]->mpText,(int *)(p[4].i+(*p[4].pi+1)*4),(unsigned char)p[2].pParams->mLength,(unsigned char)texts[n+1]->mLength);
        n=*p[5].pi;texts=(Params_80005284 **)p[5].pi;
        fn_801C2EF0(texts[n+1]->mpText,"TDs",texts[n+1]->mLength);fn_801C2EF0(texts[n+2]->mpText,"Fumble Recs",texts[n+2]->mLength);fn_801C2EF0(texts[n+3]->mpText,"INTs",texts[n+3]->mLength);
    }else if(id==0x80000004) {fn_80187D10();if(p[0].i==1)fn_800C1CA0();fn_800652A8();}else if(id!=0x80000001)return 0;
    return 1;
}
void fn_8005CAE4(int team,int *value,char *score,char *first,char *second,char *third,unsigned char scoreSize,unsigned char textSize,int *values) {
    Stats_8005CAE4 stats;
    Object_8007A334 cursor;
    fn_8014CCE8(fn_80148A58(),team,&stats);
    fn_801C2D88(score,scoreSize,"%d",stats.mValues[0]);*value=fn_8007CB6C(team!=0);
    fn_80148A58()->vfn_19(team,0,first,textSize);fn_80148A58()->vfn_19(team,1,second,textSize);fn_80148A58()->vfn_19(team,2,third,textSize);
    values[0]=stats.mValues[1];values[2]=stats.mValues[3];values[1]=stats.mValues[2];
}
int fn_8005CC50(unsigned int id,Arg_8018399C *p,int unused,int *result) {
    if(id==0x80000003) {
        fn_8005CAE4((unsigned char)p[0].i,p[1].pi,p[2].pParams->mpText,p[3].pParams->mpText,p[4].pParams->mpText,p[5].pParams->mpText,(unsigned char)p[2].pParams->mLength,(unsigned char)p[3].pParams->mLength,(int *)(p[6].i+(*p[6].pi+1)*4));
        int n=*p[7].pi;Params_80005284 **texts=(Params_80005284 **)p[7].pi;
        fn_801C2EF0(texts[n+1]->mpText,"TDs",texts[n+1]->mLength);fn_801C2EF0(texts[n+2]->mpText,"Tackles",texts[n+2]->mLength);fn_801C2EF0(texts[n+3]->mpText,"INTs",texts[n+3]->mLength);
    }else if(id==0x80000004) {fn_80187D10();if(p[0].i==1)fn_800C1CA0();fn_800652A8();}else if(id!=0x80000001)return 0;
    return 1;
}
void fn_8005CD8C(int team,int *other,char *text,int size) {
    int value;fn_80155CF0(fn_80148A58(),team,other,&value);fn_801C2D88(text,size,"%d",value);
}
void fn_8005CE10(int team,int index,char *ordinal,int ordinalSize,char *text,int size) {
    Record_8005CE10 record;fn_80155C44(fn_80148A58(),team,index,&record);
    unsigned int value=record.mOrdinal;
    Object_80039F5C *p=fn_8003AC84(record.mPlayer),*other=fn_8003AC84(record.mOther);
    if(record.mEvent==11) {*ordinal=0;*text=0;return;}
    unsigned int rem=value%10;
    if(value-11<9 || rem>3 || rem==0)fn_801C2D88(ordinal,ordinalSize,"%dth Possession",value);
    else if(rem==1)fn_801C2D88(ordinal,ordinalSize,"%dst Possession",value);
    else if(rem==2)fn_801C2D88(ordinal,ordinalSize,"%dnd Possession",value);
    else if(rem==3)fn_801C2D88(ordinal,ordinalSize,"%drd Possession",value);
    char event[32],player[32],conversion[32],outcome[32];
    switch(record.mEvent) {case 0:fn_801C2E18(event,"Receiving TD ");break;case 1:fn_801C2E18(event,"Rushing TD ");break;case 5:fn_801C2E18(event,"Safety ");break;case 6:fn_801C2E18(event,"Interception ");break;case 7:fn_801C2E18(event,"Fumble Recovered ");break;case 8:fn_801C2E18(event,"Turnover On Downs");break;}
    if(!p)*player=0;else fn_801C2E18(player,"by %s",p->mUnknown2927+21);
    if(record.mConversion==9) {*conversion=0;*outcome=0;}
    else {
        switch(record.mConversion) {case 2:if(!record.mFlag)fn_801C2E18(conversion,"Defensive TD ");else fn_801C2E18(conversion,"Defensive Conversion ");break;case 3:fn_801C2E18(conversion,"One Point Conversion ");break;case 4:fn_801C2E18(conversion,"Two Point Conversion ");break;}
        if(!record.mFlag && record.mConversion!=2)fn_801C2E18(outcome,"Failed");else fn_801C2E18(outcome,"by %s",other->mUnknown2927+21);
    }
    fn_801C2D88(text,size,"%s%s\n%s%s",event,player,conversion,outcome);
}
int fn_8005D1E4(unsigned int id,Arg_8018399C *p,int unused,int *result) {
    switch(id) {
    case 0x80000001:if(p[0].i==1)fn_800C1CA0();fn_800652A8();break;
    case 0x80000002:fn_8005CD8C((unsigned char)p[0].i,p[1].pi,p[2].pParams->mpText,p[2].pParams->mLength);*result=fn_80155D38(fn_80148A58(),(unsigned char)p[0].i);break;
    case 0x80000003:fn_8005CE10((unsigned char)p[0].i,(unsigned char)p[1].i,p[2].pParams->mpText,p[2].pParams->mLength,p[3].pParams->mpText,p[3].pParams->mLength);break;
    default:return 0;
    }return 1;
}
void fn_8005D2C8(unsigned char value) {lbl_803EA5B5=value;}
int fn_8005D2D0(unsigned int id,Arg_8018399C *p,int unused,int *result) {
    switch(id) {
    case 0x80000001: {
        char name[20]={0};const char *extra="";int size=p[1].pParams->mLength;char *text=p[1].pParams->mpText;
        *p[0].pi=fn_800A3444();
        switch(fn_800A3444()) {case 0:fn_801C2E18(name,"Randall Cunningham");break;case 1:fn_801C2E18(name,"Mike Singletary");break;case 2:fn_801C2E18(name,"Cris Carter");break;case 3:fn_801C2E18(name,"Jack Lambert");break;case 4:fn_801C2E18(name,"Anthony Munoz");break;case 5:fn_801C2E18(name,"Darrell Green");break;case 6:fn_801C2E18(name,"Mean Joe Greene");break;case 7:fn_801C2E18(name,"Bo Jackson");break;case 8:fn_801C2E18(name,"Joey Browner");break;case 9:fn_801C2E18(name,"Sterling Sharpe");break;default:fn_801C2E18(name,"Super Secret");break;}
        if(lbl_803EA5B5) {lbl_803EA5B5=0;extra="\n\nYou have unlocked the NFL Legends Team!";}
        fn_801C2D88(text,size,"You have unlocked\n%s for\nthe Pickup Pool!%s",name,extra);break;
    }
    case 0x80000002:break;
    case 0x80000003:fn_800652A8();break;
    default:return 0;
    }return 1;
}
}
