#include "game/ResLoad.h"

struct Vector_8005406C {
    float mX;
    float mY;
    float mZ;
};

struct Object_8005406C {
    char mUnknown0[4];
    Vector_8005406C mScale;
};

extern "C" {
void *fn_800A336C(void);
int fn_800A3380(void);
void LevelMeshRelocate(void);
Vector_8005406C *fn_800A3438(void);
void fn_80227264(Vector_8005406C *pOut, Vector_8005406C *pV, float scale);
void LevelMeshPostLoad(Object_8005406C *pObject);
void LevelBuildWallInfo(void);
void LevelFreeWallInfo(void);

extern float lbl_8028DEAC[];
Object_8005406C *lbl_803EA550 = 0;
extern Object_8005406C *gLevelData;

void fn_8005406C(void)
{
    lbl_803EA550 = gLevelData = (Object_8005406C *)ResLoad(fn_800A336C(), fn_800A3380(), 1);
    LevelMeshRelocate();
    fn_80227264(fn_800A3438(), &gLevelData->mScale, lbl_8028DEAC[0]);
    LevelMeshPostLoad(gLevelData);
    LevelBuildWallInfo();
}

void fn_800540E0(void)
{
    LevelFreeWallInfo();
    ResUnLoad(fn_800A336C(), fn_800A3380());
    gLevelData = 0;
    lbl_803EA550 = 0;
}
}
