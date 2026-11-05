/* Passes the front end's memory card messages on to the memory card save handler. */

#include "game/cu_80181330.h"

extern "C" {
int fn_80062A68(unsigned int id, int *p, int c, int *pResult);

int MsgMemCardDispatch(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 4:
        return fn_80062A68(id, (int *)pArgs, unused, pResult);
    }
    return 0;
}
}
