#include <dolphin/mtx.h>

extern "C" {
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0F80(Mtx44 m);
void fn_80210388(void);
int fn_80236EC0(int a);
void fn_8024CB90(int a, int b);
void fn_8024D418(void);
void fn_8024D450(int a, int b, int c, int d, int e);
void fn_8024DCE4(int a, int b, int c, int d, int e, int f);
void fn_8024DF64(int a);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void fn_80251604(int a, int b);
void fn_80251A58(int a, int b, int c, int d, int e);
void fn_80251B28(int a, int b, int c, int d);
void fn_80251CC4(int a);
void fn_80252034(int a, int b, int c, int d);
void fn_80252448(float *p);
void fn_802524D4(float *p);
void fn_8025251C(Mtx44 m, int a);
void fn_802525BC(int a);
}

static float lbl_803651E4[7];
static unsigned char lbl_803ECBE0;

extern "C" {
void fn_801981D8(void *p, int value)
{
    Mtx44 mtx;

    fn_80210388();
    fn_802525BC(0);
    fn_801D0508();
    fn_801D0F80(mtx);
    fn_8025251C(mtx, 0);
    fn_8024D418();
    fn_8024CB90(9, 1);
    fn_8024CB90(13, 1);
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 0, 0, 1, 2, 2);
    fn_80251CC4(1);
    fn_8024D450(0, 9, 1, 4, 0);
    fn_8024D450(0, 13, 1, 4, 0);
    fn_80251A58(4, 0, 0, 4, 0);
    fn_80251B28(0, 0, 0, 4);
    fn_80251604(0, 0);
    fn_8024DF64(1);
    fn_8024DCE4(0, 0, 4, 60, 0, 125);
    fn_80252034(1, 4, 1, 5);
    fn_802524D4(lbl_803651E4);
    lbl_803ECBE0 = fn_80236EC0(0);
}

void fn_8019831C(void *p, int value)
{
    Mtx44 mtx;

    fn_801D0544();
    fn_801D0F80(mtx);
    fn_8025251C(mtx, 0);
    fn_80252034(0, 0, 0, 5);
    fn_80252448(lbl_803651E4);
    fn_80236EC0(lbl_803ECBE0);
}
}
