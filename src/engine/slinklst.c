/* Sound linked lists (slinklst.c): init, push, push to the tail, pop and remove on the sound
   system's node lists. */

#include "engine/slinklst.h"

extern "C" {

void SNDLINKI_init(SndLinkList_t *list)
{
    list->mpFirst = 0;
    list->mpLast = 0;
    list->mCount = 0;
}

void SNDLINKI_push(SndLinkList_t *list, SndLinkNode_t *link)
{
    link->mpNext = list->mpFirst;
    link->mpPrev = 0;
    if (list->mpFirst != 0) {
        list->mpFirst->mpPrev = link;
    } else {
        list->mpLast = link;
    }
    list->mpFirst = link;
    list->mCount++;
}

void SNDLINKI_pushtail(SndLinkList_t *list, SndLinkNode_t *link)
{
    link->mpNext = 0;
    link->mpPrev = list->mpLast;
    if (list->mpLast != 0) {
        list->mpLast->mpNext = link;
    } else {
        list->mpFirst = link;
    }
    list->mpLast = link;
    list->mCount++;
}

SndLinkNode_t *SNDLINKI_pop(SndLinkList_t *list)
{
    SndLinkNode_t *link;

    link = list->mpFirst;
    if (link != 0) {
        list->mpFirst = link->mpNext;
        if (list->mpFirst == 0) {
            list->mpLast = 0;
        } else {
            list->mpFirst->mpPrev = 0;
        }
        list->mCount--;
    }
    return link;
}

void SNDLINKI_remove(SndLinkList_t *list, SndLinkNode_t *link)
{
    if (link == list->mpFirst) {
        list->mpFirst = link->mpNext;
    }
    if (link == list->mpLast) {
        list->mpLast = link->mpPrev;
    }
    if (link->mpPrev != 0) {
        link->mpPrev->mpNext = link->mpNext;
    }
    if (link->mpNext != 0) {
        link->mpNext->mpPrev = link->mpPrev;
    }
    list->mCount--;
}

}
