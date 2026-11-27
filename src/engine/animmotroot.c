/* Animation motion root blending: mixes the root turn and root movement of a player's
   animation channels into one heading change and one 2D offset, and turns a pose around. */

#include "engine/animchan.h"

typedef struct Entry_801BCA74 {
    float mUnknown0;
    unsigned char mUnknown4[4];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA[2];
    Triple_801BCA74 mUnknownC;
    Pair_802270A4 mUnknown18;
    unsigned char mUnknown20[12];
} Entry_801BCA74;

typedef struct Anim_801BCA74 {
    unsigned short mUnknown0;
    unsigned char mUnknown2[2];
    Entry_801BCA74 mUnknown4[1];
} Anim_801BCA74;

void OrientLerpAngle(int *pOut, int a, int b, float t);

int AnimMotBlendRootAngle(AnimHeader_t *pObject, AnimChannel_t *pRecords, Anim_801BCA74 *pAnim, int *pOut, int key, int all)
{
    float total = 0.0f;
    int found = 0;
    int value = 0;
    Triple_801BCA74 target;
    int i;

    for (i = 0; i < pAnim->mUnknown0; i++) {
        Entry_801BCA74 *pEntry = &pAnim->mUnknown4[i];
        int index = pEntry->mUnknown9;

        if (i + 1 < pAnim->mUnknown0 && pAnim->mUnknown4[i + 1].mUnknown9 == index) {
            if (!(pRecords[index].mUnknown4C.mUnknown1E & 0x10)) {
                Triple_801BCA74 *pNext = &pAnim->mUnknown4[i + 1].mUnknownC;

                target.mUnknown0 = pNext->mUnknown0;
                target.mUnknown4 = pNext->mUnknown4;
                target.mUnknown8 = pNext->mUnknown8;
            } else {
                target.mUnknown8 = 0;
                target.mUnknown4 = 0;
                target.mUnknown0 = 0;
            }
            _AnimMotBlendOrient(&pRecords[index].mUnknown10, &pEntry->mUnknownC, &target, pRecords[index].mUnknown4C.mUnknown14);
            i++;
        } else {
            Triple_801BCA74 *pDst;

            // FAKEMATCH: the first word is stored through pRecords[index] and the other two through
            // pDst; one uniform copy form gives the base+offset add order instead of offset+base.
            pRecords[index].mUnknown10.mUnknown0 = pEntry->mUnknownC.mUnknown0;
            pDst = &pRecords[index].mUnknown10;
            pDst->mUnknown4 = pEntry->mUnknownC.mUnknown4;
            pDst->mUnknown8 = pEntry->mUnknownC.mUnknown8;
        }
        if (pEntry->mUnknown8 & 2) {
            int angle;
            int delta;
            float weight;

            if (pRecords[index].mUnknown4C.mUnknown1E & 8) {
                pRecords[index].mUnknownC = pObject->mUnknown8;
                pRecords[index].mUnknown1C = 0;
                pRecords[index].mUnknown4C.mUnknown1E = (pRecords[index].mUnknown4C.mUnknown1E & ~8) | 0x10;
            }
            if (pRecords[index].mUnknown4C.mUnknown1E & 0x20) {
                pRecords[index].mUnknown4C.mUnknown1E &= ~0x38;
            }
            angle = pRecords[index].mUnknown10.mUnknown4 << 8 >> 8;
            pRecords[index].mUnknown10.mUnknown4 = 0;
            delta = angle - pRecords[index].mUnknown1C;
            pRecords[index].mUnknown1C = angle;
            delta = (int)(((long long)pRecords[index].mUnknown20 * delta) >> 24);
            total += pEntry->mUnknown0;
            weight = total != 0.0f ? pEntry->mUnknown0 / total : 0.0f;
            {
                int apply = all;

                if (pRecords[index].mUnknown8 == key || pRecords[index].mUnknown8 == 0xFFFF || key == 0xFFFF) {
                    found = 1;
                    apply = 1;
                }
                if (apply) {
                    OrientLerpAngle(&value, delta, value, weight);
                }
            }
        }
    }
    if (found) {
        *pOut = value;
    }
    return found;
}

