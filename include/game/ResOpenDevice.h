#ifndef GAME_RESOPENDEVICE_H
#define GAME_RESOPENDEVICE_H

#ifdef __cplusplus
extern "C" {
#endif
void *ResOpenDevice(const char *pName, int unknown);
int ResClose(void *p);
#ifdef __cplusplus
}
#endif

#endif
