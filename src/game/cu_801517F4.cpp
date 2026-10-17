#include "game/Class_80148A58.h"

struct Object_8015005C;

extern Record_80148C4C lbl_802DEA18[];

class Class_802A2918 : public Class_80148A58 {
public:
    Class_802A2918();
    virtual void vfn_01();

    Object_8015005C *mpUnknown1C;
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
};

Class_802A2918::Class_802A2918()
{
    mpUnknown1C = 0;
    mUnknown32 = 0;
    mUnknown36 = 0;
    mUnknown40 = 0;
    mState.mCount = 2;
    mState.mpRecords = lbl_802DEA18;
}