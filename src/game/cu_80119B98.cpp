#include "game/Object_80039F5C.h"
#include "game/Query_800CE770.h"
#include "game/cu_80136B1C.h"
#include "game/fn_801248D4.h"
#include "game/fn_80178D18.h"

struct Pair_8011BAE0 {
    float mUnknown0;
    float mUnknown4;
};

extern "C" {
int fn_80178308(void);
void fn_8011BAE0(Pair_8011BAE0 *pOut);
int fn_800CA5CC(Object_80039F5C *p, int a, int b);
int fn_800CE4A8(Query_800CE770 *pQuery);
float fn_80227890(Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int value);
void fn_8011E194(Object_80039F5C *p, unsigned char mask);
void fn_8011E1A8(Object_80039F5C *p, unsigned char mask);
int fn_8011A994(Object_80039F5C *p, Object_80039F5C *pOther);
}

extern "C" void fn_80119B98(void)
{
    int team = fn_80178308();
    unsigned char i = 0;
    Pair_8011BAE0 pair;
    unsigned int count;

    fn_8011BAE0(&pair);
    count = fn_80178D70(team);
    for (; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        Object_80137ABC *pBall;

        fn_800CA5CC(p, 8, 0);
        pBall = fn_80137C48(p);
        if (pBall == 0 && p->mUnknown1032 == 7) {
            Object_80039F5C *pA = fn_8009BCE8(&p->mUnknown1036);
            Object_80039F5C *pB = fn_8009BCE8(&p->mUnknown1040);

            fn_800CA5CC(pB, 8, 0);
            if (fn_8011A994(p, pB) && fn_80227890(&p->mMotion.mPos, &pB->mMotion.mPos) < 25.0f
                && fn_801248D4(p, 0, &pB->mMotion.mPos, 0, 0.0f, 0.5f, 0, pA)) {
                Query_800CE770 query;
                int done = 0;

                fn_800CE770(&query);
                query.mUnknown52 = 243;
                query.mUnknown36 = 0x18E38E;
                query.mUnknown57 = 0;
                query.mpUnknown0 = p;
                query.mpUnknown4Entries[0] = pA;
                query.mpUnknown4Entries[1] = pB;
                query.mUnknown44 = 0.45f;
                fn_8011E1A8(p, 2);
                if (fn_800CE4A8(&query)) {
                    done = 1;
                } else {
                    query.mUnknown57 = 1;
                    fn_8011E194(p, 2);
                    if (fn_800CE4A8(&query)) {
                        done = 1;
                    }
                }
                if (done) {
                    fn_8011E1BC(p, pA, pB, 5);
                    fn_8011E33C(pA, p, 6);
                    fn_8011E33C(pB, p, 6);
                    fn_800CA5CC(p, 8, 1);
                    fn_800CA5CC(pB, 8, 1);
                }
                fn_8011E1A8(p, 2);
            }
        }
    }
}

