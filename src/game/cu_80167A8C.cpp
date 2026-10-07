#include "game/fn_801EF390.h"
#include "game/Desc_80169DF8.h"
#include "game/Class_80148A58.h"
#include "game/fn_8016871C.h"
#include "game/Object_8007A334.h"
#include "game/fn_800670B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80238174.h"

#include "game/Team_80167A8C.h"

/* Allocated through fn_80238174 under the id 'plbk' (fn_801681A8). */
struct Object_80167A8C {
    unsigned int mUnknown0;
    Team_80167A8C mUnknown4[2];
    char mUnknownD2EC[0x28];
    unsigned char mUnknownD314[43][4];
};



extern "C" {
int fn_80066D74(unsigned int id, int a, int b, int c, int d, int e);
void fn_80066DC8(unsigned int id, int a);
int fn_800674E0(int tag, int a, int *pResult);
int fn_800675B4(int tag, int a, int b);
void fn_80067A4C(int team, int tag, int kind, int *pResult);
int fn_80067A8C(int tag, int a, int b);
void fn_80087CBC(Object_8007A334 *pCursor);
void fn_80087CFC(Object_8007A334 *pCursor);
int fn_80087D1C(Object_8007A334 *pCursor, int key);
unsigned char fn_80087DA4(Object_8007A334 *pCursor, int column);
unsigned char fn_8008973C(int index);
int fn_800B508C(unsigned char index);
int fn_800B65A0(int unknown);
int fn_800BA6F8(void);
QueryCursor fn_800C0750(unsigned char index, unsigned short *pValues);
void fn_800C07C4(QueryCursor cursor);
void fn_800C07F0(QueryCursor cursor, unsigned char index, unsigned short *pValues);
int fn_80164ED8(Object_800670B4 *pObject, Record_80067338 *pRecord, int index, unsigned char *pOut, unsigned char flag);
int fn_80165000(Object_800670B4 *pObject, Record_80067338 *pRecord, int index, unsigned char *pOut, unsigned char flag);
void fn_80167794(signed char team, int a, int b);
void fn_80167910(Point_80167910 *pPoints, int count);
void fn_8016BAD8(int team);
int fn_801485D4(void);
int fn_801486A0(void);
int fn_80177F70(void);
Point_80167910 fn_80177FE0(void);
int fn_80178308(void);
float fn_80178A2C(void);
int fn_80178E10(void);
void fn_80179144(int a);
void fn_8017916C(void);
int fn_801D34D0(void *pDest, int size, int value, int width);
void fn_801F9FA4(int tag, int index, int column);
int fn_801FA038(int tag, int index, int column);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
}

static Object_80167A8C *lbl_803ECAF4;

extern "C" {
void fn_801679B4(void);
int fn_801679B8(void *p, void *q);
void fn_801679F4(int team, int kind);
void fn_80167A40(int tag, int team, unsigned char kind, unsigned int index, Object_800670B4 *pObject);
void fn_80167A6C(int tag, int handle, unsigned int index, Team_80167A8C *pTeam, Object_8006719C *pObject);
void fn_80167A8C(int team, unsigned int a, unsigned int b, int c);
void fn_80167AD8(int team);
void fn_80167B70(int team, int flag);
void fn_80167C1C(int team);
void fn_80167C8C(int team, int a, int flag);
void fn_80167D1C(int a, int b, int c, int d, int e, int f);
void fn_80167EA0(int team);
void fn_80167FF0(int team);
void fn_801681A8(void);
void fn_80168210(void);
void fn_80168264(void);
void fn_80168324(int a, int b, int c, int d, int e, int f, int g, int h);
void fn_80168418(int a, int b, int c, int d, int e, int f, int g);
void fn_801684B8(int a);
void fn_80168640(int team, int kind);
Object_800670B4 *fn_80168708(int team);
Record_80067338 *fn_80168730(int team);
void fn_80168744(int team, unsigned int a, unsigned int b, unsigned int c);
void fn_801687E4(int team, int a, int b, int c);
unsigned int fn_80168898(int team);
unsigned int fn_801688AC(int team);
unsigned int fn_801688C0(int team);
unsigned int fn_801688D4(void);
void fn_801688E0(unsigned int flags);
void fn_801688F4(unsigned int flags);
void fn_80168908(int team, unsigned int index);
Record_80067338 *fn_8016898C(int team, int index);
void fn_801689AC(int team);
void fn_80168A14(int team);
void GetPlayerPosition(unsigned char team, int index, float *pX, float *pY);
void fn_80168A7C(int team, int kind, unsigned int a, unsigned int b, unsigned int c);
void fn_80168B04(int team, int a);
void fn_80168B5C(int team, int kind);
int fn_80168C10(int team, int a, int b);
void fn_80168C40(void);
void fn_80168D10(int which, int team, int a, int b, int c);
void fn_80168D74(int team);
unsigned int fn_80168D98(int team, int a, int b);
int fn_80168E00(int team, int index, unsigned char *pOut);
int fn_80168E54(int team, int index, unsigned char *pOut);
int fn_80168EA8(int team);
Team_80167A8C *fn_80168EBC(int team);
}

