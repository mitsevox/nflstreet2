#include "game/Class_80148A58.h"

extern Record_80148C4C lbl_802DEAA8[];

class Class_802A27F0 : public Class_80148A58 {
public:
    Class_802A27F0();
    virtual void vfn_01();
};

Class_802A27F0::Class_802A27F0()
{
    mState.mUnknownC = 0;
    mState.mCount = 2;
    mState.mpRecords = lbl_802DEAA8;
}