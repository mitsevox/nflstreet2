#ifndef GAME_CAPPORTRAIT_H
#define GAME_CAPPORTRAIT_H

struct PortraitJob_t;
struct Skeleton_80041930;

extern "C" {
void *PortraitGetModel(PortraitJob_t *pObject, int index);
Skeleton_80041930 *PortraitGetSkeleton(int index);
}

#endif
