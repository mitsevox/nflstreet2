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
    unsigned char m25;
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

void Class_80271640::vfn_05(unsigned char *data)
{
    m20 = data;
    m24 = data;
    m28 = data;
    m2C = 0;
    m30 = 0;
}

Class_80271640::~Class_80271640()
{
    if (m43 != 0) {
        vfn_04();
    }
}

void Class_80271640::fn_80271698()
{
    if (lbl_80300044 == 0) {
        m4C = lbl_803B53E4(m44 * 0x900);
        memset(m4C, 0, m44 * 0x900);
    }
}

void Class_80271640::fn_80271710()
{
    lbl_803B53E8(m4C);
}

int Class_80271640::vfn_02(unsigned int header)
{
    unsigned int id;
    int channels;
    unsigned int rate;
    int layer;
    int lsf;

    if ((header & 0xFFE00000) != 0xFFE00000) {
        return -1;
    }
    id = (header >> 19) & 1;
    m14 = 4 - ((header >> 17) & 3);
    m3A = id;
    m3B = (header >> 16) & 1;
    m3C = (header >> 12) & 0xF;
    m3E = (header >> 9) & 1;
    m3F = (header >> 6) & 3;
    m40 = (header >> 4) & 3;
    m41 = (header >> 3) & 1;
    m42 = (header >> 2) & 1;
    if (header & 0x100000) {
        m37 = id ^ 1;
        m36 = 0;
    } else {
        m36 = 1;
        m37 = 1;
    }
    if (m36 != 0) {
        m3D = ((header >> 10) & 3) + 6;
    } else {
        m3D = ((header >> 10) & 3) + m37 * 3;
        if (m37 == 0) {
            m38 = ((header >> 10) & 3) + 3;
        } else {
            m38 = (header >> 10) & 3;
        }
    }
    channels = 2;
    if (m3F == 3) {
        channels = 1;
    }
    m44 = channels;
    rate = lbl_802B7A98[m3D];
    m4 = rate;
    m0 = rate;
    if (m3C == 0) {
        return -1;
    }
    lsf = m37;
    layer = m14;
    mC = lbl_802B7AF0[lsf][layer - 1][m3C];
    if (layer == 1) {
        m10 = (mC * 12000 / (int)rate + m3E) * 4 - 4;
    } else {
        m10 = mC * 144000 / (int)rate;
        if (layer == 3 && lsf != 0) {
            m10 >>= 1;
        }
        if (m3E != 0) {
            m10++;
        }
        m10 -= 4;
    }
    return 0;
}

int Class_80271640::fn_80271918()
{
    unsigned int header;
    unsigned char *p = m20;

    if (p == 0) {
        header = m48;
    } else {
        header = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
    }
    if (vfn_02(header) == -1) {
        return -1;
    }
    return 0;
}

int Class_80271640::vfn_06()
{
    if (m14 == 1) {
        m8 = m44 * 768;
    } else {
        m8 = m44 * 2304;
        if (m14 == 3 && m37 != 0) {
            m8 >>= 1;
        }
    }
    m34 = 1;
    m35 = 1;
    return 0;
}

int fn_80271A04(void)
{
    return 0;
}

int Class_80271640::vfn_03(unsigned char *data)
{
    if (m43 != 0) {
        vfn_04();
    }
    m43 = 1;
    m20 = data;
    m24 = data;
    if (data == 0) {
        return -1;
    }
    if (fn_80271918() != 0) {
        return -1;
    }
    fn_80271698();
    vfn_06();
    fn_80271AB8();
    return 0;
}

void Class_80271640::fn_80271AB8()
{
    m28 = m20;
    m2C = 0;
    m30 = 0;
}

int Class_80271640::vfn_04()
{
    if (m43 != 0) {
        m43 = m48 = 0;
        fn_80271A04();
        fn_80271710();
    }
    return 0;
}

Class_80271B74::~Class_80271B74()
{
    if (m1B0 != 0) {
        lbl_803B53E8(m1B0);
    }
}

void fn_80271D34(Voice_803A7734 *voice)
{
    voice->m4 = 0x50000000;
    voice->m8 = 0;
    voice->mC = 0;
    voice->m10 = 0;
    voice->m34 = voice->m38 = voice->m3C = voice->m40 = voice->m44 = voice->m48 = voice->m4C = voice->m50 =
        voice->m54 = 0;
    voice->m30 = 0;
}

void fn_80271E50(AXVPB *vpb, unsigned short value, int which)
{
    Voice_803A7734 *voice = &lbl_803A7734[vpb->index];

    if (which == 1) {
        voice->m46 = value;
        voice->m42 = value;
        if (lbl_803A8D34 == 4) {
            voice->m4A = value;
            voice->m56 = value;
        }
    } else if (which == 2) {
        voice->m52 = value;
        voice->m4E = value;
        if (lbl_803A8D34 == 3) {
            voice->m56 = value;
        }
    }
    voice->m4 |= 0x40000000;
}

void fn_80271EC4(int mode)
{
    int i;

    for (i = 0; i < 64; i++) {
        fn_80271D34(&lbl_803A7734[i]);
    }
    lbl_803A8D34 = mode;
}

