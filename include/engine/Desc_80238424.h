#ifndef ENGINE_DESC_80238424_H
#define ENGINE_DESC_80238424_H
typedef struct Desc_80238424 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
} Desc_80238424;
#ifdef __cplusplus
extern "C" {
#endif
int EvMonCreate(const Desc_80238424 *pDesc);
int EvMonAlloc(const Desc_80238424 *pDesc);
#ifdef __cplusplus
}
#endif
#endif
