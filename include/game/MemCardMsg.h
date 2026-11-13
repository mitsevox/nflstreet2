#ifndef GAME_MEMCARDMSG_H
#define GAME_MEMCARDMSG_H

/* Partial access view; the complete object size is unknown. */
struct MemCardMsgText_t {
    char mUnknown0[8];
    char *mpUnknown8;
};

extern "C" {
void MemCardMsgGetText(int value, MemCardMsgText_t *pA, MemCardMsgText_t *pB, MemCardMsgText_t *pC);
void MemCardUIGetMessageText(int value, MemCardMsgText_t *pA, MemCardMsgText_t *pB, MemCardMsgText_t *pC);
}

#endif
