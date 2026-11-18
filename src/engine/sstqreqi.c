/* Sound stream queue by request id (sstqreqi.c): queues a stream request that names an
   existing request id instead of a file. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_queuerequestid(int stream, int id, int offset)
{
    return fn_8026E160(stream, id, 0, offset, 2);
}

}
