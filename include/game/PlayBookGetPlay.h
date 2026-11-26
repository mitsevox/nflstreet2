#ifndef GAME_PLAYBOOKGETPLAY_H
#define GAME_PLAYBOOKGETPLAY_H

#include "game/PlayBookDb.h"

extern "C" {
PlayBookPlay_t *PlayBookGetPlay(int team);
void *PlayAlignGetRoute(void *pRecord, int team, unsigned short index);
}

#endif
