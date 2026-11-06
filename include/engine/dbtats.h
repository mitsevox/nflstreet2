#ifndef ENGINE_DBTATS_H
#define ENGINE_DBTATS_H

#ifdef __cplusplus
extern "C" {
#endif

int DbTatsInit(int a, const char *pName, int b);
void DbTatsShutdown(void);
int DbTatsLoad(void);
int DbTatsUnload(void);

#ifdef __cplusplus
}
#endif

#endif
