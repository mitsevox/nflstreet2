#ifndef ENGINE_DBTEAMS_H
#define ENGINE_DBTEAMS_H

#ifdef __cplusplus
extern "C" {
#endif

int DbTeamsInit(const char *pName);
void DbTeamsShutdown(void);
int DbTeamsOpen(void);
int DbTeamsIsOpen(void);
int DbTeamsClose(void);
int DbTeamsLoad(int a, int *pOut);

#ifdef __cplusplus
}
#endif

#endif
