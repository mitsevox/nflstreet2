/* Recognises the chunks of a movie file that belong to the MAD video codec. */

#include "engine/moviercmp.h"

/* Chunk identifiers handled by the MAD codec: 'MADm', 'MADe', 'MADk'. */
static const int ChunkTypes[3] = { 0x4D41446D, 0x4D414465, 0x4D41446B };

int MAD_CODEC_is_chunk_for_codec(int id)
{
    int i;

    for (i = 0; i < 3; i++) {
        if (ChunkTypes[i] == id) {
            return 1;
        }
    }
    return 0;
}
