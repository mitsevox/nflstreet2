/* Level data access: the loaded level, ground areas and surfaces, walls and markers, plus the
   game's simple message box. */
#include "game/LevelWallInfo.h"
#include "game/LevelData.h"
#include "game/LevelSurface.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80218FC4.h"



/* 12-byte text slot of _MsgBox_aText, filled by 0x800544A4. */
struct MsgBoxText_t {
    int mUnknown0;
    int mUnknown4;
    const char *mpUnknown8;
};

extern "C" {
LevelSurface_t *LevelMeshFindArea(float *pPos, int value);
int fn_801784C4(void);
void *fn_801D2BB0(int a, int size, int c, int d);
int fn_801CFE40(float y, float x);
unsigned int fn_801C3180(const char *pText);
void fn_802195E4(void *p, short a, short b);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);

extern void *gUISMainInfo;

LevelData_t *gLevelData = 0;
LevelWallInfo_t *gLevelWallInfo = 0;
MsgBoxText_t *_MsgBox_apText[3];
MsgBoxText_t _MsgBox_aText[3];

void LevelUpdate(void)
{
}

LevelData_t *LevelGetData(void)
{
    return gLevelData;
}

LevelSurface_t *LevelFindArea(float *pPos)
{
    return LevelMeshFindArea(pPos, 0);
}

void LevelSetSurface(int id, int value)
{
    unsigned int i;

    for (i = 0; i < gLevelData->mUnknown24; i++) {
        if (gLevelData->mUnknown28[i].mUnknown32 == id) {
            gLevelData->mUnknown28[i].mUnknown8 = value;
        }
    }
}

void LevelGetWallBase(LevelWall_t *pRecord, void *pFirst, void *pSecond)
{
    float *pA = (float *)pFirst;
    float *pB = (float *)pSecond;
    int foundA = 0;
    int foundB = 0;
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        if (pRecord->mUnknown12[i].mZ < 0.1f) {
            if (!foundA) {
                foundA = 1;
                pA[0] = pRecord->mUnknown12[i].mX;
                pA[1] = pRecord->mUnknown12[i].mY;
            } else {
                foundB = 1;
                pB[0] = pRecord->mUnknown12[i].mX;
                pB[1] = pRecord->mUnknown12[i].mY;
            }
        }
    }
    if (foundA && foundB && fn_801784C4()) {
        pA[0] = -pA[0];
        pA[1] = -pA[1];
        pB[0] = -pB[0];
        pB[1] = -pB[1];
    }
}

float LevelGetWallHeight(LevelWall_t *pRecord)
{
    float result = 0.0f;
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        if (pRecord->mUnknown12[i].mZ >= 0.1f) {
            result = pRecord->mUnknown12[i].mZ;
        }
    }
    return result;
}

void LevelGetQuadBase(LevelQuad_t *pPoints, float *pA, float *pB)
{
    int found = 0;
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        if (pPoints->mPoint[i].mZ < 0.1f) {
            if (!found) {
                found = 1;
                pA[0] = pPoints->mPoint[i].mX;
                pA[1] = pPoints->mPoint[i].mY;
            } else {
                pB[0] = pPoints->mPoint[i].mX;
                pB[1] = pPoints->mPoint[i].mY;
            }
        }
    }
}

float LevelGetQuadHeight(LevelQuad_t *pPoints)
{
    float result = 0.0f;
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        if (pPoints->mPoint[i].mZ >= 0.1f) {
            result = pPoints->mPoint[i].mZ;
        }
    }
    return result;
}

LevelMarker_t *LevelGetMarker(int id)
{
    LevelMarker_t *pEntry = 0;

    if (id < gLevelData->mUnknown152) {
        pEntry = &gLevelData->mUnknown156[id];
    }
    return pEntry;
}

int LevelGetObjectCount(void)
{
    LevelData_t *pLevel = gLevelData;
    int total = 0;

    if (pLevel != 0) {
        total = pLevel->mUnknown88 + pLevel->mUnknown104;
    }
    return total;
}

void LevelBuildWallInfo(void)
{
    unsigned int i = 0;
    unsigned int count = LevelGetData()->mUnknown136;
    LevelWall_t *pRecord = LevelGetData()->mUnknown140;

    gLevelWallInfo = (LevelWallInfo_t *)fn_801D2BB0(1, count * 12, 0, 0);
    for (; i < count; i++, pRecord++) {
        int angle;

        gLevelWallInfo[i].mUnknown0 = LevelGetWallHeight(pRecord);
        angle = fn_801CFE40(pRecord->mUnknown0.mY, pRecord->mUnknown0.mX);
        gLevelWallInfo[i].mUnknown4 = angle;
        gLevelWallInfo[i].mUnknown8 = (angle + 0x800000) & 0xFFFFFF;
    }
}

void LevelFreeWallInfo(void)
{
    fn_801D2BD0(gLevelWallInfo);
    gLevelWallInfo = 0;
}

void MsgBoxShow(const char *pTitle, const char *pText, const char *pButtons)
{
    _MsgBox_aText[0].mUnknown0 = 0;
    _MsgBox_aText[0].mpUnknown8 = pTitle;
    _MsgBox_aText[0].mUnknown4 = fn_801C3180(pTitle) + 1;
    _MsgBox_aText[1].mUnknown0 = 0;
    _MsgBox_aText[1].mpUnknown8 = pText;
    _MsgBox_aText[1].mUnknown4 = fn_801C3180(pText) + 1;
    _MsgBox_aText[2].mUnknown0 = 0;
    _MsgBox_aText[2].mpUnknown8 = pButtons;
    _MsgBox_aText[2].mUnknown4 = fn_801C3180(pButtons) + 1;
    _MsgBox_apText[0] = &_MsgBox_aText[0];
    _MsgBox_apText[1] = &_MsgBox_aText[1];
    _MsgBox_apText[2] = &_MsgBox_aText[2];
    fn_80218FC4(gUISMainInfo, 1, 3, 3, (int *)_MsgBox_apText);
    fn_802195E4(gUISMainInfo, 1, 3);
}

int MsgBoxIsClosed(void)
{
    unsigned short group;
    unsigned short screen;

    fn_80219650(gUISMainInfo, &group, &screen);
    return group != 1 || screen != 3;
}
}
