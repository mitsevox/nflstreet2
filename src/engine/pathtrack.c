/* PATH tracks (pathtrack.c): creates and initializes stream and bank tracks, finds a track by its
   handle, reports track counts and status, and the Path::IPathTrack base class defaults. */

#include "engine/pathlib.h"

extern "C" int fn_801B3AD0(int flags, PathfinderTrackData_t *data, int value)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    int result = fn_801B3F6C(flags, data);
    if (result >= 0) {
        Node_801B3FE0 *p = fn_801B4174(flags);
        if (p)
            p->mUnknown8.halves.high = value;
    }
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return result;
}

extern "C" int fn_801B3D28(int flags, PathfinderTrackData_t *data, int value)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return -18;
    int result = fn_801B3F6C(flags, data);
    if (result >= 0) {
        Node_801B3FE0 *p = fn_801B4174(flags);
        p->mUnknown104 = value;
        p->mUnknown8.word |= 0x10;
    }
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return result;
}

extern "C" int fn_801B3F6C(int flags, PathfinderTrackData_t *data)
{
    if (!fn_801B34DC(flags))
        return -8;
    int result = fn_801B3FE0(flags, data);
    if (result < 0)
        return result;
    Node_801B3FE0 *p = fn_801B4174(flags);
    lbl_803EBB28->mUnknown40[p->mUnknown0] = p;
    return 0;
}

extern "C" Node_801B3FE0 *fn_801B4174(unsigned int flags)
{
    unsigned int bits = flags & 0x00FFFFFF;
    unsigned int high = flags & 0xF0000000;
    flags &= 0x0F000000;
    for (unsigned int i = 0; i < 4; ++i) {
        if (lbl_802F47D0[i] && (lbl_802F47D0[i]->mUnknown14 & high) &&
            (lbl_802F47D0[i]->mUnknown14 & flags)) {
            for (int j = 0; j < 24; ++j) {
                if ((bits >> j) & 1)
                    return lbl_802F47D0[i]->mUnknown40[j];
            }
        }
    }
    return 0;
}

extern "C" void fn_801B421C(void)
{
    lbl_803EBB28->mUnknown0 = -1;
    lbl_803EBB28->mUnknown4 = 0;
    lbl_803EBB28->mUnknown8 = 0;
    for (int i = 0; i < 24; ++i) {
        Node_801B3FE0 *p = lbl_803EBB28->mUnknown40[i];
        if (p && !(p->mUnknown8.word & 0x40)) {
            int active = 0;
            if (p->mUnknown4 >= 0 && p->mUnknown34)
                active = 1;
            if (active && lbl_803EBB28->mUnknown4 < (p->mUnknown8.halves.high)) {
                lbl_803EBB28->mUnknown4 = p->mUnknown8.halves.high;
                lbl_803EBB28->mUnknown0 = i;
                lbl_803EBB28->mUnknown8 = (*p->mUnknown34 >> 5) & 63;
            }
        }
    }
}

extern "C" int fn_801B42C0(unsigned int flags)
{
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if ((flags & (0x01000000 << i)) && lbl_802F47D0[i]) {
            for (int j = 0; j < 24; ++j) {
                if (lbl_802F47D0[i]->mUnknown40[j])
                    ++count;
            }
        }
    }
    return count;
}

extern "C" void fn_801B4334(Node_801B3FE0 *p, int state)
{
    unsigned int id = p->mUnknown0;
    int found = state > 0;
    p->mUnknown8.bits.flag1 = state != 0;
    for (int i = 0; i < 4; ++i) {
        if (lbl_802F47D0[i]) {
            Node_801B3FE0 *other = lbl_802F47D0[i]->mUnknown40[id];
            if (other && other != p) {
                other->mUnknown8.bits.flag1 = !found;
                found = 1;
            }
        }
    }
    if (!found)
        p->mUnknown8.bits.flag1 = 1;
}

extern "C" int fn_801B43CC(int state)
{
    int i = 0;
    for (; i < 4; ++i) {
        if (lbl_802F47D0[i] && fn_801B3480(i, 0xFFFFFFFF)) {
            for (int j = 0; j < 24; ++j) {
                Node_801B3FE0 *p = lbl_803EBB28->mUnknown40[j];
                if (p && !(p->mUnknown8.word & 0x40) && p->mUnknown100) {
                    if (state)
                        p->mUnknown100->vfn_03();
                    else
                        p->mUnknown100->vfn_06();
                }
            }
        }
    }
    return i;
}

int Class_801B44BC::fn_801B4548()
{
    Data_801B4548 *p = mUnknown5C;
    int result;
    if (p)
        result = p->mUnknown4;
    else
        result = 0;
    return result;
}

int Class_801B44BC::fn_801B4564()
{ return mUnknown60; }

Record_801B58F0 *Class_801B44BC::fn_801B456C(int index)
{ return 0; }

int Class_801B44BC::fn_801B4574()
{ return 0; }

int Class_801B44BC::fn_801B457C()
{ return -8; }

int Class_801B44BC::fn_801B4584()
{ return -8; }

int Class_801B44BC::fn_801B458C()
{ return -8; }

int Class_801B44BC::fn_801B4594(int index)
{ return -8; }

void Class_801B44BC::fn_801B459C(Data_801B4548 *p)
{ mUnknown5C = p; }

int Class_801B44BC::fn_801B45A4()
{ return mUnknown10; }

int Class_801B44BC::fn_801B45AC()
{ return mUnknownC; }

int Class_801B44BC::fn_801B45B4(int value)
{ return mUnknown8; }

int Class_801B44BC::fn_801B45BC()
{ return mUnknown0; }

int Class_801B44BC::fn_801B45C4()
{ return mUnknown20; }

void Class_801B44BC::fn_801B45CC()
{}
