#include "game/Class_802A56E8.h"

class Class_802A17A8 : public Class_802A56E8 {
public:
    unsigned char mUnknown4;
};

extern "C" {
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
}
