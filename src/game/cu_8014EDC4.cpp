#include "game/Class_80148A58.h"

struct Block_8014F104;

extern Record_80148C4C lbl_802DE99C[];

class Class_802A2B68 : public Class_80148A58 {
public:
    Class_802A2B68();
    virtual void vfn_01();

    Block_8014F104 *mpUnknown1C;
};

Class_802A2B68::Class_802A2B68()
{
    mState.mCount = 1;
    mState.mpRecords = lbl_802DE99C;
    mpUnknown1C = 0;
}
