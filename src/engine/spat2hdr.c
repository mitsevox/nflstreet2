/* Decodes the tagged sound bank patches used by the game's audio into sample headers. */

#include "engine/sndbank.h"
#include "engine/sndsys.h"
#include <string.h>

extern "C" {

int SNDI_gettag(Parser_8027823C *tag);
int SND_attrsetdef(SndSampleAttr_t *attr);
void fn_80278328(void *unused, unsigned char *patch, SndSampleFormat_t *format, SndSampleAttr_t *attr,
                 SndSampleDesc_t *desc);

void SNDI_patchtohdr(BankVer_t *bank, unsigned char *patch, SndSampleFormat_t *format, SndSampleAttr_t *attr,
                     SndSampleDesc_t *desc, unsigned char *isStream)
{
    Parser_8027823C tag;
    int channel;
    int dataBlockCount = 0;
    int flags = 0x200;
    const unsigned int *streamAddress = 0;

    memset(format, 0, sizeof(*format));
    memset(attr, 0, sizeof(*attr));
    memset(desc, 0, sizeof(*desc));
    if (!(patch[0] == 'P' && patch[1] == 'T') &&
        patch[0] == 'G' && patch[1] == 'S' && patch[2] == 'T' && patch[3] == 'R') {
        fn_80278328(0, patch, format, attr, desc);
        if (isStream) {
            *isStream = 1;
        }
        return;
    }
    if (isStream) {
        *isStream = 0;
    }
    SND_attrsetdef(attr);
    tag.m0 = patch + 4;
    format->mRate = 24000;
    format->mChannels = 1;
    format->mCodec = 7;
    desc->mFrames = 0;

    while (SNDI_gettag(&tag)) {
        if (tag.m4 == 0xA0) {
            format->mCodec = tag.m8;
        } else if (tag.m4 == 0x9C) {
            attr->mC[0] = tag.m8;
        } else if (tag.m4 == 0x9D) {
            attr->mC[1] = tag.m8;
        } else if (tag.m4 == 0x9E) {
            attr->mC[2] = tag.m8;
        } else if (tag.m4 == 0x9F) {
            attr->mC[3] = tag.m8;
        } else if (tag.m4 == 0xA6) {
            attr->mC[4] = tag.m8;
        } else if (tag.m4 == 0xA7) {
            attr->mC[5] = tag.m8;
        } else if (tag.m4 == 0x98) {
            attr->m18[0] = SNDMEMI_allocz(tag.m10);
            SNDI_memcpy(attr->m18[0], tag.mC, tag.m10);
            attr->m30[0] = tag.m10;
        } else if (tag.m4 == 0x99) {
            attr->m18[1] = SNDMEMI_allocz(tag.m10);
            SNDI_memcpy(attr->m18[1], tag.mC, tag.m10);
            attr->m30[1] = tag.m10;
        } else if (tag.m4 == 0x9A) {
            attr->m18[2] = SNDMEMI_allocz(tag.m10);
            SNDI_memcpy(attr->m18[2], tag.mC, tag.m10);
            attr->m30[2] = tag.m10;
        } else if (tag.m4 == 0x9B) {
            attr->m18[3] = SNDMEMI_allocz(tag.m10);
            SNDI_memcpy(attr->m18[3], tag.mC, tag.m10);
            attr->m30[3] = tag.m10;
        } else if (tag.m4 == 0xA4) {
            attr->m18[4] = SNDMEMI_allocz(tag.m10);
            SNDI_memcpy(attr->m18[4], tag.mC, tag.m10);
            attr->m30[4] = tag.m10;
        } else if (tag.m4 == 0xA5) {
            attr->m18[5] = SNDMEMI_allocz(tag.m10);
            SNDI_memcpy(attr->m18[5], tag.mC, tag.m10);
            attr->m30[5] = tag.m10;
        } else if (tag.m4 == 0x80) {
            attr->m7 = tag.m8;
        } else if (tag.m4 == 0x82) {
            format->mChannels = tag.m8;
        } else if (tag.m4 == 0x84) {
            format->mRate = tag.m8;
        } else if (tag.m4 == 0x85) {
            desc->mFrames = tag.m8;
        } else if (tag.m4 == 0x8A) {
            streamAddress = (const unsigned int *)tag.mC;
        } else if (tag.m4 == 0x13) {
            attr->m5 = tag.m8;
        } else if (tag.m4 == 0x0A) {
            attr->m6 = tag.m8;
        } else if (tag.m4 == 0x06) {
            attr->m2 = tag.m8;
        } else if (tag.m4 == 0x8C) {
            flags = tag.m8;
        } else if (tag.m4 == 0x88) {
            desc->mChannelData[0] = tag.m8;
        } else if (tag.m4 == 0x89) {
            desc->mChannelData[1] = tag.m8;
        } else if (tag.m4 == 0x94) {
            desc->mChannelData[2] = tag.m8;
        } else if (tag.m4 == 0x95) {
            desc->mChannelData[3] = tag.m8;
        } else if (tag.m4 == 0xA2) {
            desc->mChannelData[4] = tag.m8;
        } else if (tag.m4 == 0xA3) {
            desc->mChannelData[5] = tag.m8;
        } else if (tag.m4 == 0x14) {
            attr->mDataBlocks[dataBlockCount] = tag.mC;
            attr->mDataBlockSizes[dataBlockCount] = tag.m10;
            dataBlockCount++;
        }
    }

    attr->m8 = flags;
    for (channel = format->mChannels - 1; channel >= 0; channel--) {
        if (lbl_803A772C == 1 && format->mChannels == 2) {
            attr->mC[channel] = 0;
        }
        attr->mC[channel] = lbl_803A6C24.m1D8[format->mChannels - 1][channel] + attr->mC[channel];
        if ((attr->m8 & 4) || attr->m8 == 0) {
            desc->mChannelData[channel] = (unsigned int)bank + desc->mChannelData[channel];
        }
        if ((attr->m8 & 0x308) && streamAddress) {
            if (channel == 0) {
                desc->mChannelData[channel] = *streamAddress;
            } else {
                desc->mChannelData[channel] = *streamAddress + (desc->mChannelData[channel] - desc->mChannelData[0]);
            }
        }
    }
}

}