void fn_80271F18(AXVPB *vpb, unsigned int flags, int volume, unsigned short aux, int unused, float *p,
                 unsigned int a, int b)
{
    Voice_803A7734 *voice = &lbl_803A7734[vpb->index];
    unsigned short mixerCtrl = 0;
    BOOL enabled;

    voice->m0 = vpb;
    voice->m4 = flags & 4;
    voice->m8 = volume;
    fn_80271E50(vpb, aux, 1);
    voice->m40 = voice->m42;
    voice->m44 = voice->m46;
    voice->m48 = voice->m4A;
    fn_80271D78(vpb, p, a, b);
    voice->m34 = voice->m36;
    voice->m38 = voice->m3A;
    voice->m4C = voice->m4E;
    voice->m50 = voice->m52;
    if (voice->m4 & 4) {
        voice->m30 = 0;
    } else {
        voice->m30 = volume;
    }
    enabled = OSDisableInterrupts();
    vpb->pb.ve.currentVolume = voice->m30;
    vpb->pb.ve.currentDelta = 0;
    if ((vpb->pb.mix.vL = voice->m34) != 0) {
        mixerCtrl |= 0x1;
    }
    vpb->pb.mix.vDeltaL = 0;
    if ((vpb->pb.mix.vR = voice->m38) != 0) {
        mixerCtrl |= 0x2;
    }
    vpb->pb.mix.vDeltaR = 0;
    if ((vpb->pb.mix.vAuxAL = voice->m40) != 0) {
        mixerCtrl |= 0x10;
    }
    vpb->pb.mix.vDeltaAuxAL = 0;
    if ((vpb->pb.mix.vAuxAR = voice->m44) != 0) {
        mixerCtrl |= 0x20;
    }
    vpb->pb.mix.vDeltaAuxAR = 0;
    if ((vpb->pb.mix.vAuxBL = voice->m4C) != 0) {
        mixerCtrl |= 0x200;
    }
    vpb->pb.mix.vDeltaAuxBL = 0;
    if ((vpb->pb.mix.vAuxBR = voice->m50) != 0) {
        mixerCtrl |= 0x400;
    }
    vpb->pb.mix.vDeltaAuxBR = 0;
    if ((vpb->pb.mix.vAuxBS = voice->m54) != 0) {
        mixerCtrl |= 0x1000;
    }
    vpb->pb.mix.vDeltaAuxBS = 0;
    if ((vpb->pb.mix.vS = voice->m3C) != 0) {
        mixerCtrl |= 0x4;
    }
    vpb->pb.mix.vDeltaS = 0;
    if ((vpb->pb.mix.vAuxAS = voice->m48) != 0) {
        mixerCtrl |= 0x80;
    }
    vpb->pb.mixerCtrl = mixerCtrl;
    vpb->pb.mix.vDeltaAuxAS = 0;
    vpb->sync |= 0x212;
    OSRestoreInterrupts(enabled);
}

void fn_8027210C(AXVPB *vpb)
{
    lbl_803A7734[vpb->index].m0 = 0;
}

void fn_80272128(AXVPB *vpb, int value)
{
    Voice_803A7734 *voice = &lbl_803A7734[vpb->index];

    voice->m8 = value;
    voice->m4 |= 0x10000000;
}

void fn_80272150(void)
{
    int i;

    for (i = 0; i < 64; i++) {
        Voice_803A7734 *voice = &lbl_803A7734[i];
        AXVPB *vpb = voice->m0;
        int volumeChanged = 0;
        int mixChanged = 0;
        unsigned short mixerCtrl;

        if (vpb != 0) {
            mixerCtrl = 0;
            if (voice->m4 & 0x20000000) {
                voice->m4 &= ~0x20000000;
                volumeChanged = 1;
                voice->m30 = voice->m32;
            }
            if (voice->m4 & 0x10000000) {
                if (voice->m4 & 4) {
                    voice->m32 = 0;
                } else {
                    voice->m32 = voice->m8;
                }
                volumeChanged = 1;
                voice->m4 = (voice->m4 & ~0x10000000) | 0x20000000;
            }
            if (voice->m4 & 0x80000000) {
                mixChanged = 1;
                voice->m34 = voice->m36;
                voice->m38 = voice->m3A;
                voice->m3C = voice->m3E;
                voice->m40 = voice->m42;
                voice->m44 = voice->m46;
                voice->m48 = voice->m4A;
                voice->m4C = voice->m4E;
                voice->m50 = voice->m52;
                voice->m54 = voice->m56;
                voice->m4 &= ~0x80000000;
            }
            if (voice->m4 & 0x40000000) {
                voice->m4 = (voice->m4 & ~0x40000000) | 0x80000000;
                mixChanged = 1;
            }
            if (volumeChanged && vpb != 0) {
                vpb->pb.ve.currentVolume = voice->m32;
                vpb->pb.ve.currentDelta = 0;
                vpb->sync |= 0x200;
            }
            if (mixChanged) {
                if ((vpb->pb.mix.vL = voice->m34) != 0) {
                    mixerCtrl |= 0x1;
                }
                if ((vpb->pb.mix.vDeltaL = (voice->m36 - voice->m34) / 320) != 0) {
                    mixerCtrl |= 0x8;
                }
                if ((vpb->pb.mix.vR = voice->m38) != 0) {
                    mixerCtrl |= 0x2;
                }
                if ((vpb->pb.mix.vDeltaR = (voice->m3A - voice->m38) / 320) != 0) {
                    mixerCtrl |= 0x8;
                }
                if ((vpb->pb.mix.vAuxAL = voice->m40) != 0) {
                    mixerCtrl |= 0x10;
                }
                if ((vpb->pb.mix.vDeltaAuxAL = (voice->m42 - voice->m40) / 320) != 0) {
                    mixerCtrl |= 0x40;
                }
                if ((vpb->pb.mix.vAuxAR = voice->m44) != 0) {
                    mixerCtrl |= 0x20;
                }
                if ((vpb->pb.mix.vDeltaAuxAR = (voice->m46 - voice->m44) / 320) != 0) {
                    mixerCtrl |= 0x40;
                }
                if ((vpb->pb.mix.vAuxBL = voice->m4C) != 0) {
                    mixerCtrl |= 0x200;
                }
                if ((vpb->pb.mix.vDeltaAuxBL = (voice->m4E - voice->m4C) / 320) != 0) {
                    mixerCtrl |= 0x800;
                }
                if ((vpb->pb.mix.vAuxBR = voice->m50) != 0) {
                    mixerCtrl |= 0x400;
                }
                if ((vpb->pb.mix.vDeltaAuxBR = (voice->m52 - voice->m50) / 320) != 0) {
                    mixerCtrl |= 0x800;
                }
                if ((vpb->pb.mix.vAuxBS = voice->m54) != 0) {
                    mixerCtrl |= 0x1000;
                }
                if ((vpb->pb.mix.vDeltaAuxBS = (voice->m56 - voice->m54) / 320) != 0) {
                    mixerCtrl |= 0x2000;
                }
                if ((vpb->pb.mix.vS = voice->m3C) != 0) {
                    mixerCtrl |= 0x4;
                }
                if ((vpb->pb.mix.vDeltaS = (voice->m3E - voice->m3C) / 320) != 0) {
                    mixerCtrl |= 0x8;
                }
                if ((vpb->pb.mix.vAuxAS = voice->m48) != 0) {
                    mixerCtrl |= 0x80;
                }
                if ((vpb->pb.mix.vDeltaAuxAS = (voice->m4A - voice->m48) / 320) != 0) {
                    mixerCtrl |= 0x100;
                }
                if (lbl_803A6C24.m1C.m23 == 4) {
                    mixerCtrl |= 0x4000;
                }
                vpb->pb.mixerCtrl = mixerCtrl;
                vpb->sync |= 0x12;
            }
        }
    }
}

