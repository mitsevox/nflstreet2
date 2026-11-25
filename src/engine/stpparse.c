/* Decodes one tagged timbre from a sound-bank patch into a playback header. */

#include "engine/sndbank.h"
#include "engine/sndsys.h"

extern "C" {

int SNDI_gettag(Parser_8027823C *tag);

static SndEnvStage_t snddefaultenvelope = {0x7FFFFFFF, 127};

int SNDI_parsetimbre(char **cursor, SNDIPATCHHEADER *header)
{
    long patchValues[0x2B];
    unsigned char *patchPayloads[0x2B];
    int sampleValues[0x2E];
    unsigned char *samplePayloads[0x2E];
    int azimuths[6] = { 0 };
    Parser_8027823C tag;
    int i;
    int more;

    tag.m0 = (unsigned char *)*cursor;
    header->mTimbreStart = (char *)tag.m0;
    for (i = 0; i < 0x2B; i++) {
        patchPayloads[i] = 0;
    }
    for (i = 0; i < 0x2E; i++) {
        samplePayloads[i] = 0;
    }
    for (i = 0; i < 6; i++) {
        header->mChannelDataBlocks[i] = 0;
        header->mChannelDataBlockSizes[i] = 0;
    }
    for (i = 0; i < 6; i++) {
        header->mAdpcmCoefficients[i] = 0;
        header->mAdpcmLoopState[i] = 0;
    }

    patchValues[0x01] = 0;
    patchValues[0x02] = 127;
    patchValues[0x03] = 0;
    patchValues[0x04] = 127;
    patchValues[0x06] = 0;
    patchValues[0x07] = 60;
    patchValues[0x08] = -1;
    patchValues[0x09] = 1;
    patchValues[0x0A] = 0;
    patchValues[0x0C] = 64;
    patchValues[0x0D] = 0;
    patchValues[0x0E] = 127;
    patchValues[0x0F] = 0;
    patchValues[0x10] = 0;
    patchValues[0x11] = 0;
    patchValues[0x12] = 0;
    patchValues[0x13] = 0;
    header->mUserDataCount = 0;
    patchValues[0x17] = 0;
    patchValues[0x19] = (long)&snddefaultenvelope;
    patchValues[0x1A] = 0;
    patchValues[0x1C] = 127;
    patchValues[0x26] = 0;
    patchValues[0x27] = 0;
    patchValues[0x28] = 0;
    patchValues[0x29] = 0;
    patchValues[0x2A] = 0;
    patchValues[0x1D] = 0;
    patchValues[0x1E] = 0;
    patchValues[0x1F] = 0;
    patchValues[0x20] = 0;
    patchValues[0x21] = 0;
    patchValues[0x22] = 0;
    patchValues[0x23] = 0;

    sampleValues[0x80 - 0x80] = 2;
    sampleValues[0x82 - 0x80] = 1;
    sampleValues[0x84 - 0x80] = 24000;
    sampleValues[0x87 - 0x80] = -1;
    sampleValues[0xA7 - 0x80] = 0;
    sampleValues[0xA0 - 0x80] = 7;
    sampleValues[0x8C - 0x80] = 0x200;
    patchValues[0x24] = 0;
    patchValues[0x25] = 1;
    sampleValues[0x85 - 0x80] = 0;
    sampleValues[0x86 - 0x80] = -1;
    sampleValues[0x88 - 0x80] = 0;
    sampleValues[0x9C - 0x80] = 0;
    sampleValues[0x89 - 0x80] = 0;
    sampleValues[0x9D - 0x80] = 0;
    sampleValues[0x94 - 0x80] = 0;
    sampleValues[0x9E - 0x80] = 0;
    sampleValues[0x95 - 0x80] = 0;
    sampleValues[0x9F - 0x80] = 0;
    sampleValues[0xA2 - 0x80] = 0;
    sampleValues[0xA6 - 0x80] = 0;
    sampleValues[0xA3 - 0x80] = 0;

    more = 0;
    while (SNDI_gettag(&tag)) {
        if (tag.m4 <= 0x2A) {
            patchValues[tag.m4] = tag.m8;
            patchPayloads[tag.m4] = tag.mC;
            if (tag.m4 == 0x14) {
                header->mUserDataPayloads[header->mUserDataCount] = tag.mC;
                header->mUserDataSizes[header->mUserDataCount] = tag.m10;
                header->mUserDataCount++;
            }
        } else if ((unsigned int)(tag.m4 - 0x80) <= 0x2D) {
            sampleValues[tag.m4 - 0x80] = tag.m8;
            samplePayloads[tag.m4 - 0x80] = tag.mC;
            if (tag.m4 == 0x98) {
                header->mChannelDataBlocks[0] = tag.mC;
                header->mChannelDataBlockSizes[0] = tag.m10;
            } else if (tag.m4 == 0x99) {
                header->mChannelDataBlocks[1] = tag.mC;
                header->mChannelDataBlockSizes[1] = tag.m10;
            } else if (tag.m4 == 0x9A) {
                header->mChannelDataBlocks[2] = tag.mC;
                header->mChannelDataBlockSizes[2] = tag.m10;
            } else if (tag.m4 == 0x9B) {
                header->mChannelDataBlocks[3] = tag.mC;
                header->mChannelDataBlockSizes[3] = tag.m10;
            } else if (tag.m4 == 0xA4) {
                header->mChannelDataBlocks[4] = tag.mC;
                header->mChannelDataBlockSizes[4] = tag.m10;
            } else if (tag.m4 == 0xA5) {
                header->mChannelDataBlocks[5] = tag.mC;
                header->mChannelDataBlockSizes[5] = tag.m10;
            }
        } else if (tag.m4 == 0xFE) {
            more = 1;
            break;
        }
    }

    header->m8 = patchValues[0x01];
    header->m9 = patchValues[0x02];
    header->mA = patchValues[0x03];
    header->mB = patchValues[0x04];
    header->mC = patchValues[0x06];
    header->mD = patchValues[0x07];
    header->mE = patchValues[0x08];
    header->mF = patchValues[0x09];
    header->m10 = patchValues[0x0A];
    header->m11 = patchValues[0x0C];
    header->m12 = patchValues[0x0D];
    header->m14 = patchValues[0x0E];
    header->m15 = patchValues[0x0F];
    header->m4 = patchValues[0x10];
    header->m6 = patchValues[0x11];
    header->m20 = (unsigned long)patchPayloads[0x12] + patchValues[0x12];
    header->unk_0x16 = patchValues[0x13];
    header->m24 = (signed char *)((unsigned long)patchPayloads[0x17] + patchValues[0x17]);
    header->m28 = (SndEnvStage_t *)((unsigned long)patchPayloads[0x19] + patchValues[0x19]);
    header->mChannelRelativeOffsets[0] = patchValues[0x1A];
    header->mChannelRelativeOffsets[1] = patchValues[0x26];
    header->mChannelRelativeOffsets[2] = patchValues[0x27];
    header->mChannelRelativeOffsets[3] = patchValues[0x28];
    header->mChannelRelativeOffsets[4] = patchValues[0x29];
    header->mChannelRelativeOffsets[5] = patchValues[0x2A];
    header->m1A = patchValues[0x1C];
    header->m2C = (unsigned long)patchPayloads[0x1D] + patchValues[0x1D];
    header->m1B = patchValues[0x1E];
    header->m1C = patchValues[0x1F];
    header->m30 = (signed char *)((unsigned long)patchPayloads[0x20] + patchValues[0x20]);
    header->m1D = patchValues[0x21];
    header->m54 = patchValues[0x22];
    header->mUnknown2 = sampleValues[0x80 - 0x80];
    header->m13 = sampleValues[0xA0 - 0x80];
    header->m56 = sampleValues[0x84 - 0x80];
    header->m58 = sampleValues[0x85 - 0x80];
    header->mLoopStart = sampleValues[0x86 - 0x80];
    header->m60 = sampleValues[0x87 - 0x80];
    header->m18 = sampleValues[0x8C - 0x80];
    header->m64 = (int *)samplePayloads[0x8A - 0x80];
    header->m68 = sampleValues[0x88 - 0x80];
    header->m1E = patchValues[0x23];
    header->m0 = patchValues[0x24];
    header->mUnknown1F = patchValues[0x25];
    azimuths[0] = sampleValues[0x9C - 0x80];
    header->mOtherChannelOffsets[0] = sampleValues[0x89 - 0x80];
    azimuths[1] = sampleValues[0x9D - 0x80];
    header->m3 = sampleValues[0x82 - 0x80];
    header->mOtherChannelOffsets[1] = sampleValues[0x94 - 0x80];
    azimuths[2] = sampleValues[0x9E - 0x80];
    header->mOtherChannelOffsets[2] = sampleValues[0x95 - 0x80];
    azimuths[3] = sampleValues[0x9F - 0x80];
    azimuths[4] = sampleValues[0xA6 - 0x80];
    azimuths[5] = sampleValues[0xA7 - 0x80];
    header->mOtherChannelOffsets[3] = sampleValues[0xA2 - 0x80];
    header->mOtherChannelOffsets[4] = sampleValues[0xA3 - 0x80];
    header->mAdpcmCoefficients[0] = samplePayloads[0x8F - 0x80];
    header->mAdpcmCoefficients[1] = samplePayloads[0x90 - 0x80];
    header->mAdpcmLoopState[0] = (Loop_80273DF8 *)samplePayloads[0x8D - 0x80];
    header->mAdpcmLoopState[1] = (Loop_80273DF8 *)samplePayloads[0x8E - 0x80];
    if (header->m3 > 2) {
        header->mAdpcmCoefficients[2] = samplePayloads[0x91 - 0x80];
        header->mAdpcmLoopState[2] = (Loop_80273DF8 *)samplePayloads[0x8B - 0x80];
    }
    if (header->m3 > 3) {
        header->mAdpcmCoefficients[3] = samplePayloads[0xAB - 0x80];
        header->mAdpcmLoopState[3] = (Loop_80273DF8 *)samplePayloads[0xA8 - 0x80];
    }
    if (header->m3 > 4) {
        header->mAdpcmCoefficients[4] = samplePayloads[0xAC - 0x80];
        header->mAdpcmLoopState[4] = (Loop_80273DF8 *)samplePayloads[0xA9 - 0x80];
    }
    if (header->m3 > 5) {
        header->mAdpcmCoefficients[5] = samplePayloads[0xAD - 0x80];
        header->mAdpcmLoopState[5] = (Loop_80273DF8 *)samplePayloads[0xAA - 0x80];
    }
    for (i = 0; i < header->m3; i++) {
        if (lbl_803A772C == 1 && header->m3 == 2) {
            azimuths[i] = 0;
        }
        header->mBC[i] = lbl_803A6C24.m1D8[header->m3 - 1][i] + azimuths[i];
    }
    *cursor = (char *)tag.m0;
    return more;
}

}
