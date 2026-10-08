#ifndef GAME_OBJECT_801BC084_H
#define GAME_OBJECT_801BC084_H

/* Record returned by fn_801BC084 for a valid handle (the word at entry +12
   of the 32-byte handle table); fn_801BAD70 forwards it to fn_801BACD0. */
struct Object_801BC084 {
    char mUnknown0[3];
    unsigned char mUnknown3;
};

extern "C" {
Object_801BC084 *fn_801BC084(int handle);
}

#endif
