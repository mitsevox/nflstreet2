/* Level load and unload: loads the level data resource, lays out its mesh
   lists, copies a vector from it scaled by ten and builds the wall table;
   unloading frees the wall table and the resource. */
#include "game/LevelData.h"
#include "game/fn_801EF390.h"

extern "C" {
void *fn_800A336C(void);
int fn_800A3380(void);
void LevelMeshRelocate(LevelData_t *pLevel);
Vector_80039F5C *fn_800A3438(void);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void LevelMeshPostLoad(LevelData_t *pLevel);
void LevelBuildWallInfo(void);
void LevelFreeWallInfo(void);

LevelData_t *_LevelLoad_pLevel = 0;
extern LevelData_t *gLevelData;

void LevelLoad(void)
{
    gLevelData = _LevelLoad_pLevel = (LevelData_t *)fn_801EF390(fn_800A336C(), fn_800A3380(), 1);
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
