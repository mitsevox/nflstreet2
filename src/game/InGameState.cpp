/* A pair of flags marking when the gameplay state is active. */
static unsigned char _InGameState_bActive = 0;
static unsigned char _InGameState_bDirty = 1;

extern "C" void InGameStateClearDirty(void) { _InGameState_bDirty = 0; }

extern "C" void InGameStateReset(void)
{
    _InGameState_bActive = 0;
    InGameStateClearDirty();
}

extern "C" void InGameStateClearActive(void) { _InGameState_bActive = 0; }

extern "C" unsigned char InGameStateSetActive(unsigned char value)
{
    unsigned char previous = _InGameState_bActive;

    _InGameState_bActive = value;
    InGameStateClearDirty();
    return previous;
}