void fn_8027257C(void)
{
    int i;

    if (lbl_803A8D60.mC049 != 0) {
        for (i = 0; i < 48; i++) {
            if (lbl_803A8D60.m0[i].m1F != 0) {
                AXFreeVoice(lbl_803A8D60.m0[i].m3C);
                lbl_803A8D60.m0[i].m1F = 0;
                lbl_803A8D60.mC049--;
                lbl_803A8D60.m0[i].m3C = 0;
                if (lbl_803A8D60.mC049 == 0) {
                    break;
                }
            }
        }
    }
}

void fn_80272618(int value)
{
    fn_8026A0E8(value + lbl_803A6C24.m1C.m12);
}

void fn_80272644(AXVPB *vpb)
{
    Record_803A6DF0 *records = lbl_803A6C24.m1CC;
    Record_803A6DF0 *record = &records[vpb->userContext];
    int index;
    int i;

    if (record->m28 == -1) {
        index = vpb->userContext;
    } else {
        index = record->m28;
    }
    record = &records[index];
    for (i = 0; i < record->m23; i++) {
        int channel = record->m4[i];

        if (lbl_803A8D60.m0[channel].m3C != 0) {
            if (channel == vpb->userContext) {
                fn_80272990(channel, 1);
            } else {
                fn_80272990(channel, 2);
            }
            lbl_803A8D60.m0[record->m4[i]].m24 = 0;
        }
    }
}

void fn_80272990(int channel, int mode)
{
    Channel_803A8D60 *state = &lbl_803A8D60.m0[channel];
    AXVPB *vpb = state->m3C;
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[channel];

    fn_8027210C(vpb);
    state->m18 = -1;
    if (record->m6D != 0) {
        fn_8026A0E8(channel);
    }
    if (mode == 0) {
        if (vpb != 0) {
            AXFreeVoice(vpb);
            state->m3C = 0;
        }
    } else if (mode == 2) {
        if (state->m25 == 0 && vpb != 0) {
            state->m1F = 1;
            lbl_803A8D60.mC049++;
        }
    } else if (mode == 1) {
        if (state->m1F == 1) {
            state->m1F = 0;
            lbl_803A8D60.mC049--;
        }
        state->m3C = 0;
    }
    if (state->m25 == 0) {
        state->m25 = 1;
    }
}

int fn_80272AA4(int key)
{
    int i;
    BOOL enabled = OSDisableInterrupts();

    for (i = 0; i < 64; i++) {
        if (lbl_803A8D60.m9E30[i].m0 == -1) {
            break;
        }
    }
    lbl_803A8D60.m9E30[i].m0 = key;
    OSRestoreInterrupts(enabled);
    return i;
}

void fn_80272B30(u32 request)
{
    int i;

    lbl_803A8D60.m9DE8 = ((ARQRequest *)request)->owner;
    for (i = 0; i < 64; i++) {
        if (lbl_803A8D60.m9E30[i].m0 == ((ARQRequest *)request)->owner) {
            lbl_803A8D60.m9E30[i].m0 = -1;
            return;
        }
    }
}

int fn_80272B7C(u32 priority, u32 source, u32 dest, u32 length, int slot)
{
    BOOL enabled = OSDisableInterrupts();
    int index;
    u32 owner;

    if (slot == -1) {
        index = fn_80272AA4(lbl_803A8D60.m9DEC);
        owner = lbl_803A8D60.m9DEC;
        lbl_803A8D60.m9E30[index].m24 = priority;
        lbl_803A8D60.m9E30[index].m28 = source;
        lbl_803A8D60.m9E30[index].m2C = dest;
        lbl_803A8D60.m9E30[index].m30 = OSRoundUp32B(length);
        lbl_803A8D60.m9E30[index].m34 = lbl_803A6C24.m170;
    } else {
        index = slot;
        owner = lbl_803A8D60.m9E30[index].m0;
    }
    ARQPostRequest(&lbl_803A8D60.m9E30[index].m4, owner, ARQ_TYPE_MRAM_TO_ARAM, priority, source, dest,
                   OSRoundUp32B(length), fn_80272B30);
    OSRestoreInterrupts(enabled);
    return lbl_803A8D60.m9DEC++;
}

void fn_80272C9C(int key)
{
    int i;
    BOOL enabled = OSDisableInterrupts();

    for (i = 0; i < 64; i++) {
        if (lbl_803A8D60.m9E30[i].m0 == key) {
            ARQRemoveRequest(&lbl_803A8D60.m9E30[i].m4);
            fn_80272B7C(lbl_803A8D60.m9E30[i].m24, lbl_803A8D60.m9E30[i].m28, lbl_803A8D60.m9E30[i].m2C,
                        lbl_803A8D60.m9E30[i].m30, i);
        }
    }
    OSRestoreInterrupts(enabled);
}

void fn_80272EC4(void)
{
    Setup_80272EC4 setup;
    int i;

    fn_8027555C();
    setup.m8 = lbl_803A6C24.m1C.mE;
    if (lbl_803A6C24.m1C.m23 != 1) {
        setup.m9 = lbl_803A6C24.m1C.m23;
    } else {
        setup.m9 = 2;
    }
    setup.m0 = lbl_803A6C24.m1C.mA;
    setup.m4 = fn_80272618;
    setup.mA = 0;
    lbl_803B5028(&setup);
    fn_8026D0AC();
    for (i = 0; i < setup.m9; i++) {
        void *buffer = fn_8026B5D4(672);

        lbl_803A8D60.mC050[i] = buffer;
        lbl_803A8D60.mC068[i] = (void *)OSRoundUp32B(buffer);
    }
    fn_8026D0EC();
    lbl_803A8D60.mC048 = 1;
}

void fn_80272FB4(void)
{
    int i;

    lbl_803A8D60.mC048 = 0;
    fn_8026D0AC();
    for (i = 0; i < lbl_803A6C24.m1C.m23; i++) {
        fn_8026B7D8(lbl_803A8D60.mC050[i]);
    }
    fn_8026D0EC();
    lbl_803B502C();
}

