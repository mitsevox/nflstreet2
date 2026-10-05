struct Record_80361C64 {
    short mUnknown00;
    short mUnknown02;
    short mUnknown04;
    short mUnknown06;
    short mUnknown08;
    short mUnknown0A;
    short mUnknown0C;
    char mUnknown0E;
    char mUnknown0F;
    char mUnknown10;
    char mUnknown11;
    char mUnknown12;
};

struct Object_80361C64 {
    unsigned int mCount;
    Record_80361C64 mRecords[40];
};

extern "C" {
int fn_8009D86C(void);
int fn_8009D990(int index);
int fn_801740A8(void);
void fn_801740C4(int value);
int fn_80174114(int id);
int fn_801787DC(int a);
void fn_8017C344(unsigned short team, int play);
int fn_8022DDB4(int tag, void *data);
}

Object_80361C64 lbl_80361C64;

extern "C" void fn_80176C58(void)
{
    lbl_80361C64.mCount = 0;
    fn_8022DDB4(0x4D535347, &lbl_80361C64);
}

extern "C" void fn_80176C90(void)
{
    lbl_80361C64.mCount = 0;
    fn_8022DDB4(0x4D535347, &lbl_80361C64);
}

extern "C" void fn_80176CC8(int a, short b, int c, int d)
{
    if (a != 9) {
        fn_801740C4(1);
    }
    if (lbl_80361C64.mCount < 40) {
        int hi = (c >> 8) & 0xFF;
        lbl_80361C64.mRecords[lbl_80361C64.mCount].mUnknown10 = fn_8009D86C();
        lbl_80361C64.mRecords[lbl_80361C64.mCount].mUnknown00 = fn_8009D990(1);
        lbl_80361C64.mRecords[lbl_80361C64.mCount].mUnknown0E = a;
        lbl_80361C64.mRecords[lbl_80361C64.mCount].mUnknown02 = b;
        lbl_80361C64.mRecords[lbl_80361C64.mCount].mUnknown06 = fn_80174114(c);
        lbl_80361C64.mRecords[lbl_80361C64.mCount].mUnknown0A = fn_80174114(d);
        lbl_80361C64.mRecords[lbl_80361C64.mCount].mUnknown11 = fn_801787DC(1);
        lbl_80361C64.mRecords[lbl_80361C64.mCount].mUnknown12 = fn_801787DC(0);
        if ((a == 0 || a == 1 || a == 5) && fn_801740A8()) {
            fn_8017C344(hi, a);
        }
        lbl_80361C64.mRecords[lbl_80361C64.mCount].mUnknown0F = 13;
        lbl_80361C64.mCount++;
        fn_8022DDB4(0x4D535347, &lbl_80361C64);
    }
}

extern "C" void fn_80176E34(int a, int b, int c, int d)
{
    if (lbl_80361C64.mCount - 1 < 39) {
        lbl_80361C64.mRecords[lbl_80361C64.mCount - 1].mUnknown0F = a;
        lbl_80361C64.mRecords[lbl_80361C64.mCount - 1].mUnknown04 = b;
        lbl_80361C64.mRecords[lbl_80361C64.mCount - 1].mUnknown08 = fn_80174114(c);
        lbl_80361C64.mRecords[lbl_80361C64.mCount - 1].mUnknown0C = fn_80174114(d);
        lbl_80361C64.mRecords[lbl_80361C64.mCount - 1].mUnknown11 = fn_801787DC(1);
        lbl_80361C64.mRecords[lbl_80361C64.mCount - 1].mUnknown12 = fn_801787DC(0);
        fn_8022DDB4(0x4D535347, &lbl_80361C64);
    }
}
