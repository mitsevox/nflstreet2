#ifndef GAME_GAMEINFO_H
#define GAME_GAMEINFO_H

extern "C" {
void GameInfoRead(void);
void GameInfoShutdown(void);
unsigned char GameInfoIsInitialized(void);
int GameInfoGet(int index);
}

#endif
