/* PATH random numbers (pathrand.c): the six-word add-with-carry generator the music library draws
   its random branch choices from. */

#include "engine/pathlib.h"

extern "C" {

// Generator state, already seeded so drawing works before any seeding.
unsigned int seedPATH[6] = {0xF22D0E56U, 0x883126E9U, 0xC624DD2FU, 0x0702C49CU, 0x9E353F7DU, 0x6FDF3B64U};

// Add the state words together with carry, then step the six-word counter; returns the leading word.
unsigned int PATHI_random(void)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *format = "%s  %s";

    unsigned int sum = seedPATH[5] + seedPATH[4];
    unsigned int carry = 0;
    if (sum < seedPATH[5] || sum < seedPATH[4])
        carry = 1;
    unsigned int a = seedPATH[3];
    unsigned int b = seedPATH[2];
    unsigned int c = seedPATH[1];
    unsigned int e = seedPATH[0];
    seedPATH[4] = sum;
    sum = sum + a + carry;
    seedPATH[3] = sum;
    carry = sum < a;
    sum = sum + b + carry;
    seedPATH[2] = sum;
    carry = sum < b;
    sum = sum + c + carry;
    seedPATH[1] = sum;
    carry = sum < c;
    sum = sum + e + carry;
    seedPATH[0] = sum;
    if (++seedPATH[5] == 0)
        if (++seedPATH[4] == 0)
            if (++seedPATH[3] == 0)
                if (++seedPATH[2] == 0)
                    if (++seedPATH[1] == 0)
                        sum = ++seedPATH[0];
    return sum;
}

}
