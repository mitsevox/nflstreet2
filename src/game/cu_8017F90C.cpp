#include "game/cu_8017F90C.h"

// Offers a message to each handler in turn and returns the first nonzero result.
extern "C" int fn_8017F90C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    int result;

    result = fn_801801F8(id, (Arg_801801F8 *)pArgs, unused, (Arg_801801F8 *)pResult);
    if (result != 0) {
        return result;
    }
    result = fn_8017FB90(id, pArgs, unused, pResult);
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
    result = fn_8017FAE8(id, (Block_8017FAE8 *)pArgs, unused, pResult);
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
    result = fn_8018399C(id, pArgs, unused, (Arg_8018399C *)pResult);
    if (result != 0) {
        return result;
    }
    return FeTeamHandleMessage(id, pArgs, unused, pResult);
}
