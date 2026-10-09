#ifndef GAME_CU_8017F90C_H
#define GAME_CU_8017F90C_H

#include "game/cu_80181330.h"

/* Message handlers called in turn by fn_8017F90C. Each takes the message id,
   an argument record, an unused word and a result pointer; the handlers
   defined in source give the argument and result records their own types. */
struct Args_8005542C;
struct Block_8017FAE8;
union Arg_801801F8;
struct Params_80185284;

extern "C" {
int fn_80055058(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_800550E4(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005528C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005542C(unsigned int id, Args_8005542C *pArgs, int a, int *pResult);
int fn_8017FAE8(int id, Block_8017FAE8 *pBlock, int unused, int *pResult);
int fn_8017FB90(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_801801F8(unsigned int id, Arg_801801F8 *pArgs, int unused, Arg_801801F8 *pResult);
int fn_801811C8(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_80181238(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8018399C(unsigned int id, Arg_8018399C *pArgs, int unused, Arg_8018399C *pResult);
int fn_8018422C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_80185284(unsigned int id, Params_80185284 *pParams, int c, int *pResult);

int fn_8017F90C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
}

#endif
