#include "game/Class_801CC350.h"
#include "game/Class_801CBC50.h"

extern "C" {
void fn_801D3318(int ident, const char *pLabel);
void fn_801D339C(int ident);
void fn_801D342C(int ident);
}

extern unsigned char lbl_803EBC50;
extern unsigned int lbl_803EBC54;
extern ModuleNode *lbl_803D4780[];

extern "C" {
int fn_801CC7FC(ModuleNode *pNode);
int fn_801CC820(ModuleNode *pNode, unsigned char flags);
int fn_801CC8AC(ModuleNode *pNode, unsigned char flags);
}

void fn_801CC9DC(int a);
void fn_801CC9E4();
void fn_801CC9E8();

Class_801CBC50::Class_801CBC50()
{
    int i;

    for (i = 0; i < 20; i++) {
        mpGroups[i] = 0;
    }
    mCount = 0;
    mFlags = 0;
    mUnknownD8 = 0;
    mUnknown0 = 0;
    mUnknown1 = 0;
}

Class_801CBC50::~Class_801CBC50()
{
}

void fn_801CBCD0(Class_801CBC50 *p)
{
    int i;

    fn_801CC9DC(1);
    p->mCount = p->fn_80032340();
    p->mPendingCount = 0;
    for (i = 0; i < p->mCount; i++) {
        p->mpGroups[i] = (Class_801CC350 *)p->fn_80032348(i);
        p->mpGroups[i]->fn_801CC3C0();
    }
    fn_801CC9E4();
    fn_801CC9E8();
    p->mUnknown0 = 1;
}

int Class_801CBC50::fn_801CBD80(int a, int b)
{
    int result;
    ModuleDependency *pDeps;

    int id;

    if (b == -1) {
        result = mpGroups[a]->fn_801CC490(-1);
    } else {
        result = mpGroups[a]->fn_801CC490(b);
    }
    if (result == 1) {
        id = fn_801CC4FC(mpGroups[a]);
        pDeps = mpGroups[a]->fn_801CC524(id);
        fn_801CC05C(pDeps);
        result = fn_801CC0D0(pDeps);
    }
    return result;
}

int Class_801CBC50::fn_801CBE24(int a)
{
    int result;
    int id;

    if (fn_801CC4F4(mpGroups[a]) == 0) {
        return 0;
    }
    id = fn_801CC4FC(mpGroups[a]);
    result = mpGroups[a]->fn_801CC4DC();
    if (result == 1) {
        result = fn_801CC168(mpGroups[a]->fn_801CC524(id));
    }
    return result;
}

int Class_801CBC50::fn_801CBE9C(int a)
{
    return fn_801CC4F4(mpGroups[a]);
}

int Class_801CBC50::fn_801CBEC8(int a)
{
    return fn_801CC4FC(mpGroups[a]);
}

int Class_801CBC50::fn_801CBEF4(int a, int b)
{
    int id;

    if (fn_801CC4FC(mpGroups[a]) == b) {
        return 1;
    }
    if (fn_801CC4F4(mpGroups[a]) == 0) {
        return 0;
    }
    id = fn_801CC4FC(mpGroups[a]);
    mPending[mPendingCount].mGroup = a;
    mPending[mPendingCount].mFrom = id;
    mPending[mPendingCount].mTo = b;
    mPendingCount++;
    return 1;
}

int fn_801CBFA0(Class_801CBC50 *pTable)
{
    return pTable->mPendingCount;
}

void fn_801CBFA8(Class_801CBC50 *p)
{
    int i;

    for (i = 0; i < p->mPendingCount; i++) {
        p->fn_801CC1DC(p->mPending[i].mGroup, p->mPending[i].mFrom, p->mPending[i].mTo);
    }
    p->mPendingCount = 0;
    for (i = 0; i < p->mCount; i++) {
        if (fn_801CC4F4(p->mpGroups[i]) == 1) {
            p->mpGroups[i]->fn_801CC558();
        }
    }
}

