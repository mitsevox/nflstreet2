#include "game/Step_800C4460.h"
#include "game/Block_8030E6E8.h"
#include "game/Record_800A0624.h"
#include "game/Command_800CEE74.h"
#include "game/Record_803EA558.h"
#include "game/Level_80054130.h"
#include "game/cu_80142BB4.h"
#include "game/Object_800EA284.h"
#include "game/Object_8017886C.h"
#include "game/fn_8022781C.h"
#include "game/Block_800C9D6C.h"
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/fn_8009D990.h"
#include "engine/vptmanager.h"
#include "game/Camera_8013F738.h"
#include "game/Class_80148A58.h"
#include "game/Class_80297BF8.h"
#include "game/Entry_800B206C.h"
#include "game/Entry_80219044.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B50.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_803EC99C.h"
#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/Input_800B6D34.h"
#include "game/ModuleGroup_80033A5C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8017886C.h"
#include "game/Query_800CE770.h"
#include "game/RecordList_8002E7C0.h"
#include "game/Record_800B15FC.h"
#include "game/Table_80089904.h"
#include "game/Team_80167A8C.h"
#include "game/cu_8002B8F8.h"
#include "game/cu_80041210.h"
#include "game/cu_8003108C.h"
#include "game/cu_80064864.h"
#include "game/cu_80067C10.h"
#include "game/Block_801BE60C.h"
#include "game/Record_8011F518.h"
#include "game/cu_80136B1C.h"
#include "game/cu_8008E978.h"
#include "game/fn_8007F828.h"
#include "game/fn_800670B4.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_80195EFC.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801C68FC.h"
#include "game/fn_801C3284.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801EF390.h"
#include "game/fn_80054138.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_802372EC.h"
#include "game/fn_80218FC4.h"
#include "game/fn_802270D4.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80238174.h"
#include "game/fn_80094488.h"
#include "game/cu_80164568.h"
#include "game/Entry_802F394C.h"

extern "C" {
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8009BEFC(Object_80039F5C *p, int joint, Vector_80039F5C *pOut, Vector_80039F5C *pScratch);
int fn_800A7EA4(int team);
unsigned int fn_800ABDA4(int team);
unsigned int fn_800ACBFC(int team);
int fn_800C8744(int team);
int fn_800C9108(Object_80039F5C *p, unsigned char *pTeam);
int fn_800C91F0(Object_80039F5C *p, unsigned char *pOut, int second);
int fn_800CADC0(Object_80039F5C *p, Info_80089904 *pInfo, int angle, int check);
int fn_800CAE28(Object_80039F5C *p, Info_80089904 *pInfo, int angle);
void fn_800CB484(Point_8017886C *pOut, Point_8017886C *pFrom, Point_8017886C *pTo, int flip, int angle, float scale);
int fn_80177F70(void);
Point_8017886C fn_80177FFC(int team);
int fn_801BA2A8(void *a, void *b, unsigned short c, unsigned short d, unsigned short e, void *p, float f);
int fn_801BA6B0(Record_800D81C8 *pRecord);
void fn_801BA6BC(Record_800D81C8 *pRecord, int value);
float fn_801BD660(void *p, int key);
void fn_801BD81C(void *p, float value);
int fn_801BE068(void *, void *, void *, unsigned short, void *, float);
Block_801BE60C *fn_801BE60C(void *p, unsigned short key);
unsigned short fn_801BE648(void *p);
void fn_801BE760(void *p, unsigned short key, unsigned short flags);
int fn_801C4E98(void *p, const char *pName);
int fn_801CFE40(float y, float x);
float fn_801CFFA0(float value);
int fn_801CFFD0(int a, int b);
void fn_80227538(Point_80167910 *pOut, int angle, float length);
void fn_80227638(void *pOut, void *pA, void *pB);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80227890(void *, void *);
extern float lbl_802DA69C[];
extern unsigned int lbl_8030C084[];
extern Table_80089904 lbl_80317AF4;
extern Table_80089904 lbl_803186D8;
extern float lbl_803EA2C4;
extern float lbl_803EAC2C;
extern float lbl_803EAC30;
extern float lbl_803EAC34;
extern float lbl_803EAC38;
extern Block_800C9D6C *lbl_803EAC3C;
extern Table_80089904 *lbl_803EAC44;
extern int lbl_803EAC48;
extern unsigned char lbl_803EAC4C;
extern Point_8017886C lbl_803EAC50;
extern int lbl_803EAC58;
extern int lbl_803EAC5C;
extern float lbl_803EAC60;
extern unsigned char lbl_803EAC64;
extern unsigned char lbl_803EAC65;
extern float lbl_803EAC68;
extern float lbl_803EAC6C;
extern float lbl_803EAC70;
extern float lbl_803ECB08;
}

