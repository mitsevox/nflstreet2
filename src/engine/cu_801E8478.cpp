#include "engine/Body_801E9538.h"
#include "game/fn_802270D4.h"

#include "engine/cu_801E8478.h"
#include "engine/cu_801D03D0.h"

Class_801E8478::Class_801E8478(Body_801E9538 *pBodyA, Body_801E9538 *pBodyB,
                               Vec3_801DE1E0 *pAnchorA, Vec3_801DE1E0 *pAnchorB)
    : mpBodyA(pBodyA), mAnchorA(*pAnchorA), mpBodyB(pBodyB), mAnchorB(*pAnchorB)
{
}

Class_801E8478::~Class_801E8478()
{
    mpBodyA = 0;
    mpBodyB = 0;
}

void Class_801E8478::vfn_01()
{
    Vec3_801DE1E0 pointA;
    Vec3_801DE1E0 pointB;
    Vec3_801DE1E0 velA;
    Vec3_801DE1E0 velB;
    Vec3_801DE1E0 error;
    Vec3_801DE1E0 delta;
    Vec3_801DE1E0 normal;
    Vec3_801DE1E0 armA;
    Vec3_801DE1E0 armB;
    Vec3_801DE1E0 crossA;
    Vec3_801DE1E0 crossB;
    Vec3_801DE1E0 turnA;
    Vec3_801DE1E0 turnB;
    Vec3_801DE1E0 impulse;
    float *pMatrixA;
    float *pMatrixB;
    float *pInertiaA;
    float *pInertiaB;
    float length;
    float invMassA;
    float invMassB;
    float dotA;

    fn_801D04C4();
    pMatrixA = mpBodyA->mUnknown088[0];
    pMatrixB = mpBodyB->mUnknown088[0];
    fn_801D06D4(pMatrixA);
    fn_80227CC0(&pointA, &mAnchorA);
    fn_801D06D4(pMatrixB);
    fn_80227CC0(&pointB, &mAnchorB);
    fn_801E9E18(mpBodyA, &pointA, &velA);
    fn_801E9E18(mpBodyB, &pointB, &velB);
    fn_802276B4(&error, &velB, &velA);
    fn_802276B4(&delta, &pointB, &pointA);
    fn_80227264(&delta, &delta, 1.0f);
    fn_8022765C(&error, &error, &delta);
    length = fn_802270D4(&error);
    if (!(length <= 1e-06f)) {
        fn_80227264(&normal, &error, 1.0f / length);
        fn_802276B4(&armA, &pointA, &mpBodyA->mUnknown064);
        fn_802276B4(&armB, &pointB, &mpBodyB->mUnknown064);
        pInertiaA = mpBodyA->mUnknown0C8[0];
        pInertiaB = mpBodyB->mUnknown0C8[0];
        fn_802277DC(&crossA, &armA, &normal);
        fn_802277DC(&crossB, &armB, &normal);
        fn_801D06D4(pInertiaA);
        fn_80227C2C(&turnA, &crossA);
        fn_801D06D4(pInertiaB);
        fn_80227C2C(&turnB, &crossB);
        fn_802277DC(&crossA, &turnA, &armA);
        fn_802277DC(&crossB, &turnB, &armB);
        invMassA = mpBodyA->mUnknown044;
        invMassB = mpBodyB->mUnknown044;
        dotA = fn_80227704(&normal, &crossA);
        fn_80227264(&impulse, &normal, length / (invMassA + invMassB + dotA + fn_80227704(&normal, &crossB)));
        fn_801E9D64(mpBodyA, &impulse, &pointA);
        impulse.x = -impulse.x;
        impulse.y = -impulse.y;
        impulse.z = -impulse.z;
        fn_801E9D64(mpBodyB, &impulse, &pointB);
        fn_801E987C(mpBodyA);
        fn_801E987C(mpBodyB);
    }
    fn_801D0544();
}
