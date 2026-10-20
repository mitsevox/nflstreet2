#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/cu_8008E978.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"

extern "C" {
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
Object_80039F5C *fn_8005A8AC(int index);
void fn_8004A230(unsigned char value);
void fn_80092F98(int handle);
int fn_80092830(int handle);
float fn_80178A2C(void);

extern Block_800AACD4 *lbl_803EAA88;
}

extern "C" void fn_800ABAF0(void)
{
    Message_800F01CC message;
    Object_80039F5C *pObject0;
    Object_80039F5C *pObject1;
    unsigned int i;

    fn_801C1F94(&message, 0, sizeof(message));
    message.mId = 9;
    message.mUnknown1[0] = 203;
    message.mUnknown1[1] = 0;
    message.mUnknown1[2] = 255;
    pObject0 = fn_8005A8AC(0);
    pObject1 = fn_8005A8AC(1);
    for (i = 0; i <= 1; i++) {
        unsigned int count = fn_80178D18((unsigned char)i);
        unsigned int index;

        for (index = 0; index < count; index++) {
            Object_80039F5C *p = fn_80039F5C((unsigned char)i, index);

            fn_800EFE60(0, p->mpState, p);
            if (p != pObject0 && p != pObject1) {
                p->mMotion.mPos.mX = 0.0f;
                p->mMotion.mPos.mY = fn_80178A2C();
                p->mpUnknown4->mUnknown20 &= ~1;
                fn_800F00D4(0, p->mpState, &message, p);
            }
        }
    }
    pObject1->mMotion.mPos.mX = 0.0f;
    pObject0->mMotion.mPos.mX = 0.0f;
    pObject1->mMotion.mPos.mY = 0.75f;
    pObject0->mMotion.mPos.mY = 0.75f;
    fn_8004A230(1);
    fn_80092F98(lbl_803EAA88->mUnknownC);
    lbl_803EAA88->mUnknown8 = lbl_803EAA88->mUnknownC;
    lbl_803EAA88->mUnknownC = -1;
    fn_80092830(lbl_803EAA88->mUnknown8);
    fn_80092830(lbl_803EAA88->mUnknown8);
}
