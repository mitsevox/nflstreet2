/* Per-side playbook records: the loaded playbook value of a side and the reset of
   all four records that the in-game loop performs. */

struct PlaybookSideInfo {
    int mUnknown0[37];
    unsigned char mUnknown94;
};

static PlaybookSideInfo _PlaybookSide_aInfo[4] = {0};

extern "C" unsigned char PlaybookSideGetLoaded(int index)
{
    return _PlaybookSide_aInfo[index].mUnknown94;
}

extern "C" void PlaybookSideClearAll(void)
{
    unsigned int i;

    for (i = 0; i < 4; i++) {
        _PlaybookSide_aInfo[i].mUnknown94 = 0;
    }
}
