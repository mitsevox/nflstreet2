#ifndef GAME_PLAYCALLSCRIPT_H
#define GAME_PLAYCALLSCRIPT_H

typedef int (*PlayCallScriptCallback_t)(int, short *, int);

struct PlayCallScriptDesc_t {
    int mUnknown0;
    short *mUnknown4;
    PlayCallScriptCallback_t mUnknown8;
    PlayCallScriptCallback_t mUnknownC;
};

#ifdef __cplusplus
extern "C" {
#endif
int PlayCallOffenseCommand(int id, short *pRecord, int value);
int PlayCallDefenseCommand(int id, short *pRecord, int value);
void PlayCallScriptInit(struct PlayCallScriptDesc_t *pDesc);
#ifdef __cplusplus
}
#endif

#endif
