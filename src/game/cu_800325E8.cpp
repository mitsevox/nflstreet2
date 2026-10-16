#include "game/Class_801CC350.h"
#include "game/Class_801CBC50.h"
#include "game/InGame.h"

class Class_800325E8 : public Class_801CC350 {
public:
    virtual ~Class_800325E8();
    virtual void vfn_02();
    virtual const char *GetName();
    virtual Record_802CCBAC *vfn_04();
    virtual Record_803EA3A8 *vfn_05();
    virtual ModuleDependency *vfn_06(int id);
};

extern "C" {
void fn_80025F20(int a);
void fn_80032790(int, int);
extern const char lbl_8028AD04[];
extern Record_802CCBAC lbl_802CCBBC[];
extern Record_803EA3A8 lbl_802CCBDC[];
extern ModuleDependency lbl_803068D8[];
extern ModuleDependency lbl_80306A08[];
extern ModuleDependency lbl_803EC680[2];
}

const char *Class_800325E8::GetName() { return lbl_8028AD04; }
Record_802CCBAC *Class_800325E8::vfn_04() { return lbl_802CCBBC; }
Record_803EA3A8 *Class_800325E8::vfn_05() { return lbl_802CCBDC; }

ModuleDependency *Class_800325E8::vfn_06(int id)
{
    switch (id) {
    case 4:
        return lbl_803068D8;
    case 5:
        return lbl_80306A08;
    case 6:
        return lbl_803EC680;
    default:
        return 0;
    }
}

void Class_800325E8::vfn_02()
{
    Class_803067B0 *p = &lbl_803067B0;

    if (p->fn_801CBE9C(3) == 0) {
        switch (p->fn_801CBEC8(1)) {
        case 4:
            p->fn_801CBEF4(1, 5);
            break;
        case 5:
            if (!gInGame.fn_8002854C()) {
                p->fn_801CBEF4(1, 6);
            }
            break;
        case 6:
            p->fn_801CBE24(1);
            fn_80025F20(1);
            p->fn_801CBD80(2, -1);
            break;
        }
    }
}

extern "C" void fn_80032E90() { fn_80032790(1, 65535); }
extern "C" void fn_80032EBC() { fn_80032790(0, 65535); }
