#include "game/bitstream.h"

extern "C" {
void fn_800B44D4(BitStream_t *pStream);
void fn_800B4628(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3, float t);
void fn_80030ACC(void (*pSave)(BitStream_t *pStream),
                 void (*pLoad)(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2,
                               BitStream_t *pStream3, float t),
                 int size, const char *pName);
}

extern "C" void fn_800B4A4C(void)
{
    fn_80030ACC(fn_800B44D4, fn_800B4628, 0x8C0, "Player Abilities");
}
