#ifndef GAME_ANIMROOTITEM_H
#define GAME_ANIMROOTITEM_H

/* 0x7C-byte item of the array passed to AnimBlendRootAngles. */
struct AnimRootItem {
    char mUnknown0[1];
    unsigned char mUnknown1;
    char mUnknown2[6];
    unsigned short mUnknown8;
    char mUnknownA[6];
    int mUnknown10[3];
    char mUnknown1C[20];
    float mUnknown30;
    char mUnknown34[20];
    float mUnknown48;
    char mUnknown4C[48];
};

#endif
