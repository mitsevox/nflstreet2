#ifndef GAME_PURSUESTATE_H
#define GAME_PURSUESTATE_H

/* Pursuit state block at player +336 (partial overlay; other bytes opaque). */
struct PursueState_t {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    signed char mUnknown12;
    signed char mUnknown13;
    signed char mUnknown14;
    signed char mUnknown15;
    unsigned char mUnknown16;
    char mUnknown17[3];
    char mUnknown20[20];
    unsigned char mUnknown40;
    unsigned char mUnknown41;
    unsigned char mUnknown42;
};

#endif
