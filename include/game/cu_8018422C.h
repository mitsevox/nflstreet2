#ifndef GAME_CU_8018422C_H
#define GAME_CU_8018422C_H

/* Five callbacks registered with fn_801851A4 and cleared by fn_801851D0. */
struct MemCardListCallbacks_t {
    void (*mUnknown0)(int, int *);
    void (*mUnknown4)();
    int (*mUnknown8)(int *, int *, int *, int *);
    void (*mUnknown12)(int, int);
    int (*mUnknown16)(int, int);
};

extern "C" {
void fn_801851A4(MemCardListCallbacks_t *pCallbacks);
void fn_801851D0();
}

#endif
