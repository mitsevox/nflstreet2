#ifndef GAME_FN_801F9908_H
#define GAME_FN_801F9908_H

#include "game/Table_8007E020.h"
#include "game/fn_801FCE10.h"

/* Runs a query over a -1 terminated table list. pResult may be null, in which
   case a local result is used. */
extern "C" {
int fn_801F9908(int handle, Table_8007E020 *pTables, Object_80023BBC *pFilter, QueryResult *pResult,
                int flags);
}

#endif
