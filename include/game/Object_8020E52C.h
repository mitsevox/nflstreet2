#ifndef GAME_OBJECT_8020E52C_H
#define GAME_OBJECT_8020E52C_H

/* Result of fn_8020E52C, a 12-byte entry of the table at +0x14 of the
   data; the halfwords +2, +4 and +8 are read by its callers. */
typedef struct Object_8020E52C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    char mUnknown6[2];
    unsigned short mUnknown8;
    char mUnknownA[2];
} Object_8020E52C;

/* Result of fn_8020E560, a 16-byte entry of the table at +0x18 of the data:
   +8 is the byte size of the block at +0xC. */
typedef struct Object_8020E560 {
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned short mFormat;
    unsigned short mType;
    unsigned int mUnknown8;
    unsigned char *mpUnknownC;
} Object_8020E560;

/* Result of fn_8020E5F8, a 12-byte entry of the table at +0x1C of the data:
   +4 is the byte size of the block at +8. */
typedef struct Object_8020E5F8 {
    unsigned short mFormat;
    unsigned short mUnknown2;
    unsigned int mUnknown4;
    unsigned char *mpUnknown8;
} Object_8020E5F8;

#ifdef __cplusplus
extern "C" {
#endif
void fn_8020E2B0(void *p);
Object_8020E52C *fn_8020E52C(void *p, unsigned short index);
Object_8020E560 *fn_8020E560(void *p, unsigned short index);
Object_8020E5F8 *fn_8020E5F8(void *p, unsigned short index);
#ifdef __cplusplus
}
#endif

#endif
