#include "game/Class_802A56E8.h"
#include "game/Object_8017886C.h"

class Class_802A17A8 : public Class_802A56E8 {
public:
    unsigned char mUnknown4;
};

extern "C" {
extern unsigned char lbl_803EB2FC;

int fn_80177F70(void);
void fn_80177F88(int value);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_801787DC(int team);
void fn_80178CD8(int a);
unsigned short fn_80178E94(void);

void fn_8015539C(Class_802A17A8 *p)
{
    int a = 1;
    Object_8017886C *o = fn_8017886C();
    if (fn_80178348() == fn_80178308()) {
        a = 0;
    }
    unsigned int score0 = fn_801787DC(0);
    unsigned int score1 = fn_801787DC(1);
    unsigned short flags = fn_80178E94();
    lbl_803EB2FC = 0;
    p->Class_802A56E8::vfn_10();
    if (p->mUnknown4 == 2) {
        if (o->mUnknown1D == -2) {
            int team = fn_80178320();
            if ((team == 0 && score0 > score1) || (team == 1 && score0 < score1)) {
                p->mUnknown4 = team;
            }
        } else if (o->mUnknown1D > 0) {
            int team = fn_80178308();
            if (a) {
                if ((team == 0 && score0 > score1) || (team == 1 && score0 < score1)) {
                    p->mUnknown4 = team;
                }
            } else if (flags & 1) {
                if (team == 0) {
                    if (score0 > score1) {
                        p->mUnknown4 = 0;
                    } else if (o->mUnknown1D != 6 && score0 < score1) {
                        p->mUnknown4 = 1;
                    }
                } else {
                    if (score0 < score1) {
                        p->mUnknown4 = 1;
                    } else if (o->mUnknown1D != 6 && score0 > score1) {
                        p->mUnknown4 = 0;
                    }
                }
            }
        } else if ((a && (flags & 1) == 0) || ((o->mUnknown18 & 4) && (flags & 1))) {
            if (score0 > score1) {
                p->mUnknown4 = 0;
            } else if (score0 < score1) {
                p->mUnknown4 = 1;
            }
        }
        if (p->mUnknown4 != 2 && fn_80177F70() == 6) {
            fn_80177F88(1);
        }
    }
    if (a && fn_80177F70() == 1) {
        fn_80178CD8(1);
    } else if (o->mUnknown18 & 0x900) {
        fn_80178CD8(0);
    }
}
}
