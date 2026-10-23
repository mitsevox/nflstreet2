#include "game/Object_80039F5C.h"
#include "game/Query_800CE770.h"
#include "game/Record_800CE608.h"
#include "game/Move_8011AB38.h"

struct Pair_8011BAE0 {
    float mUnknown0;
    float mUnknown4;
};

extern "C" {
int fn_80178308(void);
unsigned int fn_80178D70(int team);
void fn_8011BAE0(Pair_8011BAE0 *pOut);
void fn_8011A2C4(Object_80039F5C *p, Object_80039F5C *pOther, Pair_8011BAE0 spot, int apply);
int fn_8011A994(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8011A608(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_800CE590(Query_800CE770 *pQuery, Record_800CE608 *pA, Record_800CE608 *pB);
void fn_800CE608(Object_80039F5C *p, Record_800CE608 *pRecord);
void fn_80143E14(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8011DCA8(unsigned int id);
void fn_80067DB8(int type, Vector_80039F5C *pPos, int a, int b, int c);
void fn_800D6C70(Object_80039F5C *p);
unsigned short fn_801BE648(void *p);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *pRecord, float e);
}

/* View of the 108 bytes at player +1032 as fn_8011AB38 uses them. */
struct Block_8011AB38 {
    int mUnknown0;
    int mUnknown4;
    char mUnknown8[16];
    Record_800CE608 mUnknown24;
    float mUnknown40;
    char mUnknown44[12];
    int mUnknown56;
    int mUnknown60;
    char mUnknown64[30];
    unsigned char mUnknown94;
};

extern "C" Move_8011AB38 *fn_8011A7B4(Object_80039F5C *p, Object_80039F5C *pOther);

static inline void SetMove_8011AB38(Object_80039F5C *p, Block_8011AB38 *pState)
{
    p->mUnknown512.mUnknown14 = 5;
    p->mUnknown512.mUnknown4 = pState->mUnknown56;
    p->mUnknown512.mUnknown8 = pState->mUnknown60;
    p->mUnknown512.mUnknown0 = pState->mUnknown40;
}

extern "C" void fn_8011AB38(void)
{
    unsigned char i = 0;
    int team = fn_80178308();
    Pair_8011BAE0 spot;
    unsigned int count;

    fn_8011BAE0(&spot);
    count = fn_80178D70(team);
    for (; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        Block_8011AB38 *pState = (Block_8011AB38 *)&p->mUnknown1032;
        int done = 0;

        if (pState->mUnknown0 == 4 || pState->mUnknown0 == 7) {
            Object_80039F5C *pOther = fn_8009BCE8(&pState->mUnknown4);
            Block_8011AB38 *pOtherState = (Block_8011AB38 *)&pOther->mUnknown1032;
            Query_800CE770 query;
            Record_800CE608 result;
            Record_800CE608 otherResult;

            if (pState->mUnknown94) {
                pState->mUnknown94 = 0;
                fn_8011A2C4(p, pOther, spot, 0);
                if (fn_8011A994(p, pOther)) {
                    done = fn_8011A608(p, pOther);
                    if (!done) {
                        unsigned char j = 0;
                        Move_8011AB38 *pMoves = fn_8011A7B4(p, pOther);

                        fn_800CE770(&query);
                        query.mpUnknown0 = p;
                        query.mpUnknown4 = pOther;
                        while (pMoves[j].mKey != 0xFFFF) {
                            if (pMoves[j].mKey != pState->mUnknown24.mUnknown8) {
                                query.mUnknown52 = pMoves[j].mKey;
                                query.mUnknown36 = pMoves[j].mUnknown8;
                                query.mUnknown44 = pMoves[j].mUnknown4;
                                if (fn_800CE590(&query, &result, &otherResult)) {
                                    fn_80143E14(p, pOther);
                                    fn_80143E14(pOther, p);
                                    if (pState->mUnknown24.mUnknown8 != pMoves[j].mKey) {
                                        pState->mUnknown24 = result;
                                        pOtherState->mUnknown24 = otherResult;
                                        SetMove_8011AB38(p, pState);
                                        SetMove_8011AB38(pOther, pOtherState);
                                        fn_800CE608(p, &result);
                                        fn_800CE608(pOther, &otherResult);
                                        p->mFlags &= ~4;
                                        pOther->mFlags &= ~4;
                                        if (fn_8011DCA8(pMoves[j].mKey)) {
                                            fn_80067DB8(103, &p->mMotion.mPos, p->mId, pOther->mId, 0);
                                        }
                                    }
                                    break;
                                }
                            }
                            j++;
                        }
                    }
                }
            }
            if (!done) {
                if ((p->mFlags & 4) || (pOther->mFlags & 4)) {
                    p->mFlags &= ~4;
                    pOther->mFlags &= ~4;
                    fn_800D6C70(pOther);
                    fn_800CE770(&query);
                    query.mpUnknown0 = p;
                    query.mpUnknown4 = pOther;
                    query.mUnknown52 = pState->mUnknown24.mUnknown8;
                    query.mUnknown36 = pState->mUnknown24.mUnknown0;
                    query.mUnknown44 = pState->mUnknown24.mUnknown4;
                    if (pState->mUnknown24.mUnknown8 != 0xFFFF && fn_8011A994(p, pOther)
                        && fn_800CE590(&query, &result, &otherResult)) {
                        pState->mUnknown24 = result;
                        pOtherState->mUnknown24 = otherResult;
                        SetMove_8011AB38(p, pState);
                        SetMove_8011AB38(pOther, pOtherState);
                        fn_800CE608(p, &result);
                        fn_800CE608(pOther, &otherResult);
                        fn_80143E14(p, pOther);
                        fn_80143E14(pOther, p);
                    } else {
                        if (fn_801BE648(p->mpUnknown792) != 74) {
                            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, p, 1.0f);
                        }
                        if (fn_801BE648(pOther->mpUnknown792) != 74) {
                            fn_801BE068(pOther->mpUnknown792, pOther->mpUnknown796, pOther->mpUnknown800, 74, pOther, 1.0f);
                        }
                    }
                }
                SetMove_8011AB38(p, pState);
                SetMove_8011AB38(pOther, pOtherState);
            }
        }
    }
}
