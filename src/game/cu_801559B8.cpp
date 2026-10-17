#include "game/Class_80148A58.h"

class Class_802A2A40 : public Class_80148A58 {
};

extern "C" {
int fn_80177F70(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_801787DC(int team);
float fn_80237260(int stream);

int fn_801559B8(Class_802A2A40 *p, int enabled)
{
    int result = 0;

    if (enabled && fn_80177F70() == 6) {
        unsigned int score = fn_801787DC(fn_80178308());
        unsigned int otherScore = fn_801787DC(fn_80178320());

        if (score < otherScore) {
            if (otherScore - score > 1) {
                result = 2;
            } else {
                result = fn_80237260(0) <= 0.5f ? 1 : 2;
            }
        } else if (score > otherScore) {
            result = fn_80237260(0) <= 0.5f ? 1 : 2;
        } else {
            result = fn_80237260(0) <= 0.7f ? 1 : 2;
        }
    }
    return result;
}
}
