/* Helpers for the stadium ambient sound objects of SndgPathfinder.cpp: create,
   update or stop one object from a sound event, and fade a group of channels out. */

#include "game/SndgPathfinder.h"
#include "game/AudmonEvent.h"

extern "C" {
int SndgAmbObjExists(int type, unsigned int index);
void SndgAmbObjCreate(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbObjUpdate(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject);
unsigned int SndgAmbObjFindSlot(int type, int value);
int SndgAmbTypeUsesPathNodes(int type);
int SndgAmbIsPathNodeName(SndgAmbObjInfo_t *p);
void SndgAmbObjStop(int type, unsigned int index);
float SndgAmbGetTypeThreshold(int type);
void SndgSfxSetVolume(int index, int a, unsigned char volume);

void SndgNullUpdate(void)
{
}

void SndgFadeOutChannelGroup(void)
{
    SndgSfxSetVolume(45, 30, 0);
    SndgSfxSetVolume(47, 30, 0);
    SndgSfxSetVolume(49, 30, 0);
    SndgSfxSetVolume(51, 30, 0);
    SndgSfxSetVolume(46, 30, 0);
    SndgSfxSetVolume(48, 30, 0);
    SndgSfxSetVolume(50, 30, 0);
    SndgSfxSetVolume(52, 30, 0);
}

void SndgSoundObjControl(int type, int mode, Vector_80039F5C *pPos, void *pObject, int index)
{
    switch (mode) {
    case 1:
        SndgAmbObjCreate(type, (unsigned char)index, pPos, pObject);
        break;
    case 2:
        if (!SndgAmbObjExists(type, (unsigned char)index)) {
            SndgAmbObjCreate(type, (unsigned char)index, pPos, pObject);
        } else {
            SndgAmbObjUpdate(type, (unsigned char)index, pPos, pObject);
        }
        break;
    case 3:
        SndgAmbObjStop(type, (unsigned char)index);
        break;
    }
}

void SndgSoundObjUpdateFromEvent(int type, AudmonEvent_t *p)
{
    SndgAmbObjInfo_t *pInfo = (SndgAmbObjInfo_t *)p->mUnknown14;
    float limit = SndgAmbGetTypeThreshold(type);
    int index = SndgAmbObjFindSlot(type, p->mUnknown18);

    if (pInfo == 0) {
        if (SndgAmbObjExists(type, (unsigned char)index)) {
            SndgSoundObjControl(type, (unsigned char)p->mUnknown10.mValue, &p->mPos, 0, index);
        }
    } else if (SndgAmbTypeUsesPathNodes(type)) {
        if (SndgAmbIsPathNodeName(pInfo)) {
            if (SndgAmbObjExists(type, (unsigned char)index)) {
                SndgSoundObjControl(type, 2, &p->mPos, 0, index);
            } else {
                SndgSoundObjControl(type, 1, &p->mPos, 0, index);
            }
        } else if (SndgAmbObjExists(type, (unsigned char)index)) {
            SndgSoundObjControl(type, 3, &p->mPos, 0, index);
        }
    } else {
        float value = pInfo->mUnknown4;

        if (SndgAmbObjExists(type, (unsigned char)index)) {
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
