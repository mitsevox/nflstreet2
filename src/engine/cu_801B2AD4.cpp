#include "engine/cu_801B8C18.h"

struct Data_801B4548 {
    unsigned char mUnknown0[4];
    unsigned short mUnknown4;
};

class Class_801B44BC {
public:
    virtual ~Class_801B44BC();
    virtual void fn_801B459C(Data_801B4548 *p);
    virtual void vfn_03() = 0;
    virtual int vfn_04() = 0;
    virtual void vfn_05(int value) = 0;
    virtual void vfn_06() = 0;
    virtual int vfn_07(void *p) = 0;
    virtual int vfn_08() = 0;
    virtual int vfn_09(int index) = 0;
    virtual void vfn_10() = 0;
    virtual void vfn_11() = 0;
    virtual int fn_801B45A4();
    virtual void vfn_13() = 0;
    virtual int fn_801B45AC();
    virtual void vfn_15() = 0;
    virtual int fn_801B45B4();
    virtual void vfn_17() = 0;
    virtual void vfn_18() = 0;
    virtual void vfn_19() = 0;
    virtual int fn_801B45BC();
    virtual int fn_801B45C4();
    virtual void vfn_22() = 0;
    virtual void fn_801B45CC();
    virtual void vfn_24() = 0;
    virtual void vfn_25() = 0;
    virtual int fn_801B4548();
    virtual int fn_801B4564();
    virtual int fn_801B456C();
    virtual int fn_801B4574();
    virtual int fn_801B457C();
    virtual int fn_801B4584();
    virtual int fn_801B458C();
    virtual int fn_801B4594();

    int mUnknown0;
    unsigned char mUnknown4[4];
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    unsigned char mUnknown14[12];
    int mUnknown20;
    unsigned char mUnknown24[56];
    Data_801B4548 *mUnknown5C;
    int mUnknown60;
    int mUnknown64;
};

extern "C" {
extern Allocator *lbl_803EBB68;
extern AllocParams lbl_8037E814;
extern void (*lbl_803EBB2C)(int, int);
extern void (*lbl_803EBB30)(int, int);
extern void (*lbl_803EBB34)(int, int);
void fn_801B39B8(int mode);

void *fn_801B2C40(int size)
{
    void *result;
    if (lbl_803EBB68)
        result = lbl_803EBB68->Alloc(size, lbl_8037E814);
    else
        result = 0;
    return result;
}

void fn_801B2C94(void *p)
{
    if (lbl_803EBB68)
        lbl_803EBB68->Free(p, 0);
}

void fn_801B2F18(void (*a)(int, int), void (*b)(int, int), void (*c)(int, int))
{
    lbl_803EBB2C = a;
    lbl_803EBB30 = b;
    lbl_803EBB34 = c;
}

void fn_801B3A88(void) { fn_801B39B8(32); }
void fn_801B3AAC(void) { fn_801B39B8(66); }

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
int Class_801B44BC::fn_801B4564() { return mUnknown60; }
int Class_801B44BC::fn_801B456C() { return 0; }
int Class_801B44BC::fn_801B4574() { return 0; }
int Class_801B44BC::fn_801B457C() { return -8; }
int Class_801B44BC::fn_801B4584() { return -8; }
int Class_801B44BC::fn_801B458C() { return -8; }
int Class_801B44BC::fn_801B4594() { return -8; }
void Class_801B44BC::fn_801B459C(Data_801B4548 *p) { mUnknown5C = p; }
int Class_801B44BC::fn_801B45A4() { return mUnknown10; }
int Class_801B44BC::fn_801B45AC() { return mUnknownC; }
int Class_801B44BC::fn_801B45B4() { return mUnknown8; }
int Class_801B44BC::fn_801B45BC() { return mUnknown0; }
int Class_801B44BC::fn_801B45C4() { return mUnknown20; }
void Class_801B44BC::fn_801B45CC() {}
extern "C" void fn_801B5E10(int value, ...) {}
