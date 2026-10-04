#ifndef GAME_OBJECT_8017886C_H
#define GAME_OBJECT_8017886C_H

/* The object whose address fn_8017886C returns; only the accessed prefix is
   declared. */
struct Object_8017886C {
    char mUnknown00[0x14];
    float mUnknown14;
    int mUnknown18;
    char mUnknown1C;
    signed char mUnknown1D;
};

extern "C" Object_8017886C *fn_8017886C(void);

#endif
