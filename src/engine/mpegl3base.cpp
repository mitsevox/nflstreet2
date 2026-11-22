/* Releases the MPEG Layer III decoder's work buffer when the sound library destroys the decoder. */

#include "engine/sndlib.h"
#include "engine/sndutil.h"

CMpegLayer3Base::~CMpegLayer3Base()
{
    if (mpWorkBuffer != 0) {
        Snd::CODADelete(mpWorkBuffer);
    }
}
