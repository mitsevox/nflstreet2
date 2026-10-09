#include "game/cu_80064864.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"

extern "C" {
int fn_8000F870(int module, unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int fn_8001BB20(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8001D0F4(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8001D180(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8001D2D8(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8001F074(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8001F120(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_80059664(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_80063AA8(int kind, int id, void *pArgs, int c, int *pResult);
int fn_8017F6A8(int group, unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
int fn_8017F90C(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult);
void fn_800AE65C(void);
void fn_800AE988(void);
int fn_80063F04(int id, void *pArgs, int unused, int *pResult);
int fn_80063F84(int id, void *pArgs, int unused, int *pResult);
int fn_80064004(int id, void *pArgs, int unused, int *pResult);
int fn_80064084(int id, void *pArgs, int unused, int *pResult);
int fn_80064104(int id, void *pArgs, int unused, int *pResult);
int fn_80064184(int id, void *pArgs, int unused, int *pResult);
int fn_80064204(int id, void *pArgs, int unused, int *pResult);
int fn_80064294(int id, void *pArgs, int unused, int *pResult);
int fn_80064334(int id, void *pArgs, int unused, int *pResult);
int fn_800643B4(int id, void *pArgs, int unused, int *pResult);
int fn_80064434(int id, void *pArgs, int unused, int *pResult);
int fn_800644B4(int id, void *pArgs, int unused, int *pResult);
int fn_80064534(int id, void *pArgs, int unused, int *pResult);
int fn_800645B4(int id, void *pArgs, int unused, int *pResult);
int fn_80064634(int id, void *pArgs, int unused, int *pResult);
}

/* Copies the character list for the given type into pText and returns the
   list's length, limited to length. */
extern "C" int fn_80063C7C(int type, char *pText, int length)
{
    unsigned int count;

    fn_801C3284(pText, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ", length);
    count = 63;
    switch (type) {
    case 0:
    case 0x204:
        fn_801C3284(pText, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ", length);
        count = 63;
        break;
    case 0x201:
        fn_801C3284(pText, "1234567890", length);
        count = 10;
        break;
    case 1:
    case 2:
        fn_801C3284(pText, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789. ", length);
        count = 64;
        break;
    }
    if (count > length) {
        count = length;
    }
    return count;
}

extern "C" int fn_80063D48(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        break;
    case 0x80000002:
        fn_800652A8();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" int fn_80063D94(int kind, int id, void *pArgs, int unused, int *pResult)
{
    switch (kind) {
    case 0:
        return fn_80064634(id, pArgs, unused, pResult);
    case 1:
        return fn_80064084(id, pArgs, unused, pResult);
    case 2:
        return fn_80064004(id, pArgs, unused, pResult);
    case 11:
        return fn_80064334(id, pArgs, unused, pResult);
    case 10:
        return fn_80064294(id, pArgs, unused, pResult);
    case 13:
        return fn_80063F04(id, pArgs, unused, pResult);
    case 12:
        return fn_80063F84(id, pArgs, unused, pResult);
    case 7:
        return fn_800643B4(id, pArgs, unused, pResult);
    case 9:
        return fn_80064434(id, pArgs, unused, pResult);
    case 8:
        return fn_80064104(id, pArgs, unused, pResult);
    case 6:
        return fn_80064534(id, pArgs, unused, pResult);
    case 5:
        return fn_80064184(id, pArgs, unused, pResult);
    case 4:
        return fn_800645B4(id, pArgs, unused, pResult);
    case 14:
        return fn_800644B4(id, pArgs, unused, pResult);
    case 15:
        return fn_80064204(id, pArgs, unused, pResult);
    }
    return 0;
}

extern "C" void fn_80063EC0(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" void fn_80063EE4(void)
{
    fn_800AE65C();
}

extern "C" int fn_80063F04(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80063EE4();
        break;
    case 0x80000002:
        fn_80063EC0();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80063F60(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_80063F84(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        fn_80063F60();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80063FE0(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_80064004(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        fn_80063FE0();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80064060(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_80064084(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        fn_80064060();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_800640E0(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_80064104(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        fn_800640E0();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80064160(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_80064184(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        fn_80064160();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_800641E0(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_80064204(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        break;
    case 0x80000002:
        fn_800641E0();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80064250(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" void fn_80064274(void)
{
    fn_800AE65C();
}

extern "C" int fn_80064294(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80064274();
        break;
    case 0x80000002:
        fn_80064250();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_800642F0(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" void fn_80064314(void)
{
    fn_800AE65C();
}

extern "C" int fn_80064334(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80064314();
        break;
    case 0x80000002:
        fn_800642F0();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80064390(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_800643B4(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        fn_80064390();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80064410(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_80064434(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        fn_80064410();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80064490(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_800644B4(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        fn_80064490();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80064510(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_80064534(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        fn_80064510();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80064590(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_800645B4(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        fn_80064590();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80064610(void)
{
    fn_800652A8();
    fn_800AE988();
}

extern "C" int fn_80064634(int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        fn_80064610();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_80064690(unsigned int id, int kind, int group, int unused, Arg_8018399C *pArgs,
                            int *pResult)
{
    int handled = 0;

    switch (kind) {
    case 0:
        handled = fn_8000F870(group, id, pArgs, unused, pResult);
        break;
    case 13:
        handled = fn_8001BB20(group, id, pArgs, unused, pResult);
        break;
    case 11:
        handled = fn_8001D180(group, id, pArgs, unused, pResult);
        break;
    case 6:
        handled = fn_8001D2D8(group, id, pArgs, unused, pResult);
        break;
    case 3:
        handled = fn_80059664(group, id, pArgs, unused, pResult);
        break;
    case 1:
        handled = fn_80063AA8(group, id, pArgs, unused, pResult);
        break;
    case 5:
        handled = fn_8001F120(group, id, pArgs, unused, pResult);
        break;
    case 2:
        handled = fn_8017F6A8(group, id, pArgs, unused, pResult);
        break;
    case 7:
        handled = fn_80063D94(group, id, pArgs, unused, pResult);
        break;
    case 12:
        handled = fn_8001D0F4(group, id, pArgs, unused, pResult);
        break;
    case 8:
        handled = fn_8001F074(group, id, pArgs, unused, pResult);
        break;
    }
    if (handled == 0) {
        fn_8017F90C(id, pArgs, unused, pResult);
    }
}
