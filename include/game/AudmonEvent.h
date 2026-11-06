#ifndef GAME_AUDMONEVENT_H
#define GAME_AUDMONEVENT_H

#include "game/Object_80039F5C.h"

/* Record returned by AudmonEventGetRecord and handed to the registered callbacks. */
struct AudmonEvent_t {
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

#include "engine/Callback_80238570.h"

extern "C" {
void AudmonEventInit(void);
void AudmonEventShutdown(void);
void AudmonEventStartInGame(void);
void AudmonEventClear(void);
void AudmonEventPost(int type, Vector_80039F5C *pPos);
void AudmonEventPostArgs(int type, Vector_80039F5C *pPos, int a, int b, int c);
void AudmonEventPostId(int type, Vector_80039F5C *pPos, int id, int a, int b, int c);
void AudmonEventAddListener(AudmonEventFn_t pCallback);
void AudmonEventRemoveListener(AudmonEventFn_t pCallback);
}

#endif
