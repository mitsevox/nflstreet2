#ifndef GAME_CALLEES_801D57E0_H
#define GAME_CALLEES_801D57E0_H

/* Functions in 0x801D57E0-0x801D6DE0 called from several game units. */
extern "C" {
int MemCFormatPort(int, char *, int);
void MemCardMgrEnablePolling(int);
void MemCardMgrSetIdleMode(int);
void MemCardMgrStartOperation(int);
void MemCardMgrUnmount(int);
void MemCardMgrSetPort(int);
int MemCardMgrGetPort();
void MemCardMgrSetFileStrings(const char *, const char *);
void MemCardMgrSetSlot(int);
void MemCardMgrSetGameCode(const char *, int);
void MemCardMgrGetFileTitle(char *, int);
int MemCardMgrGetSlotInfo(int, int, char *, int, char *, int, unsigned char *);
void MemCardMgrGetSlotEntryName(int, int, char *, int);
int MemCardMgrFindSlot(const char *, int, unsigned char *);
int MemCardMgrIsSlotCorrupt(int, int);
}

#endif
