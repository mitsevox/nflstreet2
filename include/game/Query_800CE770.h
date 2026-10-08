#ifndef GAME_QUERY_800CE770_H
#define GAME_QUERY_800CE770_H

struct Object_80039F5C;

/* 64-byte stack block that fn_800CE770 prepares before it is passed to
   fn_800CE2B8 or fn_800CE510. Only the members the reconstructed callers
   access are declared; the rest stays opaque. */
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
    char mUnknown55[1];
    unsigned char mUnknown56;
    char mUnknown57[7];
};

/* Parameter lists follow register use at the call sites only. */
extern "C" {
void fn_800CE770(Query_800CE770 *pQuery);
int fn_800CE2B8(Query_800CE770 *pQuery);
int fn_800CE510(Query_800CE770 *pQuery);
}

#endif
