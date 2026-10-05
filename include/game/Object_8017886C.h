#ifndef GAME_OBJECT_8017886C_H
#define GAME_OBJECT_8017886C_H

/* Position on the field: mX across, mY along it. */
struct Point_8017886C {
    float mX;
    float mY;
};

/* The object whose address fn_8017886C returns; fn_8017C1F0 receives one
   for the play just finished. Only the accessed fields are declared. */
struct Object_8017886C {
    int mUnknown00;
    int mUnknown04;
    Point_8017886C mUnknown08;
    char mUnknown10[4];
    float mUnknown14;
    int mUnknown18;
    char mUnknown1C;
    signed char mUnknown1D;
};

extern "C" Object_8017886C *fn_8017886C(void);

#endif
