/* Rigid-body physics: the collision system of the physics world. It keeps every body's shape
   bounds in the sweep-and-prune broad phase, runs the shape-pair tests on each overlapping pair
   of bodies, lets the game's collision handler inspect or veto the contacts, and resolves them
   with impulses, position corrections and rolling friction. */

#include <math.h>
#include "engine/physworld.h"
#include "engine/physcollide.h"
#include "engine/physcollection.h"
#include "engine/physshape.h"
#include "engine/TibNew.h"

extern "C" {
float Vec3Magnitude(void *pV);
void Vec3Sub(void *pOut, void *pA, void *pB);
void ApplyBodyAngularImpulse(RigidBody *pBody, Vec3_801DE1E0 *pImpulse);
float ComputeBodyRotationalResponse(RigidBody *pBody, Vec3_801DE1E0 *pPoint,
                                    Vec3_801DE1E0 *pDirection);
}

#define _CLAMP(value, low, high) ((value) < (low) ? (low) : ((value) > (high) ? (high) : (value)))

/* View of the sweep-and-prune broad phase of src/engine/cu_801E9F70.cpp: 44 bytes of state,
   then its vtable pointer (slot 1 is the deleting destructor). */
class BroadPhase {
public:
    virtual ~BroadPhase();

    unsigned char mState[44];
};

/* An overlapping pair of broad-phase objects. */
struct BroadPhasePair {
    unsigned short mObjectA;
    unsigned short mObjectB;
    BroadPhasePair *mpNext;
};

extern "C" {
BroadPhase *fn_801E9F70(void *pMemory, unsigned int maxObjects, unsigned int maxPairs);
void fn_801EA1D8(BroadPhase *pBroadPhase, void *pBox, unsigned int mask, RigidBody *pBody);
void fn_801EA284(BroadPhase *pBroadPhase, void *pBox);
BroadPhasePair *fn_801EA428(BroadPhase *pBroadPhase);
RigidBody *fn_801EA470(BroadPhase *pBroadPhase, unsigned short object);
}

int ShapeCollide(CollisionShape *pA, float (*pMatrixA)[4], CollisionShape *pB,
                 float (*pMatrixB)[4], Vec3_801DE1E0 *pContact);

ContactSystem::ContactSystem(unsigned int maxBodies, unsigned int maxContacts, float depthLimit,
                             float minTestLength, CollisionHandler *pHandler)
    : mMaxContacts(maxContacts), mDepthLimit(depthLimit), mMinTestLength(minTestLength),
      mpHandler(pHandler)
{
    mpBroadPhase = fn_801E9F70(operator new(48, 0), maxBodies, maxContacts);
    mpContacts = new (0) BodyContact[maxContacts];
    mCorrectionMin.x = -1000000.0f;
    mCorrectionMin.y = -1000000.0f;
    mCorrectionMin.z = -1000000.0f;
    mCorrectionMax.x = 1000000.0f;
    mCorrectionMax.y = 1000000.0f;
    mCorrectionMax.z = 1000000.0f;
}

ContactSystem::~ContactSystem()
{
    if (mpBroadPhase) {
        delete mpBroadPhase;
    }
    mpBroadPhase = 0;
    if (mpContacts) {
        delete[] mpContacts;
    }
    mpContacts = 0;
}

void ContactSystem::AddBody(RigidBody *pBody)
{
    ShapeCollection *pShapes = pBody->mpShapes;

    if (pShapes) {
        pShapes->UpdateWorldBounds(pBody->mTransform);
        fn_801EA1D8(mpBroadPhase, &pShapes->mWorldBounds, pShapes->mMask, pBody);
    }
}

void ContactSystem::RemoveBody(RigidBody *pBody)
{
    if (pBody->mpShapes) {
        fn_801EA284(mpBroadPhase, &pBody->mpShapes->mWorldBounds);
    }
}

int ContactSystem::Update(float dt)
{
    unsigned char touched = 0;
    BroadPhasePair *pPair;

    for (pPair = fn_801EA428(mpBroadPhase); pPair; pPair = pPair->mpNext) {
        RigidBody *pA = fn_801EA470(mpBroadPhase, pPair->mObjectA);
        RigidBody *pB = fn_801EA470(mpBroadPhase, pPair->mObjectB);

        if (!mpHandler->IgnorePair(pA, pB)) {
            touched |= CollidePair(pA, pB, dt);
        }
    }
    return touched;
}

