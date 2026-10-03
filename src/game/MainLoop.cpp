extern "C" {
extern char lbl_803653D4[];
extern char lbl_803067B0[];

void fn_80023048(void);
void fn_801CBCD0(void *pObject);
int fn_801CBD80(void *pObject, int a, int b);
void fn_801CBFA8(void *pObject);
void fn_801CC054(void *pObject, int a);
int fn_801CC7FC(void *pObject);
int fn_801CC820(void *pObject, int a);
int fn_801CC8AC(void *pObject, int a);
void fn_801D64EC(void);
int fn_801F3D2C(void);
}

/* Set by fn_80026BA4; ends the loop in fn_80026AF8. */
static unsigned char sDone = 0;
float lbl_803EA2C4 = 1.0f;

static void fn_80026AD0(void)
{
    fn_801CBFA8(lbl_803067B0);
}

void fn_80026AF8(void)
{
    char *pRoot = lbl_803653D4;
    fn_801CC7FC(pRoot);
    fn_801CC820(pRoot, 0);

    char *pObject = lbl_803067B0;
    fn_801CBCD0(pObject);
    fn_801CC054(pObject, 0);
    fn_801CBD80(pObject, 0, -1);
    fn_801CBD80(pObject, 2, 7);

    while (!sDone) {
        fn_80026AD0();
    }

    fn_80023048();
    fn_801F3D2C();
    fn_801D64EC();
    fn_801CC8AC(lbl_803653D4, 0);
}

void fn_80026BA4(void)
{
    sDone = 1;
}
