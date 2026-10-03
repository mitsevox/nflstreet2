struct Args_800625DC {
    int *mpOut;
};

struct Args_800626A4 {
    int mIndex;
    int *mpOut;
    int *mpFlag;
};

struct Args_80062714 {
    int mValue;
};

extern "C" {
int fn_8022F4BC(void);
int fn_80186B38(int a);
int fn_8018F3D8(int a);
int fn_8018F288(int a, int b);
int fn_8022F384(int a);
void fn_8007B5A8(int a, int b, int c);
void fn_8018F4C4(int a);

static const signed char lbl_8028F6A4[33] = {
    8, 23, 7, 16, 26, 19, 5, 14, 17, 32, 29, 18, 3, 1, 6, 15, 2,
    27, 31, 12, 25, 11, 28, 4, 20, 24, 30, 13, 10, 9, 21, 22, 34,
};
static int lbl_803EC800;

void fn_800625DC(int *pOut)
{
    int value;

    if (fn_8018F3D8(fn_80186B38(fn_8022F4BC())) > 24) {
        value = 8;
    } else if (fn_8018F3D8(fn_80186B38(fn_8022F4BC())) > 16) {
        value = 16;
    } else if (fn_8018F3D8(fn_80186B38(fn_8022F4BC())) > 8) {
        value = 24;
    } else if (fn_8018F3D8(fn_80186B38(fn_8022F4BC())) > 0) {
        value = 32;
    } else {
        value = 33;
    }
    *pOut = value;
    if (fn_8018F288(fn_80186B38(fn_8022F4BC()), 34) != 0) {
        fn_8007B5A8(fn_8022F384(fn_8022F4BC()), 11, 0);
    }
}

void fn_800626A4(int index, int *pOut, int *pFlag)
{
    *pOut = lbl_8028F6A4[index];
    if (fn_8018F288(fn_80186B38(fn_8022F4BC()), *pOut) != 0) {
        *pFlag = 1;
    } else {
        *pFlag = 0;
    }
}

int fn_8006270C(void)
{
    return lbl_803EC800;
}

int fn_80062714(unsigned int id, void *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800625DC(((Args_800625DC *)pArgs)->mpOut);
        lbl_803EC800 = -1;
        break;
    case 0x80000003:
        fn_800626A4(((Args_800626A4 *)pArgs)->mIndex, ((Args_800626A4 *)pArgs)->mpOut, ((Args_800626A4 *)pArgs)->mpFlag);
        break;
    case 0x80000004:
        lbl_803EC800 = ((Args_80062714 *)pArgs)->mValue;
        break;
    case 0x80000005:
        if (fn_8018F3D8(fn_80186B38(fn_8022F4BC())) == -1) {
            *pResult = 1;
            fn_8018F4C4(fn_80186B38(fn_8022F4BC()));
        } else {
            *pResult = 0;
        }
    default:
        return 0;
    case 0x80000002:
        break;
    }
    return 1;
}
}
