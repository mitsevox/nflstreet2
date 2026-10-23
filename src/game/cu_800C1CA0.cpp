#include "game/cu_8002B8F8.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8017F584.h"

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

extern "C" {
int fn_800AD9B4(void);
void fn_800BA7E8(float x, float y);
Camera_8013F738 *fn_8013FA04(int index);
void fn_80178370(void);
int fn_801784C4(void);
float fn_80178A2C(void);
float fn_80178A5C(void);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
void fn_8002B71C(void);
void fn_8002D274(Type_803EA368 *p);
void fn_8003A4DC(void);
void fn_800406C0(unsigned int flags);
void fn_800588E0(void);
void fn_80071C34(int value);
void fn_80073328(int resume);
void fn_80073764(void);
unsigned char fn_800737C0(void);
void fn_80074250(int index);
void fn_8009D8CC(int index);
void fn_800A7A0C(int team);
void fn_800A7E68(void);
int fn_800A8740(void);
void fn_800AD910(int mode, float dt);
void fn_800B4184(int a);
void fn_800B63B0(void);
void fn_800D6F08(void);
void fn_800D7158(void);
void fn_8013F3FC(void);
void fn_80148154(void);
void fn_801483C8(void);
void fn_8016BA80(void);
void fn_801735D8(unsigned int mask);
void fn_80173C1C(void);
void fn_80173C2C(void);
void fn_80173D10(void);
void fn_80176C58(void);
void fn_80176C90(void);
void fn_80177B7C(int a);
void fn_8017833C(int value);
void fn_80178354(int value);
int fn_80178AE0(void);
void fn_8017D4AC(void);
int fn_8022BF68(void);
int fn_8022DD4C(int value);
int fn_8022DD80(int value);
void fn_8009D818(int state);
void fn_80162780(int a, int b);


extern unsigned char lbl_803EABB8;
extern unsigned char lbl_803EABB9;
}

extern "C" void fn_800C1CA0(void)
{
    unsigned char team;

    lbl_803EABB9 = 1;
    team = fn_80178AE0();
    lbl_803EABB8 = 1;
    fn_80173C1C();
    fn_80173C2C();
    fn_80176C58();
    fn_80173D10();
    fn_80176C90();
    fn_800406C0(0x100);
    fn_8022DD4C(0);
    fn_8022DD80(0);
    if (fn_8017F584() == 6) {
        fn_8002B71C();
    } else {
        fn_80177B7C(team);
    }
    fn_8002D274(lbl_803EA368);
    fn_8016BA80();
    fn_8022BF68();
    fn_800D6F08();
    fn_800D7158();
    fn_80071C34(0);
    if (fn_800737C0()) {
        fn_80073764();
    }
    fn_80074250(0);
    fn_80074250(1);
    fn_80074250(2);
    fn_80162780(0, 0);
    fn_8013F3FC();
    if (fn_800A8740() == 0) {
        fn_800A7A0C(0);
        fn_800A7A0C(1);
    }
    fn_800A7E68();
    if (fn_800AD9B4() == 7 || fn_800AD9B4() == 0) {
        fn_8009D818(0);
    } else {
        fn_800B4184(1);
        fn_800588E0();
        fn_8003A4DC();
        fn_800B63B0();
        fn_8009D818(0);
        fn_800AD910(1, 0.0f);
    }
    if (fn_8017F584() == 8) {
        fn_8017833C(1);
        fn_80178354(1);
    }
    fn_801735D8(0x800);
    fn_8009D8CC(1);
    fn_8009D8CC(5);
    fn_8009D8CC(0);
    fn_8017D4AC();
    fn_80148154();
    fn_801483C8();
    fn_80073328(0);
    lbl_803EABB9 = 0;
}

extern "C" void fn_800C1E5C(int a, unsigned int b, float c)
{
    Object_80137ABC *pBall = fn_801374BC();
    Vector_80039F5C pos;
    Point_8017886C delta;

    fn_80137D58(pBall, &pos);
    delta.mX = 0.0f;
    delta.mY = 0.0f;
    switch (b) {
    case 0:
    case 7:
        if (c > 0.0f) {
            fn_800BA7E8(pos.mX, pos.mY);
            fn_80178370();
        }
        break;
    case 52:
        delta.mY = c * -0.16f;
        break;
    case 53:
        delta.mX = c * -0.16f;
        break;
    case 16:
    case 54:
        delta.mX = c * 0.16f;
        break;
    case 17:
    case 51:
        delta.mY = c * 0.16f;
        break;
    }
    if (fn_801784C4()) {
        delta.mX = -delta.mX;
        delta.mY = -delta.mY;
    }
    fn_80227384(&delta, &delta, (0x1000000 - fn_8013FA04(0)->mHeader.mUnknown14[2]) & 0xFFFFFF);
    pos.mX += delta.mX;
    pos.mY += delta.mY;
    pos.mX = CLAMP(pos.mX, -fn_80178A5C(), fn_80178A5C());
    pos.mY = CLAMP(pos.mY, 0.33f - fn_80178A2C(), fn_80178A2C() - 0.33f);
    fn_80137D74(pBall, &pos);
}
