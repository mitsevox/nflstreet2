#include "game/Class_80148A58.h"

struct Object_8015005C;

class Class_802A2918 : public Class_80148A58 {
public:
    Object_8015005C *mpUnknown1C;
};

struct Record_8015289C {
    char mUnknown0[60];
    unsigned char mUnknown60;
    char mUnknown61[7];
};

extern "C" {
int fn_8015289C(Class_802A2918 *p, Record_8015289C *pRecords, unsigned int count)
{
    unsigned int n = 0;
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (pRecords[i].mUnknown60) {
            n++;
        }
    }
    return n > 3;
}
}
