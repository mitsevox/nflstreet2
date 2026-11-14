/* Sound driver (snddrv.c): the audio callback, mixer start-up and restore, ARAM transfers and the
   platform start, stop and service routines. */

#include "engine/sndlib.h"


void fn_8027257C(void)
{
    int i;

    if (lbl_803A8D60.mC049 != 0) {
        for (i = 0; i < 48; i++) {
            if (lbl_803A8D60.m0[i].m1F != 0) {
                AXFreeVoice(lbl_803A8D60.m0[i].m3C);
                lbl_803A8D60.m0[i].m1F = 0;
                lbl_803A8D60.mC049--;
                lbl_803A8D60.m0[i].m3C = 0;
                if (lbl_803A8D60.mC049 == 0) {
                    break;
                }
            }
        }
    }
}

void fn_80272618(int value)
{
    fn_8026A0E8(value + lbl_803A6C24.m1C.m12);
}

void fn_80272644(AXVPB *vpb)
{
    Record_803A6DF0 *records = lbl_803A6C24.m1CC;
    Record_803A6DF0 *record = &records[vpb->userContext];
    int index;
    int i;

    if (record->m28 == -1) {
        index = vpb->userContext;
    } else {
        index = record->m28;
    }
    record = &records[index];
    for (i = 0; i < record->m23; i++) {
        int channel = record->m4[i];

        if (lbl_803A8D60.m0[channel].m3C != 0) {
            if (channel == vpb->userContext) {
                fn_80272990(channel, 1);
            } else {
                fn_80272990(channel, 2);
            }
            lbl_803A8D60.m0[record->m4[i]].m24 = 0;
        }
    }
}

int fn_8027271C(int index)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    float pitch = record->m48 * (float)record->m5F;
    unsigned short volume = (int)(record->m48 * (*record->m64 * 32767.0f));
    int i;
    int j;

    for (i = 0; i < record->m23; i++) {
        int priority;
        AXVPB *vpb;

        if (record->m2A == 101) {
            priority = 31;
        } else {
            priority = (unsigned char)(record->m2A / 3);
        }
        if (priority <= 0) {
            priority = 1;
        } else if (priority > 31) {
            priority = 30;
        }
        vpb = AXAcquireVoice(priority, (void (*)(void *))fn_80272644, record->m4[i]);
        lbl_803A8D60.m0[record->m4[i]].m3C = vpb;
        if (vpb != 0) {
            int rear;

            lbl_803A8D60.m0[record->m4[i]].m25 = 0;
            if (i > 4) {
                rear = 1;
                volume = 0;
            } else {
                rear = 0;
            }
            fn_80277A60(record->m1C, lbl_803A8D60.m0[record->m4[i]].m0);
            SNDDRV_DSPMixerInitChannel(lbl_803A8D60.m0[record->m4[i]].m3C, 0, (int)(pitch * 258.0f), volume, 0,
                                       lbl_803A8D60.m0[record->m4[i]].m0, record->m1C, rear);
        } else {
            lbl_803A8D60.m0[record->m4[i]].m25 = 1;
            if (i > 0) {
                for (j = i; j >= 0; j--) {
                    if (lbl_803A8D60.m0[record->m4[j]].m3C != 0) {
                        AXFreeVoice(lbl_803A8D60.m0[record->m4[j]].m3C);
                        lbl_803A8D60.m0[record->m4[j]].m25 = 1;
                        lbl_803A8D60.m0[record->m4[j]].m3C = 0;
                    }
                    if (lbl_803A6C24.m1CC[record->m4[j]].m6D != 0) {
                        fn_8026A0E8(record->m4[j]);
                    }
                }
            }
            return 0;
        }
    }
    return 1;
}

void fn_80272990(int channel, int mode)
{
    Channel_803A8D60 *state = &lbl_803A8D60.m0[channel];
    AXVPB *vpb = state->m3C;
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[channel];

    SNDDRV_DSPMixerReleaseChannel(vpb);
    state->m18 = -1;
    if (record->m6D != 0) {
        fn_8026A0E8(channel);
    }
    if (mode == 0) {
        if (vpb != 0) {
            AXFreeVoice(vpb);
            state->m3C = 0;
        }
    } else if (mode == 2) {
        if (state->m25 == 0 && vpb != 0) {
            state->m1F = 1;
            lbl_803A8D60.mC049++;
        }
    } else if (mode == 1) {
        if (state->m1F == 1) {
            state->m1F = 0;
            lbl_803A8D60.mC049--;
        }
        state->m3C = 0;
    }
    if (state->m25 == 0) {
        state->m25 = 1;
    }
}

int fn_80272AA4(int key)
{
    int i;
    BOOL enabled = OSDisableInterrupts();

    for (i = 0; i < 64; i++) {
        if (lbl_803A8D60.m9E30[i].m0 == -1) {
            break;
        }
    }
    lbl_803A8D60.m9E30[i].m0 = key;
    OSRestoreInterrupts(enabled);
    return i;
}

