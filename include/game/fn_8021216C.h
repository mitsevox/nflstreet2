#ifndef GAME_FN_8021216C_H
#define GAME_FN_8021216C_H

/* Descriptor read by fn_80212310 through fn_8021216C: the words +0, +4 and
   +0xC, the float +8 and the bytes +0x10 and +0x11. */
struct Desc_802EE9E4 {
    int mUnknown0;
    int mUnknown4;
    float mUnknown8;
    int mUnknownC;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
};

extern "C" void fn_8021216C(void *p, Desc_802EE9E4 *pDesc);

#endif
