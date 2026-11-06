#ifndef GAME_MSGCHEATCODES_H
#define GAME_MSGCHEATCODES_H

#include "game/TextRecord.h"

union CheatCodesArg_t {
    int mUnknown0;
    int *mpUnknown0;
    const char *mpCode;
    char *mpText;
    struct TextRecord_t *mpRecord;
    union CheatCodesArg_t *mpWords;
};

#ifdef __cplusplus
extern "C" {
#endif

int MsgCheatCodesHandleMessage(unsigned int id, union CheatCodesArg_t *pArgs, int c, int *pResult);

#ifdef __cplusplus
}
#endif

#endif