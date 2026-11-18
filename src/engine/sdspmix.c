/* DSP mixer (sdspmix.c): sets each hardware voice's mix, its aux buses and its channel volumes. */

#include "engine/sndlib.h"

static SndDrvMixChannel_t __MIXChannel[64];
static int numoutputchannels;

void SNDDRV_DSPMixerResetChannel(SndDrvMixChannel_t *voice)
{
    voice->m4 = 0x50000000;
    voice->m8 = 0;
    voice->mC = 0;
    voice->m10 = 0;
    voice->m34 = voice->m38 = voice->m3C = voice->m40 = voice->m44 = voice->m48 = voice->m4C = voice->m50 =
        voice->m54 = 0;
    voice->m30 = 0;
}

void SNDDRV_DSPMixerSetPan(AXVPB *vpb, float *p, unsigned short a, int b)
{
    SndDrvMixChannel_t *voice = &__MIXChannel[vpb->index];

    if (numoutputchannels == 4) {
        unsigned int index = a >> 8;

        // FAKEMATCH: both store orders below found by trying all 24 orders of each block
        if (b == 0) {
            voice->m3A = SNDDRV_dolbypl2balances[index][1];
            voice->m52 = SNDDRV_dolbypl2balances[index][3];
            voice->m4E = SNDDRV_dolbypl2balances[index][2];
            voice->m36 = SNDDRV_dolbypl2balances[index][0];
        } else {
            voice->m36 = 0;
            voice->m4E = 0;
            voice->m52 = 0;
            voice->m3A = 0;
        }
    } else {
        voice->m3A = p[0] * 32767.0f;
        voice->m36 = p[1] * 32767.0f;
    }
    voice->m4 |= 0x40000000;
}

void SNDDRV_DSPMixerSetAuxBus(AXVPB *vpb, unsigned short value, int which)
{
    SndDrvMixChannel_t *voice = &__MIXChannel[vpb->index];

    if (which == 1) {
        voice->m46 = value;
        voice->m42 = value;
        if (numoutputchannels == 4) {
            voice->m4A = value;
            voice->m56 = value;
        }
    } else if (which == 2) {
        voice->m52 = value;
        voice->m4E = value;
        if (numoutputchannels == 3) {
            voice->m56 = value;
        }
    }
    voice->m4 |= 0x40000000;
}

void SNDDRV_DSPMixerInit(int mode)
{
    int i;

    for (i = 0; i < 64; i++) {
        SNDDRV_DSPMixerResetChannel(&__MIXChannel[i]);
    }
    numoutputchannels = mode;
}

void SNDDRV_DSPMixerInitChannel(AXVPB *vpb, unsigned long flags, int volume, unsigned short aux, unsigned short unused,
                 float *p, unsigned short a, int b)
{
    SndDrvMixChannel_t *voice = &__MIXChannel[vpb->index];
    unsigned short mixerCtrl = 0;
    BOOL enabled;

    voice->m0 = vpb;
    voice->m4 = flags & 4;
    voice->m8 = volume;
    SNDDRV_DSPMixerSetAuxBus(vpb, aux, 1);
    voice->m40 = voice->m42;
    voice->m44 = voice->m46;
    voice->m48 = voice->m4A;
    SNDDRV_DSPMixerSetPan(vpb, p, a, b);
    voice->m34 = voice->m36;
    voice->m38 = voice->m3A;
    voice->m4C = voice->m4E;
    voice->m50 = voice->m52;
    if (voice->m4 & 4) {
        voice->m30 = 0;
    } else {
        voice->m30 = volume;
    }
    enabled = OSDisableInterrupts();
    vpb->pb.ve.currentVolume = voice->m30;
    vpb->pb.ve.currentDelta = 0;
    if ((vpb->pb.mix.vL = voice->m34) != 0) {
        mixerCtrl |= 0x1;
    }
    vpb->pb.mix.vDeltaL = 0;
    if ((vpb->pb.mix.vR = voice->m38) != 0) {
        mixerCtrl |= 0x2;
    }
    vpb->pb.mix.vDeltaR = 0;
    if ((vpb->pb.mix.vAuxAL = voice->m40) != 0) {
        mixerCtrl |= 0x10;
    }
    vpb->pb.mix.vDeltaAuxAL = 0;
    if ((vpb->pb.mix.vAuxAR = voice->m44) != 0) {
        mixerCtrl |= 0x20;
    }
    vpb->pb.mix.vDeltaAuxAR = 0;
    if ((vpb->pb.mix.vAuxBL = voice->m4C) != 0) {
        mixerCtrl |= 0x200;
    }
    vpb->pb.mix.vDeltaAuxBL = 0;
    if ((vpb->pb.mix.vAuxBR = voice->m50) != 0) {
        mixerCtrl |= 0x400;
    }
    vpb->pb.mix.vDeltaAuxBR = 0;
    if ((vpb->pb.mix.vAuxBS = voice->m54) != 0) {
        mixerCtrl |= 0x1000;
    }
    vpb->pb.mix.vDeltaAuxBS = 0;
    if ((vpb->pb.mix.vS = voice->m3C) != 0) {
        mixerCtrl |= 0x4;
    }
    vpb->pb.mix.vDeltaS = 0;
    if ((vpb->pb.mix.vAuxAS = voice->m48) != 0) {
        mixerCtrl |= 0x80;
    }
    vpb->pb.mixerCtrl = mixerCtrl;
    vpb->pb.mix.vDeltaAuxAS = 0;
    vpb->sync |= 0x212;
    OSRestoreInterrupts(enabled);
}

