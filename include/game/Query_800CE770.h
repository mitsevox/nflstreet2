#ifndef GAME_QUERY_800CE770_H
#define GAME_QUERY_800CE770_H

struct Object_80039F5C;

/* 64-byte stack block that fn_800CE770 prepares before it is passed to
   fn_800CE2B8 or fn_800CE510. Only the members the reconstructed callers
   access are declared; the rest stays opaque. */
struct Query_800CE770 {
    Object_80039F5C *mpUnknown0;
    union {
        Object_80039F5C *mpUnknown4;
        Object_80039F5C *mpUnknown4Entries[7];
    };
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
    float mUnknown44;
    float mUnknown48;
    union {
        short mUnknown52;
        unsigned short mUnknown52Unsigned;
        unsigned char mBytes52[2];
    };
    unsigned char mUnknown54;
    unsigned char mUnknown55;
    unsigned char mUnknown56;
    unsigned char mUnknown57;
    unsigned char mUnknown58;
    unsigned char mUnknown59;
    unsigned char mUnknown60;
    char mUnknown61[3];
};

/* Parameter lists follow register use at the call sites only. */
extern "C" {
void fn_800CE770(Query_800CE770 *pQuery);
int fn_800CE2B8(Query_800CE770 *pQuery);
int fn_800CE510(Query_800CE770 *pQuery);
}

#endif
