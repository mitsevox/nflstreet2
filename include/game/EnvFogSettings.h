#ifndef GAME_ENVFOGSETTINGS_H
#define GAME_ENVFOGSETTINGS_H

/* One 20-byte entry of the .data table 0x802F394C (src/game/EnvRender.cpp),
   returned by EnvGetFogSettings. fn_800A2F48 keeps the selected entry at +0x8C0 of
   0x8030E6E8, and StadiumGetFogDensity, StadiumGetFogColor and StadiumGetFogSettings read it back. */
struct EnvFogSettings {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    float mUnknownC;
    unsigned int mUnknown10;
};

extern "C" {
float StadiumGetFogDensity(void);
int StadiumGetFogColor(void);
EnvFogSettings *StadiumGetFogSettings(void);
EnvFogSettings *EnvGetFogSettings(int index);
}

#endif
