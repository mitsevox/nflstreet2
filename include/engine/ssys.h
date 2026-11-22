#ifndef ENGINE_SSYS_H
#define ENGINE_SSYS_H

/* The sound system front end (ssys.cpp, ssysveccsismutex.cpp): the Snd::System, Snd::Memory and
   Snd::Profile calls the game makes to set up, start and restore the sound library. */

namespace Snd {

enum Device {
    DEVICE_MAIN = 0,
    DEVICE_ARAM = 2
};

enum OutputMode {
    OUTPUT_MONO = 0,
    OUTPUT_STEREO = 1,
    OUTPUT_SURROUND = 8
};

class System {
public:
    static int SetMaxBanks(int count);
    static int CapOutputMode(OutputMode mode, bool *capable);
    static int SetOutputMode(OutputMode mode);
    static int SetVoices(Device device, int count);
    static int SetSndInitsAram(bool inits);
    static int SetAbortHandler(void (*handler)(const char *message));
    static int Init(int arg);
    static bool IsInited(void);
    static int Restore(void);
    static int VectorToCsisMutex(void);
};

class Memory {
public:
    static int SetHeap(Device device, void *heap, int size);
};

class Profile {
public:
    static int SetFunctionProfiler(void (*enter)(const char *name), void (*exit)(const char *name));
};

}

#endif
