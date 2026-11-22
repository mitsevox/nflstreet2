/* PATH tracks (pathtrack.c): creates and initializes stream and bank tracks, finds a track by its
   handle, reports track counts and status, and the Path::IPathTrack base class defaults. */

#include <string.h>
#include "engine/pathfinder.h"
#include "engine/pathlib.h"

extern "C" int fn_801B3AD0(int flags, PathfinderTrackData_t *data, int value)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";

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

extern "C" Class_801B44BC *PATH_createstreamimp(int flags, int a, float b)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return 0;
    if (!fn_801B34DC(flags))
        return 0;
    Class_801B44BC *track = 0;
    Node_801B3FE0 *p = fn_801B4174(flags);
    if (p) {
        int rate = PATHI_bytesperms(p->mUnknown0);
        int result = lbl_803EBB64->vfn_02(&track, a, b, rate);
        if (track && result >= 0) {
            p->mUnknown100 = track;
            track->vfn_22(p->mUnknownD0);
            track->fn_801B45CC(&p->mUnknown50);
            track->fn_801B459C(PATHI_trackinfo(p->mUnknown0));
        }
    }
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return track;
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

extern "C" Class_801B44BC *PATH_createbankobject(int flags)
{
    int acquired;
    if (++lbl_803EBB24 == 1 && lbl_803EBB38)
        acquired = 1;
    else {
        --lbl_803EBB24;
        acquired = 0;
    }
    if (!acquired)
        return 0;
    if (!fn_801B34DC(flags))
        return 0;
    Class_801B44BC *track = 0;
    Node_801B3FE0 *p = fn_801B4174(flags);
    if (p) {
        lbl_803EBB64->vfn_03(&track, p->mUnknown104);
        if (track) {
            p->mUnknown8.halves.high = lbl_803EBB28->mUnknown10;
            p->mUnknown100 = track;
            track->vfn_22(p->mUnknownD0);
            track->fn_801B45CC(&p->mUnknown50);
            track->fn_801B459C(PATHI_trackinfo(p->mUnknown0));
        }
    }
    lbl_803EBB28 = 0;
    --lbl_803EBB24;
    return track;
}

extern "C" int fn_801B3F6C(int flags, PathfinderTrackData_t *data)
{
    if (!fn_801B34DC(flags))
        return -8;
    int result = PATHI_inittrack(flags, data);
    if (result < 0)
        return result;
    Node_801B3FE0 *p = fn_801B4174(flags);
    lbl_803EBB28->mUnknown40[p->mUnknown0] = p;
    return 0;
}

extern "C" int PATHI_inittrack(int flags, PathfinderTrackData_t *data)
{
    int track = 0;
    if (!(flags & 0x00FFFFFF) || !(flags & 0x0F000000) || !(flags & 0xF0000000))
        return -8;
    Bank_801B3480 *bank = lbl_803EBB28;
    // FAKEMATCH: track-mask bit tested as ((mask >> track) ^ 1) & 1, as in pathcontrol.c
    for (track = 0; track < 24 && (((flags >> track) ^ 1) & 1); ++track)
        ;
    if (bank->mUnknown40[track])
        return -13;
    Node_801B3FE0 *p = (Node_801B3FE0 *)fn_801B2C40(sizeof(Node_801B3FE0));
    if (!p)
        return -108;
    memset(p, 0, sizeof(Node_801B3FE0));
    p->mUnknown0 = track;
    p->mUnknown8.bits.flag20 = 0;
    p->mUnknown2 = lbl_803EBB3A;
    p->mUnknown3 = 127;
    p->mUnknown18 = -1;
    p->mUnknown19 = -1;
    p->mUnknown1A = -1;
    p->mUnknown24 = -1;
    p->mUnknown25 = -1;
    p->mUnknown26 = -1;
    p->mUnknown30 = -1;
    p->mUnknown31 = -1;
    p->mUnknown8.bits.mUnknown7 = -1;
    p->mUnknownF0 = -1;
    p->mUnknownF4 = 0xBEDFACED;
    p->mUnknown110 = 1;
    p->mUnknown4 = -1;
    p->mUnknown8.bits.mUnknown1 = lbl_803EBB44;
    p->mUnknown8.bits.flag1 = (flags & 0xF0000000) == 0x10000000;
    p->mUnknown6 = -1;
    p->mUnknown4C = -1;
    p->mUnknown50.mUnknown0 = data->mpData;
    p->mUnknown50.mUnknown4 = data->mUnknown4;
    strcpy(p->mUnknownD0, "TibTrack");
    lbl_803EBB28->mUnknown40[track] = p;
    return track;
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

Class_801B44BC::Class_801B44BC()
{
    mUnknown0 = 0;
    mUnknown4 = 0;
    mUnknown8 = 0;
    mUnknownC = 127;
    mUnknown10 = 127;
    mUnknown14 = 1;
    mUnknown18 = 0;
    mUnknown1C = 1;
    mUnknown58 = -1;
    mUnknown5C = 0;
    mUnknown20 = 0;
    mUnknown64 = 0;
    mUnknown60 = 0;
}

Class_801B44BC::~Class_801B44BC()
{
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

Record_801B58F0 *Class_801B44BC::fn_801B4574()
{ return 0; }

int Class_801B44BC::fn_801B457C(int index, char *data)
{ return -8; }

int Class_801B44BC::fn_801B4584(int index)
{ return -8; }

int Class_801B44BC::fn_801B458C(int index, int header)
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

void Class_801B44BC::fn_801B45CC(PathName_801B3FE0 *path)
{}
