#include "game/Class_80148A58.h"

extern "C" {
int fn_80177F70(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_801787DC(int team);
float fn_80237260(int stream);

int fn_801559B8(Class_80148A58 *p, int a)
{
    int result = 0;

    if (a && fn_80177F70() == 6) {
        unsigned int first = fn_801787DC(fn_80178308());
        unsigned int second = fn_801787DC(fn_80178320());

        if (first < second) {
            if (second - first > 1) {
                result = 2;
            } else {
                result = fn_80237260(0) <= 0.5f ? 1 : 2;
            }
        } else if (first > second) {
            result = fn_80237260(0) <= 0.5f ? 1 : 2;
        } else {
            result = fn_80237260(0) <= 0.7f ? 1 : 2;
        }
    }
    return result;
}
}
