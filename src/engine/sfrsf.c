/* Sound filter (sfrsf.c): the resampling filter's pitch setter. The resampler and its init are not
   reconstructed yet. */

#include "engine/sndsys.h"

extern "C" {

void SFILTER_rsfsetpitch(Node_80279D90 *node, int value)
{
    ((SndRsfState_t *)node)->m1C = value;
}

}