/* Turn in place towards a move direction; payload that fn_801BE60C returns
   for the turn animations 143 and 144. */
struct Turn_800CBBAC {
    unsigned char mBeyond;
    int mRate;
    short mFrames;
    short mSteps;
    int mRecord;
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    float mStepX;
    float mStepY;
    Point_8017886C mTarget;
    float mScale;
    Info_80089904 *mpInfo;
    int mTotal;
};

extern "C" int fn_800C8774(int team)
{
    int value = 0;
    int field = team == 0 ? 0x43534847 /* 'CSHG' */ : 0x43534147 /* 'CSAG' */;

    fn_801FCE10(0, "select \x8c into \x82 from 'FNIG'\n", field, &value);
    return value;
}

extern "C" void fn_800C87CC(int team, int value)
{
    int field = team == 0 ? 0x43534847 /* 'CSHG' */ : 0x43534147 /* 'CSAG' */;

    fn_801FCE10(0, "update 'FNIG' set \x8c = \x82\n", field, value);
}

extern "C" int fn_800C8818(int team)
{
    int id = fn_800C8744(team);
    int result = 0;

    fn_801FCE10(0, "select 'DIOT' into \x82 from 'MAET' where 'DIGT' = \x82\n", &result, id);
    return result;
}

extern "C" void fn_800C89F0(Object_80039F5C *p, int angle, int rate, int which, float scale)
{
    int delta = (angle - p->mMotion.mFacing) << 8 >> 8;

    delta = delta < -0x155555 ? -0x155555 : (delta > 0x155555 ? 0x155555 : delta);
    p->mTurn.mTarget[which] = FixedMul(delta, (int)(scale * 16777216.0f));
    p->mTurn.mRate[which] = rate;
}

extern "C" int fn_800C8C1C(Object_80039F5C *p)
{
    int result = 0;
    unsigned char team = p->mIdBytes[2];
    unsigned char i;

    for (i = 0; i < lbl_803EAC3C->mCounts[team]; i++) {
        if (lbl_803EAC3C->mEntries[team][i].mUnknown8 != -1) {
            Object_80039F5C *pOther = fn_8009BCE8(&lbl_803EAC3C->mEntries[team][i].mRef);

            if (fn_80227890(&p->mMotion.mPos, &pOther->mMotion.mPos) < 16.0f) {
                result = 1;
                break;
            }
        }
    }
    return result;
}

