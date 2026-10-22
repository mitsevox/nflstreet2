/* Members of the C++ classes whose constructors are 0x8027D6E8 (vtable
   0x802C2618) and 0x8027DAE4 (vtable 0x802C23C8) and of the class with the
   vtable 0x802C24F0, and of the small class with the vtables 0x802C2798 and
   0x802C27E8. Only bodies that need no class declaration are reconstructed
   here; they use neutral C-linkage labels. */

typedef struct Record_8027D9FC {
    int m0;
    int m4;
    int m8;
    int mC;
} Record_8027D9FC;

/* Partial layout of the objects built by 0x8027D6E8; size unknown. */
typedef struct Object_8027D6E8 {
    unsigned char mUnknown0[0x10];
    int m10;
    unsigned char mUnknown14[8];
    int m1C;
    unsigned char mUnknown20[0x18];
    int m38;
    unsigned char mUnknown3C[0x18];
    int m54;
    unsigned char mUnknown58[0x14];
    Record_8027D9FC m6C;
    unsigned char mUnknown7C[0x98];
    int m114;
} Object_8027D6E8;

/* Member of the class built by 0x8027DAE4 (vtable 0x802C23C8); partial
   layout, size unknown. */
typedef struct Object_8027DAE4 {
    unsigned char mUnknown0[0x58];
    int m58;
} Object_8027DAE4;

/* Members of the class built by 0x8027E518 (vtable 0x802C24F0); partial
   layout, size unknown. */
typedef struct Object_8027E518 {
    unsigned char mUnknown0[0x124];
    int m124;
    int m128;
} Object_8027E518;

/* Partial layout of the object whose members 0x8027EF94-0x8027EFA4 store
   their argument; size unknown. */
typedef struct Object_8027EF94 {
    int m0;
    int m4;
    int m8;
} Object_8027EF94;

extern "C" {

void *fn_801B2C40(int size);
void fn_801B2C94(void *p);

void *fn_8027D5CC(int size)
{
    return fn_801B2C40(size);
}

void fn_8027D5EC(void *p)
{
    fn_801B2C94(p);
}

int fn_8027D960(Object_8027D6E8 *p)
{
    return p->m38;
}

int fn_8027D968(Object_8027D6E8 *p)
{
    return p->m54;
}

int fn_8027D970(Object_8027D6E8 *p)
{
    return p->m10;
}

int fn_8027D9EC(Object_8027D6E8 *p)
{
    return 0;
}

int fn_8027D9F4(Object_8027D6E8 *p)
{
    return 0;
}

void fn_8027D9FC(Object_8027D6E8 *p, Record_8027D9FC *record)
{
    p->m6C = *record;
}

void *fn_8027DAA4(int size)
{
    return fn_801B2C40(size);
}

void fn_8027DAC4(void *p)
{
    fn_801B2C94(p);
}

int fn_8027E0AC(Object_8027DAE4 *p, int index)
{
    if (index == 0) {
        return p->m58;
    }
    return -1;
}

void *fn_8027E4D8(int size)
{
    return fn_801B2C40(size);
}

void fn_8027E4F8(void *p)
{
    fn_801B2C94(p);
}

void fn_8027EAB4(Object_8027E518 *p, int a, int b)
{
    p->m124 = a;
    p->m128 = b;
}

void fn_8027ED4C(Object_8027D6E8 *p)
{
    p->m1C = 1;
}

void fn_8027ED58(Object_8027D6E8 *p)
{
}

int fn_8027ED5C(Object_8027D6E8 *p)
{
    return -1;
}

int fn_8027ED64(Object_8027D6E8 *p)
{
    return p->m114;
}

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
