#ifndef ENGINE_LLLIGHT_H
#define ENGINE_LLLIGHT_H

/* Light scene records read by the hardware light code: the scene's light
   list, its numbered light-set references and its projectors. */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct LLLight_t {
    unsigned int mUnknown0;
    float mUnknown4[3];
    float mUnknown16[4];
    void (*mpUnknown32)(struct LLLight_t *pLight);
    float mUnknown36[3];
} LLLight_t;

/* 32-byte entry at +0x14 of LLLightScene_t. */
typedef struct LLLightProjector_t {
    unsigned int mUnknown0;
    float mUnknown4[4];
    int mUnknown20;
    float mUnknown24;
    float mUnknown28;
} LLLightProjector_t;

typedef struct LLLightScene_t {
    unsigned int mUnknown0;
    LLLight_t *mpUnknown4;
    unsigned int mUnknown8;
    char *mpUnknown12;
    unsigned int mUnknown16;
    LLLightProjector_t mUnknown20[4];
    float mUnknown148[4];
    float unk_0xA4[2];
} LLLightScene_t;

/* 20-byte record of a 100-byte light-set reference block. */
typedef struct LLLightSetRef_t {
    int mUnknown0;
    float mUnknown4[4];
} LLLightSetRef_t;

void LLLightSetScene(LLLightScene_t *pScene);

#ifdef __cplusplus
}
#endif

#endif
