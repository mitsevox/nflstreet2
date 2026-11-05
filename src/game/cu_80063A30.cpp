extern "C" {
int MsgPlaybookStyleHandleMessage(unsigned int id, void *pArgs, int c, int *pResult);
int MsgProfileListHandleMessage(unsigned int id, void *pArgs, int c, int *pResult);
int MsgMemCardLoadHandleMessage(unsigned int id, void *pArgs, int c, int *pResult);
int MsgNameEntryHandleMessage(int id, void *pArgs, int c, int *pResult);
int MsgMemCardScanHandleMessage(unsigned int id, void *pArgs, int c, int *pResult);
int fn_80063A30(int id, int *pArgs, int c, int *pResult);
int fn_80063D48(int id, void *pArgs, int c, int *pResult);
int fn_80186324(unsigned int id, void *pArgs, int c, int *pResult);
void fn_801CEB58(int a);
void fn_8023CFD0(int a);
}

static int lbl_803EA628 = 0;

extern "C" int fn_80063A30(int id, int *pArgs, int c, int *pResult)
{
    switch (id) {
    case 0x80000001:
        if (*pArgs == 1) {
            lbl_803EA628 = *pArgs;
            fn_8023CFD0(1);
            fn_801CEB58(1);
        } else {
            lbl_803EA628 = 0;
            fn_8023CFD0(0);
        }
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" int fn_80063AA0(void)
{
    return (unsigned char)lbl_803EA628;
}

extern "C" int fn_80063AA8(int kind, int id, void *pArgs, int c, int *pResult)
{
    switch (kind) {
    case 2:
        return fn_80186324(id, pArgs, c, pResult);
    case 4:
        return MsgMemCardScanHandleMessage(id, pArgs, c, pResult);
    case 1:
        return MsgNameEntryHandleMessage(id, pArgs, c, pResult);
    case 6:
        return MsgMemCardLoadHandleMessage(id, pArgs, c, pResult);
    case 11:
        return MsgProfileListHandleMessage(id, pArgs, c, pResult);
    case 13:
        return MsgPlaybookStyleHandleMessage(id, pArgs, c, pResult);
    case 14:
        return fn_80063A30(id, (int *)pArgs, c, pResult);
    case 20:
        return fn_80063D48(id, pArgs, c, pResult);
    }
    return 0;
}
