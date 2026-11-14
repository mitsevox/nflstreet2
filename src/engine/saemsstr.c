/* Sound library module stream setters (saemsstr.c): the stream counterparts of saems.c's bank
   and play-option setters. Each clamps a module output and passes it to the stream function of
   the same parameter; the table lists them in the order of the bank and option tables. */

extern "C" {
int fn_8026D610(int handle, int value);
int fn_8026E4C0(int handle, float azimuth, int time);
int fn_8026EAC0(int handle, int a, int b);
int fn_8026ECCC(int handle, int value);
int fn_8026ED74(int handle, int value);
int fn_8026EEB0(int handle, int value);
int fn_8026EF38(int handle, int value);
int fn_8026F2C8(int handle, int value);
int fn_8026F334(int handle, float volume, int time);
}

void SNDAEMSI_streampitchmult(int handle, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    fn_8026EEB0(handle, value);
}

void SNDAEMSI_streamtimemult(int handle, int value)
{
    if (value > 8192)
        value = 8192;
    else if (value < 2048)
        value = 2048;
    fn_8026F2C8(handle, value);
}

void SNDAEMSI_streamvol(int handle, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    fn_8026F334(handle, (float)clamped * (1.0f / 32767.0f), -1);
}

void SNDAEMSI_streamazimuth(int handle, int value)
{
    fn_8026D610(handle, value);
    fn_8026E4C0(handle, (float)(value & 0xFFFF) * (360.0f / 65535.0f), -1);
}

void SNDAEMSI_streamfxwet0(int handle, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    fn_8026EAC0(handle, 0, clamped >> 8);
}

void SNDAEMSI_streamlowpass(int handle, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    fn_8026ED74(handle, value);
}

void SNDAEMSI_streamhighpass(int handle, int value)
{
    int max = 0xFFFF;

    if (value < 0)
        value = 0;
    else if (value > max)
        value = max;
    fn_8026ECCC(handle, value);
}

void SNDAEMSI_streamdrylevel(int handle, int value)
{
    int clamped;

    if (value < 0)
        clamped = 0;
    else if (value > 32767)
        clamped = 32767;
    else
        clamped = value;
    fn_8026EF38(handle, clamped >> 8);
}

void SNDAEMSI_streamstub(int handle, int value)
{
}

void (*SNDAEMSI_streamfuncs[12])(int handle, int value) = {
    SNDAEMSI_streampitchmult, SNDAEMSI_streamtimemult, SNDAEMSI_streamvol,
    SNDAEMSI_streamazimuth, SNDAEMSI_streamstub, SNDAEMSI_streamfxwet0,
    SNDAEMSI_streamlowpass, SNDAEMSI_streamhighpass, SNDAEMSI_streamdrylevel,
    SNDAEMSI_streamstub, SNDAEMSI_streamstub, SNDAEMSI_streamstub,
};
