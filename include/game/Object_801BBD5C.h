#ifndef GAME_OBJECT_801BBD5C_H
#define GAME_OBJECT_801BBD5C_H

struct Value_801BBD5C {
    float mValue;
    unsigned char mUnknown4[8];
};

/* Object whose address fn_801BBD5C returns. Only the accessed fields are
   declared; mValues holds mCount entries. */
struct Object_801BBD5C {
    unsigned char mUnknown0[4];
    unsigned int mCount;
    unsigned char mUnknown8[4];
    float mUnknown12;
    float mUnknown16;
    int mUnknown20;
    unsigned char mUnknown24[4];
    Value_801BBD5C mValues[1];
};

#endif
