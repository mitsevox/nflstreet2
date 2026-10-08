#include "game/Object_80193F84.h"
#include "game/fn_801EF390.h"

extern "C" {
int fn_801F1520(int value);
void fn_8020DFD8(int a, void *p);
int fn_8020E258(void *p);
void fn_8020E7EC(void *p);

void fn_80193E7C(Object_80193F84 *p)
{
    int previous = fn_801F1520(4);
    int data = fn_801EF390((void *)p->mUnknown0, p->mUnknown4, 1);

    fn_801F1520(previous);
    fn_8020DFD8(data, &p->mUnknown8);
    fn_8020E7EC(&p->mUnknown8);
    fn_801F010C((void *)p->mUnknown0, p->mUnknown4);
}

void fn_80193EF0(Object_80193F84 *p, int a, int b, int c, const char *pName)
{
    p->mUnknown0 = b;
    p->mUnknown4 = c;
    fn_80193E7C(p);
    p->mUnknown28 = 1;
}

void fn_80193F2C(Object_80193F84 *p)
{
    if (fn_801F0DB8((void *)p->mUnknown0, p->mUnknown4)) {
        fn_801F010C((void *)p->mUnknown0, p->mUnknown4);
    }
    fn_8020E258(&p->mUnknown8);
    fn_80193F84(p);
}

void fn_80193F84(Object_80193F84 *p)
{
    p->mUnknown0 = 0;
    p->mUnknown4 = 0;
    p->mUnknown28 = 0;
    p->mUnknown2C = 0;
    p->mUnknown30 = 0;
    p->mUnknown38 = 0;
}
}