void Vec2Scale(Pair_802270A4 *pOut, Pair_802270A4 *pIn, float scale);
void Vec2Rotate(Pair_802270A4 *pOut, Pair_802270A4 *pIn, int angle);
void Vec2Add(Pair_802270A4 *pOut, Pair_802270A4 *pA, Pair_802270A4 *pB);
void Vec2Sub(Pair_802270A4 *pOut, Pair_802270A4 *pA, Pair_802270A4 *pB);
void Vec2Lerp(Pair_802270A4 *pOut, Pair_802270A4 *pA, Pair_802270A4 *pB, float t);

// FAKEMATCH: the channel-offset reset and the running blend go through these two inline helpers;
// their parameter copies keep the 0.0f reload and the &sum/&delta addresses in the target's registers.
static inline void _AnimMotVec2Zero(Pair_802270A4 *pVec)
{
    pVec->mUnknown4 = 0.0f;
    pVec->mUnknown0 = 0.0f;
}

static inline void _AnimMotBlendSum(Pair_802270A4 *pSum, Pair_802270A4 *pDelta, float weight)
{
    Vec2Lerp(pSum, pDelta, pSum, weight);
}

int AnimMotBlendRootOffset(AnimHeader_t *pObject, AnimChannel_t *pRecords, Anim_801BCA74 *pAnim, Pair_802270A4 *pOut, int key, int all)
{
    Pair_802270A4 sum;
    Pair_802270A4 offset;
    Pair_802270A4 delta;
    float total;
    int found = 0;
    int i;

    sum.mUnknown4 = 0.0f;
    sum.mUnknown0 = 0.0f;
    total = 0.0f;
    for (i = 0; i < pAnim->mUnknown0; i++) {
        Entry_801BCA74 *pEntry = &pAnim->mUnknown4[i];

        if (pEntry->mUnknown8 & 4) {
            int index = pEntry->mUnknown9;
            int apply = all;

            if (pRecords[index].mUnknown8 == key || pRecords[index].mUnknown8 == 0xFFFF || key == 0xFFFF) {
                found = 1;
                apply = 1;
            }
            if (apply == 1) {
                if (pRecords[index].mUnknown4C.mUnknown1E & 1) {
                    _AnimMotVec2Zero(&pRecords[index].mUnknown24);
                    pRecords[index].mUnknown4C.mUnknown1E = (pRecords[index].mUnknown4C.mUnknown1E & ~1) | 2;
                }
                if (pRecords[index].mUnknown4C.mUnknown1E & 4) {
                    pRecords[index].mUnknown4C.mUnknown1E &= ~7;
                }
                if (i + 1 < pAnim->mUnknown0 && pAnim->mUnknown4[i + 1].mUnknown9 == index) {
                    if (!(pRecords[index].mUnknown4C.mUnknown1E & 2)) {
                        Vec2Lerp(&offset, &pEntry->mUnknown18, &pAnim->mUnknown4[i + 1].mUnknown18, pRecords[index].mUnknown4C.mUnknown14);
                    } else {
                        Vec2Scale(&offset, &pEntry->mUnknown18, pRecords[index].mUnknown4C.mUnknown14);
                    }
                    i++;
                } else {
                    offset.mUnknown0 = pEntry->mUnknown18.mUnknown0;
                    offset.mUnknown4 = pEntry->mUnknown18.mUnknown4;
                }
                Vec2Sub(&delta, &offset, &pRecords[index].mUnknown24);
                Vec2Add(&pRecords[index].mUnknown24, &pRecords[index].mUnknown24, &delta);
                Vec2Scale(&delta, &delta, pRecords[index].mUnknown2C);
                Vec2Rotate(&delta, &delta, pRecords[index].mUnknownC);
                total += pEntry->mUnknown0;
                _AnimMotBlendSum(&sum, &delta, total != 0.0f ? pEntry->mUnknown0 / total : 0.0f);
            }
        }
    }
    if (found) {
        pOut->mUnknown4 = sum.mUnknown4;
        pOut->mUnknown0 = sum.mUnknown0;
    }
    return found;
}

void AnimMotRotateHalfTurn(AnimHeader_t *p, AnimChannel_t *pRecords)
{
    int i;

    p->mUnknown8 = (p->mUnknown8 + 0x800000) & 0xFFFFFF;
    for (i = 0; i < p->mUnknown4; i++, pRecords++) {
        if (pRecords->mUnknown1 != 0) {
            pRecords->mUnknownC = (pRecords->mUnknownC + 0x800000) & 0xFFFFFF;
        }
    }
}
