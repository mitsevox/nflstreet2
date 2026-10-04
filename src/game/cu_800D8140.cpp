#include "game/Object_800D81C8.h"
#include "game/fn_80227638.h"

struct State_800D8140 {
    Pair_802270A4 mUnknown0;
    float mUnknown8;
    float mUnknownC;
    float mUnknown10;
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    unsigned char mUnknown16;
    unsigned char mUnknown17;
};

struct Block_801BE60C {
    char mUnknown0[32];
    State_800D8140 mUnknown20;
};

extern "C" {
float fn_800C4A2C(Object_800D81C8 *p);
void fn_80044854(Object_800D81C8 *p, State_800D8140 *pState);
Object_800D81C8 *fn_80137B40(void);
int fn_801784C4(void);
int fn_801787A0(void);
float fn_801BD660(void *p, int key);
float fn_801BD6D4(Block_801BD6D4 *p);
Block_801BE60C *fn_801BE60C(void *p, int key);
int fn_801BE648(void *p);
float fn_802270A4(Pair_802270A4 *p);
void fn_80227248(Pair_802270A4 *p, Pair_802270A4 *pOther, float value);
void fn_8022728C(Pair_802270A4 *p, Pair_802270A4 *pOther, float value);
}

static float lbl_803EC9E0;
static float lbl_803EC9E4;

extern "C" void fn_800D8140(State_800D8140 *p, Object_800D81C8 *pOther, unsigned char value)
{
    p->mUnknown14 = 0;
    p->mUnknown16 = 0;
    float a = fn_800C4A2C(pOther);
    p->mUnknown10 = a;
    if (!(a < 0.0f)) {
        p->mUnknown17 = value;
        lbl_803EC9E4 = a * 35.0f;
        lbl_803EC9E0 = a * 50.0f;
    } else {
        p->mUnknown10 = 0.0f;
        p->mUnknown17 = 255;
    }
}

extern "C" void fn_800D81C8(State_800D8140 *p, Object_800D81C8 *pOther)
{
    Block_801BD6D4 *pBlock = &pOther->mpUnknown320[p->mUnknown17].mUnknown4C;
    if (p->mUnknown17 != 255 && (pOther->mUnknownC & 0x800)) {
        if (!(pOther->mUnknownC & 8)) {
            float time = fn_801BD6D4(pBlock);
            float value = time / pBlock->mUnknown4;
            if (!p->mUnknown14) {
                p->mUnknown0.mUnknown0 = pOther->mUnknown1D0.mUnknown0;
                p->mUnknown0.mUnknown4 = pOther->mUnknown1D0.mUnknown4;
                float a = fn_800C4A2C(pOther);
                p->mUnknown10 = a;
                fn_80227248(&p->mUnknown0, &p->mUnknown0, a);
                if (fn_802270A4(&p->mUnknown0) > 0.25f) {
                    fn_8022728C(&p->mUnknown0, &p->mUnknown0, 0.25f);
                }
                p->mUnknown8 = time;
                p->mUnknownC = fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC004);
                p->mUnknownC = p->mUnknownC < fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000)
                    ? p->mUnknownC : fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000);
                float delta = p->mUnknownC - p->mUnknown8;
                if (delta > lbl_803EC9E0) {
                    p->mUnknownC = p->mUnknown8 + lbl_803EC9E0;
                } else if (delta < lbl_803EC9E4) {
                    p->mUnknownC = p->mUnknown8 + lbl_803EC9E4;
                }
                p->mUnknown8 /= pBlock->mUnknown4;
                p->mUnknownC /= pBlock->mUnknown4;
                p->mUnknown14 = 1;
                p->mUnknown15 = fn_801784C4();
                fn_80044854(pOther, p);
            } else if (value < p->mUnknownC) {
                float alpha = (value - p->mUnknown8) / (p->mUnknownC - p->mUnknown8);
                alpha = alpha < 0.0f ? 0.0f : alpha > 1.0f ? 1.0f : alpha;
                float length = fn_802270A4(&p->mUnknown0);
                float cap = pOther->mUnknown1C4;
                if (length > cap) {
                    fn_80227248(&p->mUnknown0, &p->mUnknown0, cap / length);
                }
                float a = fn_800C4A2C(pOther);
                if (a < p->mUnknown10) {
                    p->mUnknown10 = a;
                    fn_80227248(&p->mUnknown0, &p->mUnknown0, a);
                    if (fn_802270A4(&p->mUnknown0) > 0.25f) {
                        fn_8022728C(&p->mUnknown0, &p->mUnknown0, 0.25f);
                    }
                }
                int otherFlag = fn_801784C4();
                if (p->mUnknown15 != otherFlag) {
                    p->mUnknown0.mUnknown0 = -p->mUnknown0.mUnknown0;
                    p->mUnknown0.mUnknown4 = -p->mUnknown0.mUnknown4;
                    p->mUnknown15 = fn_801784C4();
                }
                Pair_802270A4 other;
                fn_80227248(&other, &p->mUnknown0, 1.0f - alpha);
                fn_80227638(&pOther->mUnknown1A8, &pOther->mUnknown1A8, &other);
                fn_80227248(&p->mUnknown0, &p->mUnknown0, 0.85f);
            }
    }
    }
}

