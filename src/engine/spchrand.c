/* Speech random numbers (spchrand.c): the seeded random generator the picker uses. */

#include "engine/spchlib.h"

extern "C" {

unsigned int fn_801B1A3C(unsigned int seed)
{
    seed += 0xF22D0E56U;
    unsigned int first = seed;
    lbl_802F477C[0] = seed;
    seed += 0x96041893U;
    lbl_802F477C[1] = seed;
    seed += 0x3DF3B646U;
    lbl_802F477C[2] = seed;
    seed += 0x40DDE76DU;
    lbl_802F477C[3] = seed;
    seed += 0x97327AE1U;
    lbl_802F477C[4] = seed;
    seed += 0xD1A9FBE7U;
    lbl_802F477C[5] = seed;
    return first;
}

int fn_801B1A90(int value, int count, int id)
{
    int result = -1;
    if (count > 32) count = 32;
    int index = lbl_803EBB20;
    int matched = 0;
    int scanned = 0;
    int done = 0;
    do {
        if (matched < count) {
            if (lbl_8037E794[index][1] == id) {
                matched++;
                if (lbl_8037E794[index][0] == value) {
                    done = 1;
                    result = matched - 1;
                }
            }
        } else {
            done = 1;
        }
        if (--index < 0) index += 32;
        if (++scanned > 32) done = 1;
    } while (!done);
    return result;
}

void fn_801B1B34(int value, int id)
{
    if (++lbl_803EBB20 > 31) lbl_803EBB20 = 0;
    lbl_8037E794[lbl_803EBB20][0] = value;
    lbl_8037E794[lbl_803EBB20][1] = id;
}

void fn_801B1B70(int seed)
{
    for (int i = 0; i <= 31; i++) {
        lbl_8037E794[i][1] = 65535;
        lbl_8037E794[i][0] = 65535;
    }
    seed += seed << 16;
    lbl_803EBB20 = 0;
    fn_801B1A3C(seed);
    int count = 32 - seed % 32;
    for (int i = 0; i < count; i++) {
        fn_801B1C1C(10, -1);
    }
}

int fn_801B1C1C(int count, int id)
{
    int tries = 0;
    int done = 0;
    int best = -1;
    int limit = count / 2;
    if (limit > 10) limit = 10;
    int value = ((fn_801B1934() >> 16) * count) >> 16;
    int selected = value;
    if (id != -1) {
        id = (unsigned short)id;
        do {
            int age = fn_801B1A90(value, limit, id);
            if (age == -1) {
                selected = value;
                done = 1;
            } else if (age > best) {
                best = age;
                selected = value;
            }
            if (++tries > 31) done = 1;
            if (!done) value = ((fn_801B1934() >> 16) * count) >> 16;
        } while (!done);
        fn_801B1B34(selected, id);
    }
    return value;
}

}
