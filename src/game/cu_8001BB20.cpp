#include "game/cu_80181330.h"

extern "C" {
int fn_8001BD88(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8001CCB4(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);

int fn_8001BB20(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 1:
        return fn_8001BD88(id, pArgs, unused, pResult);
    case 2:
        return fn_8001CCB4(id, pArgs, unused, pResult);
    }
    return 0;
}
}
