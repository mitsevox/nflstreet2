/* Helpers for the stadium ambient sound objects of SndgPathfinder.cpp: create,
   update or stop one object from a sound event, and fade a group of channels out. */

#include "game/SndgPathfinder.h"
#include "game/AudmonEvent.h"

extern "C" {
int fn_8006B810(int type, unsigned int index);
void fn_8006B91C(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006B9AC(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject);
unsigned int fn_8006BA54(int type, int value);
int fn_8006BB44(int type);
int fn_8006BBC4(Struct_8006BBC4 *p);
void fn_8006BC30(int type, unsigned int index);
float fn_8006BE3C(int type);
void fn_8006CA18(int index, int a, unsigned char volume);

void SndgNullUpdate(void)
{
}

void SndgFadeOutChannelGroup(void)
{
    fn_8006CA18(45, 30, 0);
    fn_8006CA18(47, 30, 0);
    fn_8006CA18(49, 30, 0);
    fn_8006CA18(51, 30, 0);
    fn_8006CA18(46, 30, 0);
    fn_8006CA18(48, 30, 0);
    fn_8006CA18(50, 30, 0);
    fn_8006CA18(52, 30, 0);
}

void SndgSoundObjControl(int type, int mode, Vector_80039F5C *pPos, void *pObject, int index)
{
    switch (mode) {
    case 1:
        fn_8006B91C(type, (unsigned char)index, pPos, pObject);
        break;
    case 2:
        if (!fn_8006B810(type, (unsigned char)index)) {
            fn_8006B91C(type, (unsigned char)index, pPos, pObject);
        } else {
            fn_8006B9AC(type, (unsigned char)index, pPos, pObject);
        }
        break;
    case 3:
        fn_8006BC30(type, (unsigned char)index);
        break;
    }
}

void SndgSoundObjUpdateFromEvent(int type, AudmonEvent_t *p)
{
    Struct_8006BBC4 *pInfo = (Struct_8006BBC4 *)p->mUnknown14;
    float limit = fn_8006BE3C(type);
    int index = fn_8006BA54(type, p->mUnknown18);

    if (pInfo == 0) {
        if (fn_8006B810(type, (unsigned char)index)) {
            SndgSoundObjControl(type, (unsigned char)p->mUnknown10.mValue, &p->mPos, 0, index);
        }
    } else if (fn_8006BB44(type)) {
        if (fn_8006BBC4(pInfo)) {
            if (fn_8006B810(type, (unsigned char)index)) {
                SndgSoundObjControl(type, 2, &p->mPos, 0, index);
            } else {
                SndgSoundObjControl(type, 1, &p->mPos, 0, index);
            }
        } else if (fn_8006B810(type, (unsigned char)index)) {
            SndgSoundObjControl(type, 3, &p->mPos, 0, index);
        }
    } else {
        float value = pInfo->mUnknown4;

        if (fn_8006B810(type, (unsigned char)index)) {
            if (value < limit) {
                SndgSoundObjControl(type, 3, &p->mPos, 0, index);
            } else {
                SndgSoundObjControl(type, (unsigned char)p->mUnknown10.mValue, &p->mPos, 0, index);
            }
        } else if (value >= limit) {
            SndgSoundObjControl(type, (unsigned char)p->mUnknown10.mValue, &p->mPos, 0, index);
        }
    }
}

}
