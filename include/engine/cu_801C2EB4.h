#ifndef ENGINE_CU_801C2EB4_H
#define ENGINE_CU_801C2EB4_H

/* String copy, compare, search and length. */
#ifdef __cplusplus
extern "C" {
#endif

char *fn_801C2EB4(char *pDest, const char *pSource);
char *fn_801C2EF0(char *pDest, const char *pSource, int size);
char *fn_801C2F2C(char *pDest, const char *pSource);
char *fn_801C2F88(char *pDest, const char *pSource, int size);
int fn_801C2FE4(const char *pString1, const char *pString2);
int fn_801C302C(const char *pString1, const char *pString2, int size);
char *fn_801C3084(const char *pString, int c);
char *fn_801C30C0(const char *pString, int c);
char *fn_801C310C(const char *pString, const char *pFind);
int fn_801C3180(const char *pString);
int fn_801C31B0(const char *pString1, const char *pString2);
int fn_801C3214(const char *pString1, const char *pString2, int size);
char *fn_801C32CC(char *pString);

#ifdef __cplusplus
}
#endif

#endif
