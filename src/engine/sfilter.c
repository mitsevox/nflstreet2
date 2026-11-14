/* Sound filter chain (sfilter.c): inserts a filter node into a chain ordered by priority, and removes
   one. */

#include "engine/sndsys.h"

extern "C" {

void SFILTER_add(Node_80279D90 **list, Node_80279D90 *node)
{
    Node_80279D90 *prev;
    Node_80279D90 *cur;

    prev = 0;
    cur = *list;
    while (cur != 0 && cur->m18 < node->m18) {
        prev = cur;
        cur = cur->m8;
    }
    node->m8 = cur;
    if (cur != 0) {
        cur->m10 = node;
    }
    if (prev == 0) {
        *list = node;
    } else {
        prev->m8 = node;
        node->m10 = prev;
    }
}

void SFILTER_remove(Node_80279D90 **list, Node_80279D90 *node)
{
    Node_80279D90 *prev = *list;
    Node_80279D90 *cur;
    if (node == prev) {
        *list = prev->m8;
        return;
    }
    cur = prev->m8;
    while (cur != 0 && cur != node) {
        prev = cur;
        cur = prev->m8;
    }
    if (cur != 0 && cur == node) {
        node = node->m8;
        if (node != 0) {
            node->m10 = prev;
        }
        prev->m8 = prev->m8->m8;
    }
}

}
