#ifndef GAME_RECORD_8036B55C_H
#define GAME_RECORD_8036B55C_H

#include "game/Object_8003DEC4.h"

/* Argument of fn_800B267C, fn_800B26E0 and fn_800B2A14. */
struct Object_800B267C {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    float mUnknown20;
    int mUnknown24;
    float mUnknown28;
    char mUnknown32[4];
    float mUnknown36;
};

/* First argument of fn_801BA03C, fn_801BC7C0, fn_801BCA74 and fn_801BCCAC. */
struct Object_801BA03C {
    char mUnknown0[4];
    unsigned short mUnknown4;
    char mUnknown6[6];
};

/* Element of lbl_8036B55C. */
struct Record_8036B55C {
    char mUnknown0[1];
    unsigned char mUnknown1;
    char mUnknown2[2];
    Object_8003DEC4 *mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    char mUnknown10[2];
    int mUnknown12;
    char mUnknown16[408];
    Object_800B267C mUnknown424;
    char mUnknown464[44];
    float mUnknown508;
    char mUnknown512[16];
    char mUnknown528[16];
    unsigned char mUnknown544;
    unsigned char mUnknown545;
    char mUnknown546[2];
    char mUnknown548[4];
    char mUnknown552[224];
    unsigned char mUnknown776;
    char mUnknown777[3];
    int mUnknown780;
    void *mUnknown784;
    char mUnknown788[4];
    void *mUnknown792;
    void *mUnknown796;
    void *mUnknown800;
    void *mUnknown804;
    void *mUnknown808;
    void *mUnknown812;
    char mUnknown816[192];
    int mUnknown1008;
    char mUnknown1012[232];
    Object_801BA03C mUnknown1244;
    char mUnknown1256[1240];
    char mUnknown2496[552];
    char mUnknown3048[48];
    Object_801BA03C mUnknown3096;
    char mUnknown3108[496];
    char mUnknown3604[404];
    Object_801BA03C mUnknown4008[2];
    char mUnknown4032[2][248];
    char mUnknown4528[2][404];
};

#endif
