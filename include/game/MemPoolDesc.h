#ifndef GAME_MEMPOOLDESC_H
#define GAME_MEMPOOLDESC_H

typedef struct MemPoolDesc {
    char mName[8];
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
} MemPoolDesc;

#ifdef __cplusplus
extern "C" {
#endif
MemPoolDesc *MemPoolGetDesc(unsigned int id);
#ifdef __cplusplus
}
#endif

#endif
