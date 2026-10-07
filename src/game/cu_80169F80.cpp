#include <math.h>
#include "game/Class_80148A58.h"
#include "game/fn_8016871C.h"
#include "game/fn_800670B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80238174.h"
#include "game/Object_800785C0.h"

struct Point_8016AD80 {
    float mX;
    float mY;
};

/* One 12-byte candidate passed with its count to fn_8016B364; the
   halfword at +4 is the weight these functions rescale or clear. */
struct Candidate_8016B364 {
    unsigned int mUnknown0;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned char mUnknown8;
};

/* One 20-byte history entry; fn_8016B144 shifts the list down and
   starts a new entry at index 0. */
struct Entry_8016B144 {
    int mUnknown0;
    int mUnknown4;
    unsigned int mUnknown8;
    signed char mUnknownC;
    signed char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mUnknownF;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
};

/* Allocated through fn_80238174 under the id 'ptrk' (fn_8016B04C). */
struct Object_8016B04C {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    float mUnknown10;
    unsigned int mUnknown14;
    unsigned char mUnknown18;
    Entry_8016B144 mUnknown1C[2][24];
    unsigned short mUnknown3DC[2];
};

extern "C" {
int fn_80025708(void);
int fn_800A82FC(int team);
int fn_800A8430(int team);
int fn_800B65A0(int unknown);
int fn_800BA6F8(void);
int fn_800C8744(int team);
int fn_8011F1CC(void);
int fn_801485D4(void);
Object_800670B4 *fn_80168708(int team);
int fn_80168EA8(int team);
int fn_80177F70(void);
Point_8016AD80 fn_80177FE0(void);
int fn_80178308(void);
float fn_80178A5C(void);
int fn_80187C6C(void);
int fn_80187C8C(void);
int fn_8022DDB4(int tag, void *data);
void *fn_8023816C(void);
}

static Object_8016B04C *lbl_803EB40C = 0;

float lbl_802E9970[3] = {0.10625f, 0.01875f, 0.009375f};
float lbl_802E997C[3] = {0.10625f, 0.01875f, 0.009375f};
float lbl_802E9988[3] = {0.10625f, 0.01875f, 0.009375f};
float lbl_802E9994[3] = {0.10625f, 0.01875f, 0.009375f};
float lbl_802E99A0[3] = {0.10625f, 0.01875f, 0.009375f};
float lbl_802E99AC[3] = {0.08125f, 0.028125f, 0.0140625f};
float lbl_802E99B8[3] = {0.08125f, 0.028125f, 0.0140625f};

extern "C" {
int fn_80169F80(int value);
void fn_80169FCC(int team, unsigned char *pOut, unsigned int *pFlags);
float fn_8016A2D4(int team, unsigned char kind, unsigned int flags, int group, unsigned int mask);
float fn_8016A334(int team);
float fn_8016A408(int team);
float fn_8016A4DC(int team);
float fn_8016A568(int team);
float fn_8016A5F4(unsigned int a, unsigned int b, float value);
float fn_8016A618(int team, int a, int b);
float fn_8016A770(unsigned int mask, unsigned int flags, unsigned int other, float value);
void fn_8016A7DC(int team, Candidate_8016B364 *pList, unsigned int count);
void fn_8016A9B4(int team, Candidate_8016B364 *pList, unsigned int count);
void fn_8016AC24(int team, Candidate_8016B364 *pList, unsigned int count);
void fn_8016ACD8(int team, Candidate_8016B364 *pList, unsigned int count, int mode);
unsigned int fn_8016AD80(int kind, Point_8016AD80 from, Point_8016AD80 *pTo, int flag);
void fn_8016AF34(int team, float *pA, float *pB);
void fn_8016B04C(void);
void fn_8016B0AC(void);
void fn_8016B0B0(void);
void fn_8016B144(int team, int value);
void fn_8016B210(int team, int value);
void fn_8016B22C(int team, signed char value);
void fn_8016B248(int team, Point_8016AD80 from, Point_8016AD80 to, int flag);
void fn_8016B2B8(int team, float value);
void fn_8016B2E8(int team, unsigned char value);
void fn_8016B310(int team, unsigned char value);
void fn_8016B32C(int team, unsigned char value);
void fn_8016B348(int team, unsigned char value);
void fn_8016B364(int team, Candidate_8016B364 *pList, unsigned int count);
void fn_8016B438(int team, unsigned char *pOut, unsigned int *pFlags);
unsigned char fn_8016B7C4(Point_8016AD80 *pTo);
void fn_8016B82C(int team, Record_80067338 *pRecord, unsigned char *pOut, unsigned int *pFlags);
float fn_8016B8C8(int team, int value);
float fn_8016B938(void);
float fn_8016B974(void);
float GetTrackerFloat8(void);
float fn_8016B9B0(void);
float fn_8016B9EC(void);
void SumRunWeightsBit28(int team, float *pClear, float *pSet);
void SumRunWeightsBit30(int team, float *pSet, float *pClear);
void fn_8016BA28(unsigned char *pOut);
void fn_8016BA80(void);
void fn_8016BAAC(void);
}

