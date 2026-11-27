#ifndef ENGINE_MADDEC_H
#define ENGINE_MADDEC_H

/* MAD decoder entry points shared by maddec.cpp (src/engine/maddec.cpp), maddeca.cpp
   (src/engine/maddeca.cpp), madidct.cpp (src/engine/madidct.cpp) and the MAD codec. */

void MAD_initdecode(const unsigned short *pData, int frame, int quant);
void MAD_decodemacroblock(const unsigned char *pRefY, const unsigned char *pRefU, const unsigned char *pRefV,
                          unsigned char *pDstY, unsigned char *pDstU, unsigned char *pDstV, int stride);

extern "C" {
int madvlcdecode(void);
void idctcompute(int *pOut, int stride);
}

#endif
