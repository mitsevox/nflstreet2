#ifndef ENGINE_CU_801C4960_H
#define ENGINE_CU_801C4960_H

/* Hierarchy node: child count, node id, joint index, parent, child pointers. */
typedef struct SkelNode_801C4960 {
    unsigned char mNumChildren;
    unsigned char mId;
    unsigned char mJoint;
    struct SkelNode_801C4960 *mpParent;
    struct SkelNode_801C4960 *mpChildren[1];
} SkelNode_801C4960;

/* 20-byte joint record: its hierarchy node (file-relative until relocated) and a 16-byte name. */
typedef struct SkelJoint_801C4960 {
    SkelNode_801C4960 *mpNode;
    char mName[16];
} SkelJoint_801C4960;

typedef struct SkelEuler_801C4960 {
    short x;
    short y;
    short z;
} SkelEuler_801C4960;

/* Skeleton file: header, per-joint positions and rest rotations. */
typedef struct Skel_801C4960 {
    int mUnk0;
    unsigned short mFlags;
    unsigned short mNumJoints;
    SkelNode_801C4960 *mpRoot;
    SkelJoint_801C4960 *mpJoints;
    float mPos[64][4];
    SkelEuler_801C4960 mRest[1];
} Skel_801C4960;

typedef struct SkelPose_801C4960 {
    int mUnk0[2];
    float mPos[4];
    int mUnk18[2];
    int mRotY;
    int mUnk24[3];
    void *mpLocal;  /* local rotations: Euler triples or quaternions */
    void *mpOutput; /* quaternions or 4x4 matrices */
} SkelPose_801C4960;

/* Running rotation and position while walking the hierarchy. */
typedef struct SkelXform_801C4960 {
    float mQuat[4];
    float mPos[4];
    unsigned char mUnknown20[416];
} SkelXform_801C4960;

#endif