void fn_80272B30(u32 request)
{
    int i;

    lbl_803A8D60.m9DE8 = ((ARQRequest *)request)->owner;
    for (i = 0; i < 64; i++) {
        if (lbl_803A8D60.m9E30[i].m0 == ((ARQRequest *)request)->owner) {
            lbl_803A8D60.m9E30[i].m0 = -1;
            return;
        }
    }
}

int fn_80272B7C(u32 priority, u32 source, u32 dest, u32 length, int slot)
{
    BOOL enabled = OSDisableInterrupts();
    int index;
    u32 owner;

    if (slot == -1) {
        index = fn_80272AA4(lbl_803A8D60.m9DEC);
        owner = lbl_803A8D60.m9DEC;
        lbl_803A8D60.m9E30[index].m24 = priority;
        lbl_803A8D60.m9E30[index].m28 = source;
        lbl_803A8D60.m9E30[index].m2C = dest;
        lbl_803A8D60.m9E30[index].m30 = OSRoundUp32B(length);
        lbl_803A8D60.m9E30[index].m34 = lbl_803A6C24.m170;
    } else {
        index = slot;
        owner = lbl_803A8D60.m9E30[index].m0;
    }
    ARQPostRequest(&lbl_803A8D60.m9E30[index].m4, owner, ARQ_TYPE_MRAM_TO_ARAM, priority, source, dest,
                   OSRoundUp32B(length), fn_80272B30);
    OSRestoreInterrupts(enabled);
    return lbl_803A8D60.m9DEC++;
}

void fn_80272C9C(int key)
{
    int i;
    BOOL enabled = OSDisableInterrupts();

    for (i = 0; i < 64; i++) {
        if (lbl_803A8D60.m9E30[i].m0 == key) {
            ARQRemoveRequest(&lbl_803A8D60.m9E30[i].m4);
            fn_80272B7C(lbl_803A8D60.m9E30[i].m24, lbl_803A8D60.m9E30[i].m28, lbl_803A8D60.m9E30[i].m2C,
                        lbl_803A8D60.m9E30[i].m30, i);
        }
    }
    OSRestoreInterrupts(enabled);
}

void fn_80272D34(void **buffers, void *unused)
{
    BOOL enabled = OSEnableInterrupts();
    int i;
    int j;

    if (lbl_803A8D60.mC048 != 0) {
        for (i = 0; i < lbl_8030002C; i++) {
            if (lbl_803B4E34.m14[i] != 0) {
                float *dst = fn_802753F0(i);
                int *src = (int *)buffers[0];

                lbl_803A8D40 = dst;
                for (j = 0; j < 160; j++) {
                    dst[j] = src[j];
                }
            }
        }
        if (lbl_803A6C24.m1C.m23 <= 3) {
            SNDI_memcpy(buffers[1], lbl_803A8D60.mC068[0], 640);
            SNDI_memcpy(buffers[0], lbl_803A8D60.mC068[1], 640);
        } else {
            SNDI_memcpy(buffers[1], lbl_803A8D60.mC068[0], 640);
            SNDI_memcpy(buffers[2], lbl_803A8D60.mC068[2], 640);
            SNDI_memcpy(buffers[0], lbl_803A8D60.mC068[3], 640);
            SNDI_memcpy(buffers[3], lbl_803A8D60.mC068[1], 640);
        }
    }
    OSWakeupThread(&lbl_803A8D60.m1DE0);
    lbl_80300850++;
    OSRestoreInterrupts(enabled);
}

void fn_80272EC4(void)
{
    Setup_80272EC4 setup;
    int i;

    SNDSYS_linkmaincpumixer();
    setup.m8 = lbl_803A6C24.m1C.mE;
    if (lbl_803A6C24.m1C.m23 != 1) {
        setup.m9 = lbl_803A6C24.m1C.m23;
    } else {
        setup.m9 = 2;
    }
    setup.m0 = lbl_803A6C24.m1C.mA;
    setup.m4 = fn_80272618;
    setup.mA = 0;
    lbl_803B5028(&setup);
    SNDSYS_entercritical();
    for (i = 0; i < setup.m9; i++) {
        void *buffer = SNDMEMI_allocz(672);

        lbl_803A8D60.mC050[i] = buffer;
        lbl_803A8D60.mC068[i] = (void *)OSRoundUp32B(buffer);
    }
    SNDSYS_leavecritical();
    lbl_803A8D60.mC048 = 1;
}

void fn_80272FB4(void)
{
    int i;

    lbl_803A8D60.mC048 = 0;
    SNDSYS_entercritical();
    for (i = 0; i < lbl_803A6C24.m1C.m23; i++) {
        SNDMEMI_free(lbl_803A8D60.mC050[i]);
    }
    SNDSYS_leavecritical();
    lbl_803B502C();
}

