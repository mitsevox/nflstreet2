#include "game/fn_801FCE10.h"
#include "game/fn_8017F584.h"
#include "game/Settings_800B4448.h"

extern "C" {
void fn_800497F4(int unused, int id, unsigned short *pValues);
short fn_80157448(int team, int unused, short value);
short fn_80148698(int team, int index, short value);
short fn_800ABE10(int team, int index, short value);
short fn_8009AC18(int team, int index, short value);
short fn_800A8224(int team, int unused, int index, short value);
float fn_800A0134(int team, int unused, int index);
}

extern "C" void fn_800B4798(short *pRatings, int team, int index, float *pOut)
{
    unsigned short id = *(unsigned short *)((char *)pOut + 8);
    unsigned short bonuses[10];
    float scale = 1.0f;

    fn_800497F4(team, id, bonuses);
    for (unsigned int i = 0; i <= 9; i++) {
        short value = pRatings[i] + bonuses[i];

        if (value <= 0) {
            value = 1;
        } else if (value > 255) {
            value = 255;
        }
        value = fn_80157448(team, i, value);
        value = fn_80148698(team, i, value);
        value = fn_800ABE10(team, i, value);
        value = fn_8009AC18(team, i, value);
        value = fn_800A8224(team, index, i, value);
        pRatings[i] = (short)(value * scale * fn_800A0134(team, (unsigned char)id, i));
    }
}

extern "C" void fn_800B4900(QueryCursor cursor, int index, short *pRatings, void *pOut)
{
    int values[10];
    cursor.mUnknown4 = index;
    fn_801FCE10(0,
        "fetch from \x8a 'IGAP' into \x82 and 'MUJP' into \x82 and 'KTBP' into \x82 and "
        "'HTCP' into \x82 and 'DPSP' into \x82 and 'KATP' into \x82 and 'SSPP' into \x82 and "
        "'KLBP' into \x82 and 'VOCP' into \x82 and 'TFDP' into \x82\n",
        &cursor, &values[0], &values[1], &values[2], &values[3], &values[4],
        &values[5], &values[6], &values[7], &values[8], &values[9]);
    if (fn_8017F584() == 0) fn_800B4448((Settings_800B4448 *)values);
    short *pOtherRatings = (short *)pOut;
    for (unsigned short i = 0; i <= 9; i++) {
        int value = ((short)values[i] * 255) / 99;
        pRatings[i] = value;
        pOtherRatings[i] = value;
    }
}
