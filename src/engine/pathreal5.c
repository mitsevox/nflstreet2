/* PATH platform interface (pathreal5.c): the Path::PathToReal5 singleton through which the PATH
   audio-track system gets its service task, millisecond timer and stream buffer sizing from the
   engine, plus the base Path::IPathToReal setters for its message and print callbacks. */

#include "engine/system.h"

extern "C" {

void *fn_801B2C40(int size);
void fn_801B2C94(void *p);
void fn_801B3A88(void);
int STREAM_overhead(int count, int filters, int taps);
int DebugPrintf(const char *format, ...);
void SndSetServiceCallback(void (*callback)(int a, int b));

}

namespace Path {

class IPathToReal {
public:
    void (*mAbortMessageFunc)(const char *format, ...);
    int (*mDebugPrintFunc)(const char *format, ...);
    int (*mLogPrintFunc)(const char *format, ...);

    virtual ~IPathToReal() {}
    virtual void SetAbortMessageFunc(void (*func)(const char *format, ...)) { mAbortMessageFunc = func; }
    virtual void SetDebugPrintFunc(int (*func)(const char *format, ...)) { mDebugPrintFunc = func; }
    virtual void SetLogPrintFunc(int (*func)(const char *format, ...)) { mLogPrintFunc = func; }
    virtual int GetMilliseconds() = 0;
    virtual int GetMinStreamBufferSize(int channels) = 0;
    virtual int LoadFile(char *name, int &size, int flags) = 0;
    virtual int LoadFileDone(int handle, char *&data) = 0;

    static IPathToReal *realimp;
};

class PathToReal5 : public IPathToReal {
public:
    static void *operator new(unsigned int size);
    static void operator delete(void *p);
    PathToReal5();
    virtual ~PathToReal5();
    static void TaskService(int a, int b);
    virtual int GetMilliseconds();
    virtual int GetMinStreamBufferSize(int channels);
    virtual int LoadFile(char *name, int &size, int flags);
    virtual int LoadFileDone(int handle, char *&data);
};

}

void PATH_vectortoreal5()
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *format = "%s  %s";

    if (Path::IPathToReal::realimp != 0) {
        delete Path::IPathToReal::realimp;
    }
    Path::IPathToReal::realimp = new Path::PathToReal5;
}

namespace Path {

void PathToReal5::TaskService(int a, int b)
{
    fn_801B3A88();
}

void *PathToReal5::operator new(unsigned int size)
{
    return fn_801B2C40(size);
}

void PathToReal5::operator delete(void *p)
{
    fn_801B2C94(p);
}

PathToReal5::PathToReal5()
{
    mAbortMessageFunc = 0;
    mDebugPrintFunc = DebugPrintf;
    mLogPrintFunc = 0;
    SndSetServiceCallback(TaskService);
}

PathToReal5::~PathToReal5()
{
    SndSetServiceCallback(0);
    mAbortMessageFunc = 0;
    mDebugPrintFunc = 0;
    mLogPrintFunc = 0;
}

int PathToReal5::GetMinStreamBufferSize(int channels)
{
    return STREAM_overhead(channels, 0, 0) + 6144;
}

int PathToReal5::GetMilliseconds()
{
    return ((int)SysGetSystemTime() * 50) / 3;
}

int PathToReal5::LoadFile(char *name, int &size, int flags)
{
    return 0;
}

int PathToReal5::LoadFileDone(int handle, char *&data)
{
    return 1;
}

}
