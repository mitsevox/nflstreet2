/* Case-insensitive string hash used by the resource name tables. */

#include "engine/Resource.h"

extern unsigned int strlen(const char *s);
extern int toupper(int c);

int HashString(char *pString, int multiplier)
{
    int hash = 0;
    int scale;
    int i;

    scale = 1;
    for (i = strlen(pString) - 1; i >= 0; i--) {
        hash += toupper(pString[i]) * scale;
        scale *= multiplier;
    }
    return hash;
}
