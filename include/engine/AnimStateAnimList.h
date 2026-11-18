#ifndef ENGINE_ANIMSTATEANIMLIST_H
#define ENGINE_ANIMSTATEANIMLIST_H

/* The state animation list types alone, without the animation library prototypes, so that game
   files which keep their own caller view of AnimFileGetStateAnimList (include/game/Table_80089904.h) can
   declare storage of the list's real type. include/engine/animemot.h includes this header. */

typedef struct AnimListEntry_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    void *mpUnknown4;
} AnimListEntry_t;

/* State animation list filled by AnimFileGetStateAnimList. */
typedef struct AnimStateAnimList_t {
    unsigned short mCount;
    unsigned short mMax;
    AnimListEntry_t mEntries[380];
} AnimStateAnimList_t;

#endif