int fn_802733A0(void)
{
    u32 base;

    lbl_803A6C24.m6 = 32;
    lbl_803A6C24.m0 = 32000;
    lbl_803A6C24.m2 = 32000;
    lbl_803A6C24.m4 = 1;
    lbl_803A6C24.m5 = 4;
    lbl_803A6C24.mA = 48;
    lbl_803A6C24.mC = 2;
    lbl_803A6C24.mE = 544;
    lbl_803A6C24.m10 = 36;
    lbl_803A6C24.m1C.mA = 32000;
    lbl_803A6C24.m1C.mE = 8;
    lbl_803A6C24.m1C.m12 = 48;
    lbl_803A6C24.m1C.m21 = 1;
    lbl_803A6C24.m1C.m22 = 8;
    lbl_803A6C24.m1C.m23 = 2;
    lbl_803A6C24.m1C.m25 = 1;
    lbl_803A6C24.m1C.m28 = 2;
    lbl_803A6C24.m1C.m2A[0] = 544;
    lbl_803A6C24.m1C.m2A[1] = 36;
    base = ARGetBaseAddress() + 256;
    lbl_803A6C24.m1C.m38 = base;
    lbl_803A6C24.m1C.m3C = 0x800000 - base;
    return 0;
}

void fn_80273040(int index, Stream_802743A0 *stream, Record_803A6DF0 *record)
{
    unsigned char *source[6];
    int length;
    int b;
    int remaining = 1536;
    int chunk;
    int rest;
    int i;

    do {
        if (stream->m25C4[0] == 0) {
            for (i = 0; i < record->m23; i++) {
                stream->m25C4[i] = fn_802792F0(index, i, &length, &b);
            }
            stream->m25E0 = 0;
            stream->m25DC = length * 2;
        }
        chunk = remaining;
        if (stream->m25C4[0] != 0) {
            int available = stream->m25DC - stream->m25E0;

            if (available <= 0) {
                stream->m25C4[0] = 0;
                continue;
            }
            if (remaining > available) {
                chunk = available;
            }
            stream->m25B8[stream->m2599] += chunk >> 1;
            rest = remaining - chunk;
            for (i = 0; i < record->m23; i++) {
                source[i] = stream->m25C4[i] + stream->m25E0;
            }
            stream->m25E0 += chunk;
        } else {
            rest = 0;
            for (i = 0; i < record->m23; i++) {
                source[i] = lbl_803A8D60.m1AC0;
            }
        }
        for (i = 0; i < record->m23; i++) {
            SNDI_memcpy(stream->m2580[i] + (1536 - remaining), source[i], chunk);
        }
        remaining = rest;
    } while (remaining > 0);
    for (i = 0; i < record->m23; i++) {
        DCFlushRange(stream->m2580[i], 1536);
        fn_80272B7C(1, (u32)stream->m2580[i], (u32)stream->m259C[i] + stream->m2599 * 1536, 1536, -1);
    }
}

void *fn_80273264(void *arg)
{
    for (;;) {
        SNDSYSI_mutexlockfn();
        if (lbl_803A6C24.m220 != 0) {
            lbl_803A6C24.m220();
        }
        if (lbl_803A8D60.mC048 != 0) {
            lbl_803B5030(lbl_803A8D60.mC068, 160);
            fn_80279598();
        }
        if (lbl_80300850 & 1) {
            SNDSYSI_100hzserver();
            lbl_80300854 += lbl_803A8D60.m1400;
            SNDSYSI_timertick = (int)(lbl_80300854 < 0.0f ? lbl_80300854 - 0.5f : lbl_80300854 + 0.5f);
            if (lbl_80300854 > 30.0f) {
                lbl_80300854 -= 30.0f;
            }
            SNDSYSI_variabletimerservice();
        }
        if (lbl_803A6C24.m224 != 0) {
            lbl_803A6C24.m224();
        }
        SNDSYSI_mutexunlockfn();
        OSSleepThread(&lbl_803A8D60.m1DE0);
    }
}

int fn_80273458(void)
{
    Params_803A6C40 params = lbl_803A6C24.m1C;

    if (lbl_803A6C24.m168 != 0) {
        lbl_803A6C24.m1C = lbl_803A6C24.mCC;
    }
    params.mA = 32000;
    if (params.m23 < lbl_803A6C24.m4) {
        params.m23 = lbl_803A6C24.m4;
    }
    if (params.m23 > lbl_803A6C24.m5) {
        params.m23 = lbl_803A6C24.m5;
    }
    if (params.mE > lbl_803A6C24.m6) {
        params.mE = lbl_803A6C24.m6;
    }
    if (params.m12 > lbl_803A6C24.mA) {
        params.m12 = lbl_803A6C24.mA;
    }
    if (params.m22 > 32) {
        params.m22 = 32;
    }
    if (lbl_803A6C24.m168 != 0) {
        return 0;
    }
    lbl_803A6C24.m16C = params.mE + params.m12;
    lbl_803A6C24.m1C = params;
    return 0;
}

