#ifndef GAME_MESSAGE_800F01CC_H
#define GAME_MESSAGE_800F01CC_H

/* 4-byte message cleared by memset and posted to a player's queue
   through PlyrStateQueueInsertNext, PlyrStateQueueAppend or PlyrStateQueueSet. */
struct Message_800F01CC {
    unsigned char mId;
    unsigned char mUnknown1[3];
};

struct Object_80039F5C;
struct State_80039F5C;

extern "C" {
void PlyrStateQueueInsertNext(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void PlyrStateQueueAppend(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void PlyrStateQueueSet(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
}

#endif
