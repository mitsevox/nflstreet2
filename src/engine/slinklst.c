/* Sound linked lists (slinklst.c): init, push, push to the tail, pop and remove on the sound
   system's node lists. */

#include "engine/sndsys.h"

extern "C" {

void fn_80278700(List_80278714 *list)
{
    list->m0 = 0;
    list->m4 = 0;
    list->m8 = 0;
}

void fn_80278714(List_80278714 *list, Link_80278714 *link)
{
    link->m0 = list->m0;
    link->m4 = 0;
    if (list->m0 != 0) {
        list->m0->m4 = link;
    } else {
        list->m4 = link;
    }
    list->m0 = link;
    list->m8++;
}

void fn_80278750(List_80278714 *list, Link_80278714 *link)
{
    link->m0 = 0;
    link->m4 = list->m4;
    if (list->m4 != 0) {
        list->m4->m0 = link;
    } else {
        list->m0 = link;
    }
    list->m4 = link;
    list->m8++;
}

Link_80278714 *fn_8027878C(List_80278714 *list)
{
    Link_80278714 *link;

    link = list->m0;
    if (link != 0) {
        list->m0 = link->m0;
        if (list->m0 == 0) {
            list->m4 = 0;
        } else {
            list->m0->m4 = 0;
        }
        list->m8--;
    }
    return link;
}

void fn_802787CC(List_80278714 *list, Link_80278714 *link)
{
    if (link == list->m0) {
        list->m0 = link->m0;
    }
    if (link == list->m4) {
        list->m4 = link->m4;
    }
    if (link->m4 != 0) {
        link->m4->m0 = link->m0;
    }
    if (link->m0 != 0) {
        link->m0->m4 = link->m4;
    }
    list->m8--;
}

}