int fn_80169F80(int value)
{
    switch (value) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 0x26:
        return 2;
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x25:
        return 1;
    }
    return 0;
}

void fn_80169FCC(int team, unsigned char *pOut, unsigned int *pFlags)
{
    *pOut = 0;
    *pFlags = 0;

    float pass = 0.0f;
    float other = 0.0f;
    float other4 = 0.0f;
    float other8 = 0.0f;
    float other2 = 0.0f;
    float pass100 = 0.0f;
    float pass200 = 0.0f;
    float pass80 = 0.0f;
    float pass40 = 0.0f;
    float pass20 = 0.0f;
    float pass10 = 0.0f;
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    float total = lbl_803EB40C->mUnknown3DC[team];

    if (total <= 8.0f)
        return;

    for (unsigned char i = 0; i < total; i++) {
        unsigned int flags = pEntries[i].mUnknown8;
        if (pEntries[i].mUnknownF == 2) {
            pass += 1.0f;
            if (pEntries[i].mUnknownE != 4) {
                if (flags & 0x10)
                    pass10 += 1.0f;
                if (flags & 0x20)
                    pass20 += 1.0f;
                if (flags & 0x40)
                    pass40 += 1.0f;
                if (flags & 0x80)
                    pass80 += 1.0f;
                if (flags & 0x100)
                    pass100 += 1.0f;
                if (flags & 0x200)
                    pass200 += 1.0f;
            }
        } else {
            other += 1.0f;
            if (flags & 2)
                other2 += 1.0f;
            if (flags & 4)
                other4 += 1.0f;
            if (flags & 8)
                other8 += 1.0f;
        }
    }

    if (other / total > 0.65f)
        *pOut = 1;
    else if (pass / total > 0.65f)
        *pOut = 2;

    if (other != 0.0f) {
        if (other2 / other > 0.5f)
            *pFlags |= 2;
        else if (other8 / other > 0.5f)
            *pFlags |= 8;
        else if (other4 / other > 0.5f)
            *pFlags |= 4;
    }

    if (pass != 0.0f) {
        if (pass10 / pass > 0.5f)
            *pFlags |= 0x10;
        else if (pass20 / pass > 0.5f)
            *pFlags |= 0x20;
        else if (pass40 / pass > 0.5f)
            *pFlags |= 0x40;

        if (pass80 / pass > 0.5f)
            *pFlags |= 0x80;
        else if (pass200 / pass > 0.5f)
            *pFlags |= 0x200;
        else if (pass100 / pass > 0.5f)
            *pFlags |= 0x100;
    }
}

float fn_8016A2D4(int team, unsigned char kind, unsigned int flags, int group, unsigned int mask)
{
    float value = 0.0f;

    if (kind != 0 && kind == group)
        value = 2.0f;

    unsigned int high = flags & 0x70;
    unsigned int low = flags & 0x38E;
    if (low && (low & mask))
        value += 1.5f;
    if (high && (high & mask))
        value += 1.5f;
    return value;
}

float fn_8016A334(int team)
{
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    float value = 0.0f;

    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknownE == 5 && pEntries[i].mUnknownD > 2.0f)
            value += lbl_802E997C[i / 8];
    }
    if (value > 1.0f)
        value = 1.0f;
    return value;
}

float fn_8016A408(int team)
{
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    float value = 0.0f;

    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknownE == 6 && pEntries[i].mUnknownD > 4.0f)
            value += lbl_802E9988[i / 8];
    }
    if (value > 1.0f)
        value = 1.0f;
    return value;
}

float fn_8016A4DC(int team)
{
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    float value = 0.0f;

    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknown10 != 0)
            value += lbl_802E9994[i / 8];
    }
    if (value > 1.0f)
        value = 1.0f;
    return value;
}

