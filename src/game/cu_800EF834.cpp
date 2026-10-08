#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"

extern "C" {
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
float fn_801250B8(Object_80039F5C *p, int a, int b);

extern float lbl_803EAE10;
}

extern "C" int fn_800EF834(Object_80039F5C *p)
{
    int result = 0;

    if (fn_800AD9B4() == 3) {
        switch (p->mpState->mId) {
        case 5:
        case 10:
        case 11:
        case 15:
        case 16:
        case 17:
        case 25:
        case 26:
        case 27:
        case 34:
        case 35:
            result = 0;
            break;
        default:
            result = 1;
            break;
        }
        if (result && p->mUnknown1032 == 4) {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_800EF8E8(Object_80039F5C *p, int a)
{
    int result = 0;

    if (fn_800EF834(p)) {
        Message_800F01CC message;

        fn_800D0BF4(p, a, 36);
        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 36;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_800EFC34(Object_80039F5C *p, int a)
{
    return fn_801250B8(p, a, 6) < lbl_803EAE10;
}