extern "C" Object_80039F5C *fn_800C8DBC(int team, Vector_80039F5C *pPos, Object_80039F5C *pExclude, int mode)
{
    float best = 10000.0f;
    Object_80039F5C *pBest = 0;
    unsigned int count = fn_80178D70(team);
    int favourHigher = 1;
    int penaliseState1032 = 1;
    unsigned char i;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        int valid = 1;
        int ref;
        unsigned char j;

        if (p == pExclude) {
            valid = 0;
        }
        switch (mode) {
        case 1:
            if (p->mUnknown1052 == 0) {
                valid = 0;
            }
            break;
        case 2:
            if (valid) {
                valid = p->mpState->mId == 85;
                if (p->mpState->mId == 2 && p->mUnknown361[17] != 0 && p->mMotion.mPos.mY > pPos->mY) {
                    valid = 1;
                }
            }
            break;
        }
        if (fn_801BE648(p->mpUnknown792) == 173 && count > lbl_803EAC3C->mCounts[team]) {
            valid = 0;
        }
        fn_8009BD2C(p, &ref);
        for (j = 0; j < lbl_803EAC3C->mCounts[team]; j++) {
            if (lbl_803EAC3C->mEntries[team][j].mRef == ref) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            float dist = fn_80227890(pPos, &p->mMotion.mPos);

            if (fn_800C91F0(p, 0, 1)) {
                dist -= lbl_803EAC30;
                if (dist < 0.0f) {
                    dist = 0.0f;
                }
            }
            if (favourHigher && p->mMotion.mPos.mY > pPos->mY) {
                dist -= lbl_803EAC2C;
                if (dist < 0.0f) {
                    dist = 0.0f;
                }
            }
            if (penaliseState1032 && (unsigned int)(p->mUnknown1032 - 4) <= 2) {
                dist += lbl_803EAC38;
                if (dist > 9999.0f) {
                    dist = 9999.0f;
                }
            }
            if (p->mFlags & 0x800) {
                dist += lbl_803EAC34;
                if (dist > 9999.0f) {
                    dist = 9999.0f;
                }
            }
            if (dist < best) {
                pBest = p;
                best = dist;
            }
        }
    }
    return pBest;
}

extern "C" float fn_800C9CF0(int team, int index)
{
    float result;

    if (lbl_803EAC3C->mEntries[team][index].mUnknown4 == 0) {
        result = 0.0f;
    } else {
        result = (float)lbl_803EAC3C->mEntries[team][index].mUnknown4
                 / (float)lbl_803EAC3C->mEntries[team][index].mUnknown14;
    }
    return result;
}

extern "C" void fn_800C9E4C(unsigned char count0, unsigned char count1)
{
    int *pRefs;
    int i;

    lbl_803EAC3C->mCounts[0] = count0;
    lbl_803EAC3C->mCounts[1] = count1;
    pRefs = lbl_803EAC3C->mRefs;
    for (i = 0; i < 3; i++) {
        *pRefs++ = 0;
    }
    for (i = 0; i < 5; i++) {
        lbl_803EAC3C->mEntries[0][i].mUnknown4 = 1000000000;
        lbl_803EAC3C->mEntries[0][i].mUnknown14 = 1000000000;
        lbl_803EAC3C->mEntries[0][i].mRef = 0;
        lbl_803EAC3C->mEntries[0][i].mUnknownC = (unsigned int)(lbl_803EA2C4 * 8333333.0f);
        lbl_803EAC3C->mEntries[0][i].mUnknown8 = -1;
        lbl_803EAC3C->mEntries[0][i].mUnknown10 = 0;
        lbl_803EAC3C->mEntries[0][i].mUnknown11 = lbl_803EAC3C->mEntries[0][i].mUnknown12 = 0;
        lbl_803EAC3C->mEntries[1][i].mUnknown4 = 1000000000;
        lbl_803EAC3C->mEntries[1][i].mUnknown14 = 1000000000;
        lbl_803EAC3C->mEntries[1][i].mRef = 0;
        lbl_803EAC3C->mEntries[1][i].mUnknownC = (unsigned int)(lbl_803EA2C4 * 8333333.0f);
        lbl_803EAC3C->mEntries[1][i].mUnknown8 = -1;
        lbl_803EAC3C->mEntries[1][i].mUnknown10 = 0;
        lbl_803EAC3C->mEntries[1][i].mUnknown11 = lbl_803EAC3C->mEntries[1][i].mUnknown12 = 0;
    }
}

