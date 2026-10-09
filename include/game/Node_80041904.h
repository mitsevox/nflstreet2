#ifndef GAME_NODE_80041904_H
#define GAME_NODE_80041904_H

/* Element of the list at +312 of Object_80041904 (include/game/cu_80041210.h),
   linked through mpNext and matched by its name. mId is -1 for none; its low
   halfword is the animation key passed to fn_801BE068 and the word is
   compared with fn_801BE648's result. */
struct Node_80041904 {
    char mName[64];
    int mId;
    unsigned char mUnknown68;
    char mUnknown69[3];
    float mUnknown72;
    float mUnknown76;
    char mUnknown80[12];
    unsigned short mUnknown92;
    char mUnknown94[2];
    int mUnknown96;
    int mUnknown100;
    int mUnknown104;
    int mUnknown108;
    float mUnknown112;
    int mUnknown116;
    int mUnknown120;
    unsigned char mUnknown124;
    char mUnknown125[3];
    void *mUnknown128;
    Node_80041904 *mpNext;
};

#endif