int ContactSystem::CollidePair(RigidBody *pA, RigidBody *pB, float dt)
{
    ShapeCollection *pShapesA = pA->mpShapes;
    ShapeCollection *pShapesB = pB->mpShapes;
    unsigned int countA = pShapesA->mCount;
    unsigned int countB = pShapesB->mCount;
    float (*pMatrixA)[4] = pA->mTransform;
    float (*pMatrixB)[4] = pB->mTransform;
    unsigned int count = 0;
    unsigned int i;
    unsigned int j;

    for (i = 0; i < countA; i++) {
        CollisionShape *pShapeA = pShapesA->GetShape(i);

        for (j = 0; j < countB; j++) {
            CollisionShape *pShapeB = pShapesB->GetShape(j);

            if (ShapeCollide(pShapeA, pMatrixA, pShapeB, pMatrixB,
                             &mpContacts[count].mPoint)) {
                mpContacts[count].mShapeA = i;
                mpContacts[count].mShapeB = j;
                count++;
            }
        }
    }
    if (count != 0) {
        int mode = 0;

        if (mpHandler) {
            mode = mpHandler->OnContacts(dt, pA, pB, count, mpContacts);
        }
        if (mode != 3) {
            Respond(dt, pA, pB, count, mpContacts, mode);
        }
    }
    return count != 0;
}

void ContactSystem::Respond(float dt, RigidBody *pA, RigidBody *pB, unsigned int count,
                            BodyContact *pContacts, int mode)
{
    Vec3_801DE1E0 impulses[16];
    Vec3_801DE1E0 frictions[16];
    Vec3_801DE1E0 correction;
    Vec3_801DE1E0 maxCorrection;
    unsigned int indices[16];
    Vec3_801DE1E0 pointsA[16];
    Vec3_801DE1E0 pointsB[16];
    Vec3_801DE1E0 position;
    Vec3_801DE1E0 normal;
    Vec3_801DE1E0 move;
    Vec3_801DE1E0 negated;
    unsigned int hits = 0;
    unsigned int i;

    maxCorrection.x = maxCorrection.y = maxCorrection.z = 0.0f;
    for (i = 0; i < count; i++) {
        if (ResolveContact(dt, pA, pB, &pContacts[i], &impulses[hits], &frictions[hits],
                           &correction, &pointsA[hits], &pointsB[hits], &normal)) {
            indices[hits] = i;
            Vec3Add(&impulses[hits], &impulses[hits], &frictions[hits]);
            hits++;
            if (hits > 15) {
                break;
            }
        }
        if (fabsf(correction.x) > fabsf(maxCorrection.x)) {
            maxCorrection.x = correction.x;
        }
        if (fabsf(correction.y) > fabsf(maxCorrection.y)) {
            maxCorrection.y = correction.y;
        }
        if (fabsf(correction.z) > fabsf(maxCorrection.z)) {
            maxCorrection.z = correction.z;
        }
    }
    if (hits > 1) {
        for (i = 0; i < hits; i++) {
            Vec3Scale(&impulses[i], &impulses[i], 1.0f / (float)hits);
        }
    }
    if (hits == 0) {
        return;
    }
    if (mode != 0 || (unsigned int)pA->mState <= 1 || (unsigned int)pB->mState <= 1) {
        Vec3Scale(&maxCorrection, &maxCorrection, 2.0f);
    }
    if (mode != 2 && (unsigned int)pA->mState > 1) {
        for (i = 0; i < hits; i++) {
            ApplyBodyImpulseAtPoint(pA, &impulses[i], &pointsA[i]);
        }
        if (hits == 1 && pB->mState == 0) {
            ApplyRollingFriction(pA, dt, &pointsA[0], &normal);
        }
        move.x = _CLAMP(maxCorrection.x, mCorrectionMin.x, mCorrectionMax.x);
        move.y = _CLAMP(maxCorrection.y, mCorrectionMin.y, mCorrectionMax.y);
        move.z = _CLAMP(maxCorrection.z, mCorrectionMin.z, mCorrectionMax.z);
        Vec3Add(&position, &pA->mPosition, &move);
        SetBodyPosition(pA, &position);
        UpdateBodyDerivedState(pA);
    }
    if (mode != 1 && (unsigned int)pB->mState > 1) {
        for (i = 0; i < hits; i++) {
            negated.x = -impulses[i].x;
            negated.y = -impulses[i].y;
            negated.z = -impulses[i].z;
            ApplyBodyImpulseAtPoint(pB, &negated, &pointsB[i]);
        }
        if (hits == 1 && pA->mState == 0) {
            ApplyRollingFriction(pB, dt, &pointsB[0], &normal);
        }
        move.x = _CLAMP(-maxCorrection.x, mCorrectionMin.x, mCorrectionMax.x);
        move.y = _CLAMP(-maxCorrection.y, mCorrectionMin.y, mCorrectionMax.y);
        move.z = _CLAMP(-maxCorrection.z, mCorrectionMin.z, mCorrectionMax.z);
        Vec3Add(&position, &pB->mPosition, &move);
        SetBodyPosition(pB, &position);
        UpdateBodyDerivedState(pB);
    }
    if (mpHandler) {
        for (i = 0; i < hits; i++) {
            mpHandler->OnImpulse(pA, pContacts[indices[i]].mShapeA, pB,
                                 pContacts[indices[i]].mShapeB, &pointsA[i], &pointsB[i],
                                 &impulses[i]);
        }
    }
}