void fn_801CC054(Class_801CBC50 *pTable, int flags)
{
    pTable->mFlags = flags;
}

int Class_801CBC50::fn_801CC05C(ModuleDependency *pDeps)
{
    int result = 1;
    int i;

    for (i = 0; pDeps[i].mpTarget != 0; i++) {
        result = fn_801CC05C(((ModuleNode *)pDeps[i].mpTarget)->fn_801CC974());
        fn_801CC7FC((ModuleNode *)pDeps[i].mpTarget);
    }
    return result;
}

int Class_801CBC50::fn_801CC0D0(ModuleDependency *pDeps)
{
    int result = 1;
    int i;
    ModuleNode *pNode;
    ModuleDependency *pSub;

    for (i = 0; pDeps[i].mpTarget != 0; i++) {
        pSub = ((ModuleNode *)pDeps[i].mpTarget)->fn_801CC974();
        pNode = (ModuleNode *)pDeps[i].mpTarget;
        result = fn_801CC0D0(pSub);
        if (pNode->fn_801CC96C() == 0) {
            if (fn_801CC280(pNode) == 0) {
                result = 0;
            }
        }
    }
    return result;
}

int Class_801CBC50::fn_801CC168(ModuleDependency *pDeps)
{
    int result = 1;
    int i;
    ModuleDependency *pNext;

    for (i = 0; pDeps[i].mpTarget != 0; i++) {
        pNext = ((ModuleNode *)pDeps[i].mpTarget)->fn_801CC974();
        fn_801CC2E8((ModuleNode *)pDeps[i].mpTarget);
        result = fn_801CC168(pNext);
    }
    return result;
}

int Class_801CBC50::fn_801CC1DC(int group, int from, int to)
{
    ModuleDependency *pFrom;
    ModuleDependency *pTo;
    int result;

    pFrom = mpGroups[group]->fn_801CC524(from);
    pTo = mpGroups[group]->fn_801CC524(to);
    fn_801CC05C(pTo);
    fn_801CC168(pFrom);
    mpGroups[group]->fn_801CC5B4(to);
    fn_801CC0D0(pTo);
    result = mpGroups[group]->fn_801CC654(to);
    mpGroups[group]->fn_801CC604(to);
    return result;
}

int Class_801CBC50::fn_801CC280(ModuleNode *pNode)
{
    int result;

    fn_801D339C(1);
    fn_801D3318(1, pNode->fn_801CC9A8());
    result = fn_801CC820(pNode, mFlags & 2);
    fn_801D342C(1);
    return result;
}

int Class_801CBC50::fn_801CC2E8(ModuleNode *pNode)
{
    int result;

    fn_801D339C(1);
    fn_801D3318(1, pNode->fn_801CC9A8());
    result = fn_801CC8AC(pNode, mFlags & 2);
    fn_801D342C(1);
    return result;
}

Class_801CC350::Class_801CC350() : mUnknown0(0), mUnknown1(0), mId(-1)
{
    mRecordCount = 0;
    mLinkCount = 0;
    mpRecords = 0;
    mpLinks = 0;
}

Class_801CC350::~Class_801CC350()
{
}

void Class_801CC350::fn_801CC3C0()
{
    mpRecords = vfn_04();
    mpLinks = vfn_05();
    mOverrideId = -1;
    mRecordCount = 0;
    mOverride = 0;
    while (mpRecords[mRecordCount].mId != -1) {
        mRecordCount++;
    }
    while (mpLinks[mLinkCount].mUnknown0 != -1) {
        mLinkCount++;
    }
    mUnknown0 = 1;
}

int Class_801CC350::fn_801CC490(int id)
{
    if (id == -1) {
        mId = fn_801CC518();
    } else {
        mId = id;
    }
    mUnknown1 = 1;
    return 1;
}

