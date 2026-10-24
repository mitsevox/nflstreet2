#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/cu_8003E214.h"
#include "game/fn_80178D18.h"

class Class_802A27F0 : public Class_80148A58 {
public:
    char mUnknown1C[8];
    unsigned char mUnknown24;
};

extern "C" {
extern int lbl_802DEB08[];
extern int lbl_802DEB40[];
extern const char lbl_802A05C8[];

int fn_80178EA0(int team);
int fn_80178EE0(int team);
int fn_80155130(Class_80148A58 *p, int team, unsigned char index);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
void fn_8017E17C(int slot, const char *pText0, const char *pText1,
                 const char *pText2, int key);

void fn_80154638(Class_802A27F0 *p, int value, int *pList, int *pIds, unsigned int count)
{
    int second = pList[1];
    int found = 0;
    int first;
    unsigned char i;

    fn_8003E8FC(value, pList, pIds);
    first = pList[0];
    if (fn_80178D70(0) == 1) {
        for (i = 0; i <= 6; i++) {
            if (pIds[i] == first) {
                pIds[i] = pIds[lbl_802DEB08[0]];
                pIds[lbl_802DEB08[0]] = first;
                break;
            }
        }
        for (i = 7; i <= 13; i++) {
            if (pIds[i] == first) {
                pIds[i] = pIds[lbl_802DEB08[7]];
                pIds[lbl_802DEB08[7]] = first;
                break;
            }
        }
    } else {
        unsigned char j;

        for (j = 0; j <= 13; j++) {
            unsigned char k;

            for (k = 1; k < count; k++) {
                if (pIds[lbl_802DEB40[j]] == pList[k]) {
                    second = pIds[lbl_802DEB40[j]];
                    found = 1;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        for (i = 0; i <= 6; i++) {
            if (pIds[i] == first) {
                pIds[i] = pIds[lbl_802DEB08[0]];
                pIds[lbl_802DEB08[0]] = first;
            }
        }
        for (i = 0; i <= 6; i++) {
            if (pIds[i] == second) {
                pIds[i] = pIds[lbl_802DEB08[1]];
                pIds[lbl_802DEB08[1]] = second;
            }
        }
        for (i = 7; i <= 13; i++) {
            if (pIds[i] == first) {
                pIds[i] = pIds[lbl_802DEB08[7]];
                pIds[lbl_802DEB08[7]] = first;
            }
        }
        for (i = 7; i <= 13; i++) {
            if (pIds[i] == second) {
                pIds[i] = pIds[lbl_802DEB08[8]];
                pIds[lbl_802DEB08[8]] = second;
            }
        }
    }
}

void fn_801548EC(Class_802A27F0 *p, int team, int showColors)
{
    char text[16];
    int first = fn_80178EE0(team);
    int color = 255;
    int second = fn_80178EA0(team);

    fn_801C2E18(text, "%d / %d", first, second);
    if (p->mUnknown24 == 1) {
        int slot = team == 1 ? 1 : 2;
        Object_80039F5C *pPlayer = fn_80039F5C(team, 0);

        if (showColors) {
            color = fn_80155130(p, team, 0);
            if (color == 255) {
                color = 254;
            }
        }
        fn_8017E17C(slot, pPlayer->mUnknown2927 + 21, text, lbl_802A05C8, color);
    } else {
        int slot = team == 1 ? 1 : 3;
        Object_80039F5C *pPlayer = fn_80039F5C(team, 0);

        if (showColors) {
            color = fn_80155130(p, team, 0);
            if (color == 255) {
                color = 254;
            }
        }
        fn_8017E17C(slot, pPlayer->mUnknown2927 + 21, text, lbl_802A05C8, color);
        pPlayer = fn_80039F5C(team, 1);
        if (showColors) {
            color = fn_80155130(p, team, 1);
            if (color == 255) {
                color = 254;
            }
        }
        fn_8017E17C(slot + 1, pPlayer->mUnknown2927 + 21, lbl_802A05C8,
                   lbl_802A05C8, color);
    }
}
}
