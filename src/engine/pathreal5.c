/* PATH platform interface (pathreal5.c): the Path::PathToReal5 singleton through which the PATH
   audio-track system gets its service task, millisecond timer and stream buffer sizing from the
   engine, plus the base Path::IPathToReal setters for its message and print callbacks. */

#include "engine/system.h"
#include "engine/pathreal.h"

extern "C" {

void *PATHI_memalloc(int size);
void PATHI_memfree(void *p);
void PATHI_servicetask(void);
int STREAM_overhead(int count, int filters, int taps);
int DebugPrintf(const char *format, ...);
void SndSetServiceCallback(void (*callback)(int a, int b));

}

namespace Path {

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
    PATHI_servicetask();
}

void *PathToReal5::operator new(unsigned int size)
{
    return PATHI_memalloc(size);
}

void PathToReal5::operator delete(void *p)
{
    PATHI_memfree(p);
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
