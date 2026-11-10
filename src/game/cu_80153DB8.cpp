#include "game/Class_80297AB8.h"
#include "game/Class_80297B50.h"
#include "game/Object_80039F5C.h"
#include "game/AudmonEvent.h"
#include "game/fn_800B65A0.h"
#include "game/fn_8009D990.h"
#include "game/fn_802372EC.h"

class Class_802A1B18 : public Class_80297B50 {
};

class Class_802A1AE0 : public Class_80297AB8 {
public:
    int mUnknown4;
};

struct Team_80168EBC {
    char mUnknown0[0x40];
    int mUnknown40;
};

extern "C" {
extern int lbl_803EB2F4;

int fn_80178308(void);
int fn_80178320(void);
void PlayBookSetFormationType(int team, int kind);
void PlayBookSetIndices(int team, unsigned int a, unsigned int b, unsigned int c);
void PlayBookLoadCurrentPlay(int team);
Team_80168EBC *PlayBookGetTeam(int team);
int fn_80085A34(int formation, int team);
void fn_800B3EFC(int team);
void PlayBookLoadAudibles(int team);
void fn_800AD910(int a, float b);
void fn_8009D888(int index, int value);
void CamGameResumeAll(void);
void fn_8016DDDC(int team);
void fn_801790D0(int team, float a, float b);
int fn_801787A0(void);
void HudShowAlert(const char *pText);
void fn_80178370(void);
int fn_80177C38(void);
void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);

void fn_80153DB8(Class_802A1B18 *p)
{
}

void fn_80153DBC(Class_802A1B18 *p, float dt)
{
    int team = fn_80178308();
    int other = !team;
    unsigned int flag = fn_802372EC(0, 100) & 1;

    PlayBookSetFormationType(team, 1);
    PlayBookSetFormationType(other, 11);
    PlayBookSetIndices(team, 0, 0, fn_800B65A0(team) == 255 ? flag : 0);
    PlayBookLoadCurrentPlay(team);
    fn_80085A34(PlayBookGetTeam(team)->mUnknown40, team);
    PlayBookSetIndices(other, 0, 0, 0);
    PlayBookLoadCurrentPlay(other);
    fn_800B3EFC(team);
    fn_800B3EFC(other);
    PlayBookLoadAudibles(fn_80178308());
    fn_800AD910(2, dt);
}

void fn_80153EA8(Class_802A1B18 *p)
{
    fn_8009D888(0, 10);
    CamGameResumeAll();
    fn_8016DDDC(fn_80178308());
    fn_8016DDDC(fn_80178320());
    fn_801790D0(fn_80178308(), 0.0f, 0.0f);
    fn_801790D0(fn_80178320(), 18.0f, 0.0f);
}

void fn_80153F14(Class_802A1AE0 *p)
{
    p->Class_80297AB8::vfn_03();
    p->mUnknown4 = 0;
    fn_8009D888(5, 0);
}

void fn_80153F54(Class_802A1AE0 *p, float dt)
{
    p->Class_80297AB8::vfn_04(dt);
    if (fn_801787A0() == 0) {
        if (fn_8009D990(5) == 0) {
            HudShowAlert("Time Expired");
            fn_80178370();
        } else {
            unsigned int value;

            if (fn_80177C38() % 2 != (p->mUnknown4 & 1)) {
                p->mUnknown4++;
                fn_8009D8CC(5);
                fn_8009D964(5, 20);
                fn_8009D888(5, 0);
            }
            value = fn_8009D990(5);
            if (value != lbl_803EB2F4) {
                lbl_803EB2F4 = value;
                if (value <= 5) {
                    AudmonEventPost(20, 0);
                }
            }
        }
    }
}

void fn_80154028(Class_802A1AE0 *p)
{
    p->Class_80297AB8::vfn_05();
    fn_8009D8CC(5);
}
}