void fn_80167910(Point_80167910 *pPoints, int count)
{
    while (count--) {
        pPoints[count].mX = (int)pPoints[count].mX - 100;
        pPoints[count].mY = (int)pPoints[count].mY - 150;
    }
}

void fn_801679B4(void)
{
}

int fn_801679B8(void *p, void *q)
{
    if (q == 0) {
        return 0;
    }
    return fn_80238258(p, q, sizeof(Object_80167A8C));
}

void fn_801679F4(int team, int kind)
{
    unsigned char index = team;

    fn_80168640(index, kind);
    fn_80167FF0(index);
    fn_80168908(index, 0);
    fn_80167EA0(index);
}

void fn_80167A40(int tag, int team, unsigned char kind, unsigned int index, Object_800670B4 *pObject)
{
    fn_800670B4(tag, kind, index, pObject);
}

void fn_80167A6C(int tag, int handle, unsigned int index, Team_80167A8C *pTeam, Object_8006719C *pObject)
{
    fn_8006719C(tag, handle, index, pTeam, pObject);
}

void fn_80167A8C(int team, unsigned int a, unsigned int b, int c)
{
    Team_80167A8C *pTeam = &lbl_803ECAF4->mUnknown4[team];

    pTeam->mUnknown20.mUnknown0 = a;
    pTeam->mUnknown20.mUnknown4 = b;
    fn_80167AD8(team);
    fn_80167C1C(team);
}

void fn_80167AD8(int team)
{
    int tag = lbl_803ECAF4->mUnknown4[team].mUnknown8;
    Team_80167A8C *pTeam = &lbl_803ECAF4->mUnknown4[team];
    unsigned int index = pTeam->mUnknown20.mUnknown0;
    Object_800670B4 *pObject = &pTeam->mUnknown20.mUnknown14;
    unsigned int flags = fn_801688D4();

    fn_801688E0(3);
    fn_80167A40(tag, team, lbl_803ECAF4->mUnknown4[team].mUnknownC, index, pObject);
    pTeam->mUnknown14 = fn_80067120(tag, pTeam->mUnknown20.mUnknown14.mUnknown0);
    fn_801688F4(3);
    fn_801688E0(flags);
}

void fn_80167B70(int team, int flag)
{
    int tag = lbl_803ECAF4->mUnknown4[team].mUnknown8;
    Team_80167A8C *pTeam = &lbl_803ECAF4->mUnknown4[team];
    Object_8006719C *pObject = &pTeam->mUnknown20.mUnknown14.mUnknown8;
    unsigned int index = pTeam->mUnknown20.mUnknown4;
    unsigned int flags = fn_801688D4();

    fn_801688E0(7);
    if (flag) {
        fn_801688E0(8);
    }
    fn_80167A6C(tag, pTeam->mUnknown20.mUnknown14.mUnknown0, index, pTeam, pObject);
    fn_801688F4(15);
    fn_801688E0(flags);
    fn_80167910(pTeam->mUnknown693C, 7);
    pTeam->mUnknown18 = fn_800672BC(tag, pTeam->mUnknown20.mUnknown14.mUnknown8.mUnknown0);
}

