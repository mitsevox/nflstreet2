#include "engine/cu_801B9F00.h"

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

void fn_801CF8A8(int *pOut, int a, int b, float t);

int fn_801BCA74(Object_801BA03C *pObject, Record_800D81C8 *pRecords, Anim_801BCA74 *pAnim, int *pOut, int key, int all)
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
                target = pAnim->mUnknown4[i + 1].mUnknownC;
            } else {
                target.mUnknown8 = 0;
                target.mUnknown4 = 0;
                target.mUnknown0 = 0;
            }
            fn_801BC67C(&pRecords[index].mUnknown10, &pEntry->mUnknownC, &target, pRecords[index].mUnknown4C.mUnknown14);
            i++;
        } else {
            pRecords[index].mUnknown10 = pEntry->mUnknownC;
        }
        if (pEntry->mUnknown8 & 2) {
            Record_800D81C8 *pRecord = &pRecords[index];
            int angle;
            int delta;
            int blend;
            float weight;

            if (pRecord->mUnknown4C.mUnknown1E & 8) {
                pRecord->mUnknown1C = 0;
                pRecord->mUnknownC = pObject->mUnknown8;
                pRecord->mUnknown4C.mUnknown1E = (pRecord->mUnknown4C.mUnknown1E & ~8) | 0x10;
            }
            if (pRecord->mUnknown4C.mUnknown1E & 0x20) {
                pRecord->mUnknown4C.mUnknown1E &= ~0x38;
            }
            angle = pRecord->mUnknown10.mUnknown4 << 8 >> 8;
            pRecord->mUnknown10.mUnknown4 = 0;
            delta = angle - pRecord->mUnknown1C;
            pRecord->mUnknown1C = angle;
            blend = (int)(((long long)pRecord->mUnknown20 * delta) >> 24);
            total += pEntry->mUnknown0;
            weight = total != 0.0f ? pEntry->mUnknown0 / total : 0.0f;
            {
                int apply = all;

                if (pRecord->mUnknown8 == key || pRecord->mUnknown8 == 0xFFFF || key == 0xFFFF) {
                    found = 1;
                    apply = 1;
                }
                if (apply) {
                    fn_801CF8A8(&value, blend, value, weight);
                }
            }
        }
    }
    if (found) {
        *pOut = value;
    }
    return found;
}

void fn_80227248(Pair_802270A4 *pOut, Pair_802270A4 *pIn, float scale);
void fn_80227384(Pair_802270A4 *pOut, Pair_802270A4 *pIn, int angle);
void fn_80227638(Pair_802270A4 *pOut, Pair_802270A4 *pA, Pair_802270A4 *pB);
void fn_80227690(Pair_802270A4 *pOut, Pair_802270A4 *pA, Pair_802270A4 *pB);
void fn_80227904(Pair_802270A4 *pOut, Pair_802270A4 *pA, Pair_802270A4 *pB, float t);

int fn_801BCCAC(Object_801BA03C *pObject, Record_800D81C8 *pRecords, Anim_801BCA74 *pAnim, Pair_802270A4 *pOut, int key, int all)
{
    Pair_802270A4 sum;
    Pair_802270A4 offset;
    Pair_802270A4 delta;
    float total;
    int found = 0;
    int i;

    sum.mUnknown4 = 0.0f;
    total = 0.0f;
    sum.mUnknown0 = 0.0f;
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
                Record_800D81C8 *pRecord = &pRecords[index];
                Pair_802270A4 *pOffset;

                if (pRecord->mUnknown4C.mUnknown1E & 1) {
                    pRecord->mUnknown24.mUnknown0 = 0.0f;
                    pRecord->mUnknown4C.mUnknown1E = (pRecord->mUnknown4C.mUnknown1E & ~1) | 2;
                    pRecord->mUnknown24.mUnknown4 = 0.0f;
                }
                if (pRecord->mUnknown4C.mUnknown1E & 4) {
                    pRecord->mUnknown4C.mUnknown1E &= ~7;
                }
                if (i + 1 < pAnim->mUnknown0 && pAnim->mUnknown4[i + 1].mUnknown9 == index) {
                    if (!(pRecord->mUnknown4C.mUnknown1E & 2)) {
                        fn_80227904(&offset, &pEntry->mUnknown18, &pAnim->mUnknown4[i + 1].mUnknown18, pRecord->mUnknown4C.mUnknown14);
                    } else {
                        fn_80227248(&offset, &pEntry->mUnknown18, pRecord->mUnknown4C.mUnknown14);
                    }
                    pOffset = &offset;
                    i++;
                } else {
                    offset.mUnknown0 = pEntry->mUnknown18.mUnknown0;
                    offset.mUnknown4 = pEntry->mUnknown18.mUnknown4;
                    pOffset = &offset;
                }
                fn_80227690(&delta, pOffset, &pRecord->mUnknown24);
                fn_80227638(&pRecord->mUnknown24, &pRecord->mUnknown24, &delta);
                fn_80227248(&delta, &delta, pRecord->mUnknown2C);
                fn_80227384(&delta, &delta, pRecord->mUnknownC);
                total += pEntry->mUnknown0;
                fn_80227904(&sum, &delta, &sum, total != 0.0f ? pEntry->mUnknown0 / total : 0.0f);
            }
        }
    }
    if (found) {
        pOut->mUnknown4 = sum.mUnknown4;
        pOut->mUnknown0 = sum.mUnknown0;
    }
    return found;
}

void fn_801BCEEC(Object_801BA03C *p, Record_800D81C8 *pRecords)
{
    int i;

    p->mUnknown8 = (p->mUnknown8 + 0x800000) & 0xFFFFFF;
    for (i = 0; i < p->mUnknown4; i++, pRecords++) {
        if (pRecords->mUnknown1 != 0) {
            pRecords->mUnknownC = (pRecords->mUnknownC + 0x800000) & 0xFFFFFF;
        }
    }
}
