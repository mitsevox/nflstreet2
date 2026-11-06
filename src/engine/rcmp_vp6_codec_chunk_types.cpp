/* Recognises the header and frame chunks of a movie file that belong to the VP6 video codec. */

#include "engine/moviercmp.h"

/* VP6 chunk identifiers: 'MVhd' (header), 'MV0F' and 'MV0K' (frames). */

int VP6_CODEC_is_head_chunk_for_codec(int id)
{
    return id == 0x4D566864;
}

int VP6_CODEC_is_chunk_for_codec(int id)
{
    if (id == 0x4D563046 || id == 0x4D56304B) {
        return 1;
    }
    return 0;
}
