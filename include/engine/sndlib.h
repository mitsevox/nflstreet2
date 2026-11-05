#ifndef ENGINE_SNDLIB_H
#define ENGINE_SNDLIB_H

/* Declarations shared by the files of the sound range 0x802714A8-0x80276DE4:
   cu_802714A8.cpp, sdspmix.c, snddrv.c and cu_802753F0.cpp. */

#include <dolphin/ar.h>
#include <dolphin/ax.h>
#include <dolphin/os.h>
#include <string.h>

#include "engine/cu_802714A8.h"

class Class_80271640 {
public:
    unsigned int m0;
    unsigned int m4;
    int m8;
    int mC;
    int m10;
    unsigned char m14;
    unsigned char mUnknown15[11];
    unsigned char *m20;
    unsigned char *m24;
    unsigned char *m28;
    int m2C;
    int m30;
    unsigned char m34;
    unsigned char m35;
    unsigned char m36;
    unsigned char m37;
    unsigned char m38;
    unsigned char mUnknown39;
    unsigned char m3A;
    unsigned char m3B;
    unsigned char m3C;
    unsigned char m3D;
    unsigned char m3E;
    unsigned char m3F;
    unsigned char m40;
    unsigned char m41;
    unsigned char m42;
    unsigned char m43;
    unsigned char m44;
    unsigned char mUnknown45[3];
    int m48;
    void *m4C;

    virtual ~Class_80271640();
    virtual int vfn_02(unsigned int header);
    virtual int vfn_03(unsigned char *data);
    virtual int vfn_04();
    virtual void vfn_05(unsigned char *data);
    virtual int vfn_06();

    void fn_80271698();
    void fn_80271710();
    int fn_80271918();
    void fn_80271AB8();
};

class Class_80271B74 : public Class_80271640 {
public:
    unsigned char mUnknown54[0x15C];
    void *m1B0;

    virtual ~Class_80271B74();
};

struct Voice_803A7734 {
    AXVPB *m0;
    unsigned int m4;
    int m8;
    int mC;
    int m10;
    unsigned char mUnknown14[0x1C];
    unsigned short m30;
    unsigned short m32;
    unsigned short m34;
    unsigned short m36;
    unsigned short m38;
    unsigned short m3A;
    unsigned short m3C;
    unsigned short m3E;
    unsigned short m40;
    unsigned short m42;
    unsigned short m44;
    unsigned short m46;
    unsigned short m48;
    unsigned short m4A;
    unsigned short m4C;
    unsigned short m4E;
    unsigned short m50;
    unsigned short m52;
    unsigned short m54;
    unsigned short m56;
};

struct Channel_803A8D60 {
    unsigned char mUnknown0[0x18];
    int m18;
    signed char m1C;
    unsigned char mUnknown1D[2];
    unsigned char m1F;
    unsigned char mUnknown20[4];
    unsigned char m24;
    volatile unsigned char m25;
    unsigned char mUnknown26[0x16];
    AXVPB *m3C;
};

struct Transfer_803B2B90 {
    int m0;
    ARQRequest m4;
    unsigned int m24;
    unsigned int m28;
    unsigned int m2C;
    unsigned int m30;
    unsigned int m34;
    unsigned char mUnknown38[8];
};

struct Stream_802743A0 {
    unsigned char m0[6][1600];
    unsigned char *m2580[6];
    signed char m2598;
    unsigned char m2599;
    unsigned char m259A;
    unsigned char m259B;
    unsigned char *m259C[6];
    int m25B4;
    short m25B8[6];
    unsigned char *m25C4[6];
    int m25DC;
    int m25E0;
};

struct State_803A8D60 {
    Channel_803A8D60 m0[48];
    unsigned char mUnknownC00[0x808];
    u32 m1408;
    u32 m140C;
    Stream_802743A0 *m1410[32];
    unsigned char mUnknown1490[0x630];
    unsigned char *m1AC0;
    unsigned char mUnknown1AC4[4];
    OSThread m1AC8;
    unsigned char mUnknown1DE0[0x8008];
    int m9DE8;
    int m9DEC;
    unsigned char mUnknown9DF0[0x40];
    Transfer_803B2B90 m9E30[64];
    unsigned char mUnknownAE30[0x1218];
    unsigned char mC048;
    unsigned char mC049;
    unsigned char mUnknownC04A[6];
    void *mC050[6];
    void *mC068[4];
};

struct Struct_80270E04 {
    unsigned char mUnknown0[0x64];
    int *m64;
    int m68;
};

struct Struct_802753AC {
    unsigned char mUnknown0[0x3F];
    unsigned char m3F;
};

struct Node_803B4E20 {
    Node_803B4E20 *m0;
};

struct Loop_80273DF8 {
    unsigned short m0;
    unsigned short m2;
    unsigned char m4;
};

struct Header_80273DF8 {
    unsigned char mUnknown0[2];
    signed char m2;
    signed char m3;
    unsigned char mUnknown4[0xF];
    unsigned char m13;
    unsigned char mUnknown14[0x42];
    unsigned short m56;
    u32 m58;
    u32 m5C;
    int m60;
    u32 *m64;
    int m68[6];
    int m80[6];
    void *m98[6];
    unsigned char mUnknownB0[0x18];
    unsigned char *mC8[6];
    Loop_80273DF8 *mE0[6];
};

