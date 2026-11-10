#ifndef GAME_MEM_CARD_UI_H
#define GAME_MEM_CARD_UI_H

/* Five callbacks registered with MemCardUISetCallbacks and cleared by MemCardUIClearCallbacks. */
struct MemCardListCallbacks_t {
    void (*mUnknown0)(int, int *);
    void (*mUnknown4)();
    int (*mUnknown8)(int *, int *, int *, int *);
    void (*mUnknown12)(int, int);
    int (*mUnknown16)(int, int);
};

extern "C" {
void MemCardUISetCallbacks(MemCardListCallbacks_t *pCallbacks);
void MemCardUIClearCallbacks();
}

#endif
