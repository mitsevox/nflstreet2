/* Routes UIStudio messages to the Story Mode and Gauntlet screens and holds
   strings and character mappings for legacy memory-card filenames. */

#include "game/EditMenu.h"

struct StoryTournamentArgs_t;
struct StoryPlayerMsgArgs_t;
struct GauntletMsgArgs_t;

extern "C" {
int StoryEventsHandleMessage(unsigned int id, int *pArgs, int count, int *pResult);
int StoryTournamentScreenMessage(unsigned int id, StoryTournamentArgs_t *pArgs, int count, int *pResult);
int StoryPlayerScreenMsg(unsigned int id, StoryPlayerMsgArgs_t *pArgs, int count, int *pResult);
int GauntletScreenMsg(unsigned int id, GauntletMsgArgs_t *pArgs, int count, int *pResult);

int MsgStoryModeDispatch(int screen, unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (screen) {
    case 1:
        return StoryEventsHandleMessage(id, reinterpret_cast<int *>(pArgs), count, pResult);
    case 3:
        return StoryTournamentScreenMessage(id, reinterpret_cast<StoryTournamentArgs_t *>(pArgs), count, pResult);
    case 4:
        return StoryPlayerScreenMsg(id, reinterpret_cast<StoryPlayerMsgArgs_t *>(pArgs), count, pResult);
    }
    return 0;
}

int MsgGauntletDispatch(int screen, unsigned int id, MenuArg_t *pArgs, int count, int *pResult)
{
    switch (screen) {
    case 0:
        return GauntletScreenMsg(id, reinterpret_cast<GauntletMsgArgs_t *>(pArgs), count, pResult);
    }
    return 0;
}
}

const char *_MemCard_aszLegacySaveTypeNames[14] = {
    "All Types", "DraftCls", "Tourn(R)", "Franchise", "Game", "Roster", "Settings",
    "Replay", "Tourn(E)", "Profile", "Exp Team", "Cr. Team", "Off Plbk", "Def Plbk",
};

const char *_MemCard_aszLegacySaveTypePrefixes[14] = {
    "", "", "RTour", "Fran", "Game", "Rost", "Sett",
    "Play", "ETour", "Pro", "ETeam", "CTeam", "OBook", "DBook",
};

unsigned char _MemCard_abyFullWidthPunctuation[33] = {
    0x40, 0x49, 0x68, 0x94, 0x90, 0x93, 0x95, 0x66, 0x69, 0x6A, 0x96, 0x7B, 0x43, 0x7C, 0x44, 0x5E,
    0x46, 0x47, 0x71, 0x81, 0x72, 0x48, 0x97, 0x6D, 0x8F, 0x6E, 0x4F, 0x51, 0x65, 0x6F, 0x62, 0x70,
    0x50,
};

// FAKEMATCH: Group the unused file strings in a read-only record to retain
// their four-byte alignment outside the small-data section.
struct LegacySaveFileStrings_t {
    char mTitleIds[2][8];
    char mSeparator[4];
    unsigned int unk_0x14;
    char mSlotFormat[8];
    char mDisplayNameFormat[8];
    char mWildcard[4];
};

extern const LegacySaveFileStrings_t _MemCard_LegacySaveFileStrings = {
    {"GNGE-69", "GM3E-69"},
    "/",
    0,
    "%d_%d",
    "%s %d",
    "*",
};
