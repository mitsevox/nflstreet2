#ifndef GAME_PLYRNAMETAG_H
#define GAME_PLYRNAMETAG_H

/* 36-byte instance of object type 11 (registered by PlyrNameTagAddObjType); the
   player object keeps one at +988 (include/game/Object_8003DEC4.h). */
struct PlyrNameTag_t {
    char mUnknown0[4];
    float mUnknown4[3];
    char mUnknown16[4];
    int mUnknown20;
    const char *mpUnknown24;
    unsigned char mUnknown28;
    float mUnknown32;
};

/* src/game/PlyrNameTag.cpp */
extern "C" void PlyrNameTagUpdatePosition(PlyrNameTag_t *pInstance, void *p);

#endif
