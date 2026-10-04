#ifndef GAME_ITEM_800476DC_H
#define GAME_ITEM_800476DC_H

/* 36-byte instance of object type 11 (registered by fn_80047578); the
   player object keeps one at +988 (include/game/Object_8003DEC4.h). */
struct Item_800476DC {
    char mUnknown0[4];
    float mUnknown4[3];
    char mUnknown16[4];
    int mUnknown20;
    const char *mpUnknown24;
    unsigned char mUnknown28;
    float mUnknown32;
};

/* src/game/cu_8004732C.cpp */
extern "C" void fn_800476DC(Item_800476DC *pInstance, void *p);

#endif