float fn_8016A568(int team)
{
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    float value = 0.0f;

    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknown11 != 0)
            value += lbl_802E99A0[i / 8];
    }
    if (value > 1.0f)
        value = 1.0f;
    return value;
}

float fn_8016A5F4(unsigned int a, unsigned int b, float value)
{
    float scale = (a & b) ? 0.75f : -0.75f;
    return scale * value + scale;
}

float fn_8016A618(int team, int a, int b)
{
    unsigned short matches = 0;
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    float result = 0.0f;
    float sum = result;
    unsigned short i;

    for (i = 0; i < count; i++) {
        if (b == pEntries[i].mUnknown0 && a == pEntries[i].mUnknown4) {
            matches++;
            switch (pEntries[i].mUnknownE) {
            case 1:
            case 3:
            case 4:
                sum -= 5.0f;
                break;
            default:
                sum += pEntries[i].mUnknownD;
                break;
            }
        }
    }

    if (matches != 0) {
        float limit;
        sum /= matches;
        if (pEntries[i].mUnknownF == 1)
            limit = 4.9f;
        else
            limit = 9.0f;
        if (sum < limit)
            result = 0.5f;
    }
    return result;
}

float fn_8016A770(unsigned int mask, unsigned int flags, unsigned int other, float value)
{
    unsigned int high = flags & 0x70;
    float result = 0.0f;

    flags &= 0x38E;
    if (flags & mask) {
        result = 0.35f;
        if (flags & other)
            result += 0.175f;
        result = result * value + result;
    }
    if (high & mask) {
        result += 0.75f;
        if (high & other)
            result += 0.375f;
        result = result * value + result;
    }
    return result;
}

void fn_8016A7DC(int team, Candidate_8016B364 *pList, unsigned int count)
{
    float runBias;
    float passBias;
    unsigned char kind;
    unsigned int flags;
    int preferred = 0;

    fn_8016AF34(team, &runBias, &passBias);
    fn_8016B438(team, &kind, &flags);
    if (fn_801485D4())
        preferred = fn_80148A58()->vfn_08(1);

    for (unsigned short i = 0; i < count; i++) {
        float scale = 1.0f;
        int group = fn_80169F80(pList[i].mUnknown8);

        scale += fn_8016A2D4(team, kind, flags, group, pList[i].mUnknown6);
        if (group == 2)
            scale += passBias;
        else if (group == 1)
            scale += runBias;
        if (scale < 0.0f)
            scale = 0.0f;

        if (fn_800A82FC(fn_80178308())) {
            if (fn_80177F70() != 6) {
                if (group == 2)
                    pList[i].mUnknown4 = 0;
                else if (group == 1)
                    pList[i].mUnknown4 = group;
            }
        } else if (preferred != 0) {
            if (group != preferred)
                pList[i].mUnknown4 = 0;
        } else {
            pList[i].mUnknown4 = (unsigned short)((float)pList[i].mUnknown4 * scale + 0.5f);
        }
    }
}

void fn_8016A9B4(int team, Candidate_8016B364 *pList, unsigned int count)
{
    int opponent = team ^ 1;
    Record_80067338 *pRecord = fn_8016871C(opponent);
    unsigned char kind;
    unsigned char trend;
    unsigned int mask;
    unsigned int flags;
    unsigned int rating;
    int id = pRecord->mUnknown4;

    fn_8016B82C(opponent, pRecord, &kind, &mask);
    fn_80169FCC(opponent, &trend, &flags);
    float history = fn_8016B8C8(opponent, id);
    float runRate = fn_8016A334(opponent);
    float passRate = fn_8016A408(opponent);

    int key = team == 0 ? fn_80187C8C() : fn_80187C6C();
    if (fn_801FCE10(0, "select 'ZBMT' into \x82 from 'MAET' where 'DIGT' = \x82\n", &rating, key) != 0)
        rating = 50;
    fn_80168EA8(team);

    for (unsigned short i = 0; i < count; i++) {
        float weight = pList[i].mUnknown4;
        float scale = 1.0f;

        scale += fn_8016A5F4(pList[i].mUnknown6, mask, history);
        scale += fn_8016A618(opponent, pList[i].mUnknown0, id);
        scale += fn_8016A770(pList[i].mUnknown6, flags, mask, history);
        if ((pList[i].mUnknown6 & 0x400) && kind == 2)
            scale += runRate;
        if ((pList[i].mUnknown6 & 0x800) && kind == 1)
            scale += passRate;

        float adjust = ((float)rating - 50.0f) * 0.02f;
        if (pList[i].mUnknown8 == 0x1F)
            scale += adjust * 0.5f;
        else
            scale -= adjust * 0.5f;
        if (scale < 0.0f)
            scale = 0.0f;

        pList[i].mUnknown4 = (unsigned short)(weight * scale);
    }
}

