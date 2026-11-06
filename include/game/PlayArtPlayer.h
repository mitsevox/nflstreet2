#ifndef GAME_PLAYARTPLAYER_H
#define GAME_PLAYARTPLAYER_H

struct PlayArtStep_t {
    float mUnknown0, mUnknown4, mUnknown8, mUnknownC;
    int mUnknown10, mUnknown14, mUnknown18, mUnknown1C, mUnknown20;
};

struct PlayArtPlayer_t {
    union {
        unsigned char mUnknown0[8];
        struct { int mUnknown0Word, mUnknown4Word; };
    };
    float mUnknown8;
    float mUnknownC;
    unsigned int mUnknown10;
    union {
        unsigned char mUnknown14[0x1B8];
        struct {
            int mUnknown14Word, mUnknown18Word;
            PlayArtStep_t mUnknown1C[12];
        };
    };
};

struct PlayArtPlay_t {
    union {
        unsigned char mUnknown0[0x14];
        struct { unsigned char mUnknown0Pad[12]; unsigned char mUnknownC; unsigned char mUnknownD[7]; };
    };
    unsigned int mUnknown14;
    unsigned char mUnknown18[4];
    unsigned char mUnknown1C[3][4];
};

#endif
