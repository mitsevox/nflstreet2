#ifndef ENGINE_EAXADECF_H
#define ENGINE_EAXADECF_H

/* The EA-XA block decoder of src/engine/eaxadecf.cpp, used by the EA-XA unpack filters in
   src/engine/supxaf.cpp, src/engine/supxalf.cpp and src/engine/supxapf.cpp. */

namespace Snd {

/* The decode cursor handed to process_raw_block and decodexac: samples still to produce, the two
   filter history samples, the read position in the compressed data and the float output. */
struct MXAPACKETF {
    int mCount;
    float mPrev1;
    float mPrev2;
    unsigned char *mpSrc;
    float *mpDst;
};

/* The filter history saved and restored around a loop jump. */
struct XAFSTATE {
    float mPrev1;
    float mPrev2;
};

/* 168-byte decoder object. +0x0 and +0x14-+0x23 are not accessed by this file's functions. */
class CEAXABLKDecf {
public:
    static void *operator new(unsigned int size);
    static void operator delete(void *p);
    CEAXABLKDecf();
    int Feed(void *data, int size, int count);
    int Decode(float **dst, int count);
    XAFSTATE GetState();
    void SetState(XAFSTATE *state);

    unsigned char mUnknown0[4];
    int mBufferedCount;
    int mSamplesLeft;
    int mSize;
    float *mpBuffered;
    unsigned char mUnknown14[0x10];
    float mBuffer[28];
    MXAPACKETF mPacket;
};

void process_raw_block(MXAPACKETF *packet);
void decodexac(MXAPACKETF *packet);

}

#endif
