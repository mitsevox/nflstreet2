#ifndef GAME_LOCOBLENDSET_H
#define GAME_LOCOBLENDSET_H

struct LocoBlendSample_t
{
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
};

/* Object at payload +0xC that PlayerLocoSwitchBlendPair and PlayerLocoUpdateBlendWeights index. Only the
   12-byte entries from +24 are declared. */
struct LocoBlendSet_t
{
    char mUnknown0[24];
    LocoBlendSample_t mUnknown24[1];
};

#endif
