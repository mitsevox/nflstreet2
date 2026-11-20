#ifndef ENGINE_PATHLIB_H
#define ENGINE_PATHLIB_H

/* Shared declarations of the PATH interactive-music library files (pathinit.c .. pathaction.c):
   the track, bank, node and event records they share and the library entry points. */

#include "engine/fn_801B3234.h"
#include "engine/csis.h"

struct Data_801B4548 {
    unsigned char mUnknown0[4];
    unsigned short mUnknown4;
};

struct Record_801B58F0 {
    unsigned char mUnknown0[4];
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknownC[20];
    int mUnknown20;
};

class Class_801B44BC {
public:
    virtual ~Class_801B44BC();
    virtual void fn_801B459C(Data_801B4548 *p);
    virtual void vfn_03() = 0;
    virtual void vfn_04() = 0;
    virtual void vfn_05(int value) = 0;
    virtual void vfn_06() = 0;
    virtual int vfn_07(void *p) = 0;
    virtual int vfn_08() = 0;
    virtual int vfn_09(int index) = 0;
    virtual void vfn_10() = 0;
    virtual void vfn_11() = 0;
    virtual int fn_801B45A4();
    virtual void vfn_13(int value) = 0;
    virtual int fn_801B45AC();
    virtual void vfn_15() = 0;
    virtual int fn_801B45B4(int value);
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
    virtual Record_801B58F0 *fn_801B456C(int index);
    virtual int fn_801B4574();
    virtual int fn_801B457C();
    virtual int fn_801B4584();
    virtual int fn_801B458C();
    virtual int fn_801B4594(int index);

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
    unsigned char mUnknown64[4];
};

struct Header_801B2CDC {
    unsigned char mUnknown0[15];
    unsigned char mUnknownF;
    unsigned char mUnknown10[2];
    unsigned short mUnknown12;
};

struct Node_801B3FE0 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    short mUnknown4;
    short mUnknown6;
    union {
        unsigned int word;
        struct { unsigned short high; unsigned char low[2]; } halves;
        struct { unsigned int mUnknown7:25, flag40:1, mUnknown1:5, flag1:1; } bits;
    } mUnknown8;
    unsigned char mUnknownC[4];
    unsigned int mUnknown10;
    int mUnknown14;
    signed char mUnknown18, mUnknown19, mUnknown1A;
    unsigned char mUnknown1B;
    unsigned int mUnknown1C;
    int mUnknown20;
    signed char mUnknown24, mUnknown25, mUnknown26;
    unsigned char mUnknown27;
    unsigned int mUnknown28;
    int mUnknown2C;
    signed char mUnknown30, mUnknown31, mUnknown32;
    unsigned char mUnknown33;
    unsigned int *mUnknown34;
    unsigned char mUnknown38[184];
    int mUnknownF0;
    unsigned char mUnknownF4[12];
    Class_801B44BC *mUnknown100;
    short mUnknown104;
    unsigned char mUnknown106[2];
    int mUnknown108;
    int mUnknown10C;
    int mUnknown110;
};

struct Record_801B6D20 {
    signed char mUnknown0;
    signed char mUnknown1;
    unsigned short mUnknown2;
};

struct Sequence_801B84E4;

struct Bank_801B3480 {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    unsigned char mUnknownC[8];
    unsigned int mUnknown14;
    Header_801B2CDC *mUnknown18;
    short *mUnknown1C;
    unsigned char mUnknown20[4];
    short *mUnknown24;
    unsigned char mUnknown28[8];
    unsigned int *mUnknown30;
    int *mUnknown34;
    unsigned char mUnknown38[4];
    unsigned int *mUnknown3C;
    Node_801B3FE0 *mUnknown40[24];
    unsigned char mUnknownA0[32];
    Sequence_801B84E4 *mUnknownC0[17];
    unsigned char mUnknown104[4092];
    int mUnknown1100;
};

class Class_803EBB60 {
public:
    virtual ~Class_803EBB60();
    virtual void vfn_02() = 0;
    virtual void vfn_03() = 0;
    virtual void vfn_04() = 0;
    virtual unsigned int vfn_05() = 0;
    unsigned char mUnknown0[12];
};

