#ifndef ENGINE_SEVENT_H
#define ENGINE_SEVENT_H

/* AEMS 1 compatibility layer of the sound library (src/engine/sevent.cpp). */

namespace Snd {

class Aems {
public:
    static int AddAems1CompatibilitySystem(void *system);
    static int RemoveAems1CompatibilitySystem(void);
};

}

#endif
