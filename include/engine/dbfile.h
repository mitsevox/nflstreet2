#ifndef ENGINE_DBFILE_H
#define ENGINE_DBFILE_H

#ifdef __cplusplus
extern "C" {
#endif

int DbFileInit(const char *pName);
void DbFileShutdown(void);
int DbFileTblLoad(int db, int file);
int DbFileTblDestroy(int db, int tbl);

#ifdef __cplusplus
}
#endif

#endif
