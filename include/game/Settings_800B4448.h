#ifndef GAME_SETTINGS_800B4448_H
#define GAME_SETTINGS_800B4448_H

/* Words that fn_800B4448 overrides when the matching cheat flags are set. */
struct Settings_800B4448 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
};

extern "C" void fn_800B4448(Settings_800B4448 *p);

#endif
