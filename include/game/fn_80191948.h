#ifndef GAME_FN_80191948_H
#define GAME_FN_80191948_H

/* Partial access view; the complete object size is unknown. */
struct Object_80191948 {
    char mUnknown0[8];
    char *mpUnknown8;
};

extern "C" {
void fn_80191948(int value, Object_80191948 *pA, Object_80191948 *pB, Object_80191948 *pC);
void fn_80184528(int value, Object_80191948 *pA, Object_80191948 *pB, Object_80191948 *pC);
}

#endif
