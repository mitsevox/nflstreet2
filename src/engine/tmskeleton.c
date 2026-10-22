#include "engine/tmlib.h"

extern int fn_801C4E98(void *pSkel, const char *pName);

void fn_80215E5C(Skeleton_80215E5C *pSkel, void *pOldBase, void *pNewBase)
{
    pSkel->mpNames = fn_8020EB94(pSkel->mpNames, pOldBase, pNewBase);
    pSkel->mpBones = fn_8020EB94(pSkel->mpBones, pOldBase, pNewBase);
    pSkel->mpInfo = fn_8020EB94(pSkel->mpInfo, pOldBase, pNewBase);
    if (pSkel->mpUnknown10 != 0) {
        pSkel->mpUnknown10 = fn_8020EB94(pSkel->mpUnknown10, pOldBase, pNewBase);
    }
}

short *fn_80215EE0(Skeleton_80215E5C *pSkel, void *pOther)
{
    short *pRemap = 0;
    unsigned int i;

    if (pSkel != 0 && pSkel->mpNames != 0) {
        pRemap = fn_802127D0(pSkel->mNumBones, 2);
        for (i = 0; i < pSkel->mNumBones; i++) {
            pRemap[i] = fn_801C4E98(pOther, pSkel->mpNames[i]);
        }
    }
    return pRemap;
}

void fn_80215F78(Skeleton_80215E5C *pSkel, short *pRemap)
{
    int numBones = pSkel->mNumBones;
    SkelBoneInfo_80215E5C *pInfo = pSkel->mpInfo;
    SkelBone_80215E5C *pBones = pSkel->mpBones;
    SkelBoneInfo_80215E5C *pOldInfo;
    SkelBone_80215E5C *pOldBones;
    int i;

    pOldInfo = fn_802127D0(numBones, sizeof(SkelBoneInfo_80215E5C));
    memcpy(pOldInfo, pSkel->mpInfo, numBones * sizeof(SkelBoneInfo_80215E5C));
    pOldBones = fn_802127D0(numBones, sizeof(SkelBone_80215E5C));
    memcpy(pOldBones, pSkel->mpBones, numBones * sizeof(SkelBone_80215E5C));
    for (i = 0; i < numBones; i++) {
        int index = pRemap[i];

        if (index != -1) {
            pInfo[index].maUnknown0[0] = pOldInfo[i].maUnknown0[0];
            pInfo[index].maUnknown0[1] = pOldInfo[i].maUnknown0[1];
            pInfo[index].maUnknown0[2] = pOldInfo[i].maUnknown0[2];
            pBones[index] = pOldBones[i];
            if (pOldBones[i].mParent != -1) {
                pBones[index].mParent = pRemap[pOldBones[i].mParent];
            } else {
                pBones[index].mParent = -1;
            }
        }
    }
    fn_80212814(pOldInfo);
    fn_80212814(pOldBones);
}
