#ifndef GAME_CAMEASEVEC_H
#define GAME_CAMEASEVEC_H

#include "game/CamInterp.h"
#include "game/Object_80039F5C.h"

/* Three eased angles and an eased distance around mBase; CamEaseVecUpdate
   advances them and leaves the resulting point in mResult. */
struct CamEaseVec_t {
    Vector_80039F5C mBase;
    CamInterp_t mX;
    CamInterp_t mY;
    CamInterp_t mZ;
    Vector_80039F5C mResult;
    CamInterp_t mScale;
};

#endif
