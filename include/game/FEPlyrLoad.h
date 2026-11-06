#ifndef GAME_FEPLYRLOAD_H
#define GAME_FEPLYRLOAD_H

struct Object_8003DEC4;

extern "C" {
void FEPlyrLoadInit(void);
void FEPlyrLoadShutdown(void);
unsigned char FEPlyrLoadIsActive(void);
void FEPlyrLoadRequest(int index, const char *pName, unsigned char priority, int force);
void FEPlyrLoadRequestReload(int index, unsigned char priority);
void FEPlyrLoadSetPriority(int index, unsigned char priority);
unsigned char FEPlyrLoadIsQueued(int index);
unsigned char FEPlyrLoadIsShown(Object_8003DEC4 *pPlayer);
void FEPlyrLoadGetScale(Object_8003DEC4 *pPlayer, float *pScale);
unsigned char FEPlyrLoadSetScaleRamp(unsigned char value);
}

#endif
