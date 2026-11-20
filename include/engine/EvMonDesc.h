#ifndef ENGINE_EVMONDESC_H
#define ENGINE_EVMONDESC_H
typedef struct EvMonDesc_t {
    int mNumRecords;
    int mRecordSize;
    int mNumListeners;
} EvMonDesc_t;
#ifdef __cplusplus
extern "C" {
#endif
int EvMonCreate(const EvMonDesc_t *pDesc);
int EvMonAlloc(const EvMonDesc_t *pDesc);
#ifdef __cplusplus
}
#endif
#endif
