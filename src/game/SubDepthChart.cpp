/* Sub module helpers: write a team's seven-player depth chart (position and player pairs) to the game database, read the chart back by position, and release the query. */
#include "game/fn_80177FE0.h"
#include "game/PlayBookDb.h"

extern "C" {
int fn_80177F70(void);
float fn_80178298(void);
PlayBookFormation_t *PlayBookGetFormation(int team);
int fn_8022D23C(void);
int fn_8022D25C(int value);
int fn_8022D2F4(unsigned short handle, unsigned short a, unsigned char b, unsigned char *pPairs, int c);
int fn_8022D3AC(void);
short fn_8022D3D4(unsigned char index);
int fn_8022D418(int a, int b, int mode);
int fn_8022D540(void);
int fn_8022E558(void);
int fn_8022E560(void);

void SubDepthWriteTeam(int team, PlayBookFormation_t *pTeam);

int SubDepthIsThirdAndLong(void)
{
    float y = fn_80178298();
    Point_8017886C point;
    signed char distance;

    point = fn_80177FE0();
    distance = (signed char)(y - point.mY + 0.001f);
    if (fn_80177F70() == 3 && distance > 3) {
        return 1;
    }
    return 0;
}

void SubDepthInit(void)
{
}

void SubDepthShutdown(void)
{
    fn_8022D23C();
    fn_8022D25C(0);
}

void SubDepthSetTeam(int team)
{
    SubDepthWriteTeam(team, PlayBookGetFormation(team));
}

void SubDepthWriteTeam(int team, PlayBookFormation_t *pTeam)
{
    unsigned char pairs[7][2];
    int flag;
    unsigned char i;
    int handle;

    flag = 0;
    if (SubDepthIsThirdAndLong()) {
        flag = 1;
    }
    for (i = 0; i <= 6; i++) {
        unsigned short value = pTeam->mUnknown8.mUnknown84[0][i].mUnknown0;
        if (flag && value == 1) {
            pairs[i][0] = 25;
        } else {
            pairs[i][0] = value;
        }
        pairs[i][1] = pTeam->mUnknown8.mUnknown84[0][i].mUnknown3 - 1;
    }
    if (team == 0) {
        handle = fn_8022E558();
    } else {
        handle = fn_8022E560();
    }
    fn_8022D418(handle, 0x3FF, 1);
    fn_8022D2F4(handle, pTeam->mUnknown8.mUnknown4, pTeam->mUnknown4, &pairs[0][0], 1);
}

void SubDepthRelease(void)
{
    fn_8022D540();
    fn_8022D3AC();
}

short SubDepthGetEntry(unsigned char index)
{
    return fn_8022D3D4(index);
}
}