extern "C" void fn_800C9FC0(void)
{
    unsigned char i;
    unsigned char team;
    unsigned char j;

    for (i = 0; i <= 2; i++) {
        lbl_803EAC3C->mRefs[i] = 0;
    }
    for (team = 0; team <= 1; team++) {
        for (j = 0; j < lbl_803EAC3C->mCounts[team]; j++) {
            if (!fn_800A7EA4(team)) {
                lbl_803EAC3C->mEntries[team][j].mUnknown4 = 0;
                lbl_803EAC3C->mEntries[team][j].mUnknownC = 0;
            } else {
                lbl_803EAC3C->mEntries[team][j].mUnknown4 = fn_800ACBFC(team);
                lbl_803EAC3C->mEntries[team][j].mUnknownC = (unsigned int)(lbl_803EA2C4 * 8333333.0f);
            }
            lbl_803EAC3C->mEntries[team][j].mUnknown14 = lbl_803EAC3C->mEntries[team][j].mUnknown4;
            lbl_803EAC3C->mEntries[team][j].mRef = 0;
            lbl_803EAC3C->mEntries[team][j].mUnknown10 = 0;
            lbl_803EAC3C->mEntries[team][j].mUnknown11 = 0;
        }
    }
}

extern "C" float fn_800CA9B4(int kind, Object_80039F5C *p)
{
    float scale = lbl_802DA69C[kind];

    switch (kind) {
    case 6:
        if (fn_800B65A0(p->mIdBytes[2]) == 255 && fn_800ABDA4(p->mIdBytes[2]) == 0) {
            scale = 1.0f;
        }
        break;
    case 5:
        if (fn_800B65A0(p->mIdBytes[2]) == 255 && fn_800ABDA4(p->mIdBytes[2]) == 0) {
            scale *= 0.33333334f;
        }
        break;
    }
    return scale;
}

extern "C" float fn_800CAAFC(Object_80039F5C *p)
{
    unsigned char team;
    signed char index = fn_800C9108(p, &team);
    float result;

    if (index != -1) {
        result = (float)(unsigned int)(fn_800C9CF0(team, index) * 1000000000.0f) / lbl_8030C084[0];
    } else {
        result = 1000000000.0f / lbl_8030C084[0];
    }
    return result;
}

extern "C" int fn_800CAC54(Object_80039F5C *p)
{
    Record_800D81C8 *pRecord;
    unsigned char i;
    int foot;

    for (i = 0; i < 10; i++) {
        pRecord = &p->mpUnknown800[i];
        if (pRecord->mUnknown8 == 74 && pRecord->mUnknown1 == 2 && pRecord->mUnknown4C.mUnknown1A <= 16) {
            break;
        }
        pRecord = 0;
    }
    if (pRecord != 0) {
        switch (pRecord->mUnknown4C.mUnknown18) {
        case 4:
        case 5:
        case 12:
        case 13:
            foot = 255;
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            foot = 2;
            break;
        case 1:
        case 2:
        case 3:
        case 16:
            foot = 1;
            break;
        default:
            foot = 1;
            break;
        }
        if (fn_801BA6B0(pRecord) != 0 && foot != 255) {
            if (foot == 1) {
                foot = 2;
            } else {
                foot = 1;
            }
        }
    } else {
        Vector_80039F5C left;
        Vector_80039F5C right;
        Vector_80039F5C scratch;

        foot = 2;
        fn_8009BEFC(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, "lankle"), &left, &scratch);
        fn_8009BEFC(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, "rankle"), &right, &scratch);
        if (!(left.mY <= right.mY)) {
            foot = 1;
        }
    }
    return foot;
}

