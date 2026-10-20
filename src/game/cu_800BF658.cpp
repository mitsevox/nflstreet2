#include "game/Block_800BFAD0.h"
#include "game/fn_800B65A0.h"

extern "C" {
void fn_800BE808(int a, unsigned char index);
void fn_800BE944(unsigned char index, int team, int kind, float value);
void fn_8003A3F4(int a, int index);
void fn_800BD774(unsigned char index);
void fn_800BED54(unsigned char index);
void fn_800BEFAC(int index);
void fn_800BD830(void);

extern float lbl_803EABAC[2];
}

extern "C" void fn_800BF658(int index)
{
    int team = fn_800B65A0(index);

    lbl_803EABA8->mSlots[index].mUnknown1C = 1;
    fn_800BE808(team, index);
    fn_800BE944(index, team, 132, 1.0f);
    fn_8003A3F4(1, index);
}

extern "C" void fn_800BF72C(float dt)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        switch (lbl_803EABA8->mSlots[i].mUnknown0) {
        case 4:
        case 5:
            fn_800BD774(i);
            break;
        case 8:
            lbl_803EABAC[i] -= dt;
            if (lbl_803EABAC[i] > 0.0f) {
                break;
            }
        case 2:
            lbl_803EABA8->mSlots[i].mUnknown0 = 0;
            break;
        case 6:
            fn_800BED54(i);
            break;
        case 7:
            fn_800BEFAC((unsigned char)i);
            break;
        }
    }
    if (lbl_803EABA8->mUnknownC0 > 0) {
        lbl_803EABA8->mUnknownC0--;
    }
    fn_800BD830();
}

