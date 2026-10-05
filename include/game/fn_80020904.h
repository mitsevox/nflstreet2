#ifndef GAME_FN_80020904_H
#define GAME_FN_80020904_H

#include "game/Record_80021154.h"

union Word_80020904 {
    int mUnknown0;
    int *mpUnknown0;
    const char *mpCode;
    char *mpText;
    struct Record_80021154 *mpRecord;
    union Word_80020904 *mpWords;
};

#ifdef __cplusplus
extern "C" {
#endif

int fn_80020904(unsigned int id, union Word_80020904 *pArgs, int c, int *pResult);

#ifdef __cplusplus
}
#endif

#endif