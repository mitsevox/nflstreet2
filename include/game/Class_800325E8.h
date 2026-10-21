#ifndef GAME_CLASS_800325E8_H
#define GAME_CLASS_800325E8_H

#include "game/Class_801CC350.h"

class Class_800325E8 : public Class_801CC350 {
public:
    virtual void vfn_02();
    virtual int vfn_03(int a, int id);
    virtual const char *GetName();
    virtual Record_802CCBAC *vfn_04();
    virtual Record_803EA3A8 *vfn_05();
    virtual ModuleDependency *vfn_06(int id);
};

extern Class_800325E8 lbl_803068B4;

#endif
