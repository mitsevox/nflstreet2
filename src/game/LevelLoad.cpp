/* Level load and unload: loads the level data resource, lays out its mesh
   lists, copies a vector from it scaled by ten and builds the wall table;
   unloading frees the wall table and the resource. */
#include "game/fn_801EF390.h"

struct LevelLoadVec3_t {
    float mX;
    float mY;
    float mZ;
};

/* The start of the loaded level data (LevelData_t in include/game/LevelData.h)
   as this file reads it: the three floats at +4. */
struct LevelLoadHeader_t {
    char mUnknown0[4];
    LevelLoadVec3_t mUnknown4;
};

extern "C" {
void *fn_800A336C(void);
int fn_800A3380(void);
void LevelMeshRelocate(LevelLoadHeader_t *pLevel);
LevelLoadVec3_t *fn_800A3438(void);
void fn_80227264(LevelLoadVec3_t *pOut, LevelLoadVec3_t *pV, float scale);
void LevelMeshPostLoad(LevelLoadHeader_t *pLevel);
void LevelBuildWallInfo(void);
void LevelFreeWallInfo(void);

LevelLoadHeader_t *_LevelLoad_pLevel = 0;
extern LevelLoadHeader_t *gLevelData;

void LevelLoad(void)
{
    gLevelData = _LevelLoad_pLevel = (LevelLoadHeader_t *)fn_801EF390(fn_800A336C(), fn_800A3380(), 1);
    LevelMeshRelocate(gLevelData);
    fn_80227264(fn_800A3438(), &gLevelData->mUnknown4, 10.0f);
    LevelMeshPostLoad(gLevelData);
    LevelBuildWallInfo();
}

void LevelUnload(void)
{
    LevelFreeWallInfo();
    fn_801F010C(fn_800A336C(), fn_800A3380());
    gLevelData = 0;
    _LevelLoad_pLevel = 0;
}
}