int fn_802733A0(void)
{
    u32 base;

    lbl_803A6C24.m6 = 32;
    lbl_803A6C24.m0 = 32000;
    lbl_803A6C24.m2 = 32000;
    lbl_803A6C24.m4 = 1;
    lbl_803A6C24.m5 = 4;
    lbl_803A6C24.mA = 48;
    lbl_803A6C24.mC = 2;
    lbl_803A6C24.mE = 544;
    lbl_803A6C24.m10 = 36;
    lbl_803A6C24.m1C.mA = 32000;
    lbl_803A6C24.m1C.mE = 8;
    lbl_803A6C24.m1C.m12 = 48;
    lbl_803A6C24.m1C.m21 = 1;
    lbl_803A6C24.m1C.m22 = 8;
    lbl_803A6C24.m1C.m23 = 2;
    lbl_803A6C24.m1C.m25 = 1;
    lbl_803A6C24.m1C.m28 = 2;
    lbl_803A6C24.m1C.m2A = 544;
    lbl_803A6C24.m1C.m2C = 36;
    base = ARGetBaseAddress() + 256;
    lbl_803A6C24.m1C.m38 = base;
    lbl_803A6C24.m1C.m3C = 0x800000 - base;
    return 0;
}

void fn_80273040(int index, Stream_802743A0 *stream, Record_803A6DF0 *record)
{
    unsigned char *source[6];
    int length;
    int b;
    int remaining = 1536;
    int chunk;
    int rest;
    int i;

    do {
        if (stream->m25C4[0] == 0) {
            for (i = 0; i < record->m23; i++) {
                stream->m25C4[i] = fn_802792F0(index, i, &length, &b);
            }
            stream->m25E0 = 0;
            stream->m25DC = length * 2;
        }
        chunk = remaining;
        if (stream->m25C4[0] != 0) {
            int available = stream->m25DC - stream->m25E0;

            if (available <= 0) {
                stream->m25C4[0] = 0;
                continue;
            }
            if (remaining > available) {
                chunk = available;
            }
            stream->m25B8[stream->m2599] += chunk >> 1;
            rest = remaining - chunk;
            for (i = 0; i < record->m23; i++) {
                source[i] = stream->m25C4[i] + stream->m25E0;
            }
            stream->m25E0 += chunk;
        } else {
            rest = 0;
            for (i = 0; i < record->m23; i++) {
                source[i] = lbl_803A8D60.m1AC0;
            }
        }
        for (i = 0; i < record->m23; i++) {
            fn_8026B2E0(stream->m2580[i] + (1536 - remaining), source[i], chunk);
        }
        remaining = rest;
    } while (remaining > 0);
    for (i = 0; i < record->m23; i++) {
        DCFlushRange(stream->m2580[i], 1536);
        fn_80272B7C(1, (u32)stream->m2580[i], (u32)stream->m259C[i] + stream->m2599 * 1536, 1536, -1);
    }
}


int fn_80273458(void)
{
    Params_803A6C40 params = lbl_803A6C24.m1C;

    if (lbl_803A6C24.m168 != 0) {
        lbl_803A6C24.m1C = lbl_803A6C24.mCC;
    }
    params.mA = 32000;
    if (params.m23 < lbl_803A6C24.m4) {
        params.m23 = lbl_803A6C24.m4;
    }
    if (params.m23 > lbl_803A6C24.m5) {
        params.m23 = lbl_803A6C24.m5;
    }
    if (params.mE > lbl_803A6C24.m6) {
        params.mE = lbl_803A6C24.m6;
    }
    if (params.m12 > lbl_803A6C24.mA) {
        params.m12 = lbl_803A6C24.mA;
    }
    if (params.m22 > 32) {
        params.m22 = 32;
    }
    if (lbl_803A6C24.m168 != 0) {
        return 0;
    }
    lbl_803A6C24.m16C = params.mE + params.m12;
    lbl_803A6C24.m1C = params;
    return 0;
}

int fn_80273960(int flag)
{
    AXRegisterAuxACallback(0, 0);
    if (lbl_803A8D60.mC048 != 0) {
        fn_80272FB4();
    }
    if (flag == 0) {
        fn_802798C0();
    }
    while (lbl_803A6C24.m169 != 0) {
        fn_8026D0EC();
    }
    OSCancelThread(&lbl_803A8D60.m1AC8);
    AXQuit();
    return 0;
}

void fn_802739F8(void)
{
    AXPBADPCM adpcm;
    AXPBADPCMLOOP loop;
    AXPBADDR addr;
    int i;
    int j;

    for (i = 0; i < lbl_803A6C24.m1C.m22; i++) {
        Stream_802743A0 *stream = lbl_803A8D60.m1410[i];
        Channel_803A8D60 *channel;
        Record_803A6DF0 *record;
        AXVPB *vpb;
        int position;
        int half;

        if (stream == 0 || stream->m2598 < 0) {
            continue;
        }
        channel = &lbl_803A8D60.m0[stream->m2598];
        record = &lbl_803A6C24.m1CC[stream->m2598];
        if (!(stream->m259A & 0x80)) {
            stream->m259A--;
            if (stream->m259A & 0x80) {
                addr.format = 10;
                adpcm.gain = 2048;
                addr.loopFlag = 1;
                memset(&loop, 0, sizeof(loop));
                fn_80274B50(stream->m2598);
                for (j = 0; j < record->m23; j++) {
                    u32 address;
                    u32 loopAddress;
                    u32 endAddress;

                    fn_80274960(record->m4[j]);
                    fn_802747D8(record->m4[j]);
                    address = (u32)stream->m259C[j];
                    loopAddress = address >> 1;
                    endAddress = (address + 3070) >> 1;
                    AXSetVoiceAdpcm(lbl_803A8D60.m0[record->m4[j]].m3C, &adpcm);
                    AXSetVoiceAdpcmLoop(lbl_803A8D60.m0[record->m4[j]].m3C, &loop);
                    addr.endAddressHi = endAddress >> 16;
                    addr.endAddressLo = endAddress;
                    addr.loopAddressHi = loopAddress >> 16;
                    addr.loopAddressLo = loopAddress;
                    addr.currentAddressHi = loopAddress >> 16;
                    addr.currentAddressLo = loopAddress;
                    AXSetVoiceAddr(lbl_803A8D60.m0[record->m4[j]].m3C, &addr);
                    AXSetVoiceState(lbl_803A8D60.m0[record->m4[j]].m3C, 1);
                    lbl_803A8D60.m0[record->m4[j]].m24 = 1;
                }
            }
        }
        vpb = channel->m3C;
        if (vpb == 0) {
            continue;
        }
        position = (vpb->pb.addr.currentAddressHi << 16) + vpb->pb.addr.currentAddressLo;
        half = position > stream->m25B4;
        if (half != stream->m2599) {
            if (stream->m25B8[stream->m2599] != 0) {
                for (j = 0; j < record->m23; j++) {
                    fn_8027952C(i, j, stream->m25B8[stream->m2599]);
                }
                stream->m25B8[stream->m2599] = 0;
            }
            fn_80273040(i, stream, record);
            stream->m2599 = half;
        }
    }
    fn_80279598();
    for (i = 0; i < lbl_803A6C24.m1C.m12; i++) {
        Channel_803A8D60 *channel = &lbl_803A8D60.m0[i];
        Record_803A6DF0 *record = &lbl_803A6C24.m1CC[i];
        AXVPB *vpb = channel->m3C;

        if (vpb != 0 && channel->m24 != 0 && vpb->pb.state == 0 && channel->m18 >= 0 && channel->m24 == 1) {
            for (j = 0; j < lbl_803A6C24.m1CC[i].m23; j++) {
                if (lbl_803A8D60.m0[record->m4[j]].m24 != 0) {
                    fn_80272990(record->m4[j], 0);
                    lbl_803A8D60.m0[record->m4[j]].m24 = 0;
                }
            }
        }
    }
    fn_8027257C();
    fn_80272150();
}

