#include "game/Class_80148A58.h"
#include "game/LivePlayPhase.h"
#include "game/Class_80297B50.h"
#include "game/Class_80297B90.h"
#include "game/PreGamePhase.h"
#include "game/PostPlayPhase.h"
#include "game/PreSnapPhase.h"
#include "game/ScrmRuleSet.h"
#include "game/GameOptions.h"

void *operator new(unsigned int size, int unknown);

class Class_802A2490 : public PreGamePhase {
public:
    virtual void OnEnter();
};

class Class_802A2450 : public Class_80297B50 {
public:
    virtual void vfn_03();
};

class Class_802A23E0 : public PreSnapPhase {
public:
    virtual void OnEnter(float dt);
};

class Class_802A23A8 : public LivePlayPhase {
public:
    virtual void OnEnter();
    unsigned char mUnknown4;
};

class Class_802A2320 : public PostPlayPhase {
public:
    virtual void OnEnter(float dt);
};

class Class_802A2268 : public ScrmRuleSet {
public:
    virtual int GetTeamSize();
};

class Class_802A2200 : public Class_80297B90 {
public:
    virtual void vfn_06();
};

class Block_802A21E8 {
public:
    Block_802A21E8() : mUnknown20(0), mUnknown24(0) {}

    Class_802A2490 mUnknown0;
    Class_802A2450 mUnknown4;
    Class_802A23E0 mUnknown8;
    Class_802A23A8 mUnknownC;
    Class_802A2320 mUnknown14;
    Class_802A2268 mUnknown18;
    Class_802A2200 mUnknown1C;
    int mUnknown20;
    int mUnknown24;

    virtual ~Block_802A21E8();
};

class Class_802A2C90 : public Class_80148A58 {
public:
    Block_802A21E8 *mpUnknown1C;
    int mUnknown20;
};

extern "C" {
void fn_800BC51C(PreGamePhase *pObject);
void fn_800B3644(Class_80297B50 *pObject);
void fn_800BFAB4(PreSnapPhase *pObject);
void fn_800A039C(LivePlayPhase *pObject);
void fn_800B9598(PostPlayPhase *pObject);
void fn_800AACB8(Class_80297B90 *pObject);
void fn_80178F20(ScrmRuleSet *pObject);
void fn_80177768(void *p, int team);

void fn_8014C690(Class_802A2C90 *p)
{
    p->mUnknown0 = 10;
    p->mUnknown4 = 9;
    p->mpUnknown1C = new (0) Block_802A21E8;
    p->mpUnknown1C->mUnknown20 = GameOptionsGet(14);
    if (p->mpUnknown1C->mUnknown20 != 0) {
        GameOptionsSet(14, 0);
    }
    if (p->mUnknown20 != -1) {
        p->mpUnknown1C->mUnknown24 = GameOptionsGet(1);
        GameOptionsSet(1, p->mUnknown20);
    } else {
        p->mpUnknown1C->mUnknown24 = -1;
    }
    fn_800BC51C(&p->mpUnknown1C->mUnknown0);
    fn_800B3644(&p->mpUnknown1C->mUnknown4);
    fn_800BFAB4(&p->mpUnknown1C->mUnknown8);
    fn_800A039C(&p->mpUnknown1C->mUnknownC);
    fn_800B9598(&p->mpUnknown1C->mUnknown14);
    fn_800AACB8(&p->mpUnknown1C->mUnknown1C);
    fn_80177768(&p->mpUnknown1C->mUnknown18, 2);
    fn_80178F20(&p->mpUnknown1C->mUnknown18);
}
}