int fn_80273648(int mode)
{
    float rate;
    int i;

    SNDDRV_DSPMixerInit(lbl_803A6C24.m1C.m23);
    lbl_803A7644 = lbl_803A6C24.m1C.m14;
    if (lbl_803A7644 == -1.0f) {
        lbl_803A7644 = 20.0f;
    }
    rate = lbl_803A7644 < 10.0f ? 10.0f : (lbl_803A7644 <= 100.0f ? lbl_803A7644 : 100.0f);
    lbl_803A7644 = rate;
    lbl_803A8D60.m1400 = 10.0f / rate;
    if (lbl_803A6C24.m1C.m21 != 0 && lbl_80300858 == 0) {
        ARInit(0, 0);
        ARQInit();
        lbl_80300858 = 1;
    }
    for (i = 0; i < 64; i++) {
        lbl_803A8D60.m9E30[i].m0 = -1;
    }
    if (mode == 0) {
        if (lbl_803A6C24.mB8 == 0 || lbl_803A6C24.mBC == 0) {
            unsigned int count = lbl_803A6C24.m1C.m22;

            if (count > lbl_803A6C24.m1C.m12) {
                count = lbl_803A6C24.m1C.m12;
            }
            fn_8027981C(lbl_803A6C24.m1C.m8 + (count + 2));
            fn_8027986C(lbl_803A6C24.m1C.m38, lbl_803A6C24.m1C.m3C);
        }
        lbl_803A8D60.m1404 = fn_80275150(0, 1280);
        lbl_803A8D60.m1408 = (u32)lbl_803A8D60.m1404 >> 1;
        lbl_803A8D60.m140C = (u32)lbl_803A8D60.m1404 << 1;
        lbl_803A8D60.m1AC0 = (unsigned char *)OSRoundUp32B(lbl_803A8D60.m14A0);
        fn_80272B7C(1, (u32)lbl_803A8D60.m1AC0, (u32)lbl_803A8D60.m1404, 1280, -1);
        fn_80272B7C(1, (u32)lbl_803A8D60.m1AC0, ARGetBaseAddress(), 256, -1);
    }
    AIInit(0);
    AXInit();
    AXSetCompressor(0);
    if (lbl_803A6C24.m1C.m23 > 2) {
        AXSetMode(2);
        lbl_803A6C24.m1C.m23 = 4;
    } else {
        AXSetMode(0);
    }
    for (i = 0; i < 48; i++) {
        Channel_803A8D60 *channel = &lbl_803A8D60.m0[i];

        channel->m18 = -1;
        channel->m24 = 0;
        channel->m1F = 0;
        channel->m1C = -1;
        channel->m3C = 0;
        channel->m25 = 1;
    }
    for (i = 0; i < lbl_803A6C24.m1C.m28; i++) {
        if ((lbl_803A6C24.m1C.m2A[i] & 4) && lbl_803A8D60.mC048 == 0) {
            fn_80272EC4();
            break;
        }
    }
    lbl_803A8D60.mC049 = 0;
    OSCreateThread(&lbl_803A8D60.m1AC8, fn_80273264, 0, lbl_803A8D60.m1DE8 + sizeof(lbl_803A8D60.m1DE8),
                   sizeof(lbl_803A8D60.m1DE8), 1, 1);
    OSInitThreadQueue(&lbl_803A8D60.m1DE0);
    OSResumeThread(&lbl_803A8D60.m1AC8);
    AXRegisterAuxACallback(fn_80272D34, 0);
    lbl_803A6C24.m168 = 1;
    return 0;
}

int fn_80273960(int flag)
{
    AXRegisterAuxACallback(0, 0);
    if (lbl_803A8D60.mC048 != 0) {
        fn_80272FB4();
    }
    if (flag == 0) {
        fn_802798C0();
    }
    while (lbl_803A6C24.m169 != 0) {
        SNDSYS_leavecritical();
    }
    OSCancelThread(&lbl_803A8D60.m1AC8);
    AXQuit();
    return 0;
}