void fn_80273D7C(u32 flags, int *a, int *b)
{
    if (flags & 0x200) {
        *a = 0;
        *b = lbl_803A6C24.m1C.m12;
    } else if (flags & 4) {
        *a = lbl_803A6C24.m1C.m12;
        *b = lbl_803A6C24.m16C;
    }
}

int fn_80273DC0(Struct_80270E04 *p, int value, int *base)
{
    if (*base == 0) {
        *base = p->m68;
    }
    *p->m64 = value + (p->m68 - *base);
    return 0;
}

int fn_80273DF8(Header_80273DF8 *header, int base, int index, int a, int b, int c)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    Channel_803A8D60 *channel = &lbl_803A8D60.m0[index];
    AXPBADDR addr;
    AXPBADPCM adpcm;
    AXPBADPCMLOOP loop;
    u32 size = 0;
    u32 offset = 0;
    u32 loopStart;
    u32 loopEnd;
    int i;

    record->m20 = header->m56;
    record->m14 = header->m58;
    record->m23 = header->m3;
    if (record->m24 & 0x200) {
        memset(&loop, 0, sizeof(loop));
        if (header->m60 >= 0) {
            addr.loopFlag = 1;
            loopEnd = header->m60;
            loopStart = header->m5C;
        } else {
            addr.loopFlag = 0;
            if (record->m22 == 18) {
                loopStart = lbl_803A8D60.m140C;
            } else {
                loopStart = lbl_803A8D60.m1408;
            }
            loopEnd = header->m58 - 1;
        }
        if (record->m22 == 18) {
            size = (header->m58 + 13) / 14 * 14;
            addr.format = 0;
            adpcm.gain = 0;
            adpcm.yn1 = 0;
            adpcm.yn2 = 0;
            loopEnd = loopEnd * 8 / 7;
            loopStart = loopStart * 8 / 7;
            size = size * 8 / 7;
            offset = *header->m64 << 1;
        } else if (record->m22 == 7) {
            addr.format = 10;
            adpcm.gain = 2048;
            size = header->m58;
            offset = *header->m64 >> 1;
        }
        channel->m18 = offset;
        if (fn_8027271C(index) == 0) {
            return -9;
        }
        for (i = 0; i < record->m23; i++) {
            fn_80274960(record->m4[i]);
            fn_802747D8(record->m4[i]);
        }
        fn_80274B50(index);
        fn_80271BD4(record->m4[0], 0);
        for (i = 0; i < header->m3; i++) {
            u32 start;
            u32 loopAddress;
            u32 endAddress;

            if (record->m22 == 18) {
                fn_8026B2E0(&adpcm, header->mC8[i], 32);
                adpcm.pred_scale = header->mC8[i][32];
                if (header->m60 > 0) {
                    loop.loop_pred_scale = header->mE0[i]->m4;
                    loop.loop_yn1 = header->mE0[i]->m0;
                    loop.loop_yn2 = header->mE0[i]->m2;
                }
            }
            start = offset + size * i;
            loopAddress = loopStart;
            if (header->m60 > 0) {
                loopAddress = start + loopStart;
            }
            endAddress = start + loopEnd - 2;
            if (record->m22 == 18) {
                start += 2;
                if ((loopAddress & 15) == 0) {
                    loopAddress += 2;
                } else if ((loopAddress & 15) == 1) {
                    loopAddress += 1;
                }
                if ((endAddress & 15) == 0) {
                    endAddress += 2;
                } else if ((endAddress & 15) == 1) {
                    endAddress += 1;
                }
            }
            AXSetVoiceSrcType(lbl_803A8D60.m0[record->m4[i]].m3C, 1);
            AXSetVoiceAdpcm(lbl_803A8D60.m0[record->m4[i]].m3C, &adpcm);
            AXSetVoiceAdpcmLoop(lbl_803A8D60.m0[record->m4[i]].m3C, &loop);
            addr.currentAddressHi = start >> 16;
            addr.loopAddressHi = loopAddress >> 16;
            addr.endAddressHi = endAddress >> 16;
            addr.endAddressLo = endAddress;
            addr.currentAddressLo = start;
            addr.loopAddressLo = loopAddress;
            AXSetVoiceAddr(lbl_803A8D60.m0[record->m4[i]].m3C, &addr);
            AXSetVoiceState(lbl_803A8D60.m0[record->m4[i]].m3C, 1);
            lbl_803A8D60.m0[record->m4[i]].m24 = 1;
        }
    } else {
        for (i = 0; i < record->m23; i++) {
            fn_80275F80(record->m4[i] - lbl_803A6C24.m1C.m12, header->m13, 1, base + header->m68[i],
                        base + header->m68[0] + header->m80[i], header->m98[i], record->m23, record->m14, header->m5C,
                        header->m60, 0, 0, header->m2, i);
            fn_80274960(record->m4[i]);
        }
        fn_80274B50(record->m4[0]);
        for (i = 0; i < lbl_8030002C; i++) {
            fn_80271BD4(record->m4[0], i);
        }
        fn_80274CA8(record->m4[0], a);
        fn_80274D34(record->m4[0], b);
        fn_80274E24(record->m4[0], c);
        for (i = 0; i < record->m23; i++) {
            fn_80276194(record->m4[i] - lbl_803A6C24.m1C.m12);
        }
    }
    return 0;
}

