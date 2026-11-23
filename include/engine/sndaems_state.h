#ifndef ENGINE_SNDAEMS_STATE_H
#define ENGINE_SNDAEMS_STATE_H

struct SndAemsTimerClient_t;
struct SndAemsModuleBankLink_t;

struct SndAemsState_t {
    SndAemsTimerClient_t *mpTimerClients;
    SndAemsModuleBankLink_t *mpModuleBanks;
    unsigned char unk_0x8;
    unsigned char mMissedTicks;
    unsigned char unk_0xA[2];
    int mLocked;
    unsigned char unk_0x10[0x18];
    int unk_0x28;
    int unk_0x2C;
    void (*mpBeforeAddBank)(void);
    void (*mpBeforeRemoveBank)(void);

    SndAemsState_t() : mpTimerClients(0), mpModuleBanks(0), unk_0x28(0), unk_0x2C(0) {}
};

extern "C" SndAemsState_t sndaems;

#endif
