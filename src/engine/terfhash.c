#include "engine/Resource.h"

extern unsigned int strlen(const char *s);
extern void *fn_801D2B7C(int size, int a, int b);
extern int fn_801F34C0(char *pString, int multiplier);

int fn_801F1538(char *pString, unsigned int length, unsigned int *pParams)
{
    return fn_801F34C0(pString, *pParams);
}

int fn_801F155C(unsigned char *pData, unsigned int length, unsigned int *pParams)
{
    unsigned int sum1 = 0;
    unsigned int sum3 = 0;
    unsigned int sum2 = 0;
    unsigned int i;

    for (i = 0; i < length; i++) {
        sum1 = (*pData++ + sum1 + sum3) & 0xFF;
        sum2 = (sum1 + sum2) & 0xFF;
        sum3 = (sum2 + sum3) & 0xFF;
    }
    return (sum2 << 8) | sum1;
}

int fn_801F15B0(int type, unsigned int count, char **ppStrings, int *pHashes, unsigned int **ppParams,
                int *pParamSize)
{
    int unique = 1;
    unsigned int i;
    unsigned int j;
    unsigned int *pParams;

    switch (type) {
    case 1:
        pParams = fn_801D2B7C(4, 0, 0);
        *pParamSize = 4;
        *ppParams = pParams;
        for (*pParams = 10; *pParams <= 127; (*pParams)++) {
            unique = 1;
            for (i = 0; i < count; i++) {
                if (ppStrings[i] == 0) {
                    return 0;
                }
                pHashes[i] = fn_801F1538(ppStrings[i], strlen(ppStrings[i]), *ppParams);
            }
            if (count <= 1) {
                return 1;
            }
            for (i = 0; i < count - 1; i++) {
                for (j = i + 1; j < count; j++) {
                    if (pHashes[i] == pHashes[j]) {
                        unique = 0;
                    }
                }
            }
            if (unique) {
                return 1;
            }
        }
        return 0;
    case 2:
        *ppParams = 0;
        *pParamSize = 0;
        for (i = 0; i < count; i++) {
            pHashes[i] = fn_801F155C((unsigned char *)ppStrings[i], strlen(ppStrings[i]), *ppParams);
        }
        if (count <= 1) {
            return 1;
        }
        for (i = 0; i < count - 1; i++) {
            for (j = i + 1; j < count; j++) {
                if (pHashes[i] == pHashes[j]) {
                    unique = 0;
                }
            }
        }
        return unique;
    }
    return 0;
}