void fn_802739F8(void)
{
    AXPBADPCM adpcm;
    AXPBADPCMLOOP loop;
    AXPBADDR addr;
    int i;
    int j;

    for (i = 0; i < lbl_803A6C24.m1C.m22; i++) {
        Stream_802743A0 *stream = lbl_803A8D60.m1410[i];
        Channel_803A8D60 *channel;
        Record_803A6DF0 *record;
        AXVPB *vpb;
        int position;
        int half;

        if (stream == 0 || stream->m2598 < 0) {
            continue;
        }
        channel = &lbl_803A8D60.m0[stream->m2598];
        record = &lbl_803A6C24.m1CC[stream->m2598];
        if (!(stream->m259A & 0x80)) {
            stream->m259A--;
            if (stream->m259A & 0x80) {
                addr.format = 10;
                adpcm.gain = 2048;
                addr.loopFlag = 1;
                memset(&loop, 0, sizeof(loop));
                fn_80274B50(stream->m2598);
                for (j = 0; j < record->m23; j++) {
                    u32 address;
                    u32 loopAddress;
                    u32 endAddress;

                    fn_80274960(record->m4[j]);
                    fn_802747D8(record->m4[j]);
                    address = (u32)stream->m259C[j];
                    loopAddress = address >> 1;
                    endAddress = (address + 3070) >> 1;
                    AXSetVoiceAdpcm(lbl_803A8D60.m0[record->m4[j]].m3C, &adpcm);
                    AXSetVoiceAdpcmLoop(lbl_803A8D60.m0[record->m4[j]].m3C, &loop);
                    addr.endAddressHi = endAddress >> 16;
                    addr.endAddressLo = endAddress;
                    addr.loopAddressHi = loopAddress >> 16;
                    addr.loopAddressLo = loopAddress;
                    addr.currentAddressHi = loopAddress >> 16;
                    addr.currentAddressLo = loopAddress;
                    AXSetVoiceAddr(lbl_803A8D60.m0[record->m4[j]].m3C, &addr);
                    AXSetVoiceState(lbl_803A8D60.m0[record->m4[j]].m3C, 1);
                    lbl_803A8D60.m0[record->m4[j]].m24 = 1;
                }
            }
        }
        vpb = channel->m3C;
        if (vpb == 0) {
            continue;
        }
        position = (vpb->pb.addr.currentAddressHi << 16) + vpb->pb.addr.currentAddressLo;
        half = position > stream->m25B4;
        if (half != stream->m2599) {
            if (stream->m25B8[stream->m2599] != 0) {
                for (j = 0; j < record->m23; j++) {
                    SNDPKTPLAYI_freeframes(i, j, stream->m25B8[stream->m2599]);
                }
                stream->m25B8[stream->m2599] = 0;
            }
            fn_80273040(i, stream, record);
            stream->m2599 = half;
        }
    }
    fn_80279598();
    for (i = 0; i < lbl_803A6C24.m1C.m12; i++) {
        Channel_803A8D60 *channel = &lbl_803A8D60.m0[i];
        Record_803A6DF0 *record = &lbl_803A6C24.m1CC[i];
        AXVPB *vpb = channel->m3C;

        if (vpb != 0 && channel->m24 != 0 && vpb->pb.state == 0 && channel->m18 >= 0 && channel->m24 == 1) {
            for (j = 0; j < lbl_803A6C24.m1CC[i].m23; j++) {
                if (lbl_803A8D60.m0[record->m4[j]].m24 != 0) {
                    fn_80272990(record->m4[j], 0);
                    lbl_803A8D60.m0[record->m4[j]].m24 = 0;
                }
            }
        }
    }
    fn_8027257C();
    SNDDRV_DSPMixerUpdate();
}

void fn_80273D7C(u32 flags, int *a, int *b)
{
    if (flags & 0x200) {
        *a = 0;
        *b = lbl_803A6C24.m1C.m12;
    } else if (flags & 4) {
        *a = lbl_803A6C24.m1C.m12;
        *b = lbl_803A6C24.m16C;
    }
}

int fn_80273DC0(Struct_80270E04 *p, int value, int *base)
{
    if (*base == 0) {
        *base = p->m68;
    }
    *p->m64 = value + (p->m68 - *base);
    return 0;
}

