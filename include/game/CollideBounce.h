#ifndef GAME_COLLIDEBOUNCE_H
#define GAME_COLLIDEBOUNCE_H

#include "game/Object_80039F5C.h"

/* One axis of a collision: an input value, two results written by
   BounceAxisFixed/BounceAxisPair, and the weight read as +0xC.
   BounceAxisFixed works on one axis, BounceAxisPair on a pair. */
struct BounceAxis_t {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
};

/* The three-dimensional form of BounceAxis_t, filled by BounceBody3D,
   BounceBodyPair2D and BounceBodyPair3D. */
struct BounceBody_t {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12;
    Vector_80039F5C mUnknown24;
    float mUnknown36;
};

/* Two positions compared by BounceCheckApproach; PlyrCollideContacts fills them from the
   motion block's +0 and +12 vectors. */
struct BounceSegment_t {
    Vector_80039F5C mUnknown0;
    Vector_80039F5C mUnknown12;
};

extern "C" {
void BounceAxisFixed(BounceAxis_t *pAxis, float restitution);
void BounceAxisPair(BounceAxis_t *pA, BounceAxis_t *pB, float restitution);
int BounceCheckApproach(BounceSegment_t *pA, BounceSegment_t *pB, unsigned char *pHitA, unsigned char *pHitB);
void BounceBody2D(BounceBody_t *pBody, float *pNormal, float restitution);
void BounceBody3D(BounceBody_t *pBody, Vector_80039F5C *pNormal, float restitution);
void BounceBodyPair2D(BounceBody_t *pA, BounceBody_t *pB, float *pNormal, float restitution);
void BounceBodyPair3D(BounceBody_t *pA, BounceBody_t *pB, Vector_80039F5C *pNormal, float restitution);
void BounceScatterVector(Vector_80039F5C *pOut, Vector_80039F5C *pNormal, float scale);
}

#endif
