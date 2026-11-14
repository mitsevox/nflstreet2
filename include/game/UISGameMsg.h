#ifndef GAME_UISGAMEMSG_H
#define GAME_UISGAMEMSG_H

#include "game/EditMenu.h"

/* Message handlers called in turn by UISGameMsgDispatch. Each takes the message id,
   an argument record, an unused word and a result pointer; the handlers
   defined in source give the argument and result records their own types. */
struct FeatsScreenArgs_t;
struct ColorPickMsg_t;
union MsgGameArg_t;
struct MemCardUIArgs_t;

extern "C" {
int FeTeamHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult);
int DepthChartScreenHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult);
int FeCountsHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult);
int FeatsScreenHandleMessage(unsigned int id, FeatsScreenArgs_t *pArgs, int a, int *pResult);
int ColorPickHandleMsg(int id, ColorPickMsg_t *pBlock, int unused, int *pResult);
int UISGameQueryHandleMsg(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult);
int MsgGameHandleMessage(unsigned int id, MsgGameArg_t *pArgs, int unused, MsgGameArg_t *pResult);
int FEMiscHandleStatsFunction(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult);
int FEMiscHandleFunction(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult);
int EditMenuHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, MenuArg_t *pResult);
int MemCardUIEmptyHandler(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult);
int MemCardUIHandleFunction(unsigned int id, MemCardUIArgs_t *pParams, int c, int *pResult);

int UISGameMsgDispatch(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult);
}

#endif