int fn_80273DF8(Header_80273DF8 *header, int base, int index, int a, int b, int c)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    Channel_803A8D60 *channel = &lbl_803A8D60.m0[index];
    AXPBADDR addr;
    AXPBADPCM adpcm;
    AXPBADPCMLOOP loop;
    u32 size = 0;
    u32 offset = 0;
    u32 loopStart;
    u32 loopEnd;
    int i;

    record->m20 = header->m56;
    record->m14 = header->m58;
    record->m23 = header->m3;
    if (record->m24 & 0x200) {
        memset(&loop, 0, sizeof(loop));
        if (header->m60 >= 0) {
            addr.loopFlag = 1;
            loopEnd = header->m60;
            loopStart = header->m5C;
        } else {
            addr.loopFlag = 0;
            if (record->m22 == 18) {
                loopStart = lbl_803A8D60.m140C;
            } else {
                loopStart = lbl_803A8D60.m1408;
            }
            loopEnd = header->m58 - 1;
        }
        if (record->m22 == 18) {
            size = (header->m58 + 13) / 14 * 14;
            addr.format = 0;
            adpcm.gain = 0;
            adpcm.yn1 = 0;
            adpcm.yn2 = 0;
            loopEnd = loopEnd * 8 / 7;
            loopStart = loopStart * 8 / 7;
            size = size * 8 / 7;
            offset = *header->m64 << 1;
        } else if (record->m22 == 7) {
            addr.format = 10;
            adpcm.gain = 2048;
            size = header->m58;
            offset = *header->m64 >> 1;
        }
        channel->m18 = offset;
        if (fn_8027271C(index) == 0) {
            return -9;
        }
        for (i = 0; i < record->m23; i++) {
            fn_80274960(record->m4[i]);
            fn_802747D8(record->m4[i]);
        }
        fn_80274B50(index);
        fn_80271BD4(record->m4[0], 0);
        for (i = 0; i < header->m3; i++) {
            u32 start;
            u32 loopAddress;
            u32 endAddress;

            if (record->m22 == 18) {
                SNDI_memcpy(&adpcm, header->mC8[i], 32);
                adpcm.pred_scale = header->mC8[i][32];
                if (header->m60 > 0) {
                    loop.loop_pred_scale = header->mE0[i]->m4;
                    loop.loop_yn1 = header->mE0[i]->m0;
                    loop.loop_yn2 = header->mE0[i]->m2;
                }
            }
            start = offset + size * i;
            loopAddress = loopStart;
            if (header->m60 > 0) {
                loopAddress = start + loopStart;
            }
            endAddress = start + loopEnd - 2;
            if (record->m22 == 18) {
                start += 2;
                if ((loopAddress & 15) == 0) {
                    loopAddress += 2;
                } else if ((loopAddress & 15) == 1) {
                    loopAddress += 1;
                }
                if ((endAddress & 15) == 0) {
                    endAddress += 2;
                } else if ((endAddress & 15) == 1) {
                    endAddress += 1;
                }
            }
            AXSetVoiceSrcType(lbl_803A8D60.m0[record->m4[i]].m3C, 1);
            AXSetVoiceAdpcm(lbl_803A8D60.m0[record->m4[i]].m3C, &adpcm);
            AXSetVoiceAdpcmLoop(lbl_803A8D60.m0[record->m4[i]].m3C, &loop);
            addr.currentAddressHi = start >> 16;
            addr.loopAddressHi = loopAddress >> 16;
            addr.endAddressHi = endAddress >> 16;
            addr.endAddressLo = endAddress;
            addr.currentAddressLo = start;
            addr.loopAddressLo = loopAddress;
            AXSetVoiceAddr(lbl_803A8D60.m0[record->m4[i]].m3C, &addr);
            AXSetVoiceState(lbl_803A8D60.m0[record->m4[i]].m3C, 1);
            lbl_803A8D60.m0[record->m4[i]].m24 = 1;
        }
    } else {
        for (i = 0; i < record->m23; i++) {
            MIX_playinit(record->m4[i] - lbl_803A6C24.m1C.m12, header->m13, 1, base + header->m68[i],
                        base + header->m68[0] + header->m80[i], header->m98[i], record->m23, record->m14, header->m5C,
                        header->m60, 0, 0, header->m2, i);
            fn_80274960(record->m4[i]);
        }
        fn_80274B50(record->m4[0]);
        for (i = 0; i < lbl_8030002C; i++) {
            fn_80271BD4(record->m4[0], i);
        }
        fn_80274CA8(record->m4[0], a);
        fn_80274D34(record->m4[0], b);
        fn_80274E24(record->m4[0], c);
        for (i = 0; i < record->m23; i++) {
            fn_80276194(record->m4[i] - lbl_803A6C24.m1C.m12);
        }
    }
    return 0;
}

int fn_80274304(int index)
{
    Record_803A6DF0 *record;

    index += lbl_803A6C24.m1C.m12;
    record = &lbl_803A6C24.m1CC[index];
    if (record->m28 == -1) {
        return index;
    }
    return record->m28;
}

int fn_80274334(int index)
{
    Record_803A6DF0 *records = lbl_803A6C24.m1CC;
    Record_803A6DF0 *record;
    int i;

    index += lbl_803A6C24.m1C.m12;
    record = &records[index];
    if (record->m28 == -1) {
        return 0;
    }
    record = &records[record->m28];
    for (i = 1; i < 6; i++) {
        if (record->m4[i] == index) {
            return i;
        }
    }
    return 0;
}

int fn_80274398(void)
{
    return sizeof(Stream_802743A0);
}

int fn_802743A0(int index, Stream_802743A0 *stream)
{
    int i;

    memset(stream, 0, sizeof(Stream_802743A0));
    stream->m259C[0] = (unsigned char *)fn_80275150(0, 0x4800);
    if (stream->m259C[0] == 0) {
        return -9;
    }
    for (i = 0; i < 6; i++) {
        stream->m259C[i] = stream->m259C[0] + i * 0xC00;
        stream->m2580[i] = (unsigned char *)OSRoundUp32B(stream->m0[i]);
    }
    stream->m2598 = -1;
    lbl_803A8D60.m1410[index] = stream;
    return 0;
}

