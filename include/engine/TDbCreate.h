#ifndef ENGINE_TDBCREATE_H
#define ENGINE_TDBCREATE_H

#ifdef __cplusplus
extern "C" {
#endif

int TDbCreate(int db, int size);
int TDbDestroy(int db);

#ifdef __cplusplus
}
#endif

#endif