void fn_8016AC24(int team, Candidate_8016B364 *pList, unsigned int count)
{
    int mode = fn_800A8430(team);

    if (mode == 0)
        return;
    for (unsigned short i = 0; i < count; i++) {
        int keep = 0;
        int group = fn_80169F80(pList[i].mUnknown8);
        if ((group == 2 && mode == 2) || (group == 1 && mode == 1) || group == 0)
            keep = 1;
        if (!keep)
            pList[i].mUnknown4 = keep;
    }
}

void fn_8016ACD8(int team, Candidate_8016B364 *pList, unsigned int count, int mode)
{
    if (mode == 3)
        return;
    for (unsigned short i = 0; i < count; i++) {
        int keep = 0;
        int group = fn_80169F80(pList[i].mUnknown8);
        if ((group == 2 && mode == 1) || (group == 1 && mode == 2))
            keep = 1;
        if (!keep)
            pList[i].mUnknown4 = keep;
    }
}

unsigned int fn_8016AD80(int kind, Point_8016AD80 from, Point_8016AD80 *pTo, int flag)
{
    unsigned int result = 0;

    if (fabsf(pTo->mX - from.mX) > 4.5f) {
        if (pTo->mX > from.mX) {
            if (kind == 2)
                result |= 0x200;
            else
                result |= 8;
        } else {
            if (kind == 2)
                result |= 0x80;
            else
                result |= 2;
        }
    } else {
        if (kind == 2)
            result |= 0x100;
        else
            result |= 4;
    }

    if (kind == 2) {
        float depth = pTo->mY - from.mY;
        if (depth < 7.0f)
            result |= 0x10;
        else if (depth < 15.0f)
            result |= 0x20;
        else
            result |= 0x40;
        return result;
    }

    if (fabsf(from.mX) > fn_80178A5C() * 0.33333334f) {
        if ((pTo->mX > from.mX && from.mX < 0.0f) || (pTo->mX < from.mX && from.mX > 0.0f))
            result |= 0x10000000;
        else
            result |= 0x20000000;
    }
    if ((flag && pTo->mX > from.mX) || (!flag && pTo->mX < from.mX))
        result |= 0x40000000;
    return result;
}

void fn_8016AF34(int team, float *pA, float *pB)
{
    unsigned int rating = 50;
    float value;

    int id = fn_800C8744(team);
    if (fn_801FCE10(0, "select 'PRMT' into \x82 from 'MAET' where 'DIGT' = \x82\n", &rating, id) != 0)
        rating = 50;

    *pA = 0.0f;
    *pB = 0.0f;
    if (rating > 50) {
        value = (float)(rating - 50) * 0.02f;
        *pB = value * 0.5f;
        *pA = -*pB;
    } else if (rating < 50) {
        value = (float)(50 - rating) * 0.02f;
        *pA = value * 0.5f;
        *pB = -*pA;
    }
}

void fn_8016B04C(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EB40C, sizeof(Object_8016B04C), 0, 0x7074726B);
    fn_801C1F94(fn_8023816C(), 0, sizeof(Object_8016B04C));
    fn_802381E0(pHandle);
    fn_8016BAAC();
}

void fn_8016B0AC(void)
{
}

void fn_8016B0B0(void)
{
    int team = fn_80178308();
    Record_80067338 *pRecord = fn_8016871C(team);

    lbl_803EB40C->mUnknown0 = fn_8016B8C8(team, pRecord->mUnknown4);
    lbl_803EB40C->mUnknown4 = fn_8016A334(team);
    lbl_803EB40C->mUnknown8 = fn_8016A408(team);
    lbl_803EB40C->mUnknownC = fn_8016A4DC(team);
    lbl_803EB40C->mUnknown10 = fn_8016A568(team);
    fn_8016B438(team, &lbl_803EB40C->mUnknown18, &lbl_803EB40C->mUnknown14);
}

