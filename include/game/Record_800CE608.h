#ifndef GAME_RECORD_800CE608_H
#define GAME_RECORD_800CE608_H

/* 16-byte record fn_800CE590 fills and fn_800CE608 applies. */
struct Record_800CE608 {
    int mUnknown0;
    float mUnknown4;
    unsigned short mUnknown8;
    union { unsigned short mUnknown10; unsigned char mBytes10[2]; };
    union { unsigned short mUnknown12; unsigned char mBytes12[2]; };
    unsigned short mUnknown14;
};

#endif
