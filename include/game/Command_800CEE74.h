#ifndef GAME_COMMAND_800CEE74_H
#define GAME_COMMAND_800CEE74_H

struct Object_80039F5C;

/* 64-byte stack record filled by fn_800CEE74 and read by fn_800C3BEC. */
struct Command_800CEE74 {
    char mUnknown0[64];
};

extern "C" {
void fn_800C39E0(Object_80039F5C *p, int a, int index, int value, int flag);
int fn_800C3BEC(Object_80039F5C *p, Command_800CEE74 *pCommand, int *pValue, int *pB);
void fn_800CEE74(Command_800CEE74 *pCommand, Object_80039F5C *p, Object_80039F5C *pOther, void *pData, int a, int b, int flag);
}

#endif
