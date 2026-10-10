#include "game/Object_80039F5C.h"

/* Object passed to the callbacks held in the .data blocks referenced by
   src/game/cu_8019B460.cpp; only the direction at +4 is accessed here. */
struct Object_8019B36C {
    int mUnknown0;
    Vector_80039F5C mDir;
};

extern "C" {

void *fn_800A342C(void);
void fn_802271F0(float *pOut, float *pIn);

void fn_8019B368(void)
{
}

void fn_8019B36C(Object_8019B36C *pObject)
{
    pObject->mDir.mX = ((Vector_80039F5C *)fn_800A342C())->mX;
    pObject->mDir.mY = ((Vector_80039F5C *)fn_800A342C())->mY;
    pObject->mDir.mZ = ((Vector_80039F5C *)fn_800A342C())->mZ;
}

void fn_8019B3B8(Object_8019B36C *pObject)
{
    fn_8019B36C(pObject);
}

/* Sets the direction to the negated 0x800A342C vector, then clears the z
   component before normalizing. */
void fn_8019B3D8(Object_8019B36C *pObject)
{
    pObject->mDir.mX = -((Vector_80039F5C *)fn_800A342C())->mX;
    pObject->mDir.mY = -((Vector_80039F5C *)fn_800A342C())->mY;
    pObject->mDir.mZ = -((Vector_80039F5C *)fn_800A342C())->mZ;
    pObject->mDir.mZ = 0.0f;
    fn_802271F0(&pObject->mDir.mX, &pObject->mDir.mX);
}
}
