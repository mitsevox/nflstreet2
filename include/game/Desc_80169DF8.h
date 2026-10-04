#ifndef GAME_DESC_80169DF8_H
#define GAME_DESC_80169DF8_H

typedef int (*Callback_80169DF8)(int, short *, int);

struct Desc_80169DF8 {
    int mUnknown0;
    short *mUnknown4;
    Callback_80169DF8 mUnknown8;
    Callback_80169DF8 mUnknownC;
};

#ifdef __cplusplus
extern "C" {
#endif
int fn_80169308(int id, short *pRecord, int value);
int fn_801694C8(int id, short *pRecord, int value);
void fn_80169DF8(struct Desc_80169DF8 *pDesc);
#ifdef __cplusplus
}
#endif

#endif
