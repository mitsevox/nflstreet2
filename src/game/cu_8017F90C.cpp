#include "game/cu_80181330.h"

extern "C" {
int fn_80055058(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_800550E4(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005528C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8005542C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8017FAE8(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8017FB90(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_801801F8(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_801811C8(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_80181238(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8018399C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8018422C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_80185284(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
}

// Offers a message to each handler in turn and returns the first nonzero result.
extern "C" int fn_8017F90C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    int result;

    result = fn_801801F8(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = fn_8017FB90(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = fn_8018422C(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = fn_80185284(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = fn_8017FAE8(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = fn_800550E4(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = fn_8005528C(id, pArgs, unused, pResult);
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
    result = fn_8005542C(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    result = fn_8018399C(id, pArgs, unused, pResult);
    if (result != 0) {
        return result;
    }
    return fn_80055058(id, pArgs, unused, pResult);
}
