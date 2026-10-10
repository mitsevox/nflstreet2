#ifndef GAME_ENTRY_802F394C_H
#define GAME_ENTRY_802F394C_H

/* One 20-byte entry of the .data table 0x802F394C (src/game/cu_801A5478.cpp),
   returned by fn_801A566C. fn_800A2F48 keeps the selected entry at +0x8C0 of
   0x8030E6E8, and fn_800A3400, fn_800A3410 and fn_800A34EC read it back. */
struct Entry_802F394C {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    float mUnknownC;
    unsigned int mUnknown10;
};

extern "C" {
float fn_800A3400(void);
int fn_800A3410(void);
Entry_802F394C *fn_800A34EC(void);
Entry_802F394C *fn_801A566C(int index);
}

#endif
