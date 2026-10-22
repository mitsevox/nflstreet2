#ifndef ENGINE_SORT_H
#define ENGINE_SORT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*SortFunc_801F51DC)(void *pBase, unsigned int count, int size, int (*pCompare)(void *, void *),
                                  void (*pSwap)(void *, void *), void *pTemp, int flags);

/* sort.c */
void fn_801F522C(int type, SortFunc_801F51DC pSort);

/* bubble.c */
void fn_801F542C(void);

/* quick.c */
void fn_801F5734(void);

#ifdef __cplusplus
}
#endif

#endif
