#ifndef GAME_OBJECT_8020E52C_H
#define GAME_OBJECT_8020E52C_H

/* Result of fn_8020E52C, a 12-byte entry of the table at +0x14 of the
   data; the halfwords +2, +4 and +8 are read by its callers. */
struct Object_8020E52C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    char mUnknown6[2];
    unsigned short mUnknown8;
    char mUnknownA[2];
};

/* Result of fn_8020E560, a 16-byte entry of the table at +0x18 of the data:
   +8 is the byte size of the block at +0xC. */
struct Object_8020E560 {
    int mUnknown0[2];
    unsigned int mUnknown8;
    unsigned char *mpUnknownC;
};

/* Result of fn_8020E5F8, a 12-byte entry of the table at +0x1C of the data:
   +4 is the byte size of the block at +8. */
struct Object_8020E5F8 {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned char *mpUnknown8;
};

extern "C" {
void fn_8020E2B0(void *p);
Object_8020E52C *fn_8020E52C(void *p, int index);
Object_8020E560 *fn_8020E560(void *p, unsigned short index);
Object_8020E5F8 *fn_8020E5F8(void *p, int index);
}

#endif
