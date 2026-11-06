#ifndef ENGINE_T3DB_INDEX_H
#define ENGINE_T3DB_INDEX_H

struct TDbTable_t;
struct TDbIdxColumnDef_t;
struct TDbExpr_t;

#ifdef __cplusplus
extern "C" {
#endif

int _TDbIndexCreate(struct TDbTable_t *pTable, int id, struct TDbIdxColumnDef_t *pDefs,
                        struct TDbExpr_t *pFilter, int unique);

#ifdef __cplusplus
}
#endif

#endif
