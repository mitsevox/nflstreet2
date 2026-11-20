#ifndef ENGINE_DBUTIL_H
#define ENGINE_DBUTIL_H

#ifdef __cplusplus
extern "C" {
#endif

void DbUtilRandomInit(void);
void DbUtilRandomShutdown(void);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void DbUtilSetHeap(int heap);
void *DbUtilAlloc(int size, int bUseHeap);
void DbUtilFree(void *p);

#ifdef __cplusplus
}
#endif

#endif
