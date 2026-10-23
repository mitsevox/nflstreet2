#include "game/Object_80039F5C.h"
#include "engine/Record_800D81C8.h"
#include "game/fn_802270D4.h"

extern "C" {
int fn_801CFE40(float y, float x);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFDD0(float value);
}

extern "C" float fn_8009F168(Vector_80039F5C *p, Pair_802270A4 *pVelocity,
                              Vector_80039F5C *pOther, float speed)
{
    Vector_80039F5C delta;
    fn_802276B4(&delta, pOther, p);
    float distance = fn_802270A4(&delta);
    float velocity = fn_802270A4(pVelocity);
    int angle = fn_801CFE40(pVelocity->mUnknown4, pVelocity->mUnknown0);
    angle = angle - fn_801CFE40(delta.mY, delta.mX);
    float sine = fn_801CFB18(angle);
    int correction = fn_801CFDD0(velocity * sine / speed);
    float closing = speed * fn_801CFB94(correction) + velocity * fn_801CFB94(angle);
    float time = distance / closing;
    if (time <= 0.0f || !(time <= 5.0f)) {
        time = distance / speed;
    }
    return time;
}
