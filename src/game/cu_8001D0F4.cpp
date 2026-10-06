#include "game/cu_80181330.h"

extern "C" {
int fn_8005F938(unsigned int id, void *pArgs, int unused, int *pResult);
int fn_800619FC(unsigned int id, void *pArgs, int unused, int *pResult);
int fn_800624B8(unsigned int id, void *pArgs, int unused, int *pResult);
int fn_80062714(unsigned int id, void *pArgs, int unused, int *pResult);

int fn_8001D0F4(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 1:
        return fn_8005F938(id, pArgs, unused, pResult);
    case 3:
        return fn_800619FC(id, pArgs, unused, pResult);
    case 4:
        return fn_800624B8(id, pArgs, unused, pResult);
    }
    return 0;
}

int fn_8001D180(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 0:
        return fn_80062714(id, pArgs, unused, pResult);
    }
    return 0;
}
}

const char *lbl_802F4504[14] = {
    "All Types", "DraftCls", "Tourn(R)", "Franchise", "Game", "Roster", "Settings",
    "Replay", "Tourn(E)", "Profile", "Exp Team", "Cr. Team", "Off Plbk", "Def Plbk",
};

const char *lbl_802F453C[14] = {
    "", "", "RTour", "Fran", "Game", "Rost", "Sett",
    "Play", "ETour", "Pro", "ETeam", "CTeam", "OBook", "DBook",
};

unsigned char lbl_802F4574[33] = {
    0x40, 0x49, 0x68, 0x94, 0x90, 0x93, 0x95, 0x66, 0x69, 0x6A, 0x96, 0x7B, 0x43, 0x7C, 0x44, 0x5E,
    0x46, 0x47, 0x71, 0x81, 0x72, 0x48, 0x97, 0x6D, 0x8F, 0x6E, 0x4F, 0x51, 0x65, 0x6F, 0x62, 0x70,
    0x50,
};
