#ifndef GAME_OBJECT_80228224_H
#define GAME_OBJECT_80228224_H

typedef struct Object_80228224 Object_80228224;
typedef struct Desc_80228224 Desc_80228224;

/* Callback stored at +60 and called with the object and the word at +64. */
typedef void (*Callback_80228224)(Object_80228224 *pObject, int arg);

/* Object returned by fn_80228224: a 248-byte element of the pool created by fn_802280B0. */
struct Object_80228224 {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    float mUnknown20;
    float mUnknown24;
    unsigned int mUnknown28;
    float mUnknown32;
    float mUnknown36;
    float mUnknown40;
    char mUnknown44[2];
    unsigned char mUnknown46;
    unsigned char mUnknown47;
    int mUnknown48[3];
    Callback_80228224 mUnknown60;
    int mUnknown64;
    unsigned char mUnknown68;
    unsigned char mUnknown69;
    int mUnknown72;
    float mUnknown76[4][4];
    char mUnknown140[64];
    float mUnknown204;
    float mUnknown208;
    char mUnknown212[4];
    float mUnknown216;
    float mUnknown220;
    float mUnknown224;
    float mUnknown228;
    float mUnknown232;
    float mUnknown236;
    float mUnknown240;
    char mUnknown244[4];
};

/* Argument of fn_80228224. */
struct Desc_80228224 {
    unsigned short mUnknown0;
    char mUnknown2;
    unsigned char mUnknown3;
    int mUnknown4[3];
    unsigned short mUnknown16;
    unsigned short mUnknown18;
};

#endif
