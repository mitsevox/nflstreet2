#ifndef GAME_EASEVECTOR_8013C9A4_H
#define GAME_EASEVECTOR_8013C9A4_H

#include "game/Interp_8013CC14.h"
#include "game/Object_80039F5C.h"

/* Three eased angles and an eased distance around mBase; fn_8013CAA4
   advances them and leaves the resulting point in mResult. */
struct EaseVector_8013C9A4 {
    Vector_80039F5C mBase;
    Interp_8013CC14 mX;
    Interp_8013CC14 mY;
    Interp_8013CC14 mZ;
    Vector_80039F5C mResult;
    Interp_8013CC14 mScale;
};

#endif
