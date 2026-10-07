struct Args_80055540 {
    int *mpUnknown0;
    int *mpUnknown4;
};

extern "C" {
int fn_800C8744(int team);

void fn_800554FC(int *pFirst, int *pSecond);
int fn_80055540(int id, Args_80055540 *pArgs);
}

extern "C" {

void fn_800554FC(int *pFirst, int *pSecond)
{
    *pFirst = fn_800C8744(1);
    *pSecond = fn_800C8744(0);
}

int fn_80055540(int id, Args_80055540 *pArgs)
{
    if (id == 0x80000001) {
        fn_800554FC(pArgs->mpUnknown0, pArgs->mpUnknown4);
        return 1;
    }
    return 0;
}

}
