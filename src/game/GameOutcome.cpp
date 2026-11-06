/* Holds the outcome of the current game: undecided while it is played, then won or lost. */

static int _GameOutcome_iOutcome;

extern "C" int GameOutcomeGet(void)
{
    return _GameOutcome_iOutcome;
}

extern "C" void GameOutcomeSet(int value)
{
    _GameOutcome_iOutcome = value;
}