void fn_80167C1C(int team)
{
    int tag = lbl_803ECAF4->mUnknown4[team].mUnknown8;
    Team_80167A8C *pTeam = &lbl_803ECAF4->mUnknown4[team];

    fn_80167A6C(tag, pTeam->mUnknown20.mUnknown14.mUnknown0, pTeam->mUnknown20.mUnknown4, pTeam,
                &pTeam->mUnknown20.mUnknown14.mUnknown8);
    fn_80167910(pTeam->mUnknown693C, 7);
    pTeam->mUnknown18 = fn_800672BC(tag, pTeam->mUnknown20.mUnknown14.mUnknown8.mUnknown0);
}

void fn_80167C8C(int team, int a, int flag)
{
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        if (flag) {
            fn_80168D10(1, team, i, 0xFFFF, 0);
        } else {
            fn_80168D10(0, team, i, 0xFFFF, 0);
        }
    }
}

void fn_80167D1C(int a, int b, int c, int d, int e, int f)
{
    if (a != 0x3FF) {
        int first;
        int second;

        lbl_803ECAF4->mUnknown4[0].mUnknown0 = 0x31544250;
        lbl_803ECAF4->mUnknown4[0].mUnknown4 = 0x31444250;
        first = 2;
        second = 1;
        if (fn_801485D4()) {
            first = fn_80148A58()->mUnknown0;
            second = fn_80148A58()->mUnknown4;
        }
        fn_80066D74(0x31544250, first, 4, 0, 0, 1);
        fn_80066D74(0x31444250, second, 4, 0, 0, 1);
    } else {
        lbl_803ECAF4->mUnknown4[0].mUnknown4 = lbl_803ECAF4->mUnknown4[0].mUnknown0 = -1;
    }
    if (b != 0x3FF) {
        lbl_803ECAF4->mUnknown4[1].mUnknown0 = 0x31544250;
        lbl_803ECAF4->mUnknown4[1].mUnknown4 = 0x31444250;
    } else {
        lbl_803ECAF4->mUnknown4[1].mUnknown4 = lbl_803ECAF4->mUnknown4[1].mUnknown0 = -1;
    }
    fn_801FCE10(0, "use \x8c create \x8b index on 'LASP' order by 'LASP' asc\n", 0x31544250, 0x4C415350);
    fn_801FCE10(0, "use \x8c create \x8b index on 'SYLP' order by 'LYLP' asc and 'osop' asc\n", 0x31544250, 0x4C594C50);
    fn_801FCE10(0, "use \x8c create \x8b index on 'LASP' order by 'LASP' asc\n", 0x31444250, 0x4C415350);
    fn_801FCE10(0, "use \x8c create \x8b index on 'SYLP' order by 'LYLP' asc and 'osop' asc\n", 0x31444250, 0x4C594C50);
}

void fn_80167EA0(int team)
{
    unsigned int flags = fn_801688D4();
    int tag;
    Team_80167A8C *pTeam;
    State_80167A8C *pState;
    Object_800670B4 *pObject;
    Object_8006719C *pEntry;
    Record_80067338 *pRecord;

    fn_801688E0(3);
    tag = lbl_803ECAF4->mUnknown4[team].mUnknown8;
    pTeam = &lbl_803ECAF4->mUnknown4[team];
    pState = &pTeam->mUnknown20;
    pObject = &pState->mUnknown14;
    fn_80167A40(tag, team, lbl_803ECAF4->mUnknown4[team].mUnknownC, pState->mUnknown0, pObject);
    pEntry = &pObject->mUnknown8;
    pRecord = &pState->mUnknownCF8;
    fn_801688F4(3);
    fn_80167A6C(tag, pObject->mUnknown0, pState->mUnknown4, &lbl_803ECAF4->mUnknown4[team], pEntry);
    fn_801688E0(3);
    fn_8006723C(tag, fn_80067338(tag, pEntry->mUnknown0, pState->mUnknown8, pRecord), pTeam, pEntry);
    if ((pObject->mUnknown8.mUnknown14 & 1) && (pRecord->mUnknown18 & 1)) {
        pEntry->mUnknownF = pState->mUnknown10;
    } else {
        pEntry->mUnknownF = 0;
    }
    fn_801688F4(3);
    fn_801688E0(flags);
    if (fn_80178308() == team && fn_800B65A0(team) == 0xFF && !fn_800BA6F8() &&
        (!fn_801485D4() || fn_801486A0() != 2)) {
        fn_8016BAD8(team);
    }
}

