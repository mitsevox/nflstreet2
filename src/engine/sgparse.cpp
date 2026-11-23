/* Reads GSTR patches into the sample records used by streamed game audio. */

#include "engine/sndbank.h"
#include "engine/sndsys.h"
#include <string.h>

extern "C" int SNDI_gettag(Parser_8027823C *tag);
extern "C" int SND_attrsetdef(SndSampleAttr_t *attr);

extern "C" void SNDI_patchtohdrgen(void *unused, unsigned char *patch, SndSampleFormat_t *format,
                                  SndSampleAttr_t *attr, SndSampleDesc_t *desc)
{
    int commonValues[0x2B];
    unsigned char *commonPayloads[0x2B];
    int sampleValues[0x2E];
    unsigned char *samplePayloads[0x2E];
    Parser_8027823C tag;
    int dataBlockCount = 0;
    int i;

    memset(format, 0, sizeof(*format));
    memset(attr, 0, sizeof(*attr));
    memset(desc, 0, sizeof(*desc));
    SND_attrsetdef(attr);

    tag.m0 = patch + 8;
    for (i = 0; i < 0x2B; i++) {
        commonPayloads[i] = 0;
    }
    for (i = 0; i < 0x2E; i++) {
        samplePayloads[i] = 0;
    }
    sampleValues[0x82 - 0x80] = 1;
    sampleValues[0x84 - 0x80] = 48000;
    sampleValues[0x85 - 0x80] = 0;
    sampleValues[0xA0 - 0x80] = 10;

    while (SNDI_gettag(&tag)) {
        if (tag.m4 <= 0x2A) {
            commonValues[tag.m4] = tag.m8;
            commonPayloads[tag.m4] = tag.mC;
            if (tag.m4 == 0x14) {
                attr->mDataBlocks[dataBlockCount] = tag.mC;
                attr->mDataBlockSizes[dataBlockCount] = tag.m10;
                dataBlockCount++;
            }
        } else if ((unsigned int)(tag.m4 - 0x80) > 0x2D) {
            if (tag.m4 != 0xFE) {
                continue;
            }
            break;
        } else {
            sampleValues[tag.m4 - 0x80] = tag.m8;
            samplePayloads[tag.m4 - 0x80] = tag.mC;
        }
    }

    format->mChannels = sampleValues[0x82 - 0x80];
    format->mCodec = sampleValues[0xA0 - 0x80];
    format->mRate = sampleValues[0x84 - 0x80];
    desc->mFrames = sampleValues[0x85 - 0x80];
    attr->m8 = 4;
    attr->m7 = 3;
    for (i = 0; i < format->mChannels; i++) {
        attr->mC[i] = lbl_803A6C24.m1D8[format->mChannels - 1][i];
    }
}
