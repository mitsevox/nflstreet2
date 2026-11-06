/* Animation momentum. When a player starts certain animations, the speed he
   was moving at is not dropped at once: it is captured on the first frame and
   keeps pushing the player along, fading out, until a time marked in the
   animation. A linked version also moves a second, linked player the
   same way. */

#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/Object_80039F5C.h"
#include "game/AnimMomentumActor.h"
#include "game/Block_801BE60C.h"
#include "game/fn_801BE60C.h"

extern "C" {
float fn_800C4A2C(AnimMomentumActor_t *p);
void fn_80044854(AnimMomentumActor_t *p, AnimMomentum_t *pState);
AnimMomentumActor_t *fn_80137B40(void);
int fn_801784C4(void);
int fn_801787A0(void);
float AnimSeqGetOpcodeTime(void *p, int key);
float AnimSeqGetTime(AnimSeq_t *p);
void fn_80227248(Pair_802270A4 *p, Pair_802270A4 *pOther, float value);
void fn_8022728C(Pair_802270A4 *p, Pair_802270A4 *pOther, float value);
}

static float _AnimMomentum_fMaxWindow;
static float _AnimMomentum_fMinWindow;

extern "C" void AnimMomentumInit(AnimMomentum_t *p, AnimMomentumActor_t *pOther, int value)
{
    p->mUnknown14 = 0;
    p->mUnknown16 = 0;
    float a = fn_800C4A2C(pOther);
    p->mUnknown10 = a;
    if (!(a < 0.0f)) {
        p->mUnknown17 = value;
        _AnimMomentum_fMinWindow = a * 35.0f;
        _AnimMomentum_fMaxWindow = a * 50.0f;
    } else {
        p->mUnknown10 = 0.0f;
        p->mUnknown17 = 255;
    }
}

extern "C" void AnimMomentumUpdate(AnimMomentum_t *p, AnimMomentumActor_t *pOther)
{
    AnimSeq_t *pBlock = &pOther->mpUnknown320[p->mUnknown17].mUnknown4C;
    if (p->mUnknown17 != 255 && (pOther->mUnknownC & 0x800)) {
        if (!(pOther->mUnknownC & 8)) {
            float time = AnimSeqGetTime(pBlock);
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
                p->mUnknownC = AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC004);
                p->mUnknownC = p->mUnknownC < AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000)
                    ? p->mUnknownC : AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000);
                float delta = p->mUnknownC - p->mUnknown8;
                if (delta > _AnimMomentum_fMaxWindow) {
                    p->mUnknownC = p->mUnknown8 + _AnimMomentum_fMaxWindow;
                } else if (delta < _AnimMomentum_fMinWindow) {
                    p->mUnknownC = p->mUnknown8 + _AnimMomentum_fMinWindow;
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

extern "C" void AnimMomentumUpdateLinked(AnimMomentum_t *p, AnimMomentumActor_t *pOther)
{
    if (p && pOther) {
        Record_800D81C8 *pRecord = &pOther->mpUnknown320[p->mUnknown17];
        AnimSeq_t *pBlock = &pRecord->mUnknown4C;
        if (p->mUnknown17 == 255) return;
        if ((pOther->mUnknownC & 8) && p->mUnknown16) return;
        unsigned short id = fn_801BE648(pOther->mpUnknown318);
        Object_80039F5C *pThird = fn_8009BCE8(&pOther->mUnknown150);
        if (!pThird) return;
        Block_801BE60C *pResult = fn_801BE60C(pThird->mpUnknown792, id);
        if (!pResult) return;
        AnimMomentum_t *pState = &pResult->mUnknown20;
        int flag;
        if (pOther->mUnknownC & 8) {
            flag = AnimSeqGetOpcodeTime(pRecord->mUnknown4C.mpUnknown0, 0xC00E)
                > AnimSeqGetOpcodeTime(pRecord->mUnknown4C.mpUnknown0, 0xC001);
        } else {
            flag = 0;
        }
        if (!(pOther->mUnknownC & 0x800)) return;
        if (flag && fn_80137B40() != pOther) return;
        float time = AnimSeqGetTime(pBlock);
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
            p->mUnknownC = AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC004);
            p->mUnknownC = p->mUnknownC < AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC002)
                ? p->mUnknownC : AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC002);
            p->mUnknownC = p->mUnknownC < AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000)
                ? p->mUnknownC : AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000);
            p->mUnknownC = p->mUnknownC < AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC00E)
                ? p->mUnknownC : AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC00E);
            p->mUnknownC = p->mUnknownC < AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000)
                ? p->mUnknownC : AnimSeqGetOpcodeTime(pOther->mpUnknown320[p->mUnknown17].mUnknown4C.mpUnknown0, 0xC000);
            float delta = p->mUnknownC - p->mUnknown8;
            if (delta > _AnimMomentum_fMaxWindow) {
                p->mUnknownC = p->mUnknown8 + _AnimMomentum_fMaxWindow;
            } else if (delta < _AnimMomentum_fMinWindow) {
                p->mUnknownC = p->mUnknown8 + _AnimMomentum_fMinWindow;
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
                fn_80227638(&pThird->mMotion.mPos, &pThird->mMotion.mPos, &other);
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
