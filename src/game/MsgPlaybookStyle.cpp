/* Playbook style row: steps through the playbook styles (Balanced, Rush Offense,
   Rush Defense, Pass Offense, Pass Defense, Custom) and shows the chosen name. */

#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"

struct PlaybookStyleArgs_t {
    int mUnknown0;
    Params_80005284 *mpUnknown4;
};

static const char *_MsgPlaybookStyle_pszNames[] = {
    "Balanced",
    "Rush Offense",
    "Rush Defense",
    "Pass Offense",
    "Pass Defense",
    "Custom",
};
static int _MsgPlaybookStyle_iSelection = 0;

extern "C" {
char *MsgPlaybookStyleCycle(int action, Params_80005284 **ppParams)
{
    Params_80005284 *pParams = *ppParams;

    switch (action) {
    case 3:
        --_MsgPlaybookStyle_iSelection;
        if (_MsgPlaybookStyle_iSelection < 0) {
            _MsgPlaybookStyle_iSelection = 5;
        }
        break;
    case 1:
        ++_MsgPlaybookStyle_iSelection;
        if (_MsgPlaybookStyle_iSelection > 5) {
            _MsgPlaybookStyle_iSelection = 0;
        }
        break;
    case -1:
        _MsgPlaybookStyle_iSelection = 0;
        break;
    }
    return fn_801C3284(pParams->mpText, _MsgPlaybookStyle_pszNames[_MsgPlaybookStyle_iSelection], pParams->mLength);
}

int MsgPlaybookStyleHandleMessage(unsigned int id, PlaybookStyleArgs_t *pArgs)
{
    switch (id) {
    case 0x80000001:
        break;
    case 0x80000002:
    {
        Params_80005284 *pParams = pArgs->mpUnknown4;
        MsgPlaybookStyleCycle(pArgs->mUnknown0, &pParams);
        break;
    }
    default:
        return 0;
    }
    return 1;
}
}