int fn_80274304(int index)
{
    Record_803A6DF0 *record;

    index += lbl_803A6C24.m1C.m12;
    record = &lbl_803A6C24.m1CC[index];
    if (record->m28 == -1) {
        return index;
    }
    return record->m28;
}

int fn_80274334(int index)
{
    Record_803A6DF0 *records = lbl_803A6C24.m1CC;
    Record_803A6DF0 *record;
    int i;

    index += lbl_803A6C24.m1C.m12;
    record = &records[index];
    if (record->m28 == -1) {
        return 0;
    }
    record = &records[record->m28];
    for (i = 1; i < 6; i++) {
        if (record->m4[i] == index) {
            return i;
        }
    }
    return 0;
}

int fn_80274398(void)
{
    return sizeof(Stream_802743A0);
}

int fn_802743A0(int index, Stream_802743A0 *stream)
{
    int i;

    memset(stream, 0, sizeof(Stream_802743A0));
    stream->m259C[0] = (unsigned char *)fn_80275150(0, 0x4800);
    if (stream->m259C[0] == 0) {
        return -9;
    }
    for (i = 0; i < 6; i++) {
        stream->m259C[i] = stream->m259C[0] + i * 0xC00;
        stream->m2580[i] = (unsigned char *)OSRoundUp32B(stream->m0[i]);
    }
    stream->m2598 = -1;
    lbl_803A8D60.m1410[index] = stream;
    return 0;
}

int fn_80274464(int stream, int index, int a, int b, int c, Info_80274464 *info, Struct_80274464 *p)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    int i;

    record->m14 = 0;
    record->m20 = info->m0;
    lbl_803A8D60.m0[index].m1C = stream;
    record->m23 = info->m2;
    if (record->m24 & 4) {
        for (i = 0; i < record->m23; i++) {
            lbl_803B5034(record->m4[i] - lbl_803A6C24.m1C.m12, record->m22, 0, 0, 0, p->m18[i], record->m23, 0, -1,
                         -1, 0, 0, p->m7, i);
        }
        fn_80274B50(record->m4[0]);
        for (i = 0; i < record->m23; i++) {
            fn_80274960(record->m4[i]);
            fn_802747D8(record->m4[i]);
        }
        fn_80274CA8(record->m4[0], a);
        fn_80274D34(record->m4[0], b);
        fn_80274E24(record->m4[0], c);
        for (i = 0; i < record->m23; i++) {
            lbl_803B5038(record->m4[i] - lbl_803A6C24.m1C.m12);
        }
    } else {
        Stream_802743A0 *block = lbl_803A8D60.m1410[stream];

        for (i = 0; i < 6; i++) {
            block->m25B8[i] = 0;
        }
        block->m25C4[0] = 0;
        block->m259A = 2;
        block->m2599 = 1;
        block->m2598 = index;
        block->m259B = info->m2;
        fn_8027271C(index);
        for (i = 0; i < info->m2; i++) {
            u32 loopAddress = (u32)block->m259C[i] >> 1;
            u32 endAddress = ((u32)block->m259C[i] + 3070) >> 1;

            if (i == 0) {
                block->m25B4 = (loopAddress + endAddress) >> 1;
            }
            memset(block->m2580[i], 0, 1536);
            DCFlushRange(block->m2580[i], 1536);
            fn_80272B7C(1, (u32)block->m2580[i], (u32)block->m259C[i], 1536, -1);
            AXSetVoiceSrcType(lbl_803A8D60.m0[record->m4[i]].m3C, 1);
            lbl_803A8D60.m0[record->m4[i]].m24 = 1;
        }
    }
    return 0;
}

int fn_8027474C(int index)
{
    Stream_802743A0 *stream = lbl_803A8D60.m1410[index];
    int i;

    fn_80275194(0, stream->m259C[0]);
    for (i = 0; i < 6; i++) {
        stream->m259C[i] = 0;
    }
    lbl_803A8D60.m1410[index] = 0;
    return 0;
}

int fn_802747D0(void)
{
    return -15;
}

int fn_80274CA8(int index, int value)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    int i;

    if (record->m24 & 4) {
        for (i = 0; i < record->m23; i++) {
            fn_80276B40(record->m4[i] - lbl_803A6C24.m1C.m12, value);
        }
    }
    return 0;
}

void fn_80274E24(int index, int value)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    int i;

    if (record->m24 & 4) {
        for (i = 0; i < record->m23; i++) {
            fn_80276868(record->m4[i] - lbl_803A6C24.m1C.m12, value);
        }
    }
}

int fn_80274EAC(int index)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    Channel_803A8D60 *channel = &lbl_803A8D60.m0[index];
    AXVPB *vpb;
    u32 position;

    if (record->m24 & 0x200) {
        vpb = channel->m3C;
        if (vpb == 0) {
            return -8;
        }
        position = (vpb->pb.addr.currentAddressHi << 16) + vpb->pb.addr.currentAddressLo;
        if (record->m22 == 18) {
            return ((int)(position - channel->m18) * 7) >> 3;
        }
        return position - channel->m18;
    }
    return fn_80276820(index - lbl_803A6C24.m1C.m12);
}

int fn_80274F5C(int index)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    Channel_803A8D60 *channel = &lbl_803A8D60.m0[index];
    int i;

    if (record->m24 & 0x200) {
        if (channel->m1C >= 0) {
            lbl_803A8D60.m1410[channel->m1C]->m2598 = -1;
            channel->m1C = -1;
        }
        for (i = 0; i < record->m23; i++) {
            if (lbl_803A8D60.m0[record->m4[i]].m3C == 0) {
                return -8;
            }
            AXSetVoiceState(lbl_803A8D60.m0[record->m4[i]].m3C, 0);
            if (lbl_803A8D60.m0[record->m4[i]].m24 != 0) {
                fn_80272990(record->m4[i], 0);
                lbl_803A8D60.m0[record->m4[i]].m24 = 0;
            }
        }
    } else {
        for (i = 0; i < record->m23; i++) {
            lbl_803B503C(record->m4[i] - lbl_803A6C24.m1C.m12);
            fn_8026A0E8(record->m4[i]);
        }
    }
    return 0;
}