void SNDDRV_DSPMixerReleaseChannel(AXVPB *vpb)
{
    __MIXChannel[vpb->index].m0 = 0;
}

void SNDDRV_DSPMixerSetVol(AXVPB *vpb, int value)
{
    SndDrvMixChannel_t *voice = &__MIXChannel[vpb->index];

    voice->m8 = value;
    voice->m4 |= 0x10000000;
}

void SNDDRV_DSPMixerUpdate(void)
{
    int i;

    for (i = 0; i < 64; i++) {
        SndDrvMixChannel_t *voice = &__MIXChannel[i];
        AXVPB *vpb = voice->m0;
        int volumeChanged = 0;
        int mixChanged = 0;
        unsigned short mixerCtrl;

        if (vpb != 0) {
            mixerCtrl = 0;
            if (voice->m4 & 0x20000000) {
                voice->m4 &= ~0x20000000;
                volumeChanged = 1;
                voice->m30 = voice->m32;
            }
            if (voice->m4 & 0x10000000) {
                if (voice->m4 & 4) {
                    voice->m32 = 0;
                } else {
                    voice->m32 = voice->m8;
                }
                volumeChanged = 1;
                voice->m4 = (voice->m4 & ~0x10000000) | 0x20000000;
            }
            if (voice->m4 & 0x80000000) {
                mixChanged = 1;
                voice->m34 = voice->m36;
                voice->m38 = voice->m3A;
                voice->m3C = voice->m3E;
                voice->m40 = voice->m42;
                voice->m44 = voice->m46;
                voice->m48 = voice->m4A;
                voice->m4C = voice->m4E;
                voice->m50 = voice->m52;
                voice->m54 = voice->m56;
                voice->m4 &= ~0x80000000;
            }
            if (voice->m4 & 0x40000000) {
                voice->m4 = (voice->m4 & ~0x40000000) | 0x80000000;
                mixChanged = 1;
            }
            if (volumeChanged && vpb != 0) {
                vpb->pb.ve.currentVolume = voice->m32;
                vpb->pb.ve.currentDelta = 0;
                vpb->sync |= 0x200;
            }
            if (mixChanged) {
                if ((vpb->pb.mix.vL = voice->m34) != 0) {
                    mixerCtrl |= 0x1;
                }
                if ((vpb->pb.mix.vDeltaL = (voice->m36 - voice->m34) / 320) != 0) {
                    mixerCtrl |= 0x8;
                }
                if ((vpb->pb.mix.vR = voice->m38) != 0) {
                    mixerCtrl |= 0x2;
                }
                if ((vpb->pb.mix.vDeltaR = (voice->m3A - voice->m38) / 320) != 0) {
                    mixerCtrl |= 0x8;
                }
                if ((vpb->pb.mix.vAuxAL = voice->m40) != 0) {
                    mixerCtrl |= 0x10;
                }
                if ((vpb->pb.mix.vDeltaAuxAL = (voice->m42 - voice->m40) / 320) != 0) {
                    mixerCtrl |= 0x40;
                }
                if ((vpb->pb.mix.vAuxAR = voice->m44) != 0) {
                    mixerCtrl |= 0x20;
                }
                if ((vpb->pb.mix.vDeltaAuxAR = (voice->m46 - voice->m44) / 320) != 0) {
                    mixerCtrl |= 0x40;
                }
                if ((vpb->pb.mix.vAuxBL = voice->m4C) != 0) {
                    mixerCtrl |= 0x200;
                }
                if ((vpb->pb.mix.vDeltaAuxBL = (voice->m4E - voice->m4C) / 320) != 0) {
                    mixerCtrl |= 0x800;
                }
                if ((vpb->pb.mix.vAuxBR = voice->m50) != 0) {
                    mixerCtrl |= 0x400;
                }
                if ((vpb->pb.mix.vDeltaAuxBR = (voice->m52 - voice->m50) / 320) != 0) {
                    mixerCtrl |= 0x800;
                }
                if ((vpb->pb.mix.vAuxBS = voice->m54) != 0) {
                    mixerCtrl |= 0x1000;
                }
                if ((vpb->pb.mix.vDeltaAuxBS = (voice->m56 - voice->m54) / 320) != 0) {
                    mixerCtrl |= 0x2000;
                }
                if ((vpb->pb.mix.vS = voice->m3C) != 0) {
                    mixerCtrl |= 0x4;
                }
                if ((vpb->pb.mix.vDeltaS = (voice->m3E - voice->m3C) / 320) != 0) {
                    mixerCtrl |= 0x8;
                }
                if ((vpb->pb.mix.vAuxAS = voice->m48) != 0) {
                    mixerCtrl |= 0x80;
                }
                if ((vpb->pb.mix.vDeltaAuxAS = (voice->m4A - voice->m48) / 320) != 0) {
                    mixerCtrl |= 0x100;
                }
                if (lbl_803A6C24.m1C.m23 == 4) {
                    mixerCtrl |= 0x4000;
                }
                vpb->pb.mixerCtrl = mixerCtrl;
                vpb->sync |= 0x12;
            }
        }
    }
}
