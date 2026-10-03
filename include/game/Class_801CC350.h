#ifndef GAME_CLASS_801CC350_H
#define GAME_CLASS_801CC350_H

#include "game/Module.h"

/* Element of the table returned by vfn_04; the table ends with mId -1. */
struct Record_802CCBAC {
    int mId;
    const char *mpName;
};

/* Element of the table returned by vfn_05; the table ends with -1, -1. */
struct Record_803EA3A8 {
    int mUnknown0;
    int mUnknown4;
};

class Class_801CC350 {
public:
    Class_801CC350();
    virtual ~Class_801CC350();
    virtual void vfn_02() = 0;
    virtual int vfn_03() = 0;
    virtual Record_802CCBAC *vfn_04() = 0;
    virtual Record_803EA3A8 *vfn_05() = 0;
    virtual ModuleDependency *vfn_06(int id) = 0;
    virtual const char *GetName() = 0;
    virtual void fn_801CC6F8();
    virtual void fn_801CC6FC();

private:
    char mUnknown0[32];
};

class DebugGroup : public Class_801CC350 {
public:
    virtual void vfn_02();
    virtual int vfn_03();
    virtual Record_802CCBAC *vfn_04();
    virtual Record_803EA3A8 *vfn_05();
    virtual ModuleDependency *vfn_06(int id);
    virtual const char *GetName();
};

class SystemGroup : public Class_801CC350 {
public:
    virtual void vfn_02();
    virtual int vfn_03();
    virtual Record_802CCBAC *vfn_04();
    virtual Record_803EA3A8 *vfn_05();
    virtual ModuleDependency *vfn_06(int id);
    virtual const char *GetName();
};

extern DebugGroup gDebugGroup;
extern SystemGroup gSystemGroup;

#endif
