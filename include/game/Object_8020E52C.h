#ifndef GAME_OBJECT_8020E52C_H
#define GAME_OBJECT_8020E52C_H

/* Result of fn_8020E52C; only the halfword at +8 is read by its callers. */
struct Object_8020E52C {
    int mUnknown0[2];
    unsigned short mUnknown8;
};

extern "C" {
void fn_8020E2B0(void *p);
Object_8020E52C *fn_8020E52C(void *p, int index);
void *fn_8020E5F8(void *p, int index);
}

#endif
