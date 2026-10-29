#ifndef ENGINE_T3DB_INDEX_H
#define ENGINE_T3DB_INDEX_H

struct TDbExpr_801FAA00;

#ifdef __cplusplus
extern "C" {
#endif

int CreateDatabaseIndex(void *pTable, int id, void *pDefs, struct TDbExpr_801FAA00 *pFilter, int unique);

#ifdef __cplusplus
}
#endif

#endif
