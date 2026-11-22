#ifndef ENGINE_DBNIOMHANDLERS_H
#define ENGINE_DBNIOMHANDLERS_H

typedef struct DbNiomHandlers_t {
    int (*mpUnknown0)(void);
    void *mpUnknown4;
    void *mpUnknown8;
} DbNiomHandlers_t;

#ifdef __cplusplus
extern "C" {
#endif
void DbNiomSetHandlers(DbNiomHandlers_t *p);
int DbNiomBeginMode(int *p);
#ifdef __cplusplus
}
#endif

#endif
