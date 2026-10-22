#ifndef GAME_CLASS_802A2B68_H
#define GAME_CLASS_802A2B68_H

#include "game/Class_80148A58.h"

struct Record_8014F104 {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
    unsigned int mUnknown12[9];
    unsigned int mUnknown48;
    char mUnknown52[4];
};

struct Block_8014F104 {
    char mUnknown0[0x34];
    Record_8014F104 *mpUnknown34;
};

class Class_802A2B68 : public Class_80148A58 {
public:
    Block_8014F104 *mpUnknown1C;
};

#endif
