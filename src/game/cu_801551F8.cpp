#include "game/Class_802A56E8.h"

class Class_802A17A8 : public Class_802A56E8 {
public:
    unsigned char mUnknown4;
};

extern "C" {
extern unsigned char lbl_803EB2FC;
extern unsigned char lbl_803EB2FD;
float fn_80178A2C(void);
void fn_80178E88(float value);
int fn_80177F70(void);
int fn_80178308(void);
int fn_801787DC(int team);
int fn_800A8444(int team);
float fn_80237260(int stream);

int fn_801551F8(Class_802A17A8 *p)
{
    int mode = fn_80177F70();
    int team = fn_80178308();
    int other = !team;
    unsigned short score = fn_801787DC(team);
    unsigned short otherScore = fn_801787DC(other);

    int result;

    if (mode == 6) {
        if (fn_800A8444(team)) {
            result = score + 2;
        } else if (score == otherScore + 6) {
            result = fn_80237260(0) < 0.5f ? otherScore + 7 : otherScore + 8;
        } else {
            result = score == otherScore ? score + 1 : score + 2;
        }
    } else {
        result = (otherScore < score ? score : otherScore) + 8;
    }
    return result;
}

void fn_801552C4(Class_802A17A8 *p, int flip)
{
    if (!lbl_803EB2FC) {
        float distance = fn_80178A2C() * 2.0f -
                         ((lbl_803EB2FD / 2) * 10.0f + 18.0f);
        if (!(distance >= 1.0f)) {
            distance = 1.0f;
        }
        fn_80178E88(distance);
        lbl_803EB2FC = 1;
        ++lbl_803EB2FD;
    }
    p->Class_802A56E8::vfn_20(flip);
}
}