void fn_8016B144(int team, int value)
{
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];

    for (unsigned char i = 23; i != 0; i--)
        pEntries[i] = pEntries[i - 1];
    fn_801C1F94(pEntries, 0, sizeof(Entry_8016B144));
    pEntries[0].mUnknown0 = value;
    pEntries[0].mUnknownC = -1;

    int count = lbl_803EB40C->mUnknown3DC[team] + 1;
    if (count > 24)
        count = 24;
    lbl_803EB40C->mUnknown3DC[team] = count;
}

void fn_8016B210(int team, int value)
{
    lbl_803EB40C->mUnknown1C[team][0].mUnknown4 = value;
}

void fn_8016B22C(int team, signed char value)
{
    lbl_803EB40C->mUnknown1C[team][0].mUnknownC = value;
}

void fn_8016B248(int team, Point_8016AD80 from, Point_8016AD80 to, int flag)
{
    Entry_8016B144 *pEntry = &lbl_803EB40C->mUnknown1C[team][0];
    pEntry->mUnknown8 = fn_8016AD80(pEntry->mUnknownF, from, &to, flag);
}

void fn_8016B2B8(int team, float value)
{
    lbl_803EB40C->mUnknown1C[team][0].mUnknownD = (int)value;
}

void fn_8016B2E8(int team, unsigned char value)
{
    if (lbl_803EB40C->mUnknown1C[team][0].mUnknownE == 0)
        lbl_803EB40C->mUnknown1C[team][0].mUnknownE = value;
}

void fn_8016B310(int team, unsigned char value)
{
    lbl_803EB40C->mUnknown1C[team][0].mUnknownF = value;
}

void fn_8016B32C(int team, unsigned char value)
{
    lbl_803EB40C->mUnknown1C[team][0].mUnknown10 = value;
}

void fn_8016B348(int team, unsigned char value)
{
    lbl_803EB40C->mUnknown1C[team][0].mUnknown11 = value;
}

void fn_8016B364(int team, Candidate_8016B364 *pList, unsigned int count)
{
    if (team == fn_80178308())
        fn_8016A7DC(team, pList, count);
    else
        fn_8016A9B4(team, pList, count);

    if (fn_800A82FC(team) && fn_80177F70() != 6)
        fn_8016AC24(team, pList, count);

    if (fn_80025708() && team == fn_80178308() && fn_800B65A0(team) == 0xFF) {
        int mode = fn_800785C0()->mUnknown1B4;
        if (mode != 0)
            fn_8016ACD8(team, pList, count, mode);
    }
}

void fn_8016B438(int team, unsigned char *pOut, unsigned int *pFlags)
{
    float passGain = 0.0f;
    float pass = 0.0f;
    float runGain = 0.0f;
    float run = 0.0f;
    float run4 = 0.0f;
    float run8 = 0.0f;
    float run2 = 0.0f;
    float pass100 = 0.0f;
    float pass200 = 0.0f;
    float pass80 = 0.0f;
    float pass40 = 0.0f;
    float pass20 = 0.0f;
    float pass10 = 0.0f;
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];

    *pOut = 0;
    *pFlags = 0;
    if (count <= 8)
        return;

    for (unsigned char i = 0; i < count; i++) {
        unsigned int flags = pEntries[i].mUnknown8;
        float gain;

        switch (pEntries[i].mUnknownE) {
        case 1:
        case 3:
        case 4:
            gain = 0.0f;
            break;
        default:
            gain = pEntries[i].mUnknownD;
            break;
        }

        if (pEntries[i].mUnknownF == 1) {
            run += 1.0f;
            if (gain > 4.9f) {
                runGain += 1.0f;
                if (flags & 2)
                    run2 += 1.0f;
                if (flags & 4)
                    run4 += 1.0f;
                if (flags & 8)
                    run8 += 1.0f;
            }
        } else {
            pass += 1.0f;
            if (gain > 9.0f) {
                passGain += 1.0f;
                if (flags & 0x80)
                    pass80 += 1.0f;
                if (flags & 0x100)
                    pass100 += 1.0f;
                if (flags & 0x200)
                    pass200 += 1.0f;
                if (flags & 0x10)
                    pass10 += 1.0f;
                if (flags & 0x20)
                    pass20 += 1.0f;
                if (flags & 0x40)
                    pass40 += 1.0f;
            }
        }
    }

    if (run <= 7.0f || pass <= 7.0f)
        return;

    float runRate = runGain / run;
    float passRate = passGain / pass;
    if (fabsf(runRate - passRate) > 0.35f)
        *pOut = runRate > passRate ? 1 : 2;

    if (runGain != 0.0f) {
        if (run2 / runGain > 0.4f)
            *pFlags |= 2;
        else if (run8 / runGain > 0.4f)
            *pFlags |= 8;
        else if (run4 / runGain > 0.4f)
            *pFlags |= 4;
    }

    if (passGain != 0.0f) {
        if (pass10 / passGain > 0.4f)
            *pFlags |= 0x10;
        else if (pass20 / passGain > 0.4f)
            *pFlags |= 0x20;
        else if (pass40 / passGain > 0.4f)
            *pFlags |= 0x40;

        if (pass80 / passGain > 0.4f)
            *pFlags |= 0x80;
        else if (pass200 / passGain > 0.4f)
            *pFlags |= 0x200;
        else if (pass100 / passGain > 0.4f)
            *pFlags |= 0x100;
    }
}

