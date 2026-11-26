#ifndef ENGINE_SNDAEMS_STATE_H
#define ENGINE_SNDAEMS_STATE_H

/* A client of a sound timer list: the module instances on sndaems.mpTimerClients, and the module
   player's own client sndaems.mTimerClient on Snd::gVariableTimerList. */
struct SndAemsTimerClient_t {
    SndAemsTimerClient_t *mpNext;
    SndAemsTimerClient_t *mpPrev;
    void (*mpCallback)(void *context);
    void *mpContext;
};

/* The list link of a resolved module bank (at +0x50 of the bank). */
struct SndAemsModuleBankLink_t {
    SndAemsModuleBankLink_t *mpNext;
    SndAemsModuleBankLink_t *mpPrev;
};

struct SndAemsState_t {
    SndAemsTimerClient_t *mpTimerClients;
    SndAemsModuleBankLink_t *mpModuleBanks;
    unsigned char unk_0x8;
    unsigned char mMissedTicks;
    unsigned char unk_0xA[2];
    int mLocked;
    unsigned char unk_0x10[4];
    SndAemsTimerClient_t mTimerClient;
    unsigned char unk_0x24[4];
    int unk_0x28;
    int unk_0x2C;
    void (*mpBeforeAddBank)(void);
    void (*mpBeforeRemoveBank)(void);

    SndAemsState_t() : mpTimerClients(0), mpModuleBanks(0), unk_0x28(0), unk_0x2C(0) {}
};

extern "C" SndAemsState_t sndaems;

#endif
