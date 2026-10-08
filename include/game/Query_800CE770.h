#ifndef GAME_QUERY_800CE770_H
#define GAME_QUERY_800CE770_H

struct Object_80039F5C;

/* 64-byte local record that fn_800CE770 clears; callers fill it and pass it
   to fn_800CE4A8 or fn_800CE510. Only accessed members are named. */
struct Query_800CE770 {
    Object_80039F5C *mpUnknown0;
    Object_80039F5C *mpUnknown4;
    char mUnknown8[28];
    int mUnknown36;
    char mUnknown40[4];
    float mUnknown44;
    char mUnknown48[4];
    short mUnknown52;
    unsigned char mUnknown54;
    char mUnknown55[9];
};

extern "C" {
void fn_800CE770(Query_800CE770 *pQuery);
}

#endif