extern "C" void fn_800CAF4C(Object_80039F5C *p, int key, Record_800D81C8 *pRecords, Turn_800CBBAC *pTurn,
                            Info_80089904 *pInfo)
{
    int index;
    int infoAngle;
    int facing;
    int desired;
    int turn;

    pTurn->mBeyond = lbl_803EAC64;
    pTurn->mRate = 0;
    pTurn->mUnknown10 = 0;
    pTurn->mUnknown14 = 0;
    pTurn->mUnknown18 = 0;
    index = pTurn->mRecord;
    if (lbl_803EAC4C != 0) {
        fn_801BA6BC(&pRecords[index], 1);
    }
    pRecords[index].mUnknown2C = 1.0f;
    fn_801BD81C(&pRecords[index].mUnknown4C, fn_801CFFA0(lbl_803EAC68));
    infoAngle = pInfo->mUnknown56;
    facing = p->mMotion.mFacing;
    desired = lbl_803EAC58;
    if (infoAngle > 0x800000) {
        turn = infoAngle - 0x1000000;
    } else {
        turn = infoAngle;
    }
    if (lbl_803EAC4C != 0) {
        turn = -turn;
    }
    turn = (((desired - facing) & 0xFFFFFF) - turn) & 0xFFFFFF;
    if (turn > 0x800000) {
        turn -= 0x1000000;
    }
    pTurn->mFrames = 10;
    pTurn->mRate = (int)((float)turn * 0.1f);
}

extern "C" void fn_800CB080(Object_80039F5C *p, int key, Record_800D81C8 *pRecords, Turn_800CBBAC *pTurn,
                            Info_80089904 *pInfo)
{
    Point_8017886C target;
    int index;
    int infoAngle;
    int facing;
    int desired;
    int turn;

    pTurn->mBeyond = lbl_803EAC64;
    pTurn->mRate = 0;
    pTurn->mUnknown10 = 0;
    pTurn->mUnknown14 = 0;
    pTurn->mUnknown18 = 0;
    index = pTurn->mRecord;
    target = lbl_803EAC50;
    if (fn_800F06F4(0, p->mpState, 9, 0xFFFF) == 0xFFFF) {
        fn_800F06F4(0, p->mpState, 87, 0xFFFF);
    }
    fn_800AD9B4();
    pTurn->mTarget.mX = target.mX;
    pTurn->mTarget.mY = target.mY;
    if (lbl_803EAC4C != 0) {
        fn_801BA6BC(&pRecords[index], 1);
    }
    pRecords[index].mUnknown2C = lbl_803EAC60;
    fn_801BD81C(&pRecords[index].mUnknown4C, fn_801CFFA0(lbl_803EAC6C));
    pTurn->mScale = lbl_803EAC6C;
    infoAngle = pInfo->mUnknown56;
    facing = p->mMotion.mFacing;
    desired = lbl_803EAC58;
    if (infoAngle > 0x800000) {
        turn = infoAngle - 0x1000000;
    } else {
        turn = infoAngle;
    }
    if (lbl_803EAC4C != 0) {
        turn = -turn;
    }
    turn = (((desired - facing) & 0xFFFFFF) - turn) & 0xFFFFFF;
    if (turn > 0x800000) {
        turn -= 0x1000000;
    }
    pTurn->mFrames = 10;
    pTurn->mRate = (int)((float)turn * 0.1f);
    if (pTurn->mBeyond == 2) {
        pTurn->mRate = 0;
    }
}

