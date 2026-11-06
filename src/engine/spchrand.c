/* Seeds speech choices and keeps recent choices to limit repeats within each category. */

#include "engine/spchlib.h"

extern "C" {

// The six state words advance together from the supplied seed.
void iSPCH_EACseedrandom(unsigned int seed)
{
    gSpchRandomState[0] = seed + 0xF22D0E56U;
    gSpchRandomState[1] = gSpchRandomState[0] + 0x96041893U;
    gSpchRandomState[2] = gSpchRandomState[1] + 0x3DF3B646U;
    gSpchRandomState[3] = gSpchRandomState[2] + 0x40DDE76DU;
    gSpchRandomState[4] = gSpchRandomState[3] + 0x97327AE1U;
    gSpchRandomState[5] = gSpchRandomState[4] + 0xD1A9FBE7U;
}

#if defined(DECOMP_COMPARE)
// Recency counts entries from this category, starting with the newest choice.
int iSPCH_FindRandInQueue(int value, int count, int id)
{
    int result = -1;
    if (count > 32) count = 32;
    int index = _SpchRandom_iHistoryIndex;
    int matched = 0;
    int scanned = 0;
    int done = 0;
    do {
        if (matched < count) {
            if (_SpchRandom_aHistory[index][1] == id) {
                matched++;
                if (_SpchRandom_aHistory[index][0] == value) {
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
    if (++_SpchRandom_iHistoryIndex > 31) _SpchRandom_iHistoryIndex = 0;
    _SpchRandom_aHistory[_SpchRandom_iHistoryIndex][0] = value;
    _SpchRandom_aHistory[_SpchRandom_iHistoryIndex][1] = id;
}

// Empty the history, expand the seed, and advance the generator without recording choices.
void iSPCH_InitRandom(int seed)
{
    for (int i = 0; i <= 31; i++) {
        _SpchRandom_aHistory[i][1] = 65535;
        _SpchRandom_aHistory[i][0] = 65535;
    }
    seed += seed << 16;
    _SpchRandom_iHistoryIndex = 0;
    iSPCH_EACseedrandom(seed);
    int count = 32 - seed % 32;
    for (int i = 0; i < count; i++) {
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
#endif

}
