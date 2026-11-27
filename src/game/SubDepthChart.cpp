/* Sub module helpers: write a team's seven-player depth chart (position and player pairs) to the game database, read the chart back by position, and release the query. */
#include "game/ScrmGetBallSpot.h"
#include "game/PlayBookDb.h"

extern "C" {
int ScrmGetDown(void);
float ScrmGetLineToGain(void);
PlayBookFormation_t *PlayBookGetFormation(int team);
int DbUslpResetFilter1(void);
int DbUslpSetFilter2(int value);
int DbUslpFillSlots(unsigned short handle, unsigned short a, unsigned char b, unsigned char *pPairs, int c);
int DbUslpFinish(void);
short DbUslpGetSlotPlayer(unsigned char index);
int DbOpenDepthChartCursor(int a, int b, int mode);
int DbCloseDepthChartCursor(void);
int fn_8022E558(void);
int fn_8022E560(void);

void SubDepthWriteTeam(int team, PlayBookFormation_t *pTeam);

int SubDepthIsThirdAndLong(void)
{
    float y = ScrmGetLineToGain();
    FieldPoint_t point;
    signed char distance;

    point = ScrmGetBallSpot();
    distance = (signed char)(y - point.mY + 0.001f);
    if (ScrmGetDown() == 3 && distance > 3) {
        return 1;
    }
    return 0;
}

void SubDepthInit(void)
{
}

void SubDepthShutdown(void)
{
    DbUslpResetFilter1();
    DbUslpSetFilter2(0);
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
    DbOpenDepthChartCursor(handle, 0x3FF, 1);
    DbUslpFillSlots(handle, pTeam->mUnknown8.mUnknown4, pTeam->mUnknown4, &pairs[0][0], 1);
}

void SubDepthRelease(void)
{
    DbCloseDepthChartCursor();
    DbUslpFinish();
}

short SubDepthGetEntry(unsigned char index)
{
    return DbUslpGetSlotPlayer(index);
}
}
