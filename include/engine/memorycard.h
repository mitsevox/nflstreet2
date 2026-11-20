#ifndef ENGINE_MEMORYCARD_H
#define ENGINE_MEMORYCARD_H

/* Directory entry filled by the memory-card directory scan (0x801D4848). */
typedef struct Struct_801D4848 {
    unsigned char mUnknown0;
    unsigned char mSecond;
    unsigned char mMinute;
    unsigned char mHour;
    unsigned char mDay;
    unsigned char mMonth;
    unsigned short mYear;
    char mName[32];
    unsigned int mIconAddr;
    unsigned int mLength;
} Struct_801D4848;

void MemCInit(void);
void MemCShutdown(void);
int MemCUnMount(int chan);
int MemCAsyncOpen(int port, const char *pName, int unused, int flags, int size);
int MemCAsyncFlush(int handle);
int MemCAsyncClose(int handle);
int MemCAsyncDelete(int port, const char *pName);
int MemCAsyncRead(int handle, char *pBuffer, int length);
int MemCAsyncWrite(int handle, char *pBuffer, int length);
int MemCAsyncSetSysInfo(int handle, unsigned int *pSysInfo);
void MemCFormatCardType(int type, char *pBuffer, int size);
int MemCAsyncPoll(int *pResult);

#endif