void fn_80167FF0(int team)
{
    unsigned int flags = fn_801688D4();
    int count = lbl_803ECAF4->mUnknown4[team].mUnknown20.mUnknown14.mUnknown8.mUnknown4;
    int tag;
    int kind;
    unsigned char swap;
    unsigned int i;

    if (fn_80178308() == team) {
        tag = 0x31544250;
        kind = 1;
    } else {
        tag = 0x31444250;
        kind = 11;
    }
    swap = fn_80168708(team)->mUnknown8.mUnknownF;
    for (i = 0; i <= 3; i++) {
        State_80167A8C *pState = &lbl_803ECAF4->mUnknown4[team].mUnknown2D2C[i];
        unsigned char value;
        Team_80167A8C *pOwner;

        if (swap) {
            if (i == 3) {
                value = lbl_803ECAF4->mUnknownD314[count - 1][2];
            } else if (i == 2) {
                value = lbl_803ECAF4->mUnknownD314[count - 1][3];
            } else {
                value = lbl_803ECAF4->mUnknownD314[count - 1][i];
            }
        } else {
            value = lbl_803ECAF4->mUnknownD314[count - 1][i];
        }
        fn_801688E0(3);
        pState->mUnknown10 = 0;
        pState->mUnknown8 = value;
        pState->mUnknown0 = 0;
        pState->mUnknown4 = 0;
        pState->mUnknownC = value / 3;
        fn_800670B4(tag, kind, 0, &pState->mUnknown14);
        fn_801688F4(3);
        pOwner = fn_80168EBC(0);
        fn_8006719C(tag, pState->mUnknown14.mUnknown0, pState->mUnknown4, pOwner, &pState->mUnknown14.mUnknown8);
        fn_801688E0(3);
        fn_8006723C(tag, fn_80067338(tag, pState->mUnknown14.mUnknown8.mUnknown0, pState->mUnknown8, &pState->mUnknownCF8),
                    pOwner, &pState->mUnknown14.mUnknown8);
        pState->mUnknown14.mUnknown8.mUnknownF = swap;
        fn_801688F4(3);
        fn_801688E0(flags);
    }
    lbl_803ECAF4->mUnknown4[team].mUnknown1C = 4;
}

void fn_801681A8(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803ECAF4, sizeof(Object_80167A8C), 0, 0x706C626B);

    fn_80238234(pHandle, 0, 0, 0, fn_801679B8);
    fn_802381E0(pHandle);
}

void fn_80168210(void)
{
    if (lbl_803ECAF4) {
        fn_801D34D0(lbl_803ECAF4, sizeof(Object_80167A8C), 0, 4);
        lbl_803ECAF4->mUnknown4[1].mUnknown4 = lbl_803ECAF4->mUnknown4[1].mUnknown0 =
            lbl_803ECAF4->mUnknown4[0].mUnknown4 = lbl_803ECAF4->mUnknown4[0].mUnknown0 = -1;
    }
}

