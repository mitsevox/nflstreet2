#include "game/Class_80148A58.h"

extern Record_80148C4C lbl_802DE130[];

class Class_802A2DB8 : public Class_80148A58 {
public:
    Class_802A2DB8();
    virtual void vfn_01();
    virtual ~Class_802A2DB8();
};

Class_802A2DB8::Class_802A2DB8()
{
    mState.mCount = 14;
    mState.mpRecords = lbl_802DE130;
}

Class_802A2DB8::~Class_802A2DB8()
{
    mState.mCount = 0;
    mState.mpRecords = 0;
}
