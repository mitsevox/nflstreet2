#ifndef GAME_CU_80041210_H
#define GAME_CU_80041210_H

#include "game/Object_80039F5C.h"

struct Extra_8004149C {
    char mUnknown0[32];
    unsigned char mUnknown32;
    unsigned char mUnknown33;
    char mUnknown34[2];
    char mUnknown36[4];
    char mUnknown40[8];
    char mUnknown48[2];
    unsigned short mUnknown50;
    unsigned short mUnknown52;
    char mUnknown54[2];
    int mUnknown56;
    char mUnknown60[1240];
    char mUnknown1300[404];
    unsigned char mUnknown1704;
    unsigned char mUnknown1705;
    unsigned char mUnknown1706;
    unsigned char mUnknown1707;
    int mUnknown1708;
};

struct Object_80040818;
struct Object_80041904;
struct Node_80041904;
/* Timed cycle at +200 that fn_8004B354 advances: an active flag, two
   durations, the current step, the elapsed time and the phase. */
struct Cycle_80041904 {
    unsigned char mActive;
    char mUnknown1[3];
    float mUnknown4;
    float mUnknown8;
    unsigned int mStep;
    float mTime;
    int mPhase;
};

/* Recent hit at +384 of Object_80041904 (three entries): the time from
   0x800289A8 and the hit type, kept by fn_8004C844 to drop repeats. */
struct Hit_8004C844 {
    unsigned int mTime;
    unsigned short mType;
    char mUnknown6[2];
};

typedef void (*Callback_80041904)(Object_80041904 *pObject, int entry, int mode);

struct Object_80041904 {
    int mUnknown0;
    int mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    char mUnknown20[12];
    int mUnknown32;
    char mUnknown36[12];
    float mUnknown48;
    float mUnknown52;
    float mUnknown56;
    char mUnknown60[36];
    float mUnknown96;
    float mUnknown100;
    float mUnknown104;
    float mUnknown108;
    float mUnknown112;
    float mUnknown116;
    float mUnknown120;
    float mUnknown124;
    float mUnknown128;
    float mUnknown132;
    float mUnknown136;
    int mUnknown140;
    int mUnknown144;
    unsigned short mUnknown148;
    char mUnknown150[2];
    Object_80040818 *mUnknown152[8];
    Callback_80041904 mUnknown184;
    int mUnknown188;
    void (*mUnknown192)(Object_80040818 *pOwner);
    int mUnknown196;
    Cycle_80041904 mUnknown200;
    unsigned char mUnknown224;
    char mUnknown225[3];
    float mUnknown228[10];
    float mUnknown268;
    unsigned int mUnknown272;
    unsigned int mUnknown276;
    int mUnknown280;
    int mUnknown284;
    int mUnknown288;
    int mUnknown292;
    float mUnknown296;
    int mUnknown300;
    int mUnknown304;
    unsigned short mUnknown308;
    unsigned short mUnknown310;
    Node_80041904 *mUnknown312;
    char mUnknown316[32];
    float mUnknown348;
    float mUnknown352;
    float mUnknown356;
    Vector_80039F5C mUnknown360;
    float mUnknown372;
    int mUnknown376;
    unsigned char mUnknown380;
    unsigned char mUnknown381;
    unsigned char mUnknown382;
    char mUnknown383;
    Hit_8004C844 mUnknown384[3];
    float mUnknown408;
    float mUnknown412;
    char mUnknown416[4];
    void *mUnknown420;
    unsigned int mUnknown424;
    Extra_8004149C *mUnknown428;
};

struct Desc_8004149C {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    float mUnknown20;
    float mUnknown24;
};

extern "C" {
void fn_800413F0(int maxObjects, int maxExtras);
void fn_80041490(void);
Object_80041904 *fn_8004149C(void *pOwner, Desc_8004149C *pDesc);
int fn_80041664(void);
int fn_800416CC(float dt);
int fn_8004183C(void);
Object_80041904 *fn_80041904(int index);
unsigned int fn_80041928(void);
}

#endif