void fn_80168264(void)
{
    if (fn_80178E10()) {
        Object_8007A334 cursor;
        unsigned int key;

        fn_80087CBC(&cursor);
        for (key = 1; key <= 43; key++) {
            if (fn_80087D1C(&cursor, key)) {
                unsigned int i;

                for (i = 0; i <= 3; i++) {
                    lbl_803ECAF4->mUnknownD314[key - 1][i] = fn_80087DA4(&cursor, i);
                }
            }
        }
        fn_80087CFC(&cursor);
    }
}

void fn_80168324(int a, int b, int c, int d, int e, int f, int g, int h)
{
    fn_801684B8(h);
    fn_80167D1C(b, c, d, e, f, g);
    fn_80167C8C(0, d, 1);
    fn_80167C8C(1, e, 1);
    fn_80167C8C(0, f, 0);
    fn_80167C8C(1, g, 0);
    if (h) {
        Desc_80169DF8 desc;

        desc.mUnknown0 = fn_801EF390((void *)a, 4, 1);
        desc.mUnknown4 = (short *)lbl_803ECAF4->mUnknownD2EC;
        desc.mUnknown8 = fn_80169308;
        desc.mUnknownC = fn_801694C8;
        fn_80169DF8(&desc);
    }
}

void fn_80168418(int a, int b, int c, int d, int e, int f, int g)
{
    fn_801684B8(g);
    fn_80167D1C(a, b, c, d, e, f);
    fn_80167C8C(0, c, 1);
    fn_80167C8C(1, d, 1);
    fn_80167C8C(0, e, 0);
    fn_80167C8C(1, f, 0);
}

void fn_801684B8(int a)
{
    if (!fn_801FA038(0x31544250, 0x4C415350, 0x4C415350)) {
        fn_801F9FA4(0x31544250, 0x4C415350, 0x4C415350);
    }
    if (!fn_801FA038(0x31544250, 0x53594C50, 0x4C594C50)) {
        fn_801F9FA4(0x31544250, 0x53594C50, 0x4C594C50);
    }
    if (!fn_801FA038(0x31444250, 0x4C415350, 0x4C415350)) {
        fn_801F9FA4(0x31444250, 0x4C415350, 0x4C415350);
    }
    if (!fn_801FA038(0x31444250, 0x53594C50, 0x4C594C50)) {
        fn_801F9FA4(0x31444250, 0x53594C50, 0x4C594C50);
    }
    if (lbl_803ECAF4->mUnknown4[0].mUnknown4 != -1) {
        fn_80066DC8(0x31444250, fn_8008973C(1));
        lbl_803ECAF4->mUnknown4[0].mUnknown4 = -1;
    }
    if (lbl_803ECAF4->mUnknown4[0].mUnknown0 != -1) {
        fn_80066DC8(0x31544250, fn_8008973C(0));
        lbl_803ECAF4->mUnknown4[0].mUnknown0 = -1;
    }
}

void fn_80168640(int team, int kind)
{
    int tag;

    switch (kind) {
    case 1:
        lbl_803ECAF4->mUnknown4[team].mUnknown8 = lbl_803ECAF4->mUnknown4[team].mUnknown0;
        break;
    case 11:
        lbl_803ECAF4->mUnknown4[team].mUnknown8 = lbl_803ECAF4->mUnknown4[team].mUnknown4;
        break;
    }
    tag = lbl_803ECAF4->mUnknown4[team].mUnknown8;
    lbl_803ECAF4->mUnknown4[team].mUnknownC = kind;
    lbl_803ECAF4->mUnknown4[team].mUnknown20.mUnknown10 = 0;
    lbl_803ECAF4->mUnknown4[team].mUnknown10 = fn_80067038(tag, kind);
    fn_80167794(team, 0, -1);
    fn_80167A8C(team, 0, 0, 1);
}

Object_800670B4 *fn_80168708(int team)
{
    return &lbl_803ECAF4->mUnknown4[team].mUnknown20.mUnknown14;
}

Record_80067338 *fn_8016871C(int team)
{
    return &lbl_803ECAF4->mUnknown4[team].mUnknown20.mUnknownCF8;
}

