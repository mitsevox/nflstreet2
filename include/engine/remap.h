#ifndef ENGINE_REMAP_H
#define ENGINE_REMAP_H

#ifdef __cplusplus
extern "C" {
#endif

int RemapInit(unsigned int numTables, unsigned int numEntries, unsigned int numInputs);
int RemapShutdown(void);
int RemapSetupEntries(unsigned int table, unsigned int start, unsigned int count, void *pData);
int RemapCopyTable(unsigned int dst, unsigned int src);
float RemapCheckEntry(unsigned int table, unsigned int entry, unsigned char *pInputs);

#ifdef __cplusplus
}
#endif

#endif