void ContactSystem::ApplyRollingFriction(RigidBody *pBody, float dt, Vec3_801DE1E0 *pPoint,
                                         Vec3_801DE1E0 *pDirection)
{
    if (pBody->mUnknown04C > 0.0f) {
        CollisionShape *pShape = pBody->mpShapes->GetShape(0);

        if (pShape->GetSupportWeight(pPoint, pDirection, pBody->mTransform) != 0.0f) {
            Vec3_801DE1E0 *pMomentum = &pBody->mAngularMomentum;
            float amount = pBody->mUnknown04C * dt;
            float length = Vec3Magnitude(pMomentum);
            Vec3_801DE1E0 impulse;

            if (amount > length) {
                impulse.x = -pMomentum->x;
                impulse.y = -pMomentum->y;
                impulse.z = -pMomentum->z;
            } else {
                Vec3Scale(&impulse, pMomentum, -amount / length);
            }
            ApplyBodyAngularImpulse(pBody, &impulse);
        }
    }
}

void ContactSystem::SetCorrectionLimits(Vec3_801DE1E0 *pMin, Vec3_801DE1E0 *pMax)
{
    mCorrectionMin = *pMin;
    mCorrectionMax = *pMax;
}

int ContactSystem::ResolveContact(float dt, RigidBody *pA, RigidBody *pB, BodyContact *pContact,
                                  Vec3_801DE1E0 *pImpulse, Vec3_801DE1E0 *pFriction,
                                  Vec3_801DE1E0 *pCorrection, Vec3_801DE1E0 *pPointA,
                                  Vec3_801DE1E0 *pPointB, Vec3_801DE1E0 *pNormal)
{
    Vec3_801DE1E0 velocityA;
    Vec3_801DE1E0 velocityB;
    Vec3_801DE1E0 relative;
    Vec3_801DE1E0 normalA;
    Vec3_801DE1E0 normalB;
    Vec3_801DE1E0 along;
    Vec3_801DE1E0 tangent;
    Vec3_801DE1E0 impulse;
    Vec3_801DE1E0 friction;
    Vec3_801DE1E0 probeB;
    Vec3_801DE1E0 probeA;
    float depthA;
    float depthB;
    float frictionA;
    float bounceA;
    float frictionB;
    float bounceB;
    float approach;
    float weightA;
    float weightB;
    float speed;
    CollisionShape *pShapeA;
    CollisionShape *pShapeB;

    pCorrection->x = pCorrection->y = pCorrection->z = 0.0f;
    pNormal->x = pNormal->y = pNormal->z = 0.0f;
    pShapeA = pA->mpShapes->GetShape(pContact->mShapeA);
    pShapeB = pB->mpShapes->GetShape(pContact->mShapeB);
    GetBodyPointVelocity(pA, &pContact->mPoint, &velocityA);
    GetBodyPointVelocity(pB, &pContact->mPoint, &velocityB);
    Vec3Sub(&relative, &velocityB, &velocityA);
    approach = 0.0f;
    depthA = 0.0f;
    speed = Vec3Magnitude(&relative);
    if (speed > 1e-16f) {
        float length = speed * dt;
        float limit;

        length = length + length;
        if (length < mMinTestLength) {
            length = mMinTestLength;
        }
        Vec3Scale(&probeB, &relative, length / speed);
        probeA.x = -probeB.x;
        probeA.y = -probeB.y;
        probeA.z = -probeB.z;
        weightA = pShapeA->TestPoint(&pContact->mPoint, pA->mTransform, &probeA, &normalA, pPointA,
                                     &depthA, length);
        weightB = pShapeB->TestPoint(&pContact->mPoint, pB->mTransform, &probeB, &normalB, pPointB,
                                     &depthB, length);
        if (weightA == weightB) {
            if ((unsigned int)pA->mState <= 1) {
                weightA += 0.001f;
            }
            if ((unsigned int)pB->mState <= 1) {
                weightB += 0.001f;
            }
            if (weightA == weightB) {
                if (depthA > depthB) {
                    weightA += 0.001f;
                } else {
                    weightB += 0.001f;
                }
            }
        }
        limit = length;
        if (limit < mDepthLimit) {
            limit = mDepthLimit;
        }
        if (depthA > limit && depthB < limit) {
            weightA = weightA > 0.01f ? 0.01f : weightA * 0.5f;
            if (depthB < depthA) {
                depthA = depthB;
            }
        }
        if (depthB > limit && depthA < limit) {
            weightB = weightB > 0.01f ? 0.01f : weightB * 0.5f;
            if (depthA < depthB) {
                depthB = depthA;
            }
        }
        if (weightB > weightA) {
            normalA.x = -normalB.x;
            normalA.y = -normalB.y;
            normalA.z = -normalB.z;
            depthA = depthB;
        }
        *pNormal = normalA;
        if (depthA > limit) {
            depthA = limit;
        }
        Vec3Scale(pCorrection, &normalA, -depthA);
        if (weightA > 0.0f && weightB > 0.0f) {
            approach = -Vec3DotProduct(&normalA, &relative);
        }
    }
    if (approach > 0.0f) {
        float response;
        float scale;
        float length;

        if ((approach * dt) + (approach * dt) > depthA) {
            pCorrection->x = pCorrection->y = pCorrection->z = 0.0f;
        }
        response = ComputeBodyRotationalResponse(pA, pPointA, &normalA);
        scale = ComputeBodyRotationalResponse(pB, pPointB, &normalA);
        pShapeA->GetMaterial(&frictionA, &bounceA, pA->mTransform, pPointA);
        scale = approach / (pA->mInvMass + pB->mInvMass + response + scale);
        pShapeB->GetMaterial(&frictionB, &bounceB, pB->mTransform, pPointB);
        scale *= (bounceA + bounceB) * 0.5f + 1.0f;
        Vec3Scale(&impulse, &normalA, -scale);
        friction.x = friction.y = friction.z = 0.0f;
        Vec3Scale(&along, &normalA, -approach);
        Vec3Sub(&tangent, &relative, &along);
        length = Vec3Magnitude(&tangent);
        if (length > 1e-6f) {
            float mu;

            Vec3Scale(&tangent, &tangent, 1.0f / length);
            if (frictionA < 0.2f || frictionB < 0.2f) {
                mu = frictionB <= frictionA ? frictionB : frictionA;
            } else {
                mu = (frictionA + frictionB) * 0.5f;
            }
            Vec3Sub(&probeB, &pA->mForce, &pB->mForce);
            mu = mu * Vec3DotProduct(&probeB, &normalA) * dt;
            if (mu > 0.0) {
                Vec3Scale(&friction, &tangent, mu);
            }
        }
        *pImpulse = impulse;
        *pFriction = friction;
        return 1;
    }
    return 0;
}
