#ifndef ENGINE_MEMEXTERN_H
#define ENGINE_MEMEXTERN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Register a separately managed address range with the memory manager. */
int MemInitExternHeap(int ident, int parentIdent, char *pStart, unsigned int size,
                      unsigned int maxBlocks, unsigned int align);

#ifdef __cplusplus
}
#endif

#endif