extern "C" int fn_800CB228(Object_80039F5C *p, Info_80089904 *pInfo, int angle, Point_8017886C target, float limit)
{
    Point_8017886C step;
    Point_8017886C delta;
    Point_8017886C origin = {0.0f, 0.0f};
    Point_8017886C toTarget;
    Point_80167910 arc;
    Point_8017886C aim;
    int infoAngle = pInfo->mUnknown56;
    int facing = p->mMotion.mFacing;
    int turn;
    int heading;
    int bend;
    float stepLength;
    float ratio;

    if (infoAngle > 0x800000) {
        turn = infoAngle - 0x1000000;
    } else {
        turn = infoAngle;
    }
    if (lbl_803EAC4C != 0) {
        turn = -turn;
    }
    turn = (((angle - facing) & 0xFFFFFF) - turn) & 0xFFFFFF;
    if (turn > 0x800000) {
        turn -= 0x1000000;
    }
    step.mX = pInfo->mUnknown20Float;
    step.mY = pInfo->mUnknown24;
    heading = (turn + facing) & 0xFFFFFF;
    fn_800CB484(&delta, &origin, &step, lbl_803EAC4C, heading, 1.0f);
    turn = fn_801CFE40(delta.mY, delta.mX);
    fn_80227690(&toTarget, &target, &p->mMotion.mPos);
    bend = fn_801CFFD0(fn_801CFE40(toTarget.mY, toTarget.mX), turn);
    fn_80227538(&arc, (0x400000 - bend) & 0xFFFFFF, fn_802270A4(&toTarget) * (3.7450704e-07f * bend));
    fn_80227638(&aim, &arc, &target);
    fn_80227690(&arc, &aim, &p->mMotion.mPos);
    stepLength = fn_802270A4(&delta);
    ratio = fn_802270A4(&arc) / stepLength;
    if (ratio > 1.2f) {
        ratio = 1.2f;
    } else if (ratio < 0.9f) {
        ratio = 0.9f;
    }
    fn_80227538(&arc, turn, stepLength * ratio);
    fn_80227638(&aim, &arc, &p->mMotion.mPos);
    if (fn_8022781C(&aim, &target) < limit) {
        lbl_803EAC60 = ratio;
        lbl_803EAC5C = (heading - facing) & 0xFFFFFF;
        return 1;
    }
    lbl_803EAC5C = 0;
    lbl_803EAC60 = 1.0f;
    return 0;
}

extern "C" void fn_800CB504(void)
{
    fn_801BBC3C(1, 143, &lbl_80317AF4);
    fn_801BBC3C(1, 144, &lbl_803186D8);
    lbl_803EAC44 = 0;
    lbl_803EAC48 = 0;
    lbl_803EAC4C = 0;
    lbl_803EAC50.mY = 0.0f;
    lbl_803EAC50.mX = 0.0f;
    lbl_803EAC58 = 0;
    lbl_803EAC5C = 0;
    lbl_803EAC60 = 1.0f;
    lbl_803EAC64 = 0;
}

extern "C" int fn_800CB580(Object_80039F5C *p, int *pIndex, Point_8017886C target, int angle, int check)
{
    Point_8017886C delta;
    int found = 0;
    int facing;
    unsigned int i;
    float distance;

    if (p->mUnknown2914 == 19 || p->mUnknown2914 == 23) {
        if (fn_80177F70() == 0) {
            return 0;
        }
    }
    facing = p->mMotion.mFacing;
    fn_80227690(&delta, &target, &p->mMotion.mPos);
    distance = fn_802270A4(&delta);
    fn_801CFFD0(facing, angle);
    lbl_803EAC48 = 144;
    lbl_803EAC44 = &lbl_803186D8;
    for (i = 0; i < lbl_803EAC44->mCount; i++) {
        Info_80089904 *pInfo;
        int limit;

        lbl_803EAC4C = 0;
        pInfo = lbl_803EAC44->mEntries[i].mpInfo;
        limit = 0x238E39;
        if (!(distance - fn_802270A4(&pInfo->mUnknown20) <= 0.5f)
            && fn_801CFFD0(fn_801CFFD0(pInfo->mUnknown56, 0), fn_801CFFD0(facing, angle)) < limit
            && fn_800CADC0(p, pInfo, angle, check) != 0) {
            *pIndex = i;
            found = 1;
            break;
        }
    }
    return found;
}

