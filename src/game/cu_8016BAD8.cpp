#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_802372EC.h"

extern "C" {
Object_800670B4 *fn_80168708(int team);
int fn_80169F80(int value);
void fn_8016B438(int team, unsigned char *pOut, unsigned int *pFlags);
float fn_80178A5C(void);

// Randomly flips the side flag of team's object, more or less likely
// depending on the ball position and the tendencies fn_8016B438 reports.
// Returns 1 when the flag was flipped.
int fn_8016BAD8(int team)
{
    int flipped = 0;
    int chance = 50;
    Record_80067338 *pRecord = fn_8016871C(team);
    Object_800670B4 *pObject = fn_80168708(team);
    float x;
    unsigned char kind;
    unsigned int flags;

    if ((pObject->mUnknown8.mUnknown14 & 1) == 0 || (fn_8016871C(team)->mUnknown18 & 1) == 0) {
        return 0;
    }

    x = fn_80177FE0().mX;
    fn_8016B438(team, &kind, &flags);
    switch (fn_80169F80(pRecord->mUnknown17)) {
    case 1:
        if (pRecord->mUnknown18 & 2) {
            if (x < 0.1f - fn_80178A5C()) {
                chance = 67;
            } else if (x > fn_80178A5C() - 0.1f) {
                chance = 33;
            }
            if (flags & 8) {
                chance += 15;
            }
            if (flags & 2) {
                chance -= 15;
            }
        }
        if (pRecord->mUnknown18 & 8) {
            if (x > fn_80178A5C() - 0.1f) {
                chance += 17;
            } else if (x < 0.1f - fn_80178A5C()) {
                chance -= 17;
            }
            if (flags & 2) {
                chance += 15;
            }
            if (flags & 8) {
                chance -= 15;
            }
        }
        break;
    case 2:
        if (pRecord->mUnknown18 & 0x80) {
            if (x < 0.1f - fn_80178A5C()) {
                chance = 67;
            } else if (x > fn_80178A5C() - 0.1f) {
                chance = 33;
            }
            if (flags & 0x200) {
                chance += 15;
            }
            if (flags & 0x80) {
                chance -= 15;
            }
        }
        if (pRecord->mUnknown18 & 0x200) {
            if (x > fn_80178A5C() - 0.1f) {
                chance += 17;
            } else if (x < 0.1f - fn_80178A5C()) {
                chance -= 17;
            }
            if (flags & 0x80) {
                chance += 15;
            }
            if (flags & 0x200) {
                chance -= 15;
            }
        }
        break;
    default:
        chance = 0;
        break;
    }

    if (fn_802372EC(0, 100) < chance) {
        flipped = 1;
        pObject->mUnknown8.mUnknownF ^= 1;
    }
    return flipped;
}
}
