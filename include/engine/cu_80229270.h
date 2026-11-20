#ifndef ENGINE_CU_80229270_H
#define ENGINE_CU_80229270_H
struct SaveStreamOps_t;
#ifdef __cplusplus
extern "C" {
#endif
int fn_8022DA44(int a, int *b, int c, int *d, int e);
int fn_8022D2F4(int a, int b, int c, void *pPairs, int mode);
int DbEvasLoad(void);
int DbEvasUnload(void);
int DbEvasSaveStream(void *pTarget, struct SaveStreamOps_t *pOps);
int DbUserGetId(int index);
#ifdef __cplusplus
}
#endif
#endif
