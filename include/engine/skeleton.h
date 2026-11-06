#ifndef ENGINE_SKELETON_H
#define ENGINE_SKELETON_H

/* Hierarchy node: child count, node id, joint index, parent, child pointers. */
typedef struct SkelNode_t {
    unsigned char mNumChildren;
    unsigned char mId;
    unsigned char mJoint;
    struct SkelNode_t *mpParent;
    struct SkelNode_t *mpChildren[1];
} SkelNode_t;

/* 20-byte joint record: its hierarchy node (file-relative until relocated) and a 16-byte name. */
typedef struct SkelJoint_t {
    SkelNode_t *mpNode;
    char mName[16];
} SkelJoint_t;

typedef struct SkelEuler_t {
    short x;
    short y;
    short z;
} SkelEuler_t;

/* Skeleton file: header, per-joint positions and rest rotations. */
typedef struct Skel_t {
    int mUnk0;
    unsigned short mFlags;
    unsigned short mNumJoints;
    SkelNode_t *mpRoot;
    SkelJoint_t *mpJoints;
    float mPos[64][4];
    SkelEuler_t mRest[1];
} Skel_t;

typedef struct SkelPose_t {
    int mUnk0[2];
    float mPos[4];
    int mUnk18[2];
    int mRotY;
    int mUnk24[3];
    void *mpLocal;  /* local rotations: Euler triples or quaternions */
    void *mpOutput; /* quaternions or 4x4 matrices */
} SkelPose_t;

/* Running rotation and position while walking the hierarchy. */
typedef struct SkelXform_t {
    float mQuat[4];
    float mPos[4];
    unsigned char mUnknown20[416];
} SkelXform_t;

#endif
