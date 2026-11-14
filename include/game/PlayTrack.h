#ifndef GAME_PLAYTRACK_H
#define GAME_PLAYTRACK_H

/* One 20-byte history entry; PlayTrackPushPlay shifts the list down and
   starts a new entry at index 0. */
struct PlayTrackEntry_t {
    int mUnknown0;
    int mUnknown4;
    unsigned int mUnknown8;
    signed char mUnknownC;
    signed char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mUnknownF;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
};

/* Allocated through fn_80238174 under the id 'ptrk' (PlayTrackInit). */
struct PlayTrack_t {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    float mUnknown10;
    unsigned int mUnknown14;
    unsigned char mUnknown18;
    PlayTrackEntry_t mUnknown1C[2][24];
    unsigned short mUnknown3DC[2];
};

#endif
