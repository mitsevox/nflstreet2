#ifndef ENGINE_SLINKLST_H
#define ENGINE_SLINKLST_H

/* Intrusive links and list headers used by the sound system. */
typedef struct SndLinkNode_t SndLinkNode_t;

struct SndLinkNode_t {
    SndLinkNode_t *mpNext;
    SndLinkNode_t *mpPrev;
};

typedef struct SndLinkList_t {
    SndLinkNode_t *mpFirst;
    SndLinkNode_t *mpLast;
    int mCount;
} SndLinkList_t;

#ifdef __cplusplus
extern "C" {
#endif

void SNDLINKI_init(SndLinkList_t *list);
void SNDLINKI_push(SndLinkList_t *list, SndLinkNode_t *link);
void SNDLINKI_pushtail(SndLinkList_t *list, SndLinkNode_t *link);
SndLinkNode_t *SNDLINKI_pop(SndLinkList_t *list);
void SNDLINKI_remove(SndLinkList_t *list, SndLinkNode_t *link);

#ifdef __cplusplus
}
#endif

#endif
