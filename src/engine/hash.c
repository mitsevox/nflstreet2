#include "engine/Resource.h"

extern unsigned int strlen(const char *s);
extern int toupper(int c);

int fn_801F34C0(char *pString, int multiplier)
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
