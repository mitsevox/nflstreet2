#ifndef GAME_INFO_SCRMSTATE_H
#define GAME_INFO_SCRMSTATE_H

/* Returned by fn_801787D0; the layout is that read by fn_8016F6A4. */
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

extern "C" Info_ScrmState *fn_801787D0(void);

#endif
