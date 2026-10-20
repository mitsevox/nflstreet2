#include "game/Class_80297B90.h"
#include "game/cu_80064864.h"
#include "game/fn_80195EFC.h"

extern "C" {
int fn_80196278(void);
void fn_800AD910(int a, float b);
void fn_8006BCC8(int type);
void fn_80072F04(void);
int fn_8006F394(int index, int unknown);
}

extern "C" void fn_800AB074(Class_80297B90 *p, float dt)
{
    if (fn_80196278() == 0) {
        fn_80195EFC(5, 20, 0, 0);
        fn_800AD910(1, 0.0f);
        fn_800655E8();
        fn_8006BCC8(3);
        fn_80072F04();
        fn_8006F394(3, 0);
    }
}