unsigned char fn_8016B7C4(Point_8016AD80 *pTo)
{
    int kind = 1;

    if (fn_8011F1CC())
        kind = 2;
    return fn_8016AD80(kind, fn_80177FE0(), pTo, 1) & lbl_803EB40C->mUnknown14;
}

void fn_8016B82C(int team, Record_80067338 *pRecord, unsigned char *pOut, unsigned int *pFlags)
{
    *pFlags = pRecord->mUnknown18 & 0x3FE;
    if (fn_80168708(team)->mUnknown8.mUnknownF != 0) {
        if (*pFlags & 8)
            *pFlags = (*pFlags & ~8) | 2;
        else if (*pFlags & 2)
            *pFlags = (*pFlags & ~2) | 8;
        if (*pFlags & 0x80)
            *pFlags = (*pFlags & ~0x80) | 0x200;
    }
    *pOut = fn_80169F80(pRecord->mUnknown17);
}

float fn_8016B8C8(int team, int value)
{
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    float result = 0.0f;

    for (unsigned short i = 0; i < count; i++) {
        if (value == pEntries[i].mUnknown0)
            result += lbl_802E9970[i / 8];
    }
    return result;
}

float fn_8016B938(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return lbl_803EB40C->mUnknown0;
}

float fn_8016B974(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return lbl_803EB40C->mUnknown4;
}

float GetTrackerFloat8(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return lbl_803EB40C->mUnknown8;
}

float fn_8016B9B0(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return lbl_803EB40C->mUnknownC;
}

float fn_8016B9EC(void)
{
    if (fn_800BA6F8())
        return 0.0f;
    return lbl_803EB40C->mUnknown10;
}

void SumRunWeightsBit28(int team, float *pClear, float *pSet)
{
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    unsigned short runs = 0;

    *pClear = 0.0f;
    *pSet = 0.0f;
    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknownF == 1) {
            runs++;
            if (pEntries[i].mUnknown8 & 0x10000000)
                *pSet += lbl_802E99AC[runs / 8];
            else if (pEntries[i].mUnknown8 & 0x20000000)
                *pClear += lbl_802E99AC[runs / 8];
        }
    }
}

void SumRunWeightsBit30(int team, float *pSet, float *pClear)
{
    unsigned short count = lbl_803EB40C->mUnknown3DC[team];
    Entry_8016B144 *pEntries = lbl_803EB40C->mUnknown1C[team];
    unsigned short runs = 0;

    *pSet = 0.0f;
    *pClear = 0.0f;
    for (unsigned short i = 0; i < count; i++) {
        if (pEntries[i].mUnknownF == 1) {
            runs++;
            if (pEntries[i].mUnknown8 & 0x40000000)
                *pSet += lbl_802E99B8[runs / 8];
            else
                *pClear += lbl_802E99B8[runs / 8];
        }
    }
}

void fn_8016BA28(unsigned char *pOut)
{
    unsigned int flags;

    if (fn_800BA6F8()) {
        *pOut = 0;
        flags = 0;
    } else {
        fn_80169FCC(fn_80178308(), pOut, &flags);
    }
}

void fn_8016BA80(void)
{
    fn_801C1F94(lbl_803EB40C, 0, sizeof(Object_8016B04C));
}

void fn_8016BAAC(void)
{
    fn_8022DDB4(0x53545047, lbl_803EB40C);
}
