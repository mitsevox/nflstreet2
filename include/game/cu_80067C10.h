#ifndef GAME_CU_80067C10_H
#define GAME_CU_80067C10_H

#include "game/Object_80039F5C.h"

/* Record returned by fn_80067CA8 and handed to the registered callbacks. */
struct Record_80067CA8 {
    int mUnknown0;
    Vector_80039F5C mPos;
    union {
        unsigned int mValue;
        void *mpObject;
    } mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    unsigned short mType;
};

typedef void (*Callback_80067EC8)(Record_80067CA8 *pRecord);

extern "C" {
void fn_80067C10(void);
void fn_80067C44(void);
void fn_80067C70(void);
void fn_80067CCC(void);
void fn_80067D4C(int type, Vector_80039F5C *pPos);
void fn_80067DB8(int type, Vector_80039F5C *pPos, int a, int b, int c);
void fn_80067E3C(int type, Vector_80039F5C *pPos, int id, int a, int b, int c);
void fn_80067EC8(Callback_80067EC8 pCallback);
void fn_80067EF0(Callback_80067EC8 pCallback);
}

#endif
