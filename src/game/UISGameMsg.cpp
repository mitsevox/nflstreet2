/* Fallback handler for UIStudio game messages: offers each message to twelve game handlers in turn. */
#include "game/UISGameMsg.h"

// Offers a message to each handler in turn and returns the first nonzero result.
extern "C" int UISGameMsgDispatch(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
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
    result = fn_8018422C(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = fn_80185284(id, (Params_80185284 *)pArgs, unused, pResult);
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
    result = fn_801811C8(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = fn_80181238(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = FeatsScreenHandleMessage(id, (FeatsScreenArgs_t *)pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = fn_8018399C(id, pArgs, unused, (Arg_8018399C *)pResult);
    if (result != 0) {
        return result;
    }
    return FeTeamHandleMessage(id, pArgs, unused, pResult);
}