Record_80067338 *fn_80168730(int team)
{
    return &lbl_803ECAF4->mUnknown4[team].mUnknown1E28.mUnknownCF8;
}

void fn_80168744(int team, unsigned int a, unsigned int b, unsigned int c)
{
    State_80167A8C *pState = &lbl_803ECAF4->mUnknown4[team].mUnknown20;

    if (a < lbl_803ECAF4->mUnknown4[team].mUnknown10) {
        pState->mUnknown0 = a;
    } else {
        pState->mUnknown0 = lbl_803ECAF4->mUnknown4[team].mUnknown10 - 1;
    }
    if (b < lbl_803ECAF4->mUnknown4[team].mUnknown14) {
        pState->mUnknown4 = b;
    } else {
        pState->mUnknown4 = lbl_803ECAF4->mUnknown4[team].mUnknown14 - 1;
    }
    if (c < lbl_803ECAF4->mUnknown4[team].mUnknown18) {
        pState->mUnknown8 = c;
    } else {
        pState->mUnknown8 = lbl_803ECAF4->mUnknown4[team].mUnknown18 - 1;
    }
    pState->mUnknownC = pState->mUnknown8 / 3;
}

void fn_801687E4(int team, int a, int b, int c)
{
    if (a == -1 && b == -1) {
        int mode = fn_80177F70();

        if (mode == 4 || mode == 6) {
            State_80167A8C *pState = &lbl_803ECAF4->mUnknown4[team].mUnknown20;
            Point_80167910 point;

            point = fn_80177FE0();

            if (mode == 6 || !(point.mY < fn_80178A2C() - 15.0f)) {
                pState->mUnknownC = 2;
            } else {
                pState->mUnknownC = 0;
            }
        }
    }
}

unsigned int fn_80168898(int team)
{
    State_80167A8C *pState = &lbl_803ECAF4->mUnknown4[team].mUnknown20;

    return pState->mUnknown4;
}

unsigned int fn_801688AC(int team)
{
    State_80167A8C *pState = &lbl_803ECAF4->mUnknown4[team].mUnknown20;

    return pState->mUnknown0;
}

unsigned int fn_801688C0(int team)
{
    State_80167A8C *pState = &lbl_803ECAF4->mUnknown4[team].mUnknown20;

    return pState->mUnknown8;
}

unsigned int fn_801688D4(void)
{
    return lbl_803ECAF4->mUnknown0;
}

void fn_801688E0(unsigned int flags)
{
    lbl_803ECAF4->mUnknown0 |= flags;
}

void fn_801688F4(unsigned int flags)
{
    lbl_803ECAF4->mUnknown0 &= ~flags;
}

void fn_80168908(int team, unsigned int index)
{
    Team_80167A8C *pTeam;
    State_80167A8C *pState;

    if (index >= lbl_803ECAF4->mUnknown4[team].mUnknown1C) {
        index = 0;
    }
    pTeam = &lbl_803ECAF4->mUnknown4[team];
    pState = &pTeam->mUnknown2D2C[index];
    pTeam->mUnknown20 = *pState;
}

Record_80067338 *fn_8016898C(int team, int index)
{
    return &lbl_803ECAF4->mUnknown4[team].mUnknown2D2C[index].mUnknownCF8;
}

void fn_801689AC(int team)
{
    Team_80167A8C *pTeam = &lbl_803ECAF4->mUnknown4[team];

    pTeam->mUnknown1E28 = pTeam->mUnknown20;
}

void fn_80168A14(int team)
{
    Team_80167A8C *pTeam = &lbl_803ECAF4->mUnknown4[team];

    pTeam->mUnknown20 = pTeam->mUnknown1E28;
}

void GetPlayerPosition(unsigned char team, int index, float *pX, float *pY)
{
    Team_80167A8C *pTeam = &lbl_803ECAF4->mUnknown4[team];

    if (pTeam->mUnknown20.mUnknown10 == 1) {
        index = pTeam->mUnknown20.mUnknown14.mUnknown8.mUnknown84[index].mUnknownB;
    }
    if (pX) {
        *pX = pTeam->mUnknown693C[index].mX;
        if (pTeam->mUnknown20.mUnknown10 == 1) {
            *pX *= -1.0f;
        }
    }
    if (pY) {
        *pY = pTeam->mUnknown693C[index].mY + 9.0f;
    }
}

