#include "game/Class_801CC350.h"
#include "game/Class_801CBC50.h"
#include "game/FELoop.h"

class MainFEGroup : public Class_801CC350 {
public:
    virtual void vfn_02();
    virtual int vfn_03(int a, int b);
    virtual Record_802CCBAC *vfn_04();
    virtual Record_803EA3A8 *vfn_05();
    virtual ModuleDependency *vfn_06(int id);
    virtual const char *GetName();
};

extern "C" {
void fn_800245DC(void);
void fn_80024628(void);
void fn_80026BA4(void);
void fn_80072C90(unsigned int delay, int wait);
void fn_80072D98(unsigned int delay);
void fn_80187C5C(unsigned char a);
extern const char lbl_8028ADDC[];
extern Record_802CCBAC lbl_802CCBF4[];
extern Record_803EA3A8 lbl_802CCC34[];
extern ModuleDependency lbl_80306B58[];
extern ModuleDependency lbl_80306B84[];
extern ModuleDependency lbl_80306B98[];
extern ModuleDependency lbl_80306BF4[];
extern ModuleDependency lbl_80306C4C[];
extern ModuleDependency lbl_80306C58[];
}

const char *MainFEGroup::GetName() { return lbl_8028ADDC; }
Record_802CCBAC *MainFEGroup::vfn_04() { return lbl_802CCBF4; }
Record_803EA3A8 *MainFEGroup::vfn_05() { return lbl_802CCC34; }

ModuleDependency *MainFEGroup::vfn_06(int id)
{
    switch (id) {
    case 7:
        return lbl_80306B58;
    case 8:
        return lbl_80306B84;
    case 9:
        return lbl_80306B98;
    case 10:
        return lbl_80306BF4;
    case 12:
    case 14:
        return lbl_80306C58;
    case 11:
        return lbl_80306C4C;
    default:
        return 0;
    }
}

void MainFEGroup::vfn_02()
{
    Class_803067B0 *p = &lbl_803067B0;

    if (p->fn_801CBE9C(3) == 0) {
        switch (p->fn_801CBEC8(2)) {
        case 7:
            gFELoop.fn_800279AC();
            p->fn_801CBEF4(2, 8);
            break;
        case 8:
            fn_80187C5C(1);
            p->fn_801CBEF4(2, 9);
            break;
        case 9:
            fn_800245DC();
            p->fn_801CBEF4(2, 10);
            break;
        case 10:
            if (!gFELoop.fn_80027C58()) {
                fn_80024628();
                if (!fn_801CBFA0(p)) {
                    p->fn_801CBEF4(2, 14);
                }
            }
            break;
        case 12:
            p->fn_801CBE24(2);
            p->fn_801CBD80(1, -1);
            break;
        case 14:
            fn_80026BA4();
            break;
        }
    }
}

int MainFEGroup::vfn_03(int a, int b)
{
    switch (b) {
    case 12:
        fn_80072C90(250, 1);
        break;
    case 10:
        fn_80072D98(250);
        break;
    }
    return 1;
}

extern "C" int fn_80033124(Class_801CC350 *pGroup) { return fn_801CC4F4(pGroup); }

extern "C" int fn_80033144(Class_801CC350 *pGroup)
{
    int result = 0;
    int stage = fn_801CC4FC(pGroup);

    if (fn_80033124(pGroup) && (stage == 7 || stage == 8)) {
        result = 1;
    }
    return result;
}

extern "C" void fn_8003319C(int initialize, int priority);

extern "C" void fn_80033438() { fn_8003319C(1, 65535); }
extern "C" void fn_80033464() { fn_8003319C(0, 65535); }
