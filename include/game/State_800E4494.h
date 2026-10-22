#ifndef GAME_STATE_800E4494_H
#define GAME_STATE_800E4494_H

struct Object_80039F5C;

struct State_800E4494 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    union {
        char mUnknown4[28];
        struct {
            char mUnknown4Head[18];
            unsigned char mUnknown22[2];
            unsigned char mUnknown24;
            char mUnknown25[1];
            unsigned short mUnknown26;
            short mUnknown28;
            unsigned short mUnknown30;
        };
    };
    unsigned char mUnknown32;
    unsigned char mUnknown33;
    char mUnknown34[2];
    union {
        int mUnknown36;
        Object_80039F5C *mpUnknown36;
    };
    char mUnknown40[9];
    unsigned char mUnknown49;
    unsigned char mUnknown50;
    unsigned char mUnknown51;
    char mUnknown52[2];
    unsigned char mUnknown54;
    unsigned char mUnknown55;
    int mUnknown56;
    char mUnknown60[8];
    float mUnknown68;
    float mUnknown72;
    unsigned char mUnknown76;
    unsigned char mUnknown77;
    unsigned char mUnknown78;
    char mUnknown79[1];
};

#endif
