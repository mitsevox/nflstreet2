#ifndef GAME_RES_BANK_H
#define GAME_RES_BANK_H

struct ResBankDesc_t {
    int mUnknown0;
    int mUnknown4;
    char *mUnknown8;
    char **mUnknown12;
};

struct ResBank_t;

#ifdef __cplusplus
extern "C" {
#endif
ResBank_t *ResBankCreate(ResBankDesc_t *pDesc);
void ResBankDestroy(ResBank_t *pCache);
void ResBankOpenFile(ResBank_t *pCache, int key);
void ResBankCloseFile(ResBank_t *pCache, int key);
void ResBankLoad(ResBank_t *pCache, int key, int index, int async);
void ResBankUnload(ResBank_t *pCache, int key, int index);
int ResBankGetData(ResBank_t *pCache, int key, int index);
#ifdef __cplusplus
}
#endif

#endif
