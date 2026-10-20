#include "game/Class_80148A58.h"
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
}