extern "C" int fn_800CB708(Object_80039F5C *p, int *pIndex, Point_8017886C target, int angle, int beyond)
{
    float offset = 0.0f;
    int message;
    int mode;
    int found;
    int facing;
    int kind;
    int direction;
    int turn;
    unsigned int i;
    float distance;
    Point_8017886C aim;
    Point_8017886C delta;
    Point_8017886C goal;

    mode = fn_800AD9B4();
    found = 0;
    facing = p->mMotion.mFacing;
    message = fn_800F06F4(0, p->mpState, 9, 0xFFFF);
    if (message == 0xFFFF) {
        message = fn_800F06F4(0, p->mpState, 87, 0xFFFF);
    }
    kind = 0;
    if (message != 0xFFFF && mode == 2) {
        kind = p->mpState[message].mUnknown1;
    }
    aim.mX = target.mX;
    aim.mY = offset + target.mY;
    fn_80227690(&delta, &aim, &p->mMotion.mPos);
    goal = fn_80177FFC(p->mIdBytes[2]);
    direction = fn_801CFE40(delta.mY, delta.mX);
    distance = fn_802270A4(&delta);
    turn = fn_801CFFD0(facing, direction);
    if (beyond != 2 && turn > 0x18E38E) {
        return 0;
    }
    if (mode == 2) {
        int allowed = 1;

        if (fn_801CFFD0(facing, angle) < 621378.0f && fn_801CFFD0(direction, facing) < 621378.0f) {
            switch (p->mUnknown2914) {
            case 4:
                if (kind == 86) {
                    allowed = 0;
                }
                break;
            case 0:
                if (target.mY > goal.mY - 3.0f) {
                    allowed = 0;
                }
                break;
            case 1:
            case 2:
                if (kind == 85) {
                    allowed = 0;
                }
                break;
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                allowed = 0;
                break;
            case 10:
            case 11:
            case 12:
            case 16:
            case 17:
            case 18:
            case 24:
                allowed = 0;
                break;
            }
        }
        if (allowed == 0) {
            return 0;
        }
    }
    lbl_803EAC48 = 143;
    lbl_803EAC44 = &lbl_80317AF4;
    for (i = 0; i < lbl_803EAC44->mCount; i++) {
        Info_80089904 *pInfo;
        float length;

        lbl_803EAC4C = 0;
        pInfo = lbl_803EAC44->mEntries[i].mpInfo;
        length = fn_802270A4(&pInfo->mUnknown20);
        if (beyond == 2 || !(fabsf(length - distance) >= 2.0f)) {
            int infoAngle = fn_801CFFD0(pInfo->mUnknown56, 0);
            int limit = 0x155555;
            int turn = fn_801CFFD0(facing, angle);

            if (turn > 0x555554) {
                limit = 0x2AAAAA;
            }
            if (fn_801CFFD0(infoAngle, turn) < limit && fn_800CAE28(p, pInfo, angle) != 0) {
                float scale = 0.25f;

                switch (beyond) {
                case 0:
                    break;
                case 1:
                    if (mode != 4) {
                        scale = 0.45f;
                    } else {
                        scale = 1.0f;
                    }
                    break;
                }
                if (beyond == 2 || fn_800CB228(p, pInfo, angle, aim, scale) != 0) {
                    *pIndex = i;
                    found = 1;
                    break;
                }
            }
        }
    }
    return found;
}

extern "C" int fn_800CBB00(Object_80039F5C *p, int index, Point_8017886C target, int angle, int beyond)
{
    unsigned short first;
    unsigned short second;

    p->mUnknown512.mUnknown14 = 0;
    second = lbl_803EAC44->mEntries[index].mUnknown2;
    first = lbl_803EAC44->mEntries[index].mUnknown0;
    p->mUnknown9[0] = 1;
    p->mUnknown1008.mUnknown0 = second;
    p->mUnknown1008.mUnknown1 = second >> 8;
    p->mUnknown1008.mUnknown2 = first;
    p->mUnknown1011 = first >> 8;
    p->mFlags &= ~4;
    lbl_803EAC64 = beyond;
    lbl_803EAC50 = target;
    lbl_803EAC58 = angle;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, lbl_803EAC48, p, 1.0f);
    return 1;
}

