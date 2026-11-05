#ifndef GAME_MEMHEAPDESC_T_H
#define GAME_MEMHEAPDESC_T_H

typedef struct MemHeapDesc_t {
    char mName[8];
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
} MemHeapDesc_t;

#ifdef __cplusplus
extern "C" {
#endif
MemHeapDesc_t *fn_80025E50(unsigned int id);
#ifdef __cplusplus
}
#endif

#endif
