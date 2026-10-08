#ifndef GAME_FN_801EBC18_H
#define GAME_FN_801EBC18_H

/* Three words fn_801EBC18 stores through its first argument (mr r31,r3 at
   0x801EBC68); the second argument points to four floats (lfs 0, 4, 8, 12
   of r4 at 0x801EBC54-0x801EBC6C). */
struct Angles_801EBC18 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" void fn_801EBC18(Angles_801EBC18 *pOut, float *pRot);

#endif
