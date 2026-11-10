/* Starts and ends a pending in-game prompt handed to the opposing team's controller and holds its result. */
#include "game/InGame.h"
#include "game/fn_800B65A0.h"

struct PlayerSideRec_t {
    unsigned char mUnknown0[2];
    unsigned char mUnknown2;
};

extern "C" {
void PauseBlock(void);
void PauseUnblock(void);
PlayerSideRec_t *fn_800B2340(unsigned char index);
void UISGameLockPad(int value);
int UISGameUnlockPad(void);
}

static int _TeamPrompt_iResult = -1;
static unsigned char _TeamPrompt_bActive;
static int _TeamPrompt_iPlayer;
static int _TeamPrompt_iSecond;
static int _TeamPrompt_iFirst;

extern "C" {
void TeamPromptStart(int a, int b, int c)
{
    _TeamPrompt_iFirst = b;
    _TeamPrompt_iSecond = c;
    _TeamPrompt_bActive = 1;
    _TeamPrompt_iResult = -1;
    _TeamPrompt_iPlayer = a;
    PauseBlock();
    InGameSetInputPaused(1);
    UISGameLockPad(fn_800B65A0(fn_800B2340(a)->mUnknown2 ^ 1));
}

void TeamPromptSetResult(int value)
{
    _TeamPrompt_iResult = value;
    _TeamPrompt_iPlayer = 0xFFFF;
}

void TeamPromptEnd(void)
{
    UISGameUnlockPad();
    _TeamPrompt_bActive = 0;
    if (_TeamPrompt_iPlayer != 0xFFFF) {
        InGameSetInputPaused(0);
        PauseUnblock();
    }
}

unsigned char TeamPromptIsActive(void)
{
    return _TeamPrompt_bActive;
}

int TeamPromptGetResult(void)
{
    return _TeamPrompt_iResult;
}
}
