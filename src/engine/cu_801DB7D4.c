extern void fn_801CE82C(void);
extern int fn_801CEA08(void);
extern int fn_801CE930(void);
extern int fn_801CE944(int a);
extern void fn_801DB900(void *pDst, int x, int y, int pitch, int width, int height, int mode);
extern void fn_801DBEB4(void *pDst, int x, int y, int pitch, int width, int height, int mode);

extern int lbl_803ECF30;
extern int lbl_803ECF34;
extern int lbl_803ECF38;
extern int lbl_803ECF3C;
extern int lbl_803ECF40;
extern int lbl_803ECF44;
extern int lbl_803ECF48;

void fn_801DB7D4(void)
{
}

void fn_801DB7D8(int x, int y, int width, int height, int mode, int unused)
{
    fn_801DB7D4();
    lbl_803ECF30 = -1;
    lbl_803ECF34 = x;
    lbl_803ECF38 = y;
    lbl_803ECF3C = width;
    lbl_803ECF40 = height;
    lbl_803ECF44 = mode;
    lbl_803ECF48 = 2;
}

void fn_801DB838(void *pDst)
{
    int pitch;
    int mode;

    fn_801CE82C();
    pitch = (fn_801CEA08() + 15) & 0xFFF0;
    mode = fn_801CE944((unsigned char)fn_801CE930());
    fn_801DB900(pDst, lbl_803ECF34, lbl_803ECF38, pitch, lbl_803ECF3C, lbl_803ECF40, mode);
}

void fn_801DB89C(void *pDst)
{
    int pitch;
    int mode;

    fn_801CE82C();
    pitch = (fn_801CEA08() + 15) & 0xFFF0;
    mode = fn_801CE944((unsigned char)fn_801CE930());
    fn_801DBEB4(pDst, lbl_803ECF34, lbl_803ECF38, pitch, lbl_803ECF3C, lbl_803ECF40, mode);
}
