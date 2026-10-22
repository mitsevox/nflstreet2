#ifndef ENGINE_REMAP_H
#define ENGINE_REMAP_H

#ifdef __cplusplus
extern "C" {
#endif

int fn_801EC1B4(unsigned int numTables, unsigned int numEntries, unsigned int numInputs);
int fn_801EC298(void);
int fn_801EC314(unsigned int table, unsigned int start, unsigned int count, void *pData);
int fn_801EC3B8(unsigned int dst, unsigned int src);
float fn_801EC418(unsigned int table, unsigned int entry, unsigned char *pInputs);

#ifdef __cplusplus
}
#endif

#endif
