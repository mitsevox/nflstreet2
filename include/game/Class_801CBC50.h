#ifndef GAME_CLASS_801CBC50_H
#define GAME_CLASS_801CBC50_H

class Class_801CC350;
class ModuleNode;
struct ModuleDependency;

/* Queued group change: group index, current and requested id (12 bytes). */
struct Request_801CBC50 {
    int mGroup;
    int mFrom;
    int mTo;
};

class Class_801CBC50 {
public:
    Class_801CBC50();
    virtual ~Class_801CBC50();
    virtual int fn_80032340() = 0;
    virtual void *fn_80032348(int index) = 0;
    virtual void fn_800323AC() = 0;

    int fn_801CBD80(int a, int b);
    int fn_801CBE24(int a);
    int fn_801CBE9C(int a);
    int fn_801CBEC8(int a);
    int fn_801CBEF4(int a, int b);
    int fn_801CC05C(ModuleDependency *pDeps);
    int fn_801CC0D0(ModuleDependency *pDeps);
    int fn_801CC168(ModuleDependency *pDeps);
    int fn_801CC1DC(int group, int from, int to);
    int fn_801CC280(ModuleNode *pNode);
    int fn_801CC2E8(ModuleNode *pNode);

    unsigned char mUnknown0;
    unsigned char mUnknown1;
    int mFlags;
    int mCount;
    int mPendingCount;
    Class_801CC350 *mpGroups[20];
    Request_801CBC50 mPending[10];
    int mUnknownD8;
};

class Class_803067B0 : public Class_801CBC50 {
public:
    virtual ~Class_803067B0() {}
    virtual int fn_80032340();
    virtual void *fn_80032348(int index);
    virtual void fn_800323AC();
};
extern Class_803067B0 lbl_803067B0;

extern "C" {
void fn_801CBCD0(Class_801CBC50 *pTable);
int fn_801CBFA0(Class_801CBC50 *pTable);
void fn_801CBFA8(Class_801CBC50 *pTable);
void fn_801CC054(Class_801CBC50 *pTable, int flags);
}

#endif
