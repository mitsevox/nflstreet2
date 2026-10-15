#include <dolphin/ar.h>
#include <dolphin/ax.h>
#include <dolphin/os.h>
#include <string.h>

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

struct Params_803A6C40 {
    unsigned char mUnknown0[0xA];
    unsigned short mA;
    unsigned char mUnknownC[2];
    unsigned char mE;
    unsigned char mUnknownF[3];
    unsigned char m12;
    unsigned char mUnknown13[0xE];
    unsigned char m21;
    unsigned char m22;
    unsigned char m23;
    unsigned char mUnknown24;
    unsigned char m25;
    unsigned char mUnknown26[2];
    unsigned char m28;
    unsigned char mUnknown29;
    unsigned short m2A;
    unsigned short m2C;
    unsigned char mUnknown2E[0xA];
    unsigned int m38;
    unsigned int m3C;
    unsigned char mUnknown40[0x5C];
};

struct Record_803A6DF0 {
    unsigned char mUnknown0[4];
    short m4[15];
    unsigned char mUnknown22;
    unsigned char m23;
    unsigned char mUnknown24[4];
    short m28;
    unsigned char mUnknown2A[0x43];
    unsigned char m6D;
    unsigned char mUnknown6E[0x22];
};

struct Struct_803A6C24 {
    unsigned short m0;
    unsigned short m2;
    unsigned char m4;
    unsigned char m5;
    unsigned char m6;
    unsigned char mUnknown7[3];
    unsigned char mA;
    unsigned char mUnknownB;
    unsigned char mC;
    unsigned char mUnknownD;
    unsigned short mE;
    unsigned short m10;
    unsigned char mUnknown12[0xA];
    Params_803A6C40 m1C;
    unsigned char mUnknownB8[0x14];
    Params_803A6C40 mCC;
    unsigned char m168;
    unsigned char m169;
    unsigned char mUnknown16A[2];
    unsigned short m16C;
    unsigned char mUnknown16E[2];
    unsigned int m170;
    unsigned char mUnknown174[0x58];
    Record_803A6DF0 *m1CC;
};

struct Channel_803A8D60 {
    unsigned char mUnknown0[0x18];
    int m18;
    unsigned char mUnknown1C[3];
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

struct State_803A8D60 {
    Channel_803A8D60 m0[48];
    unsigned char mUnknownC00[0xEC8];
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

struct Setup_80272EC4 {
    int m0;
    void (*m4)(int);
    unsigned char m8;
    unsigned char m9;
    unsigned char mA;
};

extern "C" {
extern int lbl_80300044;
extern void *(*lbl_803B53E4)(int size);
extern void (*lbl_803B53E8)(void *p);
extern const unsigned short lbl_802B7A98[];
extern const short lbl_802B7AF0[2][3][16];
extern Struct_803A6C24 lbl_803A6C24;
extern Voice_803A7734 lbl_803A7734[64];
extern int lbl_803A8D34;
extern State_803A8D60 lbl_803A8D60;
extern void (*lbl_803B5028)(Setup_80272EC4 *setup);
extern void (*lbl_803B502C)(void);

void fn_8026A0E8(int value);
void *fn_8026B5D4(int size);
void fn_8026B7D8(void *p);
void fn_8026D0AC(void);
void fn_8026D0EC(void);
void fn_8027555C(void);
void fn_802798C0(void);

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
    int i = 0;
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
    int i = 0;
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