struct Event_801B845C {
    unsigned char mUnknown0[4];
    union {
        unsigned int mUnknown4;
        struct { unsigned int mUnknown6:26, depth:3, mUnknown0:3; } mBits4;
    };
    unsigned char mUnknown8[4];
};
struct Sequence_801B84E4 {
    unsigned int mUnknown0;
    unsigned char mUnknown4[4];
    unsigned int mUnknown8;
    unsigned char mUnknownC[3];
    unsigned char mUnknownF;
    unsigned char mUnknown10;
    unsigned char mUnknown11[3];
    Event_801B845C mUnknown14[1];
};
struct PathfinderStatus_t;
struct Entry_801B63F0 {
    unsigned char mUnknown0[4];
    unsigned int mUnknown4;
    unsigned char mUnknown8[4];
    unsigned int mUnknownC;
    union {
        unsigned int word;
        struct { unsigned int mUnknownF:17, flag4000:1, mUnknown0:14; } bits;
    } mUnknown10;
};
struct Record_801B6780 {
    short mUnknown0;
};
struct PathfinderTrackData_t;

class Class_803EBB64 {
public:
    virtual ~Class_803EBB64();
};

extern "C" {
extern Allocator *lbl_803EBB68;
extern AllocParams lbl_8037E814;
extern void (*lbl_803EBB2C)(int, int);
extern void (*lbl_803EBB30)(int, int);
extern void (*lbl_803EBB34)(int, int);
extern int lbl_803EBB24;
extern Bank_801B3480 *lbl_803EBB28;
extern unsigned char lbl_803EBB38;
extern unsigned char lbl_803EBB39;
extern unsigned char lbl_803EBB3B;
extern unsigned int lbl_803EBB3C;
extern int lbl_803EBB40;
extern int lbl_803EBB48;
extern int lbl_803EBB4C;
extern int lbl_803EBB50;
extern int lbl_803EBB54;
extern Bank_801B3480 *lbl_802F47D0[4];
extern Class_803EBB60 *lbl_803EBB60;
void fn_801B3724(void);
int fn_801B3FE0(int flags, PathfinderTrackData_t *data);
int fn_801B7880(Sequence_801B84E4 *p, Event_801B845C *entry);
extern unsigned int seedPATH[6];
extern Class_803EBB64 *lbl_803EBB64;
int fn_801B2F28(int flags);
void SNDSYS_entercritical(void);
void SNDSYS_leavecritical(void);
int fn_801B2AD4(void);
int fn_801B2B58(void);
void *fn_801B2C40(int size);
void fn_801B2C94(void *p);
void fn_801B2F18(void (*a)(int, int), void (*b)(int, int), void (*c)(int, int));
unsigned int fn_801B343C(void);
unsigned int fn_801B3480(unsigned int index, unsigned int flags);
int fn_801B34DC(unsigned int flags);
int fn_801B3568(void);
void fn_801B39B8(int mode);
void fn_801B3A88(void);
void fn_801B3AAC(void);
int fn_801B3AD0(int flags, PathfinderTrackData_t *data, int value);
int fn_801B3D28(int flags, PathfinderTrackData_t *data, int value);
int fn_801B3F6C(int flags, PathfinderTrackData_t *data);
Node_801B3FE0 *fn_801B4174(unsigned int flags);
void fn_801B421C(void);
int fn_801B42C0(unsigned int flags);
void fn_801B4334(Node_801B3FE0 *p, int state);
int fn_801B43CC(int state);
void fn_801B4824(Node_801B3FE0 *p, int value);
void fn_801B4960(Node_801B3FE0 *p, int a, int b, int c);
void fn_801B49C4(Node_801B3FE0 *p, int a, int b, int c);
int fn_801B57C0(Node_801B3FE0 *p, int index);
int fn_801B58F0(Node_801B3FE0 *p);
int fn_801B59B0(int flags, int value);
void fn_801B5AB0(int flags, unsigned char value);
int fn_801B5BCC(int flags, PathfinderStatus_t *info);
int fn_801B5C88(Node_801B3FE0 *p, void *info);
void fn_801B5CD0(int flags);
int fn_801B5DB4(Node_801B3FE0 *p);
void PATHI_printf(const char *format, ...);
int fn_801B5E5C(int flags, Sequence_801B84E4 *sequence);
void fn_801B6334(Sequence_801B84E4 *p);
void fn_801B63F0(Entry_801B63F0 *p, int value);
void fn_801B6460(void);
int fn_801B64C0(int index);
int fn_801B6780(int index);
int fn_801B6CB4(Node_801B3FE0 *p);
int fn_801B6D20(int count, int value, Record_801B6D20 *entries);
int fn_801B7178(int index, int value);
unsigned int PATHI_random(void);
Event_801B845C *fn_801B845C(Event_801B845C *p, int state, Event_801B845C *end);
int fn_801B84E4(Event_801B845C *p, Sequence_801B84E4 *sequence);
int fn_801B8580(Node_801B3FE0 *p);
}

#endif
