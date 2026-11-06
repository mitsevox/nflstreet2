/* Starts and stops in-game speech: in the tutorial it opens the narrator, in normal games it opens
   the play-by-play commentary (switched off in some modes), and remembers which so it can shut down
   cleanly. */

#include "game/fn_8017F584.h"
extern "C" {
void SpchIGStart(void);
void SpchIGStop(void);
void SpchIGSetCommentaryOn(unsigned char value);
int fn_801486A0(void);
unsigned int fn_801568F0(void);
}

static int _SpchIG_iMode = 0;

extern "C" void SpchIGInit(void)
{
    int state;

    SpchIGSetCommentaryOn(1);
    if (fn_8017F584() == 11 && fn_801568F0() <= 4) {
        SpchIGStart();
        state = 1;
    } else {
        if (fn_801486A0() == 0 || fn_801486A0() == 1 || fn_801486A0() == 2) {
            SpchIGStart();
            SpchIGSetCommentaryOn(0);
        } else {
            SpchIGStart();
        }
        state = 2;
    }
    _SpchIG_iMode = state;
}

extern "C" void SpchIGShutdown(void)
{
    switch (_SpchIG_iMode) {
    case 1:
    case 2:
        SpchIGStop();
        break;
    }
    _SpchIG_iMode = 0;
}
