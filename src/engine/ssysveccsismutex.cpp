/* Sound system CSIS mutex hookup (ssysveccsismutex.cpp): points the sound system's lock and
   unlock vector at the CSIS mutex, so sound calls share the CSIS critical section. */

#include "engine/sndstrm.h"

extern "C" {

int fn_801B9148(void);
int fn_801B9174(void);

extern void (*lbl_802FFDF0)(void);
extern void (*lbl_802FFDF4)(void);

}

namespace Snd {

void CsisMutexLock(void)
{
    fn_801B9148();
}

void CsisMutexUnlock(void)
{
    fn_801B9174();
}

class System {
public:
    static int VectorToCsisMutex(void);
};

int System::VectorToCsisMutex(void)
{
    if (lbl_802FFDF0 == CsisMutexLock) {
        return 0;
    }
    lbl_802FFDF0 = CsisMutexLock;
    lbl_802FFDF4 = CsisMutexUnlock;
    return 0;
}

}