int fn_80274464(int stream, int index, int a, int b, int c, Info_80274464 *info, Struct_80274464 *p)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    int i;

    record->m14 = 0;
    record->m20 = info->m0;
    lbl_803A8D60.m0[index].m1C = stream;
    record->m23 = info->m2;
    if (record->m24 & 4) {
        for (i = 0; i < record->m23; i++) {
            lbl_803B5034(record->m4[i] - lbl_803A6C24.m1C.m12, record->m22, 0, 0, 0, p->m18[i], record->m23, 0, -1,
                         -1, 0, 0, p->m7, i);
        }
        fn_80274B50(record->m4[0]);
        for (i = 0; i < record->m23; i++) {
            fn_80274960(record->m4[i]);
            fn_802747D8(record->m4[i]);
        }
        fn_80274CA8(record->m4[0], a);
        fn_80274D34(record->m4[0], b);
        fn_80274E24(record->m4[0], c);
        for (i = 0; i < record->m23; i++) {
            lbl_803B5038(record->m4[i] - lbl_803A6C24.m1C.m12);
        }
    } else {
        Stream_802743A0 *block = lbl_803A8D60.m1410[stream];

        for (i = 0; i < 6; i++) {
            block->m25B8[i] = 0;
        }
        block->m25C4[0] = 0;
        block->m259A = 2;
        block->m2599 = 1;
        block->m2598 = index;
        block->m259B = info->m2;
        fn_8027271C(index);
        for (i = 0; i < info->m2; i++) {
            u32 loopAddress = (u32)block->m259C[i] >> 1;
            u32 endAddress = ((u32)block->m259C[i] + 3070) >> 1;

            if (i == 0) {
                block->m25B4 = (loopAddress + endAddress) >> 1;
            }
            memset(block->m2580[i], 0, 1536);
            DCFlushRange(block->m2580[i], 1536);
            fn_80272B7C(1, (u32)block->m2580[i], (u32)block->m259C[i], 1536, -1);
            AXSetVoiceSrcType(lbl_803A8D60.m0[record->m4[i]].m3C, 1);
            lbl_803A8D60.m0[record->m4[i]].m24 = 1;
        }
    }
    return 0;
}

int fn_8027474C(int index)
{
    Stream_802743A0 *stream = lbl_803A8D60.m1410[index];
    int i;

    fn_80275194(0, stream->m259C[0]);
    for (i = 0; i < 6; i++) {
        stream->m259C[i] = 0;
    }
    lbl_803A8D60.m1410[index] = 0;
    return 0;
}

int fn_802747D0(void)
{
    return -15;
}

void fn_802747D8(int index)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    Channel_803A8D60 *channel = &lbl_803A8D60.m0[index];
    float volume;
    int count;
    int i;

    if (record->m24 & 0x200) {
        volume = record->m48 * (float)record->m5F;
        SNDDRV_DSPMixerSetVol(lbl_803A8D60.m0[index].m3C, (int)(volume * 258.0f));
    } else {
        volume = record->m48 * (float)record->m5F * (1.0f / 127.0f);
        count = lbl_803A6C24.m1C.m23;
        if (count == 1) {
            count = 2;
        }
        for (i = 0; i < count; i++) {
            fn_80276378(index - lbl_803A6C24.m1C.m12, i, volume * channel->m0[i]);
        }
    }
}

void fn_80274924(int index)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];

    if ((record->m24 & 0x200) || (record->m24 & 4)) {
        fn_802747D8(index);
    }
}

void fn_80274960(int index)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    Channel_803A8D60 *channel = &lbl_803A8D60.m0[index];
    int i;

    if (record->m4E != 0) {
        for (i = 0; i < lbl_803A7728; i++) {
            channel->m0[i] = 0.0f;
        }
    } else if (lbl_803A772C == 0) {
        channel->m0[0] = 0.70710683f;
        channel->m0[1] = 0.70710683f;
        channel->m0[2] = 0.0f;
        channel->m0[3] = 0.0f;
        channel->m0[4] = 0.0f;
        channel->m0[5] = 0.0f;
    } else {
        fn_80277A60(record->m1C, channel->m0);
    }
    if ((record->m24 & 4) && lbl_803A6C24.m1C.m23 > 2 && record->m4E == 0) {
        int pan = record->m1C >> 8;

        channel->m0[0] = (unsigned int)SNDDRV_dolbypl2balances[pan][1] * (1.0f / 32767.0f);
        channel->m0[1] = (unsigned int)SNDDRV_dolbypl2balances[pan][3] * (1.0f / 32767.0f);
        channel->m0[2] = (unsigned int)SNDDRV_dolbypl2balances[pan][2] * (1.0f / 32767.0f);
        channel->m0[5] = 0.0f;
        channel->m0[3] = (unsigned int)SNDDRV_dolbypl2balances[pan][0] * (1.0f / 32767.0f);
    }
    if (record->m24 & 0x200) {
        SNDDRV_DSPMixerSetPan(channel->m3C, channel->m0, record->m1C, record->m4E);
    } else {
        fn_802747D8(index);
    }
}

int fn_80274B50(int index)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    unsigned int pitch;
    int i;

    if (record->m24 & 0x200) {
        float ratio;

        pitch = (record->m20 << 12) / lbl_803A6C24.m1C.mA;
        pitch = pitch * record->m8E >> 12;
        ratio = pitch * (1.0f / 4096.0f);
        for (i = 0; i < record->m23; i++) {
            AXVPB *vpb = lbl_803A8D60.m0[record->m4[i]].m3C;

            if (vpb == 0) {
                return -8;
            }
            AXSetVoiceSrcRatio(vpb, ratio);
        }
    } else {
        pitch = (record->m20 << 15) / lbl_803A6C24.m1C.mA;
        pitch = pitch * record->m8E >> 11;
        for (i = 0; i < record->m23; i++) {
            lbl_803B5040(record->m4[i] - lbl_803A6C24.m1C.m12, pitch);
        }
    }
    return 0;
}