extern "C" void fn_800D84DC(State_800D8140 *p, Object_800D81C8 *pOther)
{
    if (p && pOther) {
        Record_800D81C8 *pRecord = &pOther->mpUnknown320[p->mUnknown17];
        Block_801BD6D4 *pBlock = &pRecord->mUnknown4C;
        if (p->mUnknown17 == 255) return;
        if ((pOther->mUnknownC & 8) && p->mUnknown16) return;
        int id = fn_801BE648(pOther->mpUnknown318);
        Object_800D81C8 *pThird = fn_8009BCE8(pOther->mUnknown150);
        if (!pThird) return;
        Block_801BE60C *pResult = fn_801BE60C(pThird->mpUnknown318, id);
        if (!pResult) return;
        State_800D8140 *pState = &pResult->mUnknown20;
        int flag;
        if (pOther->mUnknownC & 8) {
            flag = fn_801BD660(pRecord->mUnknown4C.mpUnknown0, 0xC00E)
                > fn_801BD660(pRecord->mUnknown4C.mpUnknown0, 0xC001);
        } else {
            flag = 0;
        }
        if (!(pOther->mUnknownC & 0x800)) return;
        if (flag && fn_80137B40() != pOther) return;
        float time = fn_801BD6D4(pBlock);
        float value = time / pBlock->mUnknown4;
        if (!p->mUnknown14) {
            p->mUnknown0.mUnknown0 = pOther->mUnknown1D0.mUnknown0;
            p->mUnknown0.mUnknown4 = pOther->mUnknown1D0.mUnknown4;
            float a = fn_800C4A2C(pOther);
            p->mUnknown10 = a;
            fn_80227248(&p->mUnknown0, &p->mUnknown0, a);
            if (fn_802270A4(&p->mUnknown0) > 0.25f) {
                fn_8022728C(&p->mUnknown0, &p->mUnknown0, 0.25f);
            }
            p->mUnknown8 = time;
            p->mUnknownC = fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC004);
            p->mUnknownC = p->mUnknownC < fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC002)
                ? p->mUnknownC : fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC002);
            p->mUnknownC = p->mUnknownC < fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000)
                ? p->mUnknownC : fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000);
            p->mUnknownC = p->mUnknownC < fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC00E)
                ? p->mUnknownC : fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC00E);
            p->mUnknownC = p->mUnknownC < fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000)
                ? p->mUnknownC : fn_801BD660(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000);
            float delta = p->mUnknownC - p->mUnknown8;
            if (delta > lbl_803EC9E0) {
                p->mUnknownC = p->mUnknown8 + lbl_803EC9E0;
            } else if (delta < lbl_803EC9E4) {
                p->mUnknownC = p->mUnknown8 + lbl_803EC9E4;
            }
            p->mUnknown8 /= pBlock->mUnknown4;
            p->mUnknownC /= pBlock->mUnknown4;
            p->mUnknown14 = 1;
            p->mUnknown15 = fn_801784C4();
            fn_80044854(pOther, p);
        } else if (value < p->mUnknownC) {
            float alpha = (value - p->mUnknown8) / (p->mUnknownC - p->mUnknown8);
            alpha = alpha < 0.0f ? 0.0f : alpha > 1.0f ? 1.0f : alpha;
            float length = fn_802270A4(&p->mUnknown0);
            float cap = pOther->mUnknown1C4;
            if (length > cap) {
                fn_80227248(&p->mUnknown0, &p->mUnknown0, cap / length);
            }
            float a = fn_800C4A2C(pOther);
            if (a < p->mUnknown10) {
                p->mUnknown10 = a;
                fn_80227248(&p->mUnknown0, &p->mUnknown0, a);
                if (fn_802270A4(&p->mUnknown0) > 0.25f) {
                    fn_8022728C(&p->mUnknown0, &p->mUnknown0, 0.25f);
                }
            }
            int otherFlag = fn_801784C4();
            if (p->mUnknown15 != otherFlag) {
                p->mUnknown0.mUnknown0 = -p->mUnknown0.mUnknown0;
                p->mUnknown0.mUnknown4 = -p->mUnknown0.mUnknown4;
                p->mUnknown15 = fn_801784C4();
            }
            Pair_802270A4 other;
            fn_80227248(&other, &p->mUnknown0, 1.0f - alpha);
            fn_80227638(&pOther->mUnknown1A8, &pOther->mUnknown1A8, &other);
            fn_80227248(&p->mUnknown0, &p->mUnknown0, 0.85f);
            if ((pOther->mUnknownC & 8) && !fn_801787A0()) {
                fn_80227638(&pThird->mUnknown1A8, &pThird->mUnknown1A8, &other);
                pState->mUnknown0.mUnknown0 = p->mUnknown0.mUnknown0;
                pState->mUnknown0.mUnknown4 = p->mUnknown0.mUnknown4;
            }
        }
        if ((pOther->mUnknownC & 8) && fn_80137B40() == pOther && !fn_801787A0()) {
            pState->mUnknown8 = p->mUnknown8;
            pState->mUnknownC = p->mUnknownC;
            pState->mUnknown14 = 1;
            pState->mUnknown16 = 1;
        }
    }
}
