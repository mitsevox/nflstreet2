/* TM renderer names: exact and wildcard name comparison and splitting of "dir/name" paths, used
   by the registries. */

#include "engine/tmlib.h"

extern int strcmp(const char *s1, const char *s2);
extern char *strcpy(char *dest, const char *src);

int TMNameCompareExact(const char *pName, const char *pOther)
{
    return strcmp(pName, pOther) == 0;
}

int TMNameCompareWildcard(const char *pPattern, const char *pName)
{
    while (*pPattern == *pName) {
        if (*pPattern == '\0') {
            return 1;
        }
        pPattern++;
        pName++;
    }
    return *pPattern == '*';
}

void TMNameSplitPath(const char *pPath, char *pDir, char *pFile)
{
    int i;

    for (i = 0; pPath[i] != '\0'; i++) {
        if (pPath[i] == '/') {
            memcpy(pDir, pPath, i);
            pDir[i] = '\0';
            strcpy(pFile, &pPath[i + 1]);
            return;
        }
    }
    strcpy(pDir, "*");
    strcpy(pFile, pPath);
}
