#ifndef GAME_INFO_SCRMSTATE_H
#define GAME_INFO_SCRMSTATE_H

/* Returned by ScrmGetInfo; the layout is that read by ScrmSpotReset. */
struct Info_ScrmState {
    float mUnknown00;
    float mUnknown04;
    float mUnknown08;
    int mUnknown0C;
    int mUnknown10;
    short mUnknown14;
    float mUnknown18;
    int mUnknown1C;
};

extern "C" Info_ScrmState *ScrmGetInfo(void);

#endif
