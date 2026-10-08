#ifndef GAME_CU_8008E978_H
#define GAME_CU_8008E978_H

/* Views of the records returned by fn_80093BAC, fn_80093BCC and
   fn_80096DA8. Their original identities and the contents of the opaque
   spans remain unknown. */
struct Frame_80141210 { unsigned char mUnknown0[0x30]; float mUnknown30, mUnknown34; unsigned char mUnknown38[4]; float mUnknown3C; };
struct Actor_801C009C { int mUnknown0,mUnknown4; unsigned int mUnknown8; unsigned char mUnknownC[12]; Frame_80141210 *mUnknown18; };
struct Selection_80141210 { unsigned char mUnknown0; unsigned char mUnknown1[3]; union { int mWord; unsigned short mParts[2]; } mUnknown4,mUnknown8; };
struct MotionSource_80141210 { unsigned char mUnknown0[0x1C0]; int mUnknown1C0; };

/* One of the four 912-byte records at +128 of the block fn_800925F0
   allocates. */
struct Character_80093BCC {
    int mUnknown0,mUnknown4;
    unsigned char mUnknown8[12];
    MotionSource_80141210 *mUnknown14;
    unsigned char mUnknown18[0xC0];
    union { int mWord; unsigned short mParts[2]; } mUnknownD8;
    unsigned char mUnknownDC[4];
    Selection_80141210 mUnknownE0;
    unsigned char mUnknownEC[0x2A0];
    int mUnknown38C;
};

/* One of the two 48-byte records at +16 of the block fn_80096954
   allocates. */
struct Playback_80096DA8 {
    int mUnknown0,mUnknown4; unsigned char mUnknown8[4]; unsigned int mUnknownC;
    int mUnknown10; union { int mWord; unsigned short mParts[2]; } mUnknown14,mUnknown18,mUnknown1C;
    float mUnknown20,mUnknown24;
    unsigned char mUnknown28[8];
};

extern "C" {
Actor_801C009C *fn_80093BAC(int,int);
Character_80093BCC *fn_80093BCC(unsigned short);
Playback_80096DA8 *fn_80096DA8(unsigned int);
Actor_801C009C *fn_80096DCC(unsigned int,int);
}

#endif
