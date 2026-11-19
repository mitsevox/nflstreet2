/* MPEG-audio layer-3 decoder base class, derived from the MPEG-audio decoder base: only its
   destructor, which releases the layer-3 work buffer, remains in this build. */

#include "engine/sndlib.h"


CMpegLayer3Base::~CMpegLayer3Base()
{
    if (m1B0 != 0) {
        lbl_803B53E8(m1B0);
    }
}
