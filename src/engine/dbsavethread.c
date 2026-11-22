/* Starts the worker that reads or writes a user-profile database on the memory card. */

#include <dolphin/os/OSThread.h>

typedef struct DbSaveThreadJob_t {
    unsigned int unk_0x00;
    unsigned int mStackSize;
    void *mpArg;
    unsigned int unk_0x0C;
    void *(*mpEntry)(void *);
    char *mpStack;
} DbSaveThreadJob_t;

static OSThread _DbSaveThread_tThread;

void DbSaveThreadStart(void *pJob)
{
    DbSaveThreadJob_t *p = pJob;

    if ((unsigned char)OSCreateThread(&_DbSaveThread_tThread, p->mpEntry, p->mpArg,
                                      p->mpStack + p->mStackSize, p->mStackSize, 22,
                                      OS_THREAD_ATTR_DETACH)) {
        OSResumeThread(&_DbSaveThread_tThread);
    }
}

void DbSaveThreadOnComplete(void)
{
}
