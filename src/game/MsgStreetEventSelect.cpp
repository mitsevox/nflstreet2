/* Street Event list: the front-end screen where the player picks one of the Street
   Event mini-games. It reads each event's name and description from the game
   database and remembers the chosen event for the game. */

#include "game/FELoop.h"
#include "game/cu_80181330.h"
#include "game/fn_801FCE10.h"

extern "C" {
void fn_8000FCD4(int a);
void fn_801485B4(void);
void fn_801485C0(void);
void fn_801485EC(int value);
int MsgGameGetSetupState(void);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
}

static unsigned char _MsgStreetEventSelect_bOpen = 0;
static int _MsgStreetEventSelect_iPending = 15;
static int _MsgStreetEventSelect_iChosen = 15;

extern "C" {
void MsgStreetEventSelectInit(int *pCount, int *pValue)
{
    if (_MsgStreetEventSelect_bOpen == 0) {
        if (fn_8022EF8C(0, 0x5444474D) == 0) {
            *pCount = 6;
            fn_801FCE10(0, "select count(*) into \x82 from 'TDGM'\n", pCount);
        }
        if (_MsgStreetEventSelect_iChosen != 15) {
            *pValue = _MsgStreetEventSelect_iChosen;
        } else {
            *pValue = 0;
        }
        _MsgStreetEventSelect_iPending = 15;
        _MsgStreetEventSelect_bOpen = 1;
        FELoopResetIdle();
        if (MsgGameGetSetupState() == 0) {
            fn_801485C0();
        }
        fn_801485B4();
    }
}

void MsgStreetEventSelectShutdown(void)
{
    if (_MsgStreetEventSelect_bOpen != 0) {
        fn_8022EFBC(0, 0x5444474D);
        if (_MsgStreetEventSelect_iPending >= 0 && _MsgStreetEventSelect_iPending <= 5) {
            fn_801485EC(_MsgStreetEventSelect_iPending);
            _MsgStreetEventSelect_iChosen = _MsgStreetEventSelect_iPending;
        } else {
            fn_801485C0();
            _MsgStreetEventSelect_iChosen = 15;
        }
        _MsgStreetEventSelect_bOpen = 0;
    }
}

void MsgStreetEventSelectGetName(int id, char *pDest, int count)
{
    char name[32];

    if (fn_801FCE10(0, "select 'NMIU' into \x88 from 'TDGM' where 'DIGM' = \x82\n", name, id) != 0) {
        name[0] = '?';
        name[1] = 0;
    }
    fn_801C2EF0(pDest, name, count);
}

void MsgStreetEventSelectGetInfo(int id, int *pValue, char *pDest, int count)
{
    char name[208];

    if (fn_801FCE10(0, "select 'DMIU' into \x88 and 'PMIU' into \x82 from 'TDGM' where 'DIGM' = \x82\n", name,
                    pValue, id) != 0) {
        name[0] = '?';
        name[1] = 0;
    }
    fn_801C2EF0(pDest, name, count);
}

int MsgStreetEventSelectSetChoice(int value)
{
    _MsgStreetEventSelect_iPending = value;
    return value;
}

int MsgStreetEventSelectHandleMessage(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgStreetEventSelectInit(pArgs[0].pi, pArgs[1].pi);
        break;
    case 0x80000002:
        MsgStreetEventSelectShutdown();
        break;
    case 0x80000003:
        MsgStreetEventSelectGetName(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength);
        break;
    case 0x80000004:
        MsgStreetEventSelectGetInfo(pArgs[0].i, pArgs[1].pi, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength);
        break;
    case 0x80000005:
        *pResult = MsgStreetEventSelectSetChoice(pArgs[0].i);
        fn_8000FCD4(pArgs[1].i);
        break;
    default:
        return 0;
    }
    return 1;
}
}
