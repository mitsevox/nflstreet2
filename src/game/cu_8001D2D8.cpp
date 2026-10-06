#include "game/cu_80181330.h"

extern "C" {
int fn_80062A68(unsigned int id, int *p, int c, int *pResult);

int fn_8001D2D8(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 4:
        return fn_80062A68(id, (int *)pArgs, unused, pResult);
    }
    return 0;
}
}
