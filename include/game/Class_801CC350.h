#ifndef GAME_CLASS_801CC350_H
#define GAME_CLASS_801CC350_H

#include "game/Module.h"

/* Element of the table returned by fn_800324BC; the table ends with mId -1. */
struct Record_802CCBAC {
    int mId;
    const char *mpName;
};

/* Element of the table returned by fn_800324C8; the table ends with -1, -1. */
struct Record_803EA3A8 {
    int mUnknown0;
    int mUnknown4;
};

class Class_801CC350 {
public:
    Class_801CC350();
    virtual ~Class_801CC350();
    virtual void fn_800324E4() = 0;
    virtual int fn_800324E8() = 0;
    virtual Record_802CCBAC *fn_800324BC() = 0;
    virtual Record_803EA3A8 *fn_800324C8() = 0;
    virtual ModuleDependency *fn_800324D0(int id) = 0;
    virtual const char *GetName() = 0;
    virtual void fn_801CC6F8();
    virtual void fn_801CC6FC();

private:
    char mUnknown0[32];
};

class DebugGroup : public Class_801CC350 {
public:
    virtual void fn_800324E4();
    virtual int fn_800324E8();
    virtual Record_802CCBAC *fn_800324BC();
    virtual Record_803EA3A8 *fn_800324C8();
    virtual ModuleDependency *fn_800324D0(int id);
    virtual const char *GetName();
};

extern DebugGroup gDebugGroup;

#endif