int fn_802750B8(int index, Desc_80276798 *desc)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    int i;

    if (record->m24 & 4) {
        for (i = 0; i < record->m23; i++) {
            fn_80276798(record->m4[i] - lbl_803A6C24.m1C.m12, i, desc);
        }
        return 0;
    }
    return -7;
}

void *fn_80275150(int unused, int size)
{
    size = OSRoundUp32B(size);
    if (lbl_803A6C24.mB8 != 0) {
        return lbl_803A6C24.mB8(size);
    }
    return fn_80279960(size);
}

int fn_80275194(int unused, void *p)
{
    if (lbl_803A6C24.mBC == 0) {
        fn_80279B24(p);
    } else {
        lbl_803A6C24.mBC(p);
    }
    return 0;
}

int fn_802751E0(u32 start, u32 end)
{
    if (start == (u32)-1) {
        start = lbl_803A6C24.m1C.m38;
    }
    if (end == (u32)-1) {
        end = lbl_803A6C24.m1C.m38 + lbl_803A6C24.m1C.m3C;
    }
    fn_8027986C(start, end - start);
    return 0;
}

int fn_80275234(int unused, u32 source, u32 dest, u32 length)
{
    DCFlushRange((void *)source, length);
    return fn_80272B7C(0, source, dest, length, -1);
}

int fn_80275288(int key)
{
    BOOL enabled = OSDisableInterrupts();
    int i;

    for (i = 0; i < 64; i++) {
        if (lbl_803A8D60.m9E30[i].m0 != -1 && lbl_803A8D60.m9E30[i].m0 == key) {
            if (lbl_803A6C24.m170 - lbl_803A8D60.m9E30[i].m34 > 200) {
                OSRestoreInterrupts(enabled);
                fn_80272C9C(key);
            } else {
                OSRestoreInterrupts(enabled);
            }
            return 0;
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}

void fn_80275330(void)
{
    OSInitMutex(&lbl_803B4B90);
}

void fn_80275358(void)
{
}

void fn_8027535C(void)
{
    OSLockMutex(&lbl_803B4B90);
}

void fn_80275384(void)
{
    OSUnlockMutex(&lbl_803B4B90);
}

int fn_802753AC(Struct_802753AC *p, int mode)
{
    switch (mode) {
    case 0:
        p->m3F = 1;
        break;
    case 1:
        p->m3F = 2;
        break;
    case 8:
        p->m3F = 4;
        break;
    }
    return 0;
}

float *fn_802753F0(int index)
{
    return lbl_803B4E24[index];
}

void fn_80275404(void)
{
    int size = lbl_8030002C * 12;

    lbl_803B4E24 = (float **)fn_8026B5D4(size);
    lbl_803B4E34.m14 = (int *)(lbl_803B4E24 + lbl_8030002C);
    lbl_803B4E34.m100 = (float *)(lbl_803B4E34.m14 + lbl_8030002C);
    memset(lbl_803B4E24, 0, size);
    lbl_803B4E20 = (Node_803B4E20 **)fn_8026B5D4(lbl_8030002C * 4);
    memset(lbl_803B4E20, 0, lbl_8030002C * 4);
    lbl_80300E98 = 1;
}

void fn_802754A8(void)
{
    int i;

    if (lbl_80300E98 != 0) {
        fn_8026B7D8(lbl_803B4E24);
        for (i = 0; i < lbl_8030002C; i++) {
            Node_803B4E20 *node = lbl_803B4E20[i];

            if (node != 0) {
                do {
                    Node_803B4E20 *next = node->m0;

                    fn_8026B7D8(node);
                    node = next;
                } while (node != 0);
            }
        }
        fn_8026B7D8(lbl_803B4E20);
        lbl_80300E98 = 0;
    }
}

void fn_8027555C(void)
{
    lbl_803B5028 = fn_80275BBC;
    lbl_803B502C = fn_80275E7C;
    lbl_803B5030 = fn_802763E0;
    lbl_803B5034 = fn_80275F80;
    lbl_803B5038 = fn_80276194;
    lbl_803B503C = fn_80276278;
    lbl_803B5040 = fn_80276A84;
}


void fn_80275948(float value)
{
}

void *fn_80275B7C(int size)
{
    return fn_8026B5D4(size);
}

void fn_80275B9C(void *p)
{
    fn_8026B7D8(p);
}

void fn_80275BBC(Setup_80272EC4 *setup)
{
    int i;

    fn_802797F4(fn_80275B7C);
    fn_80279800(fn_80275B9C);
    fn_8027980C(fn_8026B2E0);
    lbl_803B4E34.m0 = *setup;
    fn_8026D0AC();
    fn_80275404();
    for (i = 0; i < lbl_8030002C; i++) {
        lbl_803B4E34.m14[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        void *buffer = fn_8026B5D4(2748);

        lbl_803B4E34.mA8[i] = buffer;
        lbl_803B4E34.mB0[i] = (int *)buffer + 2;
        while ((u32)lbl_803B4E34.mB0[i] & 0x3F) {
            lbl_803B4E34.mB0[i]++;
        }
    }
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        void *buffer = fn_8026B5D4(704);

        lbl_803B4E34.mB8[i] = buffer;
        lbl_803B4E34.mD0[i] = (int *)buffer;
        while ((u32)lbl_803B4E34.mD0[i] & 0x3F) {
            lbl_803B4E34.mD0[i]++;
        }
    }
    if (lbl_803B4E34.m0.m8 != 0) {
        float *p;

        lbl_803B4E34.m1DC = (Record_803B5010 *)fn_8026B5D4(
            lbl_803B4E34.m0.m8 * sizeof(Record_803B5010) + lbl_8030002C * sizeof(float) * lbl_803B4E34.m0.m8 +
            lbl_8030002C * sizeof(float) * lbl_803B4E34.m0.m8);
        memset(lbl_803B4E34.m1DC, 0,
               lbl_803B4E34.m0.m8 * sizeof(Record_803B5010) + lbl_8030002C * sizeof(float) * lbl_803B4E34.m0.m8 +
            lbl_8030002C * sizeof(float) * lbl_803B4E34.m0.m8);
        p = (float *)&lbl_803B4E34.m1DC[lbl_803B4E34.m0.m8];
        for (i = 0; i < lbl_803B4E34.m0.m8; i++) {
            lbl_803B4E34.m1DC[i].m34 = p;
            p += lbl_8030002C;
            lbl_803B4E34.m1DC[i].m38 = p;
            p += lbl_8030002C;
        }
    }
    fn_8026D0EC();
    fn_8027A7FC();
    fn_8027A8A4();
    fn_8027A844();
    fn_80275F54();
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        lbl_803B4E34.m104[i] = 0;
        fn_80279C20(&lbl_803B4E34.m134[i]);
        lbl_803B4E34.m134[i].m18 = 0;
        lbl_803B4E34.m134[i].m1A = 0;
        fn_80279D90(&lbl_803B4E34.m104[i], &lbl_803B4E34.m134[i]);
        memset(lbl_803B4E34.mD0[i], 0, 640);
    }
}

void fn_80275F54(void)
{
    lbl_803B4E34.m1E0 = fn_8027A8EC;
    lbl_803B4E34.m1E4 = fn_802774C8;
    lbl_803B4E34.mC = 320;
}

void fn_80275F80(int index, int type, int mode, int a, int b, void *data, int c, int d, int e, int f, int g, int h,
                 int k, int slot)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Params_80275F80 params;
    int table = 0;
    int kind;

    record->m40 = 0;
    record->m48 = 0;
    record->m50 = 0;
    record->m54 = 0;
    record->m58 = 0;
    record->m4C = 0;
    params.m18 = 1;
    params.m28 = 0;
    kind = -1;
    if (type == 7) {
        kind = 0;
    } else if (type == 10) {
        kind = 1;
    } else if (type == 4) {
        kind = 2;
    } else if (type == 22) {
        kind = 3;
    } else if (type == 16) {
        kind = 4;
    } else if (type == 23) {
        kind = 5;
    }
    if (mode == 1) {
        if (f > 0) {
            table = 1;
        }
    } else if (mode == 0) {
        table = 2;
    }
    if (lbl_803B4E34.m18[kind][table] != 0) {
        record->m48 = (Node_80279D90 *)fn_8026B5D4(lbl_803B4E34.m60[kind][table]);
        params.m0 = a;
        params.m24 = k;
        params.m4 = b;
        params.m8 = c;
        params.mC = d;
        params.m10 = e;
        params.m14 = f;
        params.m20 = lbl_803A6C24.m16F;
        params.m1C = index;
        record->m48->m4 = 0;
        record->m48->m18 = 240;
        record->m48->m1A = slot;
        lbl_803B4E34.m18[kind][table](record->m48, &params);
        record->m44 = params.m28;
        fn_80279D90(&record->m40, record->m48);
    }
    if (data != 0) {
        if (mode != 0) {
            index = -1;
        }
        record->m4C = (Node_80279D90 *)fn_8026B5D4(6196);
        record->m4C->m4 = 0;
        record->m4C->m18 = 200;
        record->m4C->m1A = slot;
        fn_80277404(record->m4C, data, index);
        fn_80279D90(&record->m40, record->m4C);
    }
    record->m0 = 1;
}

