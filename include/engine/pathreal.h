#ifndef ENGINE_PATHREAL_H
#define ENGINE_PATHREAL_H

/* The two back-end interfaces of the PATH interactive-music library: Path::IPathToReal, through which
   it reads the clock and loads files on the platform (installed by pathreal5.c), and
   Path::IPathToSnd, through which it creates its stream and bank track objects in the sound library. */

class Allocator;
class IPathTrack;

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
    static Allocator *memimp;
};

class IPathToSnd {
public:
    virtual ~IPathToSnd() {}
    virtual int CreateStreamTrack(IPathTrack **track, int flags, float rate, int value) = 0;
    virtual int CreateBankTrack(IPathTrack **track, int bank) = 0;
    virtual void GetDefaultPlayOpts(void *opts) = 0;

    static IPathToSnd *sndimp;
};

}

#endif
