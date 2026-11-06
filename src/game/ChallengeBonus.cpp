/* Holds the bonus result of the current challenge. */

static int _ChallengeBonus_iResult;

extern "C" void ChallengeBonusSet(int value)
{
    _ChallengeBonus_iResult = value;
}

extern "C" int ChallengeBonusGet(void)
{
    return _ChallengeBonus_iResult;
}
