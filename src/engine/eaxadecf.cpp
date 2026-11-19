/* EA-XA block decoder (eaxadecf.cpp): decodes EA-XA compressed sample blocks (28 samples per block,
   a 4-bit predictor and shift per block, raw 16-bit blocks marked 0xEE) to floats for the EA-XA
   unpack filters. The decoder object keeps the samples of a partly consumed block for the next call
   and its two-sample filter history across loop jumps. */

#include "engine/sndsys.h"
#include "engine/sndutil.h"

namespace Snd {

/* Predictor pairs: [0] weights the previous sample, [1] the one before it. */
float xafilterf[2][4] = {
    { 0.0f, 0.9375f, 1.796875f, 1.53125f },
    { 0.0f, 0.0f, -0.8125f, -0.859375f }
};

/* Decoded nibble values per block shift: [shift][nibble] = (signed nibble << 12) >> shift as an integer (all 0 for shifts 13-15). */
float xatablef[16][16] = {
    { 0.0f, 4096.0f, 8192.0f, 12288.0f, 16384.0f, 20480.0f, 24576.0f, 28672.0f,
      -32768.0f, -28672.0f, -24576.0f, -20480.0f, -16384.0f, -12288.0f, -8192.0f, -4096.0f },
    { 0.0f, 2048.0f, 4096.0f, 6144.0f, 8192.0f, 10240.0f, 12288.0f, 14336.0f,
      -16384.0f, -14336.0f, -12288.0f, -10240.0f, -8192.0f, -6144.0f, -4096.0f, -2048.0f },
    { 0.0f, 1024.0f, 2048.0f, 3072.0f, 4096.0f, 5120.0f, 6144.0f, 7168.0f,
      -8192.0f, -7168.0f, -6144.0f, -5120.0f, -4096.0f, -3072.0f, -2048.0f, -1024.0f },
    { 0.0f, 512.0f, 1024.0f, 1536.0f, 2048.0f, 2560.0f, 3072.0f, 3584.0f,
      -4096.0f, -3584.0f, -3072.0f, -2560.0f, -2048.0f, -1536.0f, -1024.0f, -512.0f },
    { 0.0f, 256.0f, 512.0f, 768.0f, 1024.0f, 1280.0f, 1536.0f, 1792.0f,
      -2048.0f, -1792.0f, -1536.0f, -1280.0f, -1024.0f, -768.0f, -512.0f, -256.0f },
    { 0.0f, 128.0f, 256.0f, 384.0f, 512.0f, 640.0f, 768.0f, 896.0f,
      -1024.0f, -896.0f, -768.0f, -640.0f, -512.0f, -384.0f, -256.0f, -128.0f },
    { 0.0f, 64.0f, 128.0f, 192.0f, 256.0f, 320.0f, 384.0f, 448.0f,
      -512.0f, -448.0f, -384.0f, -320.0f, -256.0f, -192.0f, -128.0f, -64.0f },
    { 0.0f, 32.0f, 64.0f, 96.0f, 128.0f, 160.0f, 192.0f, 224.0f,
      -256.0f, -224.0f, -192.0f, -160.0f, -128.0f, -96.0f, -64.0f, -32.0f },
    { 0.0f, 16.0f, 32.0f, 48.0f, 64.0f, 80.0f, 96.0f, 112.0f,
      -128.0f, -112.0f, -96.0f, -80.0f, -64.0f, -48.0f, -32.0f, -16.0f },
    { 0.0f, 8.0f, 16.0f, 24.0f, 32.0f, 40.0f, 48.0f, 56.0f,
      -64.0f, -56.0f, -48.0f, -40.0f, -32.0f, -24.0f, -16.0f, -8.0f },
    { 0.0f, 4.0f, 8.0f, 12.0f, 16.0f, 20.0f, 24.0f, 28.0f,
      -32.0f, -28.0f, -24.0f, -20.0f, -16.0f, -12.0f, -8.0f, -4.0f },
    { 0.0f, 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f,
      -16.0f, -14.0f, -12.0f, -10.0f, -8.0f, -6.0f, -4.0f, -2.0f },
    { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
      -8.0f, -7.0f, -6.0f, -5.0f, -4.0f, -3.0f, -2.0f, -1.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }
};

void process_raw_block(MXAPACKETF *packet)
{
    short value;
    unsigned int i;

    // FAKEMATCH: each 16-bit read goes through its own block-scoped byte pointer (three blocks below)
    if (*packet->mpSrc == 0xEE) {
        packet->mpSrc++;
        {
            unsigned char *b = (unsigned char *)&value;
            b[0] = packet->mpSrc[0];
            b[1] = packet->mpSrc[1];
            packet->mpSrc += 2;
        }
        packet->mPrev1 = value;
        {
            unsigned char *b = (unsigned char *)&value;
            b[0] = packet->mpSrc[0];
            b[1] = packet->mpSrc[1];
            packet->mpSrc += 2;
        }
        packet->mPrev2 = value;
        for (i = 0; i < 28; i++) {
            {
                unsigned char *b = (unsigned char *)&value;
                b[0] = packet->mpSrc[0];
                b[1] = packet->mpSrc[1];
            }
            *packet->mpDst = value;
            packet->mpDst++;
            packet->mpSrc += 2;
        }
    }
}

void decodexac(MXAPACKETF *packet)
{
    unsigned char *src;
    float c1;
    float c2;
    int shift;
    int predictor;
    int i;
    unsigned char d;

    src = packet->mpSrc;
    packet->mpDst[-2] = packet->mPrev2;
    packet->mpDst[-1] = packet->mPrev1;
    while (packet->mCount > 0) {
        if (*src == 0xEE) {
            process_raw_block(packet);
            packet->mCount -= 28;
        } else {
            predictor = *packet->mpSrc >> 4;
            packet->mCount -= 28;
            c1 = xafilterf[0][predictor];
            c2 = xafilterf[1][predictor];
            shift = *packet->mpSrc & 0xF;
            packet->mpSrc++;
            for (i = 0; i < 14; i++) {
                d = packet->mpSrc[i];
                packet->mpDst[0] = xatablef[shift][d >> 4] + packet->mpDst[-1] * c1 + packet->mpDst[-2] * c2;
                packet->mpDst[1] = xatablef[shift][d & 0xF] + packet->mpDst[0] * c1 + packet->mpDst[-1] * c2;
                packet->mpDst += 2;
            }
            packet->mpSrc += 14;
            packet->mPrev2 = packet->mpDst[-2];
            packet->mPrev1 = packet->mpDst[-1];
        }
        src = packet->mpSrc;
    }
}

void *CEAXABLKDecf::operator new(unsigned int size)
{
    return CODANew(size);
}

void CEAXABLKDecf::operator delete(void *p)
{
    CODADelete(p);
}

CEAXABLKDecf::CEAXABLKDecf()
{
    // FAKEMATCH: store order found by search over the 120 orders of the five clearing stores
    mSize = 0;
    mSamplesLeft = 0;
    mBufferedCount = 0;
    mPacket.mPrev1 = 0.0f;
    mPacket.mPrev2 = 0.0f;
}

int CEAXABLKDecf::Feed(void *data, int size, int count)
{
    if (data == 0) {
        return -1;
    }
    if (mSamplesLeft != 0) {
        return -1;
    }
    mSamplesLeft = count;
    mSize = size;
    mPacket.mpSrc = (unsigned char *)data;
    return 0;
}

int CEAXABLKDecf::Decode(float **dst, int count)
{
    int done;
    int n;
    int k;
    int i;
    int blocks;
    int tail;
    float *save;

    done = 0;
    mPacket.mpDst = *dst;
    if (mSamplesLeft == 0) {
        return 0;
    }
    n = mSamplesLeft;
    if (n > count) {
        n = count;
    }
    if (mBufferedCount != 0) {
        if (mBufferedCount > n) {
            k = n;
        } else {
            k = mBufferedCount;
        }
        for (i = 0; i < k; i++) {
            *mPacket.mpDst = *mpBuffered;
            mPacket.mpDst++;
            mpBuffered++;
        }
        n -= k;
        mSamplesLeft -= k;
        mBufferedCount -= k;
        done = k;
    }
    blocks = n / 28 * 28;
    tail = n - blocks;
    mPacket.mCount = blocks;
    if (blocks > 0) {
        done += blocks;
        decodexac(&mPacket);
        mSamplesLeft -= blocks;
    }
    if (tail > 0) {
        save = mPacket.mpDst;
        mPacket.mCount = tail;
        mPacket.mpDst = mBuffer;
        // FAKEMATCH: loop index set before the decode call (keeps it in a saved register as the target does)
        i = 0;
        decodexac(&mPacket);
        mSamplesLeft -= tail;
        mpBuffered = mPacket.mpDst + mPacket.mCount;
        mBufferedCount = -mPacket.mCount;
        mPacket.mpDst -= 28;
        for (; i < tail; i++) {
            save[i] = mPacket.mpDst[i];
        }
        done += tail;
    }
    if (mSamplesLeft <= 0) {
        mBufferedCount = 0;
    }
    return done;
}

XAFSTATE CEAXABLKDecf::GetState()
{
    XAFSTATE state;

    state.mPrev1 = mPacket.mPrev1;
    state.mPrev2 = mPacket.mPrev2;
    return state;
}

void CEAXABLKDecf::SetState(XAFSTATE *state)
{
    mPacket.mPrev1 = state->mPrev1;
    mPacket.mPrev2 = state->mPrev2;
}

}
