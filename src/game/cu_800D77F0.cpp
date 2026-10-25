#include "game/bitstream.h"

extern "C" {
void fn_80030ACC(void (*pWrite)(BitStream_t *),
                 void (*pRead)(BitStream_t *, BitStream_t *, BitStream_t *, BitStream_t *, float),
                 unsigned int size, const char *pName);
void fn_800D760C(BitStream_t *pStream);
void fn_800D7708(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2,
                 BitStream_t *pStream3, float t);
}

extern "C" void fn_800D77F0(void)
{
    fn_80030ACC(fn_800D760C, fn_800D7708, 448, "Animations");
}
