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
    /* Called by 0x801CC654 with the word at +4 and that function's argument. */
    virtual int vfn_03(int a, int id) = 0;
    virtual Record_802CCBAC *vfn_04() = 0;
    virtual Record_803EA3A8 *vfn_05() = 0;
    virtual ModuleDependency *vfn_06(int id) = 0;
    virtual const char *GetName() = 0;
    virtual void fn_801CC6F8();
    virtual void fn_801CC6FC(int id);

    void fn_801CC3C0();
    int fn_801CC490(int id);
    int fn_801CC4DC();
    int fn_801CC518();
    ModuleDependency *fn_801CC524(int id);
    void fn_801CC558();
    void fn_801CC5B4(int id);
    void fn_801CC604(int id);
    int fn_801CC654(int id);
    const char *fn_801CC6C4();

    unsigned char mUnknown0;
    unsigned char mUnknown1;
    int mId;
    Record_802CCBAC *mpRecords;
    Record_803EA3A8 *mpLinks;
    int mRecordCount;
    int mLinkCount;
    int mOverrideId;
    unsigned char mOverride;
};

extern "C" {
int fn_801CC4F4(Class_801CC350 *pGroup);
int fn_801CC4FC(Class_801CC350 *pGroup);
}

class DebugGroup : public Class_801CC350 {
public:
    virtual void vfn_02();
    virtual int vfn_03(int a, int id);
    virtual Record_802CCBAC *vfn_04();
    virtual Record_803EA3A8 *vfn_05();
    virtual ModuleDependency *vfn_06(int id);
    virtual const char *GetName();
};

class SystemGroup : public Class_801CC350 {
public:
    virtual void vfn_02();
    virtual int vfn_03(int a, int id);
    virtual Record_802CCBAC *vfn_04();
    virtual Record_803EA3A8 *vfn_05();
    virtual ModuleDependency *vfn_06(int id);
    virtual const char *GetName();
};

extern DebugGroup gDebugGroup;
extern SystemGroup gSystemGroup;

#endif