void fn_80276238(int index)
{
    fn_80276278(index);
    lbl_803B4E34.m0.m4(index);
}

void fn_80276278(int index)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Node_80279D90 *next;
    int i;

    for (i = 0; i < lbl_8030002C; i++) {
        lbl_803B4E34.m100[i] += record->m34[i] * record->m3C;
    }
    for (i = 0; i < lbl_803B4E34.m0.m9; i++) {
        lbl_803B4E34.mE8[i] += record->m4[i] * record->m3C;
    }
    do {
        if (record->m40->m4 != 0) {
            record->m40->m4(record->m40);
        }
        next = record->m40->m8;
        fn_8026B7D8(record->m40);
        record->m40 = next;
    } while (next != 0);
    record->m0 = 0;
}

void fn_80276378(int index, int channel, float value)
{
    lbl_803B4E34.m1DC[index].m1C[channel] = value;
    lbl_803B4E34.m1DC[index].m1 = 1;
}

void fn_802763AC(int index, int slot, float value)
{
    lbl_803B4E34.m1DC[index].m38[slot] = value;
    lbl_803B4E34.m1DC[index].m1 = 1;
}

void fn_80276798(int index, int slot, Desc_80276798 *desc)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Node_80279D90 *node = (Node_80279D90 *)fn_8026B5D4(desc->m4);

    desc->mC(node, desc->m0, slot);
    node->m18 = desc->mA;
    node->m0 = desc->m10;
    node->m4 = desc->m14;
    node->m1A = 0;
    fn_80279D90(&record->m40, node);
}

int fn_80276820(int index)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];

    if (record->m44 != 0) {
        return record->m44(record->m48);
    }
    return -1;
}

void fn_80276868(int index, int value)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Node_80279D90 *node;
    Params_80279D0C params;

    if (value > 0) {
        node = record->m58;
        if (node == 0) {
            record->m58 = (Node_80279D90 *)fn_8026B5D4(88);
            record->m58->m4 = 0;
            record->m58->m18 = 80;
            record->m58->m1A = 0;
            fn_80279CB8(record->m58);
            fn_80279D90(&record->m40, record->m58);
        }
        params.m0 = value << 8;
        params.m4 = lbl_803A6C24.m1C.mA << 8;
        fn_80279D0C(record->m58, &params);
    } else if (record->m58 != 0) {
        fn_80279DF8(&record->m40, record->m58);
        fn_8026B7D8(record->m58);
        record->m58 = 0;
    }
}

void fn_80276A84(int index, int value)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];
    Node_80279D90 *node;
    int flag = 0;

    if (value > 0x40000) {
        value = 0x40000;
    }
    node = record->m50;
    if (node == 0) {
        record->m50 = (Node_80279D90 *)fn_8026B5D4(60);
        if (lbl_803B4E34.mE > 49) {
            flag = 1;
        }
        record->m50->m4 = 0;
        record->m50->m18 = 160;
        record->m50->m1A = 0;
        fn_8027A7A0(record->m50, lbl_803A6C24.m16F, flag);
        fn_80279D90(&record->m40, record->m50);
    }
    fn_8027A4C0(record->m50, value);
}

void fn_80276B40(int index, int value)
{
    Record_803B5010 *record = &lbl_803B4E34.m1DC[index];

    if (record->m4C != 0) {
        fn_80277240(record->m4C);
    }
}
