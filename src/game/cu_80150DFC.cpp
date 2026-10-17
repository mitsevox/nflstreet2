#include "game/Class_80297AB8.h"

class Class_802A1D20 : public Class_80297AB8 {
public:
    unsigned char mUnknown4;
    char mUnknown5[3];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

extern "C" {
void fn_80150DFC(Class_802A1D20 *p)
{
    p->Class_80297AB8::vfn_05();
}
}
