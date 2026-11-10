#ifndef GAME_PLAYBOOKGETPLAY_H
#define GAME_PLAYBOOKGETPLAY_H

#include "game/fn_800670B4.h"

extern "C" {
Record_80067338 *PlayBookGetPlay(int team);
void *fn_80164EC8(void *pRecord, int team, unsigned short index);
}

#endif
