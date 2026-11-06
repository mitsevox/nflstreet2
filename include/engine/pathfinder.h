#ifndef ENGINE_PATHFINDER_H
#define ENGINE_PATHFINDER_H

struct PathfinderInitDesc_t {
    int mHeap;
    int mCount;
};

struct PathfinderTrackData_t {
    void *mpData;
    int mUnknown4;
    int mUnknown8;
};

struct PathfinderTrackDesc_t {
    int mId;
    int mUnknown04;
    int mUnknown08;
    float mUnknown0C;
    int mUnknown10;
    PathfinderTrackData_t mUnknown14;
    int mUnknown20;
    unsigned char mUnknown24;
};

struct PathfinderStatus_t;

extern "C" {
int PathfinderIsInit(void);
int PathfinderInit(PathfinderInitDesc_t *pDesc);
void PathfinderShutdown(void);
int PathfinderLoadMap(void *pData, int a, int b);
int PathfinderUnloadMap(int handle);
int PathfinderCreateTrack(PathfinderTrackDesc_t *pDesc);
int PathfinderDestroyTrack(int id);
int PathfinderControl(int id, int a);
int PathfinderEvent(int id, int a);
void PathfinderSetVolume(int id, int value);
void PathfinderFade(int a, int b, int c);
void PathfinderPause(int a, int b);
void PathfinderStop(int a);
void PathfinderSetStreamValue(int a, int b);
int PathfinderGetStatus(int id, PathfinderStatus_t *pInfo);
}

#endif