int fn_80274CA8(int index, int value)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    int i;

    if (record->m24 & 4) {
        for (i = 0; i < record->m23; i++) {
            MIX_settimemult(record->m4[i] - lbl_803A6C24.m1C.m12, value);
        }
    }
    return 0;
}

void fn_80274D34(int index, int value)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    int i;

    if (record->m24 & 4) {
        float cutoff = (float)value * (1.0f / ((float)lbl_803A6C24.m1C.mA * 0.5f));

        for (i = 0; i < record->m23; i++) {
            fn_80276938(record->m4[i] - lbl_803A6C24.m1C.m12, cutoff);
        }
    }
}

void fn_80274E24(int index, int value)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    int i;

    if (record->m24 & 4) {
        for (i = 0; i < record->m23; i++) {
            MIX_sethighpass(record->m4[i] - lbl_803A6C24.m1C.m12, value);
        }
    }
}

int fn_80274EAC(int index)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    Channel_803A8D60 *channel = &lbl_803A8D60.m0[index];
    AXVPB *vpb;
    u32 position;

    if (record->m24 & 0x200) {
        vpb = channel->m3C;
        if (vpb == 0) {
            return -8;
        }
        position = (vpb->pb.addr.currentAddressHi << 16) + vpb->pb.addr.currentAddressLo;
        if (record->m22 == 18) {
            return ((int)(position - channel->m18) * 7) >> 3;
        }
        return position - channel->m18;
    }
    return MIX_getframe(index - lbl_803A6C24.m1C.m12);
}

int fn_80274F5C(int index)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    Channel_803A8D60 *channel = &lbl_803A8D60.m0[index];
    int i;

    if (record->m24 & 0x200) {
        if (channel->m1C >= 0) {
            lbl_803A8D60.m1410[channel->m1C]->m2598 = -1;
            channel->m1C = -1;
        }
        for (i = 0; i < record->m23; i++) {
            if (lbl_803A8D60.m0[record->m4[i]].m3C == 0) {
                return -8;
            }
            AXSetVoiceState(lbl_803A8D60.m0[record->m4[i]].m3C, 0);
            if (lbl_803A8D60.m0[record->m4[i]].m24 != 0) {
                fn_80272990(record->m4[i], 0);
                lbl_803A8D60.m0[record->m4[i]].m24 = 0;
            }
        }
    } else {
        for (i = 0; i < record->m23; i++) {
            lbl_803B503C(record->m4[i] - lbl_803A6C24.m1C.m12);
            fn_8026A0E8(record->m4[i]);
        }
    }
    return 0;
}

int fn_802750B8(int index, Desc_80276798 *desc)
{
    Record_803A6DF0 *record = &lbl_803A6C24.m1CC[index];
    int i;

    if (record->m24 & 4) {
        for (i = 0; i < record->m23; i++) {
            MIX_filteradd(record->m4[i] - lbl_803A6C24.m1C.m12, i, desc);
        }
        return 0;
    }
    return -7;
}

void *fn_80275150(int unused, int size)
{
    size = OSRoundUp32B(size);
    if (lbl_803A6C24.mB8 != 0) {
        return lbl_803A6C24.mB8(size);
    }
    return fn_80279960(size);
}

int fn_80275194(int unused, void *p)
{
    if (lbl_803A6C24.mBC == 0) {
        fn_80279B24(p);
    } else {
        lbl_803A6C24.mBC(p);
    }
    return 0;
}

int fn_802751E0(u32 start, u32 end)
{
    if (start == (u32)-1) {
        start = lbl_803A6C24.m1C.m38;
    }
    if (end == (u32)-1) {
        end = lbl_803A6C24.m1C.m38 + lbl_803A6C24.m1C.m3C;
    }
    fn_8027986C(start, end - start);
    return 0;
}

int fn_80275234(int unused, u32 source, u32 dest, u32 length)
{
    DCFlushRange((void *)source, length);
    return fn_80272B7C(0, source, dest, length, -1);
}

int fn_80275288(int key)
{
    BOOL enabled = OSDisableInterrupts();
    int i;

    for (i = 0; i < 64; i++) {
        if (lbl_803A8D60.m9E30[i].m0 != -1 && lbl_803A8D60.m9E30[i].m0 == key) {
            if (lbl_803A6C24.m170 - lbl_803A8D60.m9E30[i].m34 > 200) {
                OSRestoreInterrupts(enabled);
                fn_80272C9C(key);
            } else {
                OSRestoreInterrupts(enabled);
            }
            return 0;
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}

void fn_80275330(void)
{
    OSInitMutex(&lbl_803B4B90);
}

void fn_80275358(void)
{
}

void fn_8027535C(void)
{
    OSLockMutex(&lbl_803B4B90);
}

void fn_80275384(void)
{
    OSUnlockMutex(&lbl_803B4B90);
}

int fn_802753AC(Struct_802753AC *p, int mode)
{
    switch (mode) {
    case 0:
        p->m3F = 1;
        break;
    case 1:
        p->m3F = 2;
        break;
    case 8:
        p->m3F = 4;
        break;
    }
    return 0;
}
