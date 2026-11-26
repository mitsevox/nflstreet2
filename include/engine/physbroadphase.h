#ifndef ENGINE_PHYSBROADPHASE_H
#define ENGINE_PHYSBROADPHASE_H

/* The sweep-and-prune broad phase of the rigid-body physics world (src/engine/physbroadphase.cpp):
   each object's box puts a min and a max endpoint on a sorted list per axis, and objects whose
   intervals overlap on all three axes are kept as pairs for the collision system. */

#define BROADPHASE_NONE 0xFFFF

/* Corner vector, read by axis index. */
struct BroadPhaseVec {
    float operator[](int i) const { return (&x)[i]; }

    float x;
    float y;
    float z;
};

/* The broad phase's view of an object's world box (the BoundingBox of src/engine/physaabb.cpp):
   its min and max corners, indexed by an endpoint's mIsMax. */
struct BroadPhaseBox {
    BroadPhaseVec mCorner[2];
};

/* Tracked object. */
struct BroadPhaseObject {
    void *mUser;
    BroadPhaseBox *mpBox;
    unsigned int mMask;
    unsigned short mNext;
    unsigned short mPrev;
};

/* Interval endpoint on one axis. */
struct BroadPhaseEndpoint {
    unsigned short mObject;
    unsigned short mIsMax;
    unsigned short mNext;
    unsigned short mPrev;
};

/* Overlapping pair. */
struct BroadPhasePair {
    unsigned short mObjectA;
    unsigned short mObjectB;
    BroadPhasePair *mpNext;
    BroadPhasePair *mpPrev;
};

/* Overlap state of two objects: one bit per axis and the pair index. */
struct BroadPhaseOverlap {
    unsigned short mAxes;
    unsigned short mPair;
};

/* Sweep-and-prune broad phase over three axes. */
class BroadPhase {
public:
    BroadPhase(unsigned int maxObjects, unsigned int maxPairs);
    virtual ~BroadPhase();
    void AddObject(BroadPhaseBox *pBox, unsigned int mask, void *user);
    void RemoveObject(BroadPhaseBox *pBox);
    BroadPhasePair *UpdatePairs();
    void *GetObjectUser(unsigned short object);
    void SortAxis(int axis);
    void SwapEndpoints(unsigned short a, unsigned short b, int axis);
    unsigned int GetOverlapIndex(unsigned short a, unsigned short b);
    float GetEndpointValue(int axis, unsigned short endpoint, unsigned char *pIsMin);
    void TestAxisOverlap(unsigned short a, unsigned short b, unsigned short axis);
    void AddPair(unsigned short a, unsigned short b, BroadPhaseOverlap *pOverlap);
    void RemovePair(unsigned short pair);
    void InsertObjectOnAxis(int axis, unsigned short object);
    void RemoveObjectFromAxis(int axis, unsigned short object);
    void InsertEndpoint(int axis, unsigned short endpoint);
    BroadPhasePair *AllocPair();
    void FreePair(BroadPhasePair *pPair);
    unsigned short AllocEndpoint();
    void FreeEndpoint(unsigned short endpoint);
    unsigned short AllocObject();
    void FreeObject(unsigned short object);

    unsigned int mMaxObjects;
    unsigned int mMaxPairs;
    BroadPhaseObject *mpObjects;
    unsigned short mFirstObject;
    unsigned short mFreeObject;
    unsigned short mAxisHead[3];
    unsigned short mFreeEndpoint;
    BroadPhaseEndpoint *mpEndpoints;
    BroadPhasePair *mpPairs;
    BroadPhasePair *mpFreePair;
    BroadPhasePair *mpFirstPair;
    BroadPhaseOverlap *mpOverlaps;
};

#endif
