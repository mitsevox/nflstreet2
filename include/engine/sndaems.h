#ifndef ENGINE_SNDAEMS_H
#define ENGINE_SNDAEMS_H

/* Declarations shared by the sound files of 0x80266E88-0x8026A664: saems.c, salloc.c and
   sbadd.c (once one neutral file, src/engine/cu_80266A2C.c). */

typedef struct Voice_803A6C24 {
    int mUnknown0;
    short mUnknown4[12];
    unsigned short mUnknown1C;
    unsigned char mUnknown1E[5];
    unsigned char mUnknown23;
    unsigned char mUnknown24[2];
    unsigned char m26;
    unsigned char m27;
    short m28;
    unsigned char m2A;
    unsigned char mUnknown2B;
    int m2C;
    unsigned char mUnknown30[47];
    unsigned char mUnknown5F;
    unsigned char mUnknown60[13];
    unsigned char mUnknown6D;
    unsigned short mUnknown6E;
    unsigned char mUnknown70[30];
    unsigned short mUnknown8E;
} Voice_803A6C24;

typedef struct Object_803A6C24 {
    unsigned char mUnknown0[0x34];
    unsigned char m34;
    unsigned char mUnknown35[0x137];
    short mUnknown16C;
    signed char mUnknown16E;
    unsigned char mUnknown16F;
    int m170;
    unsigned char mUnknown174[48];
    void (*mUnknown1A4[10])(void *);
    Voice_803A6C24 *mUnknown1CC;
} Object_803A6C24;

#ifdef __cplusplus
extern "C" {
#endif

extern Object_803A6C24 lbl_803A6C24;

#ifdef __cplusplus
}
#endif

#endif
