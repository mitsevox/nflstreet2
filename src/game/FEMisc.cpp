// Front-end helpers: shows the help line for the highlighted item and answers
// a few UI script queries about the current team and profile, such as its stats.
#include <string.h>
#include "game/DbCursor.h"
#include "game/cu_80181330.h"
#include "game/fn_8021D7B8.h"
#include "game/UISGameMsg.h"

extern void *gUISMainInfo;

static char _FEMisc_szHelpText[81] = "";

extern "C" {

int fn_80061C44(void);
int fn_80061CAC(void);
int fn_8005F910(void);
int fn_8005F938(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult);
int fn_80186B38(int a);
int GauntletGetCurrentTeam(int a);
void GauntletStatsOpen(DbCursor *pObject, int a);
void GauntletStatsClose(DbCursor *pObject);
int GauntletStatsGet(DbCursor *pObject, int index);
void fn_80183368(int mode, int value);
int fn_801835A0(void);
int fn_80183948(void);
int fn_8022F384(int a);
int fn_8022F4BC(void);

/* Posts message 0x80000006 with the text when it differs from the last
   text posted. */
void FEMiscSetHelpText(const char *pText)
{
    static Params_80005284 sText;

    if (strncmp(pText, _FEMisc_szHelpText, 81)) {
        MenuArg_t args[1];

        strncpy(_FEMisc_szHelpText, pText, 81);
        sText.mUnknown0 = 0;
        sText.mLength = 80;
        sText.mpText = _FEMisc_szHelpText;
        args[0].pParams = &sText;
        fn_8021D7B8(gUISMainInfo, 0x80000006, 1, args);
    }
}

int FEMiscIsTeamUnset(void)
{
    return GauntletGetCurrentTeam(fn_80186B38(fn_8022F4BC())) == 0x3FF;
}

/* Reads sixteen values of the current entry; element 6 is the sum of
   elements 3 to 5. */
void FEMiscGetStats(int *pValues)
{
    DbCursor object;
    int total;

    GauntletStatsOpen(&object, (signed char)fn_8022F384(fn_8022F4BC()));
    pValues[0] = GauntletStatsGet(&object, 0);
    pValues[1] = GauntletStatsGet(&object, 1);
    pValues[2] = GauntletStatsGet(&object, 14);
    total = pValues[3] = GauntletStatsGet(&object, 3);
    total += pValues[4] = GauntletStatsGet(&object, 4);
    total += pValues[5] = GauntletStatsGet(&object, 5);
    pValues[6] = total;
    pValues[7] = GauntletStatsGet(&object, 13);
    pValues[8] = GauntletStatsGet(&object, 2);
    pValues[9] = GauntletStatsGet(&object, 6);
    pValues[10] = GauntletStatsGet(&object, 7);
    pValues[11] = GauntletStatsGet(&object, 8);
    pValues[12] = GauntletStatsGet(&object, 10);
    pValues[13] = GauntletStatsGet(&object, 9);
    pValues[14] = GauntletStatsGet(&object, 11);
    pValues[15] = GauntletStatsGet(&object, 12);
    GauntletStatsClose(&object);
}

int FEMiscHandleStatsFunction(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x17A:
        *pResult = FEMiscIsTeamUnset();
        break;
    case 0x187: {
        int index = pArgs[0].pi[0] + 1;

        FEMiscGetStats(&pArgs[0].pi[index]);
        break;
    }
    default:
        return 0;
    }
    return 1;
}

int FEMiscHandleFunction(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x173:
        if (fn_8005F910()) {
            *pResult = 1;
            if (!fn_801835A0()) {
                fn_80183368(3, 0x3FF);
            }
        } else if (fn_801835A0() && fn_80183948() == 3) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    case 0x148:
        if (fn_80061C44()) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    case 0x14E:
        if (fn_80061CAC()) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    case 0x146:
    case 0x16E:
        fn_8005F938(id, pArgs, unused, pResult);
        break;
    default:
        return 0;
    }
    return 1;
}
}
