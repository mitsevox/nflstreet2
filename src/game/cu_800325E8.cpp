#include "game/Class_801CC350.h"

class Class_800325E8 : public Class_801CC350 {
public:
    virtual ~Class_800325E8();
    virtual const char *GetName();
    virtual Record_802CCBAC *vfn_04();
    virtual Record_803EA3A8 *vfn_05();
};

extern "C" {
void fn_80032790(int, int);
extern const char lbl_8028AD04[];
extern Record_802CCBAC lbl_802CCBBC[];
extern Record_803EA3A8 lbl_802CCBDC[];
}

const char *Class_800325E8::GetName() { return lbl_8028AD04; }
Record_802CCBAC *Class_800325E8::vfn_04() { return lbl_802CCBBC; }
Record_803EA3A8 *Class_800325E8::vfn_05() { return lbl_802CCBDC; }

extern "C" void fn_80032E90() { fn_80032790(1, 65535); }
extern "C" void fn_80032EBC() { fn_80032790(0, 65535); }
