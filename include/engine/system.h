#ifndef ENGINE_SYSTEM_H
#define ENGINE_SYSTEM_H

#include "engine/fn_801F7BD4.h"
#include "engine/fn_801F8014.h"

#ifdef __cplusplus
extern "C" {
#endif

struct OSMutex;

typedef struct SysTimer_801F7B1C {
    void *pFunc;
    unsigned int mType;
    unsigned int mElapsed;
    unsigned short mFlags;
    int mUnknown10;
    char mUnknown14[8];
    int mUnknown1C;
    unsigned int mCount;
} SysTimer_801F7B1C;

typedef struct SysTime_8039B430 {
    unsigned char mSeconds;
    unsigned char mMinutes;
    unsigned char mHours;
    unsigned char mDays;
    unsigned char mMonth;
    unsigned short mYear;
    unsigned int mHundredths;
} SysTime_8039B430;

/* system.c */
unsigned int fn_801F7ABC(void);
void fn_801F7AE8(void);
unsigned int fn_801F7B14(void);

/* llsystem.c */
int fn_801F7E90(void);
int fn_801F7ED0(void);
int fn_801F7EF8(SysTimer_801F7B1C *pTimer);
int fn_801F7F60(SysTimer_801F7B1C *pTimer);
void fn_801F80E8(struct OSMutex **ppMutex);
int fn_801F8128(struct OSMutex **ppMutex);
void fn_801F8150(struct OSMutex **ppMutex);
void fn_801F8174(struct OSMutex **ppMutex);
void fn_801F81AC(void);
int fn_801F81D4(void);

#ifdef __cplusplus
}
#endif

#endif
