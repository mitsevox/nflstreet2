#ifndef ENGINE_MEMORYCARD_H
#define ENGINE_MEMORYCARD_H

/* Directory entry filled by the memory-card directory scan (0x801D4848). */
typedef struct MemCDirEntry {
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
} MemCDirEntry;

void fn_801D4120(void);
void fn_801D4198(void);
int fn_801D466C(int chan);
int fn_801D4A3C(int port, const char *pName, int unused, int flags, int size);
int fn_801D4E6C(int handle);
int fn_801D4F58(int handle);
int fn_801D4FF4(int port, const char *pName);
int fn_801D5440(int handle, char *pBuffer, int length);
int fn_801D56A0(int handle, char *pBuffer, int length);
int fn_801D56D4(int handle, unsigned int *pSysInfo);
void fn_801D5764(int type, char *pBuffer, int size);
int fn_801D5840(int *pResult);

#endif
