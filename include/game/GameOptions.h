#ifndef GAME_GAMEOPTIONS_H
#define GAME_GAMEOPTIONS_H

extern "C" {
void GameOptionsSet(int id, int value);
int GameOptionsGet(int id);
void GameOptionsInit(int reset);
int GameOptionsShutdown(void);
void GameOptionsSetDeferWrites(int defer);
int GameOptionsResetMarked(void);
void GameOptionsCopyShadow(void);
}

#endif
