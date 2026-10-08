#ifndef GAME_CU_801882B4_H
#define GAME_CU_801882B4_H

struct Desc_80188688 {
    int mUnknown0;
    int mUnknown4;
    char *mUnknown8;
    char **mUnknown12;
};

struct Cache_80188688;

#ifdef __cplusplus
extern "C" {
#endif
Cache_80188688 *fn_80188688(Desc_80188688 *pDesc);
void fn_80188728(Cache_80188688 *pCache);
void fn_80188784(Cache_80188688 *pCache, int key);
void fn_801888A4(Cache_80188688 *pCache, int key);
void fn_8018897C(Cache_80188688 *pCache, int key, int index, int async);
void fn_801889A4(Cache_80188688 *pCache, int key, int index);
int fn_801889CC(Cache_80188688 *pCache, int key, int index);
#ifdef __cplusplus
}
#endif

#endif
