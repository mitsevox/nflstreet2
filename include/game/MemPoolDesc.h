#ifndef GAME_MEMPOOLDESC_H
#define GAME_MEMPOOLDESC_H

typedef struct MemPoolDesc_t {
    char mName[8];
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
} MemPoolDesc_t;

#ifdef __cplusplus
extern "C" {
#endif
MemPoolDesc_t *MemPoolGetDesc(unsigned int id);
#ifdef __cplusplus
}
#endif

#endif
