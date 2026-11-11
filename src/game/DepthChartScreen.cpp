/* Front-end script handlers for the depth-chart and team screens: the depth-chart messages, side
   names and formation spots, the next-screen choice for a user's created team, and record counts. */
#include "game/cu_80181330.h"
#include "game/DepthChart.h"

extern "C" {
void MsgChallengeSetFlowState(int value);
int MsgChallengeGetFlowState(void);
int TeamFilterGet(void);
void ChalCloseCursors(void);
int fn_80082414(int index);
int FormationSlotGetInfo(int a, int b, float *pX, float *pY, int *pValue, char *pLabel, int labelSize);
void fn_80183920(int mode, int value);
int fn_8018D720(int a);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_8022F384(int a);
int fn_8022F4BC(void);

void FeTeamChooseScreen(int *pResult)
{
    if (fn_8018D720(fn_8022F384(fn_8022F4BC()))) {
        if (TeamFilterGet() != 0x3FF) {
            *pResult = 401;
        } else if (MsgChallengeGetFlowState() == 6) {
            MsgChallengeSetFlowState(4);
            *pResult = 123;
        } else {
            *pResult = 400;
        }
    } else {
        *pResult = 404;
        fn_80183920(0, 0x3FF);
    }
    ChalCloseCursors();
}

int FeTeamHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 272:
        *pResult = 0;
        *pArgs[0].pi = 0;
        break;
    case 285:
        *pResult = 0;
        break;
    case 392:
        FeTeamChooseScreen(pArgs[0].pi);
        break;
    case 250:
    case 251:
    case 252:
    case 253:
    case 254:
        break;
    default:
        return 0;
    }
    return 1;
}

int DepthChartScreenHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 270:
        DepthChartCommit(pArgs[0].i);
        break;
    case 271:
        DepthChartCancel(pArgs[0].i);
        break;
    case 268: {
        int *pList = pArgs[5].pi;
        int list = pList[0] + 1;

        pList += list;
        DepthChartGetSpotPlayer(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].i, pArgs[7].i, (DepthChartText_t *)pArgs[4].pParams, pList,
                    pArgs[6].pi);
        break;
    }
    case 267:
        DepthChartGetSpotStatNames(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[6].i, (DepthChartText_t *)pArgs[3].pParams,
                    (DepthChartText_t *)pArgs[4].pParams, (DepthChartText_t *)pArgs[5].pParams);
        break;
    case 269:
        DepthChartCanSwapSpots(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].i, pArgs[4].i);
        break;
    default:
        return 0;
    }
    return 1;
}

int DepthChartScreenIsSideShown(unsigned char side)
{
    return 1;
}

void DepthChartScreenGetSideName(unsigned char side, int unused, char *pText, int size)
{
    if (side) {
        fn_801C2EF0(pText, "Offense", size);
    } else {
        fn_801C2EF0(pText, "Defense", size);
    }
}

void DepthChartScreenGetSpot(unsigned char side, int unused, int index, float *pX, float *pY, char *pLabel, int labelSize)
{
    int value;

    FormationSlotGetInfo(side, index, pX, pY, &value, pLabel, labelSize);
    DepthChartSetSpotSlot(side != 0, index, value);
}

int FeCountsHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 372:
        *pResult = fn_80082414(0);
        break;
    case 373:
        *pResult = fn_80082414(1);
        break;
    case 374:
        *pResult = fn_80082414(2);
        break;
    case 375:
        *pResult = fn_80082414(3);
        break;
    default:
        return 0;
    }
    return 1;
}
}
