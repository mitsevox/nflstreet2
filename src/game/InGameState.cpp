/* Whether the gameplay state is active, plus a flag that stays set until that state is first
   written. */
static unsigned char _InGameState_bActive = 0;
static unsigned char _InGameState_bUnwritten = 1;

extern "C" void InGameStateClearUnwritten(void) { _InGameState_bUnwritten = 0; }

extern "C" void InGameStateReset(void)
{
    _InGameState_bActive = 0;
    InGameStateClearUnwritten();
}

extern "C" void InGameStateClearActive(void) { _InGameState_bActive = 0; }

extern "C" unsigned char InGameStateSetActive(unsigned char value)
{
    unsigned char previous = _InGameState_bActive;

    _InGameState_bActive = value;
    InGameStateClearUnwritten();
    return previous;
}
