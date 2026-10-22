#ifndef ENGINE_CU_801DA52C_H
#define ENGINE_CU_801DA52C_H

/* MAD decoder entry points shared by maddec.cpp (src/engine/cu_801DA52C.cpp), maddeca.cpp
   (src/engine/cu_801DB058.cpp), madidct.cpp (src/engine/cu_801DB21C.cpp) and the MAD codec. */

void fn_801DABE0(const unsigned short *pData, int frame, int quant);
void fn_801DAD20(const unsigned char *pRefY, const unsigned char *pRefU, const unsigned char *pRefV,
                 unsigned char *pDstY, unsigned char *pDstU, unsigned char *pDstV, int stride);

extern "C" {
int fn_801DB0B0(void);
void fn_801DB670(int *pOut, int stride);
}

#endif
