extern "C" {
extern char lbl_8031B7D0[];
extern unsigned char lbl_803EB249;

void fn_80196F48(void *pObject, float value);

void fn_80145224(void);
void fn_80145264(void);
}

static float lbl_803EB244 = 0.05f;
static unsigned char lbl_803EB248 = 0;
unsigned char lbl_803EB249 = 0;

void fn_80145224(void)
{
    lbl_803EB244 += 0.14750001f;
    if (lbl_803EB244 > 3.0f) {
        lbl_803EB248 = 0;
        lbl_803EB244 = 0.05f;
    }
}

void fn_80145264(void)
{
    if (lbl_803EB248 == 1) {
        fn_80196F48(lbl_8031B7D0, lbl_803EB244);
    }
}