void fn_80168A7C(int team, int kind, unsigned int a, unsigned int b, unsigned int c)
{
    State_80167A8C *pState = &lbl_803ECAF4->mUnknown4[team].mUnknown20;

    lbl_803ECAF4->mUnknown4[team].mUnknownF24 = lbl_803ECAF4->mUnknown4[team].mUnknown20;
    lbl_803ECAF4->mUnknown4[team].mUnknownC = kind;
    pState->mUnknown0 = a;
    pState->mUnknown4 = b;
    pState->mUnknown8 = c;
}

void fn_80168B04(int team, int a)
{
    int result[4];

    fn_800674E0(lbl_803ECAF4->mUnknown4[team].mUnknown8, a, result);
    fn_80168A7C(team, result[3], result[0], result[1], result[2]);
}

void fn_80168B5C(int team, int kind)
{
    int tag = lbl_803ECAF4->mUnknown4[team].mUnknown8;
    int result[4];

    if (fn_800B65A0(team) == 0xFF) {
        if (kind == 14) {
            fn_80179144(2);
            fn_8017916C();
        } else if (kind == 17) {
            fn_80179144(1);
            fn_8017916C();
        }
    }
    fn_80067A4C(team, tag, kind, result);
    lbl_803ECAF4->mUnknown4[team].mUnknownC = result[3];
    fn_80168A7C(team, result[3], result[0], result[1], result[2]);
}

int fn_80168C10(int team, int a, int b)
{
    return fn_80067A8C(lbl_803ECAF4->mUnknown4[team].mUnknown8, a, b);
}

void fn_80168C40(void)
{
    int team;

    for (team = 0; team <= 1; team++) {
        unsigned short values[7];
        QueryCursor cursor;

        fn_801679F4(team, 1);
        cursor = fn_800C0750(team, values);
        fn_800C07F0(cursor, team, values);
        fn_800C07C4(cursor);
        fn_800B508C(team);
    }
}

void fn_80168D10(int which, int team, int a, int b, int c)
{
    int tag;

    if (team == 0) {
        tag = which ? 0x31544250 : 0x31444250;
    } else {
        tag = which ? 0x32544250 : 0x32444250;
    }
    fn_800675B4(tag, a, b);
}

void fn_80168D74(int team)
{
    State_80167A8C *pState = &lbl_803ECAF4->mUnknown4[team].mUnknown20;

    pState->mUnknown10 = !pState->mUnknown10;
}

unsigned int fn_80168D98(int team, int a, int b)
{
    State_80167A8C *pState;

    fn_80168B04(team, a);
    fn_80167AD8(team);
    fn_80167B70(team, 1);
    pState = &lbl_803ECAF4->mUnknown4[team].mUnknown20;
    pState->mUnknownC = pState->mUnknown8 / 3;
    return pState->mUnknown8;
}

int fn_80168E00(int team, int index, unsigned char *pOut)
{
    Record_80067338 *pRecord = fn_8016871C(team);
    Object_800670B4 *pObject = fn_80168708(team);

    return fn_80164ED8(pObject, pRecord, index, pOut, pObject->mUnknown8.mUnknownF);
}

int fn_80168E54(int team, int index, unsigned char *pOut)
{
    Record_80067338 *pRecord = fn_8016871C(team);
    Object_800670B4 *pObject = fn_80168708(team);

    return fn_80165000(pObject, pRecord, index, pOut, pObject->mUnknown8.mUnknownF);
}

int fn_80168EA8(int team)
{
    return lbl_803ECAF4->mUnknown4[team].mUnknown8;
}

Team_80167A8C *fn_80168EBC(int team)
{
    return &lbl_803ECAF4->mUnknown4[team];
}
