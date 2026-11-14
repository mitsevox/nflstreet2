/* Seeds speech choices and keeps recent choices to limit repeats within each category. */

#include "engine/spchlib.h"

extern "C" {

// Generator state: iSPCH_EACseedrandom(0) expanded, so drawing works before any seeding.
unsigned int seedX[6] = {0xF22D0E56U, 0x883126E9U, 0xC624DD2FU, 0x0702C49CU, 0x9E353F7DU, 0x6FDF3B64U};
// Recent choices as value/category pairs, and the index of the newest one.
unsigned short gRandArray[32][2];
int gRandArrayIndex = 0;

// The six state words advance together from the supplied seed.
void iSPCH_EACseedrandom(unsigned int seed)
{
    seedX[0] = seed + 0xF22D0E56U;
    seedX[1] = seedX[0] + 0x96041893U;
    seedX[2] = seedX[1] + 0x3DF3B646U;
    seedX[3] = seedX[2] + 0x40DDE76DU;
    seedX[4] = seedX[3] + 0x97327AE1U;
    seedX[5] = seedX[4] + 0xD1A9FBE7U;
}

// Recency counts entries from this category, starting with the newest choice.
int iSPCH_FindRandInQueue(int value, int count, int id)
{
    int result = -1;
    if (count > 32) count = 32;
    int index = gRandArrayIndex;
    int matched = 0;
    int scanned = 0;
    int done = 0;
    do {
        if (matched < count) {
            if (gRandArray[index][1] == id) {
                matched++;
                if (gRandArray[index][0] == value) {
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

// Advance before storing so the index always identifies the newest entry.
void iSPCH_AddRandToQueue(int value, int id)
{
    if (++gRandArrayIndex > 31) gRandArrayIndex = 0;
    gRandArray[gRandArrayIndex][0] = value;
    gRandArray[gRandArrayIndex][1] = id;
}

// Empty the history, expand the seed, and advance the generator without recording choices.
void iSPCH_InitRandom(int seed)
{
    int i;
    for (i = 0; i <= 31; i++) {
        gRandArray[i][0] = 65535;
        gRandArray[i][1] = 65535;
    }
    seed += seed << 16;
    gRandArrayIndex = 0;
    iSPCH_EACseedrandom(seed);
    int count = 32 - seed % 32;
    for (i = 0; i < count; i++) {
        iSPCH_Rand(10, -1);
    }
}

// Limit repeat retries; record the preferred candidate but return the last draw.
int iSPCH_Rand(int count, int id)
{
    int tries = 0;
    int done = 0;
    int best = -1;
    int limit = count / 2;
    if (limit > 10) limit = 10;
    int value = ((iSPCH_EACrandom() >> 16) * count) >> 16;
    int selected = value;
    if (id != -1) {
        id = (unsigned short)id;
        do {
            int age = iSPCH_FindRandInQueue(value, limit, id);
            if (age == -1) {
                selected = value;
                done = 1;
            } else if (age > best) {
                best = age;
                selected = value;
            }
            if (++tries > 31) done = 1;
            if (!done) value = ((iSPCH_EACrandom() >> 16) * count) >> 16;
        } while (!done);
        iSPCH_AddRandToQueue(selected, id);
    }
    return value;
}

}