int Class_801CC350::fn_801CC4DC()
{
    mId = -1;
    mUnknown1 = 0;
    return 1;
}

int fn_801CC4F4(Class_801CC350 *pGroup)
{
    return pGroup->mUnknown1;
}

int fn_801CC4FC(Class_801CC350 *pGroup)
{
    if (pGroup->mOverride != 0) {
        return pGroup->mOverrideId;
    }
    return pGroup->mId;
}

int Class_801CC350::fn_801CC518()
{
    return mpRecords->mId;
}

ModuleDependency *Class_801CC350::fn_801CC524(int id)
{
    return vfn_06(id);
}

void Class_801CC350::fn_801CC558()
{
    fn_801D3318(-1, fn_801CC6C4());
    vfn_02();
    fn_801D3318(-1, 0);
}

void Class_801CC350::fn_801CC5B4(int id)
{
    fn_801CC6F8();
    mOverrideId = id;
    mOverride = 1;
}

void Class_801CC350::fn_801CC604(int id)
{
    int old = mId;

    mId = id;
    mOverrideId = -1;
    mOverride = 0;
    fn_801CC6FC(old);
}

int Class_801CC350::fn_801CC654(int id)
{
    int result;

    fn_801D3318(-1, fn_801CC6C4());
    result = vfn_03(mId, id);
    fn_801D3318(-1, 0);
    return result;
}

const char *Class_801CC350::fn_801CC6C4()
{
    return GetName();
}

void Class_801CC350::fn_801CC6F8()
{
}

void Class_801CC350::fn_801CC6FC(int id)
{
}

ModuleNode::ModuleNode()
{
    lbl_803D4780[lbl_803EBC54] = this;
    lbl_803EBC54++;
    mUnknown0 = 0;
    mUnknown8 = 0;
    mUnknown4 = 0;
}

ModuleNode::~ModuleNode()
{
    unsigned int i;
    int found = 0;

    for (i = 0; i < lbl_803EBC54; i++) {
        if (lbl_803D4780[i] == this) {
            found = 1;
        }
        if (found) {
            if (i != lbl_803EBC54 - 1) {
                lbl_803D4780[i] = lbl_803D4780[i + 1];
            } else {
                lbl_803D4780[i] = 0;
            }
        }
    }
    lbl_803EBC54--;
}

int fn_801CC7FC(ModuleNode *pNode)
{
    pNode->mUnknown4++;
    return pNode->mUnknown4 > 0;
}

int fn_801CC820(ModuleNode *pNode, unsigned char flags)
{
    int result;

    pNode->fn_80025F24(pNode);
    result = pNode->Init();
    if (result == 1) {
        pNode->mUnknown8 = result;
    }
    pNode->fn_80025F28(pNode);
    return result;
}

int fn_801CC8AC(ModuleNode *pNode, unsigned char flags)
{
    int result;

    if (--pNode->mUnknown4 == 0) {
        pNode->fn_80025F5C(pNode);
        if (pNode->mUnknown8 == 1) {
            result = pNode->Shutdown();
        } else {
            result = 1;
        }
        if (result == 1) {
            pNode->mUnknown8 = 0;
        }
        pNode->fn_80025F60(pNode);
    } else {
        result = 1;
    }
    return result;
}

int ModuleNode::fn_801CC96C()
{
    return mUnknown8;
}

ModuleDependency *ModuleNode::fn_801CC974()
{
    return GetDependencies();
}

const char *ModuleNode::fn_801CC9A8()
{
    return GetName();
}

void fn_801CC9DC(int a)
{
    lbl_803EBC50 = a;
}

void fn_801CC9E4()
{
}

void fn_801CC9E8()
{
}

Class_801CC9EC::~Class_801CC9EC()
{
}

void Class_801CC9EC::fn_801CCA20(ModuleNode *pNode)
{
    if (pNode->fn_801CC96C() == 0) {
        mCount++;
    }
}
