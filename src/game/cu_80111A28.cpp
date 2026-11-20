#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80227638.h"

extern "C" {
extern const char lbl_8029E8F4[];
extern const char lbl_8029E8FC[];
int MathAngleDiff(int a, int b);
int CharSkelGetJointByName(void *p, const char *pName);
void fn_80227538(Point_8017886C *pOut, int angle, float magnitude);
void fn_80227248(void *pOut, void *p, float scale);
void fn_80227264(void *pOut, void *pV, float scale);
void fn_8022765C(void *pOut, void *pA, void *pB);
}

/* Where the player's hands reach after running length along angle: the
   step from his speed along angle (cut by 30 when angle differs from his
   facing, never below 0), plus the midpoint of his two wrists. */
extern "C" void CatchGetHandReach(Object_80039F5C *p, int angle, float length, Vector_80039F5C *pOut)
{
    Vector_80039F5C right;
    Vector_80039F5C left;
    int angles[4];
    Point_8017886C step;

    if (MathAngleDiff(angle, p->mMotion.mUnknown32) != 0) {
        length -= 30.0f;
        if (length < 0.0f) {
            length = 0.0f;
        }
    }
    fn_80227538(&step, angle, p->mMotion.mUnknown28);
    fn_80227248(pOut, &step, length);
    fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, lbl_8029E8F4), &right, angles);
    fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, lbl_8029E8FC), &left, angles);
    fn_8022765C(&right, &right, &left);
    fn_80227264(&right, &right, 0.5f);
    fn_80227638(pOut, pOut, &right);
}
