#include "game/Object_80039F5C.h"
#include "game/Block_800B0CFC.h"
#include "game/Class_80297CE8.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_8009D990.h"
#include "game/fn_802372EC.h"
#include "game/fn_800B65A0.h"

extern "C" {
int fn_80178308(void);
int fn_8011F32C(void);
int fn_8011F228(void);
int fn_8011F1CC(void);
int fn_8011F1F4(void);
int fn_8011F1A4(void);
float fn_8011F4D4(void);
unsigned char fn_8011F4C8(void);
void fn_800C02EC(void *p, short value);
}

static inline void PickPlay(void)
{
    short play = fn_8009D990(0) - 2;

    play -= fn_802372EC(0, 3);
    if (play <= 2) {
        play = fn_802372EC(0, 2) + 3;
    }
    fn_800C02EC(lbl_803EABA4, play);
}

extern "C" int fn_800B1200(void)
{
    float right = 0.0f;
    int team = fn_80178308();
    float left = 0.0f;

    if (fn_800B65A0(team) != 0xFF || fn_8011F32C() != 0 || fn_8011F228() != 0) {
        return 1;
    }
    if (lbl_803EAB14->mUnknown2E5 == 0) {
        return 1;
    }
    if (fn_8009D990(0) <= 2) {
        return 1;
    }

    unsigned int count = fn_80178D18(team);
    for (unsigned short i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        switch (p->mUnknown2914) {
        case 0:
            break;
        case 5:
            left = p->mMotion.mPos.mX;
            break;
        case 9:
            right = p->mMotion.mPos.mX;
            break;
        }
    }

    float x = fn_8009BCE8(&lbl_803EAB14->mUnknown2D0)->mMotion.mPos.mX;
    Point_8017886C los;
    los = fn_80177FE0();

    if ((fn_8011F1CC() != 0 || fn_8011F1F4() != 0) && !(x < left - 0.5f) && x <= right + 0.5f) {
        PickPlay();
        return 0;
    }
    if (fn_8011F1A4() == 0) {
        return 1;
    }
    if (!(x < fn_8011F4D4() - 0.5f) && x <= fn_8011F4D4() + 0.5f) {
        return 1;
    }
    if (!(x < left - 0.5f) && !(x > right + 0.5f)) {
        PickPlay();
        return 0;
    }
    if ((fn_8011F1A4() != 0 && (fn_8011F4C8() & 1) == 0 && x < los.mX)
        || (fn_8011F1A4() != 0 && (fn_8011F4C8() & 1) != 0 && x > los.mX)) {
        return 0;
    }
    return 1;
}
