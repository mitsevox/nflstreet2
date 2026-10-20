#include "game/Class_80148A58.h"

struct Object_8015005C;

class Class_802A2918 : public Class_80148A58 {
public:
    Object_8015005C *mpUnknown1C;
};

extern "C" {
void fn_80152400(Class_802A2918 *p, int value, int *list, int *ids)
{
    unsigned char i;

    for (i = 0; i < 7 && list[i] != 32767; i++) {
        ids[i] = ids[i + 7] = list[i];
    }
}

void fn_80152448(Class_802A2918 *p, int value, int *list, int *ids, int a, int b)
{
    p->vfn_10(value, list, ids);
}
}
