#ifndef ENGINE_SORT_H
#define ENGINE_SORT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*SortFunc_801F51DC)(void *pBase, unsigned int count, int size, int (*pCompare)(void *, void *),
                                  void (*pSwap)(void *, void *), void *pTemp, int flags);

/* sort.c */
void SortAddSortType(int type, SortFunc_801F51DC pSort);

/* bubble.c */
void SortInitBubbleModule(void);

/* quick.c */
void SortInitQuickModule(void);

#ifdef __cplusplus
}
#endif

#endif