struct Info_80274464 {
    unsigned short m0;
    unsigned char m2;
};

struct Struct_80274464 {
    unsigned char mUnknown0[7];
    unsigned char m7;
    unsigned char mUnknown8[0x10];
    void *m18[8];
};

struct Params_80279D0C {
    int m0;
    int m4;
};

extern "C" {
extern int lbl_80300044;
extern const unsigned short lbl_802B7A98[];
extern const short lbl_802B7AF0[2][3][16];
extern Voice_803A7734 lbl_803A7734[64];
extern int lbl_803A8D34;
extern State_803A8D60 lbl_803A8D60;
extern void (*lbl_803B5028)(Setup_80272EC4 *setup);
extern void (*lbl_803B502C)(void);
extern void (*lbl_803B5030)(void **buffers, int count);
extern void (*lbl_803B5034)(int index, int a, int b, int c, int d, void *p, int count, int e, int f, int g, int h,
                            int j, int k, int slot);
extern void (*lbl_803B5038)(int index);
extern void (*lbl_803B503C)(int index);
extern void (*lbl_803B5040)(int index, int value);
extern int lbl_8030002C;
extern int lbl_80300E98;
extern OSMutex lbl_803B4B90;
extern Node_803B4E20 **lbl_803B4E20;
extern float **lbl_803B4E24;

void fn_8026A0E8(int value);
void *fn_8026B5D4(int size);
void fn_8026B7D8(void *p);
void fn_8026D0AC(void);
void fn_8026D0EC(void);
void fn_8027555C(void);
int fn_80276820(int index);
void fn_80276868(int index, int value);
void *fn_80279960(int size);
void fn_80279B24(void *p);
void fn_80279D0C(Node_80279D90 *node, Params_80279D0C *params);
void fn_80279DF8(Node_80279D90 **list, Node_80279D90 *node);
void fn_8027A7A0(Node_80279D90 *node, int a, int b);
void fn_80277240(Node_80279D90 *node);
void fn_80275F54(void);
void fn_802747D8(int index);
void fn_80279598(void);
int fn_8027271C(int index);
int fn_80271BD4(int index, int slot);
void fn_80275E7C(void);
void fn_80276194(int index);
void fn_802763E0(void **buffers, int count);
void fn_80277404(Node_80279D90 *node, void *data, int index);

int fn_80271A04(void);
void fn_80271D34(Voice_803A7734 *voice);
void fn_80271D78(AXVPB *vpb, float *p, unsigned int a, int b);
void fn_80271E50(AXVPB *vpb, unsigned short value, int which);
void fn_80271EC4(int mode);
void fn_80271F18(AXVPB *vpb, unsigned int flags, int volume, unsigned short aux, int unused, float *p,
                 unsigned int a, int b);
void fn_8027210C(AXVPB *vpb);
void fn_80272128(AXVPB *vpb, int value);
void fn_80272150(void);
void fn_8027257C(void);
void fn_80272618(int value);
void fn_80272644(AXVPB *vpb);
void fn_80272990(int channel, int mode);
int fn_80272AA4(int key);
void fn_80272B30(u32 request);
int fn_80272B7C(u32 priority, u32 source, u32 dest, u32 length, int slot);
void fn_80272C9C(int key);
void fn_80272EC4(void);
void fn_80272FB4(void);
int fn_802733A0(void);
int fn_80273458(void);
int fn_80273960(int flag);
void fn_80273040(int index, Stream_802743A0 *stream, Record_803A6DF0 *record);
void fn_802739F8(void);
void fn_80273D7C(u32 flags, int *a, int *b);
int fn_80273DF8(Header_80273DF8 *header, int base, int index, int a, int b, int c);
int fn_80273DC0(Struct_80270E04 *p, int value, int *base);
int fn_802743A0(int index, Stream_802743A0 *stream);
int fn_802747D0(void);
int fn_80274CA8(int index, int value);
int fn_80274464(int stream, int index, int a, int b, int c, Info_80274464 *info, Struct_80274464 *p);
int fn_80274EAC(int index);
int fn_80274F5C(int index);
void *fn_80275150(int unused, int size);
int fn_80275194(int unused, void *p);
int fn_802751E0(u32 start, u32 end);
int fn_80275234(int unused, u32 source, u32 dest, u32 length);
int fn_80275288(int key);
void fn_80275330(void);
void fn_80275358(void);
void fn_8027535C(void);
void fn_80275384(void);
int fn_802753AC(Struct_802753AC *p, int mode);
float *fn_802753F0(int index);
void fn_80275404(void);
void fn_802754A8(void);
void fn_8027555C(void);
void fn_80275F80(int index, int type, int mode, int a, int b, void *data, int c, int d, int e, int f, int g, int h,
                 int k, int slot);
void fn_80275948(float value);
void *fn_80275B7C(int size);
void fn_80275B9C(void *p);
void fn_80275BBC(Setup_80272EC4 *setup);
void fn_80276238(int index);
void fn_80276278(int index);
void fn_80276378(int index, int channel, float value);
void fn_802763AC(int index, int slot, float value);
void fn_80276798(int index, int slot, Desc_80276798 *desc);
int fn_80276820(int index);
void fn_80276868(int index, int value);
void fn_80276A84(int index, int value);
void fn_80276B40(int index, int value);
}


#endif
