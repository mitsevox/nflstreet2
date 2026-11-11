/* Fallback handler for UIStudio game messages: offers each message to twelve game handlers in turn. */
#include "game/UISGameMsg.h"

// Offers a message to each handler in turn and returns the first nonzero result.
extern "C" int UISGameMsgDispatch(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    int result;

    result = MsgGameHandleMessage(id, (MsgGameArg_t *)pArgs, unused, (MsgGameArg_t *)pResult);
    if (result != 0) {
        return result;
    }
    result = UISGameQueryHandleMsg(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = MemCardUIEmptyHandler(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = MemCardUIHandleFunction(id, (MemCardUIArgs_t *)pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = ColorPickHandleMsg(id, (ColorPickMsg_t *)pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = DepthChartScreenHandleMessage(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = FeCountsHandleMessage(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = FEMiscHandleStatsFunction(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = FEMiscHandleFunction(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = FeatsScreenHandleMessage(id, (FeatsScreenArgs_t *)pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = fn_8018399C(id, pArgs, unused, (MenuArg_t *)pResult);
    if (result != 0) {
        return result;
    }
    return FeTeamHandleMessage(id, pArgs, unused, pResult);
}
