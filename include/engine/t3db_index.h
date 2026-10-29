#ifndef ENGINE_T3DB_INDEX_H
#define ENGINE_T3DB_INDEX_H

struct TDbTable_801FAA00;
struct TDbIdxColumnDef_801FFFC4;
struct TDbExpr_801FAA00;

#ifdef __cplusplus
extern "C" {
#endif

int CreateDatabaseIndex(struct TDbTable_801FAA00 *pTable, int id, struct TDbIdxColumnDef_801FFFC4 *pDefs,
                        struct TDbExpr_801FAA00 *pFilter, int unique);

#ifdef __cplusplus
}
#endif

#endif
