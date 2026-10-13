#ifndef GAME_QUEUE_800EFE0C_H
#define GAME_QUEUE_800EFE0C_H

struct Handlers_800EFC68;

struct Queue_800EFE0C {
    unsigned short mUnknown0;
    unsigned short mCount;
    Handlers_800EFC68 *mpHandlers;
};

extern "C" void fn_800EFE0C(int kind, Queue_800EFE0C *pQueue);

#endif
