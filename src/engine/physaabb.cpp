/* Rigid-body physics: axis-aligned bounding boxes for collision shapes, which can be grown by
   points, moved by a matrix and drawn for debugging. */

#include "engine/physaabb.h"
#include "engine/llmatrix.h"

extern "C" {
void DispatchCollisionDebugLine(Vec3_801DE1E0 *pA, Vec3_801DE1E0 *pB, int a, int b, int c);
}

BoundingBox::BoundingBox()
{
    Vec3_801DE1E0 *pMax = &mMax;

    mMin.x = mMin.y = mMin.z = 0.0f;
    pMax->x = pMax->y = pMax->z = 0.0f;
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::SetBounds(Vec3_801DE1E0 *pMin, Vec3_801DE1E0 *pMax)
{
    mMin = *pMin;
    mMax = *pMax;
}

void BoundingBox::SetToPoint(Vec3_801DE1E0 *pPoint)
{
    mMin = *pPoint;
    mMax = *pPoint;
}

void BoundingBox::ExtendToPoint(Vec3_801DE1E0 *pPoint)
{
    mMin.x = pPoint->x <= mMin.x ? pPoint->x : mMin.x;
    mMin.y = pPoint->y <= mMin.y ? pPoint->y : mMin.y;
    mMin.z = pPoint->z <= mMin.z ? pPoint->z : mMin.z;
    mMax.x = pPoint->x >= mMax.x ? pPoint->x : mMax.x;
    mMax.y = pPoint->y >= mMax.y ? pPoint->y : mMax.y;
    mMax.z = pPoint->z >= mMax.z ? pPoint->z : mMax.z;
}

void BoundingBox::TransformBox(float (*m)[4], BoundingBox *pOut)
{
    Vec3_801DE1E0 axisX;
    Vec3_801DE1E0 axisY;
    Vec3_801DE1E0 axisZ;
    Vec3_801DE1E0 corner;
    Vec3_801DE1E0 point;
    float sizeX;
    float sizeY;
    float sizeZ;

    MatPush();
    MatLoad(m[0]);
    Vec3Mat34Mul(&corner, &mMin);
    MatPop();
    axisX.x = m[0][0];
    axisX.y = m[1][0];
    axisX.z = m[2][0];
    axisY.x = m[0][1];
    axisY.y = m[1][1];
    axisY.z = m[2][1];
    axisZ.x = m[0][2];
    axisZ.y = m[1][2];
    axisZ.z = m[2][2];
    sizeX = mMax.x - mMin.x;
    sizeY = mMax.y - mMin.y;
    sizeZ = mMax.z - mMin.z;
    Vec3Scale(&axisX, &axisX, sizeX);
    Vec3Scale(&axisY, &axisY, sizeY);
    Vec3Scale(&axisZ, &axisZ, sizeZ);
    pOut->SetToPoint(&corner);
    Vec3Add(&point, &corner, &axisX);
    pOut->ExtendToPoint(&point);
    Vec3Add(&point, &point, &axisY);
    pOut->ExtendToPoint(&point);
    Vec3Add(&point, &corner, &axisY);
    pOut->ExtendToPoint(&point);
    Vec3Add(&corner, &corner, &axisZ);
    pOut->ExtendToPoint(&corner);
    Vec3Add(&point, &corner, &axisX);
    pOut->ExtendToPoint(&point);
    Vec3Add(&point, &point, &axisY);
    pOut->ExtendToPoint(&point);
    Vec3Add(&point, &corner, &axisY);
    pOut->ExtendToPoint(&point);
}

void BoundingBox::DrawDebug(int a, int b, int c)
{
    Vec3_801DE1E0 axisX;
    Vec3_801DE1E0 axisY;
    Vec3_801DE1E0 axisZ;
    Vec3_801DE1E0 corner;
    Vec3_801DE1E0 point;
    Vec3_801DE1E0 corners[8];
    float sizeX = mMax.x - mMin.x;
    float sizeY = mMax.y - mMin.y;
    float sizeZ = mMax.z - mMin.z;

    axisX.x = 1.0f;
    axisX.y = 0.0f;
    axisX.z = 0.0f;
    axisY.x = 0.0f;
    axisY.y = 1.0f;
    axisY.z = 0.0f;
    axisZ.x = 0.0f;
    axisZ.y = 0.0f;
    axisZ.z = 1.0f;
    Vec3Scale(&axisX, &axisX, sizeX);
    Vec3Scale(&axisY, &axisY, sizeY);
    Vec3Scale(&axisZ, &axisZ, sizeZ);
    corner = mMin;
    corners[0] = mMin;
    Vec3Add(&point, &corner, &axisX);
    corners[1] = point;
    Vec3Add(&point, &point, &axisY);
    corners[2] = point;
    Vec3Add(&point, &corner, &axisY);
    corners[3] = point;
    Vec3Add(&corner, &corner, &axisZ);
    corners[4] = corner;
    Vec3Add(&point, &corner, &axisX);
    corners[5] = point;
    Vec3Add(&point, &point, &axisY);
    corners[6] = point;
    Vec3Add(&point, &corner, &axisY);
    corners[7] = point;
    DispatchCollisionDebugLine(&corners[0], &corners[1], a, b, c);
    DispatchCollisionDebugLine(&corners[1], &corners[2], a, b, c);
    DispatchCollisionDebugLine(&corners[2], &corners[3], a, b, c);
    DispatchCollisionDebugLine(&corners[3], &corners[0], a, b, c);
    DispatchCollisionDebugLine(&corners[4], &corners[5], a, b, c);
    DispatchCollisionDebugLine(&corners[5], &corners[6], a, b, c);
    DispatchCollisionDebugLine(&corners[6], &corners[7], a, b, c);
    DispatchCollisionDebugLine(&corners[7], &corners[4], a, b, c);
    DispatchCollisionDebugLine(&corners[0], &corners[4], a, b, c);
    DispatchCollisionDebugLine(&corners[1], &corners[5], a, b, c);
    DispatchCollisionDebugLine(&corners[2], &corners[6], a, b, c);
    DispatchCollisionDebugLine(&corners[3], &corners[7], a, b, c);
}
