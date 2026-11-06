#ifndef GAME_CHEAT_H
#define GAME_CHEAT_H

#ifdef __cplusplus
extern "C" {
#endif

void CheatSelectSlot(int index);
void CheatClearSlot(void);
int CheatCountUnlocked(void);
int CheatAreAllUnlocked(void);
int CheatFindByCode(const char *pCode, int unused, char *pName);
int CheatGetUnlockedId(int index);
int CheatGetUnlockedInfo(int index, int *pId, char *pName, int count, int *pEnabled);
unsigned char CheatIsUnlocked(int id);
int CheatUnlock(int id);
int CheatIsEnabled(int id);
int CheatEnable(int id);
int CheatDisable(int id);

#ifdef __cplusplus
}
#endif

#endif
