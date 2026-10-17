#include "game/Class_80148A58.h"

struct Block_802A21E8;

extern Record_80148C4C lbl_802DE41C[];

class Class_802A2C90 : public Class_80148A58 {
public:
    Class_802A2C90();
    virtual void vfn_01();

    Block_802A21E8 *mpUnknown1C;
    int mUnknown20;
};

Class_802A2C90::Class_802A2C90()
{
    mpUnknown1C = 0;
    mUnknown20 = -1;
    mState.mCount = 14;
    mState.mpRecords = lbl_802DE41C;
}