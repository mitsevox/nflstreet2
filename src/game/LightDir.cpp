/* Light direction callbacks of the level light sets: point a light along the
   level's light vector (or the opposite way, kept flat), plus the empty
   per-frame light update. */
#include "game/Object_80039F5C.h"

/* Object passed to the callbacks held in the .data blocks referenced by
   src/game/LevelLights.cpp; only the direction at +4 is accessed here. */
struct LightDirRecord {
    int mUnknown0;
    Vector_80039F5C mDir;
};

extern "C" {

void *fn_800A342C(void);
void fn_802271F0(float *pOut, float *pIn);

void LightDirUpdate(void)
{
}

void LightDirSetFromLevel(LightDirRecord *pObject)
{
    pObject->mDir.mX = ((Vector_80039F5C *)fn_800A342C())->mX;
    pObject->mDir.mY = ((Vector_80039F5C *)fn_800A342C())->mY;
    pObject->mDir.mZ = ((Vector_80039F5C *)fn_800A342C())->mZ;
}

void LightDirRefreshFromLevel(LightDirRecord *pObject)
{
    LightDirSetFromLevel(pObject);
}

/* Sets the direction to the negated 0x800A342C vector, then clears the z
   component before normalizing. */
void LightDirSetOppositeLevelFlat(LightDirRecord *pObject)
{
    pObject->mDir.mX = -((Vector_80039F5C *)fn_800A342C())->mX;
    pObject->mDir.mY = -((Vector_80039F5C *)fn_800A342C())->mY;
    pObject->mDir.mZ = -((Vector_80039F5C *)fn_800A342C())->mZ;
    pObject->mDir.mZ = 0.0f;
    fn_802271F0(&pObject->mDir.mX, &pObject->mDir.mX);
}
}
