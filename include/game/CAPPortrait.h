#ifndef GAME_CAPPORTRAIT_H
#define GAME_CAPPORTRAIT_H

struct PortraitJob;
struct Skeleton_80041930;

extern "C" {
void *PortraitGetModel(PortraitJob *pObject, int index);
Skeleton_80041930 *PortraitGetSkeleton(int index);
}

#endif
