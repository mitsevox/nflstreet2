#ifndef GAME_CAPPORTRAIT_H
#define GAME_CAPPORTRAIT_H

struct PortraitJob_t;
struct AnimSkeleton_t;

extern "C" {
void *PortraitGetModel(PortraitJob_t *pObject, int index);
AnimSkeleton_t *PortraitGetSkeleton(int index);
}

#endif
