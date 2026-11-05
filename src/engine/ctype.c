/* Character case conversion (toupper, tolower) over the engine's character-class table. */

#include "engine/ctype.h"
#include <ctype.h>

extern const unsigned char lbl_802AEF10[];

#define CTYPE(c) ((lbl_802AEF10 + 1)[(unsigned char)(c)])

int toupper(int c)
{
    if (CTYPE(c) & 2) {
        c -= 'a' - 'A';
    }
    return c;
}

int tolower(int c)
{
    if (CTYPE(c) & 1) {
        c += 'a' - 'A';
    }
    return c;
}
