#ifndef GAME_TDBQRYDELETEROW_H
#define GAME_TDBQRYDELETEROW_H

#include "game/DbQueryTable.h"
#include "game/TDbCompilePerformOp.h"

/* Runs a query over a -1 terminated table list. pResult may be null, in which
   case a local result is used. */
extern "C" {
int TDbQryDeleteRow(int handle, DbQueryTable *pTables, DbFilter *pFilter, QueryResult *pResult,
                int flags);
}

#endif
