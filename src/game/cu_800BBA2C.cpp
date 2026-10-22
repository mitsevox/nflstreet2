#include "game/Object_80039F5C.h"
#include "game/fn_80178D18.h"

extern "C" {
int fn_800BA6F8(void);
void fn_8016DDDC(int team);
void fn_801475F4(void);
}

extern "C" void fn_800BBA2C(void)
{
    unsigned int count;
    unsigned short i;

    if (!fn_800BA6F8()) {
        count = fn_80178D18(0);
        for (i = 0; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C(0, i);
            Block_80170E64 *pBody;

            p->mMotion.mPos.mX = 55.0f;
            p->mMotion.mPos.mY = -100.0f;
            pBody = p->mpUnknown4;
            pBody->mUnknown4.mY = -100.0f;
            pBody->mUnknown4.mX = 55.0f;
            pBody->mUnknown20 &= ~1;
        }
        count = fn_80178D18(1);
        for (i = 0; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C(1, i);
            Block_80170E64 *pBody;

            p->mMotion.mPos.mX = 55.0f;
            p->mMotion.mPos.mY = -100.0f;
            pBody = p->mpUnknown4;
            pBody->mUnknown4.mY = -100.0f;
            pBody->mUnknown4.mX = 55.0f;
            pBody->mUnknown20 &= ~1;
        }
    } else {
        fn_8016DDDC(0);
        fn_8016DDDC(1);
        fn_801475F4();
    }
}
