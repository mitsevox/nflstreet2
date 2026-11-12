#include "game/Class_80148A58.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297CE8.h"
#include "game/Object_80039F5C.h"
#include "game/Ball.h"
#include "game/fn_8009D990.h"
#include "game/fn_800B65A0.h"
#include "game/fn_80178D18.h"
#include "game/fn_802372EC.h"
#include "game/Class_802A56E8.h"
#include "game/cu_8013BB18.h"

class Class_802A1930 : public Class_802A56E8 {
};

class Class_802A1BC8 : public Class_80297BF8 {
};

class Class_802A1B58 : public Class_80297CE8 {
public:
    Block_80170E64 *mpUnknown4[2][2];
    signed char mUnknown20[2][2];
};

class Class_802A27F0 : public Class_80148A58 {
public:
    virtual void vfn_35(int a, int b);
};

struct Score_801531C4 {
    int mUnknown0[2];
    int mUnknown8;
    unsigned int mUnknown12;
    unsigned int mUnknown16;
    unsigned short mUnknown20[2];
    unsigned short mUnknown24[2];
    unsigned short mUnknown28[2];
    unsigned char mUnknown32;
};

struct Rules_801531C4 {
    char mUnknown0[44];
    Class_802A1930 mUnknown44;
    char mUnknown48[4];
    Score_801531C4 *mpUnknown52;
};

extern "C" {
extern char *lbl_803EB2F0;
extern const char lbl_802A0B74[];

int fn_800C1E40(void);
void MsgBoxShow(const char *pTitle, const char *pText, const char *pButtons);
Rules_801531C4 *fn_80155128(Class_80148A58 *p);
int MsgBoxIsClosed(void);
void CamGameSetModeAll(int a);
void CamGameSelectCamera(int a);
GameCamera_t *CamGameGetCamera(int index);
void fn_80141164(float value);
int fn_80178308(void);
int fn_80178320(void);
void fn_801486A8(void);
void fn_801487C0(int team, unsigned char begin);
unsigned int fn_80153328(Class_802A1930 *p);
void HudShowAlert(const char *pText);
void BallResetToSpot(void);
Object_80039F5C *PlyrFindNearest(Vector_80039F5C *pPos, float *pOut, int team);
unsigned char fn_8007AFDC(int team);
int fn_800B65D0(int team);
void fn_800B6714(Object_80039F5C *p, int a);
void fn_800B65C0(int team, unsigned char index);

void fn_80153844(Class_802A1930 *p, int team)
{
    Rules_801531C4 *pRules = fn_80155128(fn_80148A58());
    int other = !team;

    pRules->mpUnknown52->mUnknown24[team] = pRules->mpUnknown52->mUnknown20[team] = pRules->mpUnknown52->mUnknown20[other] = pRules->mpUnknown52->mUnknown16;
    if (pRules->mpUnknown52->mUnknown24[other] >= pRules->mpUnknown52->mUnknown24[team]) {
        pRules->mpUnknown52->mUnknown24[other] = pRules->mpUnknown52->mUnknown24[team] - 1;
    }
    pRules->mpUnknown52->mUnknown32 = team;
}

void fn_801538C8(Class_802A1BC8 *p)
{
    p->Class_80297BF8::vfn_05();
    CamGameSetModeAll(1);
    CamGameSelectCamera(0);
    fn_8013C6F0(CamGameGetCamera(5));
    fn_80141164(2.5f);
}

void fn_80153910(Class_802A1BC8 *p, float dt)
{
    if (MsgBoxIsClosed()) {
        p->Class_80297BF8::vfn_04(dt);
    }
}

void fn_8015399C(Class_802A1BC8 *p)
{
}

void fn_8015395C(Class_802A1BC8 *p)
{
    if (fn_800C1E40() == 0) {
        MsgBoxShow("Open Field Showdown", lbl_803EB2F0, lbl_802A0B74);
    }
}

void fn_801539A0(Class_802A1B58 *p, float dt)
{
    Rules_801531C4 *pRules = fn_80155128(fn_80148A58());
    int team = fn_80178308();

    fn_801486A8();
    p->Class_80297CE8::vfn_04(dt);
    fn_801487C0(0, fn_80148A58()->vfn_05(0));
    fn_801487C0(1, fn_80148A58()->vfn_05(1));
    do {
        pRules->mpUnknown52->mUnknown8 = fn_802372EC(0, 3);
    } while (pRules->mpUnknown52->mUnknown8 == pRules->mpUnknown52->mUnknown0[team] && fn_802372EC(0, 100) > 20);
    pRules->mpUnknown52->mUnknown0[team] = pRules->mpUnknown52->mUnknown8;
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(fn_80178308(), 1);
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(fn_80178320(), 0);

    unsigned int limit = pRules->mpUnknown52->mUnknown12;
    if (fn_80153328(&pRules->mUnknown44) > limit && pRules->mpUnknown52->mUnknown20[0] == pRules->mpUnknown52->mUnknown20[1]) {
        HudShowAlert("Playoff Round!");
    }
    if ((unsigned int)fn_80178D70(0) > 1) {
        unsigned int value = fn_8009D990(0);
        lbl_803EABA4->fn_800C02D4(value - 2);
        value = fn_8009D990(0);
        lbl_803EABA4->fn_800C02EC(value - 4);
    } else {
        lbl_803EABA4->fn_800C02EC(39);
    }
    BallResetToSpot();
    Ball_t *pBall = BallGetCurrent();
    Vector_80039F5C pos;
    BallGetPosition(pBall, &pos);
    BallGiveToPlayer(pBall, PlyrFindNearest(&pos, 0, fn_80178308()));
}

void fn_80153BBC(Class_802A1B58 *p)
{
    p->Class_80297CE8::vfn_10();
    int team = fn_80178308();
    unsigned char kind = fn_8007AFDC(team);
    int first = fn_800B65A0(team);
    int second = fn_800B65D0(team);
    Object_80039F5C *p0 = PlyrGet(team, 0);
    Object_80039F5C *p1 = PlyrGet(team, 1);

    if (kind == 2) {
        if (!p->mpUnknown4[team][0]) {
            p->mpUnknown4[team][0] = p0->mpUnknown4;
            p->mUnknown20[team][0] = first;
        }
        if (!p->mpUnknown4[team][1]) {
            p->mpUnknown4[team][1] = p1->mpUnknown4;
            p->mUnknown20[team][1] = second;
        }
        if (p->mpUnknown4[team][0] == p0->mpUnknown4 || p->mUnknown20[team][0] != first) {
            fn_800B6714(p0, first);
            fn_800B6714(p1, second);
            fn_800B65C0(team, first);
        } else {
            fn_800B6714(p1, first);
            fn_800B6714(p0, second);
            fn_800B65C0(team, second);
        }
    }
    team = fn_80178320();
    kind = fn_8007AFDC(team);
    first = fn_800B65A0(team);
    second = fn_800B65D0(team);
    p0 = PlyrGet(team, 0);
    p1 = PlyrGet(team, 1);
    if (kind == 2) {
        if (!p->mpUnknown4[team][0]) {
            p->mpUnknown4[team][0] = p0->mpUnknown4;
            p->mUnknown20[team][0] = first;
        }
        if (!p->mpUnknown4[team][1]) {
            p->mpUnknown4[team][1] = p1->mpUnknown4;
            p->mUnknown20[team][1] = second;
        }
        fn_800B6714(p0, first);
        fn_800B6714(p1, second);
        fn_800B65C0(team, first);
    }
}
}
