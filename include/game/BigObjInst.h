#ifndef GAME_BIGOBJINST_H
#define GAME_BIGOBJINST_H

#include "game/Object_80039F5C.h"

struct BigObjPhysics_t {
    char mUnknown0[32];
    unsigned char mUnknown32;
    unsigned char mUnknown33;
    char mUnknown34[2];
    union { char mUnknown36[4]; int mWord36; };
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

struct BigObj_t;
struct BigObjInst;
struct BigObjNode_t;
/* Timed cycle at +200 that fn_8004B354 advances: an active flag, two
   durations, the current step, the elapsed time and the phase. */
struct BigObjCycle_t {
    unsigned char mActive;
    char mUnknown1[3];
    float mUnknown4;
    float mUnknown8;
    unsigned int mStep;
    float mTime;
    int mPhase;
};

/* Recent hit at +384 of BigObjInst (three entries): the time from
   0x800289A8 and the hit type, kept by fn_8004C844 to drop repeats. */
struct BigObjHit_t {
    unsigned int mTime;
    unsigned short mType;
    char mUnknown6[2];
};

typedef int (*BigObjBehaviorFunc)(BigObjInst *pObject, BigObj_t *pOwner, int mode);

struct BigObjInst {
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
    BigObj_t *mUnknown152[8];
    BigObjBehaviorFunc mUnknown184;
    int mUnknown188;
    void (*mUnknown192)(BigObj_t *pOwner);
    int mUnknown196;
    BigObjCycle_t mUnknown200;
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
    BigObjNode_t *mUnknown312;
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
    BigObjHit_t mUnknown384[3];
    float mUnknown408;
    float mUnknown412;
    char mUnknown416[4];
    void *mUnknown420;
    unsigned int mUnknown424;
    BigObjPhysics_t *mUnknown428;
};

struct BigObjPlacement_t {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    float mUnknown20;
    float mUnknown24;
};

extern "C" {
void BigObjInstInit(int maxObjects, int maxExtras);
void BigObjInstShutdown(void);
BigObjInst *BigObjInstCreate(void *pOwner, BigObjPlacement_t *pDesc);
int BigObjInstSyncAll(void);
int BigObjInstSimulateAll(float dt);
int BigObjInstTickAll(void);
BigObjInst *BigObjInstGet(int index);
unsigned int BigObjInstGetFrame(void);
}

#endif
