/* Bound to the \x8a placeholder of the 'LRDC' queries. */
struct QueryCursor {
    int mUnknown0;
    short mUnknown4;
    int mUnknown8;
    int mUnknown12;
};

extern "C" {
int fn_801FCE10(int a, const char *pFormat, ...);
int fn_801FCFA0(QueryCursor *pCursor);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
}

static QueryCursor lbl_8037DED0;
static char lbl_8037DEE0[72];
static int lbl_803ECE94;

extern "C" {
int fn_80023514(void)
{
    return fn_801FCE10(0, "fetch from \x8a 'ilRC' into \x88 and 'ytRC' into \x82\n", &lbl_8037DED0, lbl_8037DEE0,
                       &lbl_803ECE94) == 0;
}

void fn_80023560(void)
{
    lbl_8037DEE0[0] = 0;
    lbl_803ECE94 = 0;
    if (fn_8022EF8C(0, 0x4C524443) == 0) {
        lbl_8037DED0.mUnknown0 = 0;
        lbl_8037DED0.mUnknown4 = 0;
        lbl_8037DED0.mUnknown8 = -1;
        lbl_8037DED0.mUnknown12 = 0;
        fn_801FCE10(0, "declare \x8a cursor for select * from 'LRDC'\n", &lbl_8037DED0);
    }
}

void fn_800235DC(void)
{
    if (lbl_8037DED0.mUnknown0 != 0) {
        fn_801FCFA0(&lbl_8037DED0);
    }
    fn_8022EFBC(0, 0x4C524443);
    lbl_8037DEE0[0] = 0;
    lbl_803ECE94 = 0;
}

void fn_80023634(int *pCount)
{
    int count = 0;

    fn_801FCE10(0, "select count(*) into \x85 from 'LRDC'\n", &count);
    *pCount = count;
}

void fn_80023684(char *pDest, int count)
{
    fn_801C2EF0(pDest, lbl_8037DEE0, count);
}

void fn_800236B0(int *pValue)
{
    *pValue = lbl_803ECE94;
}
}
