#ifndef ENGINE_DSLIST_H
#define ENGINE_DSLIST_H

/* List creation, deletion and node insertion of the EA data-structure library (src/engine/list.c). */

#ifdef __cplusplus
extern "C" {
#endif
void *DSNewList(int a, int b, int count, int size,
              int (*cmp)(void *, void *), void *storage);
int DSDelList(void *pool);
void *DSAddListNode(void *pool, void *item, int c);
#ifdef __cplusplus
}
#endif

#endif