extern "C" int fn_800CBBAC(Table_80089904 *pTable, unsigned short key, void *pOwner, Record_800D81C8 *pRecords,
                           Object_80039F5C *p, unsigned int event)
{
    Turn_800CBBAC *pTurn = (Turn_800CBBAC *)fn_801BE60C(p->mpUnknown792, key);
    unsigned short index = 0;
    unsigned short second;
    unsigned short first;

    switch (event) {
    case 1:
        p->mUnknown512.mUnknown14 = 1;
        p->mFlags &= ~4;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
        break;
    case 0: {
        unsigned short i;

        second = p->mUnknown1008.mUnknown0;
        second |= p->mUnknown1008.mUnknown1 << 8;
        first = p->mUnknown1008.mUnknown2;
        first |= p->mUnknown1011 << 8;
        fn_801BE760(p->mpUnknown792, key, 1);
        pTurn->mRecord = fn_801BA2A8(pOwner, pRecords, first, second, key, p, 1.0f);
        pTurn->mScale = 1.0f;
        for (i = 0; i < pTable->mCount; i++) {
            if (pTable->mEntries[i].mUnknown2 == second && pTable->mEntries[i].mUnknown0 == first) {
                index = i;
                break;
            }
        }
        switch (key) {
        case 143:
            fn_800CB080(p, 143, pRecords, pTurn, pTable->mEntries[index].mpInfo);
            break;
        case 144:
            fn_800CAF4C(p, 144, pRecords, pTurn, pTable->mEntries[index].mpInfo);
            break;
        }
        pTurn->mpInfo = pTable->mEntries[index].mpInfo;
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            short frames = pTurn->mFrames;

            if (frames > 0) {
                p->mMotion.mFacing = (p->mMotion.mFacing + pTurn->mRate) & 0xFFFFFF;
                p->mpUnknown800[pTurn->mRecord].mUnknownC =
                    (p->mpUnknown800[pTurn->mRecord].mUnknownC + pTurn->mRate) & 0xFFFFFF;
                pTurn->mFrames--;
                pTurn->mTotal += pTurn->mRate;
            } else if (frames == 0) {
                if (key == 144) {
                    pTurn->mUnknown10 = frames;
                    pTurn->mStepY = pTurn->mStepX = 0.0f;
                } else {
                    Record_800D81C8 *pRecord = &pRecords[pTurn->mRecord];
                    Point_8017886C origin;
                    Point_8017886C step;
                    Point_8017886C end;
                    Point_8017886C delta;
                    float remaining;

                    remaining = fn_801BD660(pRecord->mUnknown4C.mpUnknown0, 0xC004) * (1.0f / pTurn->mScale)
                                - pRecord->mUnknown4C.mUnknown8;
                    pTurn->mUnknown10 = frames;
                    origin.mX = pRecord->mUnknown24.mUnknown0;
                    origin.mY = pRecord->mUnknown24.mUnknown4;
                    step.mX = pTurn->mpInfo->mUnknown20Float;
                    step.mY = pTurn->mpInfo->mUnknown24;
                    fn_800CB484(&end, &origin, &step, fn_801BA6B0(pRecord),
                                p->mpUnknown800[pTurn->mRecord].mUnknownC, pRecord->mUnknown2C);
                    fn_80227638(&end, &p->mMotion.mPos, &end);
                    fn_80227690(&delta, &pTurn->mTarget, &end);
                    pTurn->mSteps = (int)(remaining / lbl_803EAC70);
                    pTurn->mStepX = delta.mX / pTurn->mSteps;
                    pTurn->mStepY = delta.mY / pTurn->mSteps;
                    if (pTurn->mBeyond != 0 || lbl_803EAC65 != 0) {
                        pTurn->mStepY = pTurn->mStepX = 0.0f;
                    }
                }
                pTurn->mFrames--;
            } else if ((p->mFlags & 4) == 0) {
                if (pTurn->mSteps > 0) {
                    p->mMotion.mPos.mX += pTurn->mStepX;
                    p->mMotion.mPos.mY += pTurn->mStepY;
                    pTurn->mSteps--;
                }
                pTurn->mUnknown10++;
            }
        }
        break;
    }
    return 0;
}
