#include "game/Item_80097440.h"
#include "game/Team_80167A8C.h"

/* Comparison source of fn_80111A28 (0x80111A28-0x80111B4C) of the
   cu_800EFC68 grouping. When fn_801CFFD0(angle, +0x1C8 word) is nonzero,
   length drops by 30 (not below 0). fn_80227538 builds a pair from angle and
   the +0x1C4 float, fn_80227248 scales it by length into pOut, and half the
   sum of the "rwrist" and "lwrist" joint positions is added to pOut.
   Not registered in comparisons.json: its two joint-name strings sit at
   0x8029E8F4-0x8029E904, inside the pool slice of cu_80104C9C.cpp that
   fn_80105168 shares, so this body can only be measured once the whole
   cu_800EFC68 file links. fcmp compiles its .text byte-identical
   (relocations masked). */

extern "C" {
int fn_801CFFD0(int a, int b);
int fn_801C4E98(void *p, const char *pName);
void fn_8009BF5C(Object_80039F5C *p, int joint, Vector_80039F5C *pOut, void *pAngles);
void fn_80227538(Point_80167910 *pOut, int angle, float length);
void fn_80227248(void *pOut, void *pIn, float scale);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_80227638(void *pOut, void *pA, void *pB);
}

extern "C" void fn_80111A28(Object_80039F5C *p, int angle, float length, Vector_80039F5C *pOut) {
    Vector_80039F5C right;
    Vector_80039F5C left;
    Quat_801EB488 angles;
    Point_80167910 dir;

    if (fn_801CFFD0(angle, p->mMotion.mUnknown32) != 0) {
        length -= 30.0f;
        length = length < 0.0f ? 0.0f : length;
    }
    fn_80227538(&dir, angle, p->mMotion.mUnknown28);
    fn_80227248(pOut, &dir, length);
    fn_8009BF5C(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, "rwrist"), &right, &angles);
    fn_8009BF5C(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, "lwrist"), &left, &angles);
    fn_8022765C(&right, &right, &left);
    fn_80227264(&right, &right, 0.5f);
    fn_80227638(pOut, pOut, &right);
}
