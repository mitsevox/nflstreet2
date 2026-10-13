#ifndef GAME_COMMAND_800CEE74_H
#define GAME_COMMAND_800CEE74_H

#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"

struct Table_80089904;

struct Anchor_800CE804 {
    int mAngle;
    Point_8017886C mPoint;
    unsigned char mUnknown12;
    char mUnknown13[3];
};

/* Command filled by fn_800CEE74 and passed to fn_800C3BEC. */
struct Command_800CEE74 {
    union {
        struct {
            char mUnknown0[62];
            unsigned char mUnknown62;
            char mUnknown63[1];
        };
        struct {
            Vector_80039F5C mVector0;
            Vector_80039F5C mUnknown12;
            float mUnknown24;
            union {
                struct {
                    int mUnknown28;
                    Point_8017886C mUnknown32;
                    unsigned char mUnknown40;
                    char mUnknown41[3];
                    int mUnknown44;
                    Point_8017886C mUnknown48;
                    unsigned char mUnknown56;
                    char mUnknown57[3];
                };
                struct { Anchor_800CE804 mAnchor28; Anchor_800CE804 mAnchor44; };
            };
            unsigned short mUnknown60;
            unsigned char mUnknown62Value;
            unsigned char mUnknown63Value;
        };
    };
};

/* Parameter lists follow register use at the call sites only. */
extern "C" {
void fn_800C39E0(Object_80039F5C *p, int a, int index, int value, int flag);
int fn_800C3BEC(Object_80039F5C *p, Command_800CEE74 *pCommand, int *pValue, int *pB);
void fn_800CE804(Command_800CEE74 *pCommand, Table_80089904 *pTable, int index);
void fn_800CEE74(Command_800CEE74 *pCommand, Object_80039F5C *p, Object_80039F5C *pOther, void *pData, int a, int b, int flag);
}

#endif
