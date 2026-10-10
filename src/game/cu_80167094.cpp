#include "game/State_80167094.h"
#include "game/fn_801C1F94.h"
#include "game/Team_80167A8C.h"
#include "game/fn_800B65A0.h"

struct Record_80167094 {
    unsigned char mUnknown0[8];
    float mUnknown8;
    float mUnknownC;
    unsigned int mUnknown10;
    unsigned char mUnknown14[0x1B8];
};
struct Object_80167160 {
    unsigned char mUnknown0[0x14];
    unsigned int mUnknown14;
};

static Record_80167094 lbl_8031D38C[9][11];
static unsigned char lbl_80328570[3][9];
static State_80167094 lbl_8032858C[3][9];
extern "C" float lbl_802E992C[][2];

extern "C" {
void fn_801651E0(void *, int, signed char, int, Record_80167094 *);
void fn_80165464(void *, int, int, Record_80167094 *);
void fn_80165890(void *, Record_80167094 *, int, unsigned char);
void fn_80165110(Object_80167160 *, int);
void fn_80166BE8(Object_80167160 *, State_80167094 *, Record_80167094 *, int, int, unsigned char);
int fn_8016631C(Record_80167094 *, int, void *, void *, void *, void *, int);
void fn_80165770(Object_80167160 *, State_80167094 *, Record_80167094 *);
Team_80167A8C *fn_80168EBC(int);
void fn_8018A8C8(int);
int fn_8017F60C(void);
int fn_801486A0(void);
int fn_800BA6F8(void);
void fn_801A133C(float, float, void *, unsigned char);
void fn_8018A908(void (*)(int, float, float, float, float));
void fn_801A1338(void);
int fn_801F1520(int);
void fn_801A1240(int);
void fn_801A12E8(void);

void fn_80167094(void *p, unsigned char *input, void *, int a, int b, signed char c, int group, int index)
{
    fn_801651E0(p, a, c, b, lbl_8031D38C[index]);
    unsigned char *out = lbl_8032858C[group][index].mUnknown2078;
    input += 0x8F;
    for (int i = 0; i < 11; ++i) {
        *out++ = *input;
        input += 0x28;
    }
}

void fn_80167128(void *p, void *, int a, int b, int, int index)
{
    fn_80165464(p, a, b, lbl_8031D38C[index]);
}

void fn_80167160(void *p, Object_80167160 *object, int, int, int, int group, int index, int first, unsigned char count, void *)
{
    State_80167094 *state = &lbl_8032858C[group][index];
    int used = first == 0 ? 0 : state->mUnknown940[first];
    int remaining = 0x128;
    Record_80167094 *records = lbl_8031D38C[index];
    fn_80165890(p, records, first, count);
    int flag = object->mUnknown14 > 36 || object->mUnknown14 <= 30;
    state->mUnknown2083 = flag;
    if (lbl_80328570[group][index]) {
        fn_80165110(object, 1);
    }
    int i;
    for (i = first; i < count; ++i) {
        Record_80167094 *record = &records[i];
        state->mUnknown940[i] = used;
        float x = record->mUnknown8;
        float y = record->mUnknownC;
        float dx = lbl_802E992C[record->mUnknown10][0];
        float dy = lbl_802E992C[record->mUnknown10][1];
        state->mUnknown2084[i][3] = y + dy;
        state->mUnknown2084[i][2] = x + dx;
        state->mUnknown2084[i][0] = x - dx;
        state->mUnknown2084[i][1] = y - dy;
        unsigned char value = fn_80168EBC((unsigned char)group)->mUnknown20.mUnknown10;
        fn_80166BE8(object, state, record, group, i, value);
        state->mUnknown2134[i] = record->mUnknown10;
        fn_801C1F94(state->mUnknown19F0[i], 0, 0x30);
        int size = fn_8016631C(record, remaining, state->mUnknown0 + used * 8,
            state->mUnknown970[i], state->mUnknown19F0[i], state->mUnknown1E10[i], flag);
        remaining -= size;
        used += size;
    }
    state->mUnknown940[i] = used;
    fn_80165770(object, state, records);
}

void fn_801673A0(int code, float x, float y, float, float)
{
    fn_8018A8C8(5);
    int flag = 1;
    if ((!fn_8017F60C() && fn_801486A0() != 3 && fn_800B65A0(0) != 0xFF && fn_800B65A0(1) != 0xFF) || fn_800BA6F8()) {
        flag = 0;
    }
    switch ((unsigned int)code) {
    case 0: fn_801A133C(x, y, &lbl_8032858C[1][0], lbl_80328570[1][0]); break;
    case 1: fn_801A133C(x, y, &lbl_8032858C[1][1], lbl_80328570[1][1]); break;
    case 4:
        if (flag) { fn_801A133C(x, y, &lbl_8032858C[1][4], lbl_80328570[1][4]); break; }
    case 2: fn_801A133C(x, y, &lbl_8032858C[1][2], lbl_80328570[1][2]); break;
    case 5:
        if (flag) { fn_801A133C(x, y, &lbl_8032858C[1][5], lbl_80328570[1][5]); break; }
    case 3: fn_801A133C(x, y, &lbl_8032858C[1][3], lbl_80328570[1][3]); break;
    case 6: fn_801A133C(x, y, &lbl_8032858C[1][6], lbl_80328570[1][6]); break;
    case 7: fn_801A133C(x, y, &lbl_8032858C[1][7], lbl_80328570[1][7]); break;
    case 10: if (flag) goto case14;
    case 8: fn_801A133C(x, y, &lbl_8032858C[0][0], lbl_80328570[0][0]); break;
    case 11: if (flag) goto case15;
    case 9: fn_801A133C(x, y, &lbl_8032858C[0][1], lbl_80328570[0][1]); break;
    case 12: fn_801A133C(x, y, &lbl_8032858C[0][4], lbl_80328570[0][4]); break;
    case 13: fn_801A133C(x, y, &lbl_8032858C[0][5], lbl_80328570[0][5]); break;
    case 14:
        if (flag) { fn_801A133C(x, y, &lbl_8032858C[0][6], lbl_80328570[0][6]); break; }
    case14: fn_801A133C(x, y, &lbl_8032858C[0][2], lbl_80328570[0][2]); break;
    case 15:
        if (flag) { fn_801A133C(x, y, &lbl_8032858C[0][7], lbl_80328570[0][7]); break; }
    case15: fn_801A133C(x, y, &lbl_8032858C[0][3], lbl_80328570[0][3]); break;
    default: fn_801A133C(x, y, &lbl_8032858C[0][code + 2], lbl_80328570[0][code + 2]); break;
    }
}

void fn_80167720(void)
{
    fn_801C1F94(lbl_80328570[0], fn_80168EBC(0)->mUnknown20.mUnknown10, 9);
    fn_801C1F94(lbl_80328570[1], fn_80168EBC(1)->mUnknown20.mUnknown10, 9);
    fn_801C1F94(lbl_80328570[2], 0, 9);
    fn_8018A908(fn_801673A0);
}
void fn_80167794(signed char group, int value, int index)
{
    if (index == -1) {
        fn_801C1F94(lbl_80328570[group], value, 9);
    } else {
        lbl_80328570[group][index] = value;
    }
}
void fn_801677F4(void)
{
    fn_8018A908(0);
    fn_801A1338();
}
void fn_8016781C(int value)
{
    int saved = fn_801F1520(4);
    fn_801A1240(value);
    fn_801F1520(saved);
}
void fn_80167860(void)
{
    fn_801A12E8();
}
void fn_80167880(void)
{
    fn_801C1F94(lbl_8031D38C, 0, sizeof(lbl_8031D38C));
    fn_801C1F94(lbl_8032858C, 0, sizeof(lbl_8032858C));
}
void fn_801678CC(int group)
{
    fn_801C1F94(lbl_8032858C[group], 0, sizeof(lbl_8032858C[group]));
}
}
