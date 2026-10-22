#ifndef ENGINE_PARTICLELIB_H
#define ENGINE_PARTICLELIB_H

typedef struct Vec3_801DE1E0 {
    float x;
    float y;
    float z;
} Vec3_801DE1E0;

typedef struct Vec4_801DE1E0 {
    float x;
    float y;
    float z;
    float w;
} Vec4_801DE1E0;

/* Colour ramp key (16 bytes). */
typedef struct RampNode_801E052C {
    float mT;
    Vec3_801DE1E0 mColor;
} RampNode_801E052C;

/* Colour ramp (0x288 bytes): sorted key pointers into a fixed key pool. */
typedef struct Ramp_801E052C {
    unsigned short mCount;
    int mInterp;
    RampNode_801E052C *mpNodes[32];
    RampNode_801E052C mPool[32];
} Ramp_801E052C;

/* Colour ramp as stored in a parameter file: keys inline after the header. */
typedef struct RampParm_801E071C {
    unsigned short mCount;
    int mInterp;
    RampNode_801E052C mNodes[32];
} RampParm_801E071C;

/* Emitter shape parameters (0x48 bytes at +0xF4 of a particle system). */
typedef struct Shape_801DF428 {
    Vec3_801DE1E0 mUnknown00;
    Vec3_801DE1E0 mUnknown0C;
    Vec3_801DE1E0 mUnknown18;
    float mUnknown24;
    float mUnknown28;
    Vec3_801DE1E0 mUnknown2C;
    Vec3_801DE1E0 mUnknown38;
    float mUnknown44;
} Shape_801DF428;

typedef struct ShapeLine_801DFE0C {
    Vec3_801DE1E0 mUnknown00;
    Vec3_801DE1E0 mUnknown0C;
} ShapeLine_801DFE0C;

typedef struct ShapeSphere_801DFE0C {
    Vec3_801DE1E0 mUnknown00;
    float mUnknown0C;
} ShapeSphere_801DFE0C;

typedef union Emitter_801DFE0C {
    Vec3_801DE1E0 mPoint;
    ShapeLine_801DFE0C mLine;
    ShapeSphere_801DFE0C mSphere;
    Shape_801DF428 mBox;
} Emitter_801DFE0C;

/* Plane collision parameters (normal, point, distance). */
typedef struct Plane_801E0384 {
    Vec3_801DE1E0 mNormal;
    Vec3_801DE1E0 mPoint;
    float mDistance;
} Plane_801E0384;

typedef struct Ground_801E0384 {
    float mHeight;
} Ground_801E0384;

typedef union Collision_801E0384 {
    Ground_801E0384 mGround;
    Plane_801E0384 mPlane;
} Collision_801E0384;

/* Extra collision entry (0x14 bytes at +0x2B8 of a particle system). */
typedef struct ColExt_801E043C {
    int mType;
    union {
        float mHeight;
        struct {
            Vec3_801DE1E0 mNormal;
            float mDistance;
        } mPlane;
    } mData;
} ColExt_801E043C;

/* Particle record (0x54 bytes). */
typedef struct Particle_801DE1E0 {
    Vec3_801DE1E0 mPrevPos;
    Vec3_801DE1E0 mPos;
    Vec3_801DE1E0 mVel;
    Vec3_801DE1E0 mForce;
    float mUnknown30;
    float mUnknown34;
    unsigned char mActive;
    unsigned char mUnknown39;
    char mPad3A[0x3C - 0x3A];
    float mLife;
    unsigned int mUnknown40;
    float mAge;
    float mAgeRatio;
    float mUnknown4C;
    float mUnknown50;
} Particle_801DE1E0;

/* Particle system object (0x3D4 bytes). A template in a loaded parameter
   file has the same layout and is followed by its colour ramp. */
typedef struct PartObj_801DE1E0 {
    char mPad000[0x14];
    char mUnknown014[8];
    char mUnknown01C[0x20];
    unsigned char mUnknown03C;
    unsigned char mUnknown03D;
    unsigned char mUnknown03E;
    unsigned char mUnknown03F;
    unsigned char mUnknown040;
    unsigned char mUnknown041;
    unsigned char mUnknown042;
    unsigned char mUnknown043;
    unsigned char mUnknown044;
    unsigned char mUnknown045;
    unsigned short mUnknown046;
    unsigned short mUnknown048;
    char mPad04A[2];
    int mUnknown04C;
    unsigned int mUnknown050;
    float mUnknown054;
    int mForceType;
    int mUnknown05C;
    int mUnknown060;
    Vec3_801DE1E0 mUnknown064;
    Vec3_801DE1E0 mUnknown070;
    Vec4_801DE1E0 mUnknown07C;
    Ramp_801E052C *mpUnknown08C;
    float mUnknown090;
    float mUnknown094;
    float mUnknown098;
    float mUnknown09C;
    float mUnknown0A0;
    float mUnknown0A4;
    float mUnknown0A8;
    float mUnknown0AC;
    float mUnknown0B0;
    int mUnknown0B4;
    float mUnknown0B8;
    float mUnknown0BC;
    float mUnknown0C0;
    float mUnknown0C4;
    float mUnknown0C8;
    float mUnknown0CC;
    float mUnknown0D0;
    float mUnknown0D4;
    float mUnknown0D8;
    int mUnknown0DC;
    int mUnknown0E0;
    float mUnknown0E4;
    float mUnknown0E8;
    float mUnknown0EC;
    unsigned int mEmitterType;
    Emitter_801DFE0C mEmitter;
    char mPad13C[0x1F4 - 0x13C];
    float mUnknown1F4;
    float mUnknown1F8;
    float mUnknown1FC;
    float mUnknown200;
    unsigned int mCollisionType;
    Collision_801E0384 mCollision;
    char mPad224[0x288 - 0x224];
    float mUnknown288;
    char mUnknown28C[0x20];
    void *mpUnknown2AC;
    float mUnknown2B0;
    unsigned char mUnknown2B4;
    unsigned char mUnknown2B5;
    unsigned char mUnknown2B6;
    unsigned char mColExtCount;
    ColExt_801E043C mColExt[8];
    unsigned short mUnknown358;
    unsigned char mUnknown35A;
    unsigned char mUnknown35B;
    float mUnknown35C[4][4];
    float mUnknown39C;
    float mUnknown3A0;
    float mUnknown3A4;
    float mUnknown3A8;
    float mUnknown3AC;
    float mUnknown3B0;
    int mUnknown3B4;
    unsigned int mCount;
    unsigned int mMax;
    Particle_801DE1E0 **mppParticles;
    Particle_801DE1E0 *mpParticles;
    float mUnknown3C8;
    float mUnknown3CC;
    float mUnknown3D0;
} PartObj_801DE1E0;

/* Particle system template as loaded from a parameter file. */
typedef struct Template_801DE1E0 {
    PartObj_801DE1E0 mObj;
    Ramp_801E052C mRamp;
} Template_801DE1E0;

#endif
