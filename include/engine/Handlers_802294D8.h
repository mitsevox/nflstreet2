#ifndef ENGINE_HANDLERS_802294D8_H
#define ENGINE_HANDLERS_802294D8_H

typedef struct Handlers_802294D8 {
    int (*mpUnknown0)(void);
    void *mpUnknown4;
    void *mpUnknown8;
} Handlers_802294D8;

#ifdef __cplusplus
extern "C" {
#endif
void DbNiomSetHandlers(Handlers_802294D8 *p);
int DbNiomBeginMode(int *p);
#ifdef __cplusplus
}
#endif

#endif
