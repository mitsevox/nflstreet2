struct Args_80054E08 {
    char mUnknown0[4];
    int mUnknown4;
    int mUnknown8;
};

struct Message_80054E08 {
    int mUnknown0;
    Args_80054E08 *mpArgs;
};

extern "C" {
extern void *lbl_803EA368;

void fn_8002CA74(void *p, int a, int b);
int fn_8002D0D0(void *p);
int fn_8002D0FC(void *p);
void fn_8017DBCC(void);
void fn_8018A798(int value);
int fn_8018A7A0(void);
unsigned char fn_8018AFD8(unsigned char value);
}

static unsigned char lbl_803EA568 = 0;
static int lbl_803EA56C = -1;

extern "C" void fn_80054D34(void)
{
    lbl_803EA56C = fn_8018A7A0();
    lbl_803EA568 = fn_8018AFD8(0);
    fn_8002CA74(lbl_803EA368, 7, 0);
}

extern "C" int fn_80054D74(void) { return fn_8002D0D0(lbl_803EA368); }

extern "C" void fn_80054D98(void)
{
    fn_8018A798(lbl_803EA56C);
    lbl_803EA56C = -1;
    fn_8018AFD8(lbl_803EA568);
    fn_8002CA74(lbl_803EA368, 9, 0);
    fn_8017DBCC();
}

extern "C" int fn_80054DE0(void) { return fn_8002D0FC(lbl_803EA368); }

extern "C" void fn_80054E04(int a, int b, int c) {}

extern "C" int fn_80054E08(unsigned int id, Message_80054E08 *pMessage, int c, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80054D34();
        break;
    case 0x80000002:
        *pResult = fn_80054D74();
        break;
    case 0x80000003:
        fn_80054D98();
        break;
    case 0x80000004:
        *pResult = fn_80054DE0();
        break;
    case 0x80000005:
        fn_80054E04(pMessage->mUnknown0, pMessage->mpArgs->mUnknown8, pMessage->mpArgs->mUnknown4);
        break;
    default:
        return 0;
    }
    return 1;
}
