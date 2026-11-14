/* PATH platform interface (pathreal5.c): the PathToReal5 singleton through which the PATH audio-track
   system gets its service task, millisecond timer and stream buffer sizing from the engine, plus the
   setters for its message and print callbacks. */

#include "engine/system.h"

/* Partial layout of the object whose members 0x8027EF94-0x8027EFA4 store
   their argument; size unknown. */
typedef struct Object_8027EF94 {
    virtual ~Object_8027EF94();
    virtual void vfn_02();
    virtual void vfn_03();
    virtual void vfn_04();
    int m0;
    int m4;
    int m8;
    virtual int vfn_05(void);
    virtual int vfn_06(int value);
} Object_8027EF94;

extern "C" {

void *fn_801B2C40(int size);
void fn_801B2C94(void *p);
void fn_801B3A88(void);
int fn_801F685C(int count, int filters, int taps);

void fn_8027EDC0(void)
{
    fn_801B3A88();
}

void *fn_8027EDE0(int size)
{
    return fn_801B2C40(size);
}

void fn_8027EE00(void *p)
{
    fn_801B2C94(p);
}

}

int Object_8027EF94::vfn_06(int value)
{
    return fn_801F685C(value, 0, 0) + 6144;
}

int Object_8027EF94::vfn_05(void)
{
    return ((int)fn_801F7ABC() * 50) / 3;
}

extern "C" {

int fn_8027EF50(Object_8027EF94 *p)
{
    return 0;
}

int fn_8027EF58(Object_8027EF94 *p)
{
    return 1;
}

void fn_8027EF94(Object_8027EF94 *p, int value)
{
    p->m0 = value;
}

void fn_8027EF9C(Object_8027EF94 *p, int value)
{
    p->m4 = value;
}

void fn_8027EFA4(Object_8027EF94 *p, int value)
{
    p->m8 = value;
}

}
