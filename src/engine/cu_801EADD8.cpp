#include "engine/vec.h"
#include "engine/cu_801D03D0.h"

extern "C" {
void fn_801E736C(Vec3_801DE1E0 *pA, Vec3_801DE1E0 *pB, int a, int b, int c);
}

/* Axis-aligned box. */
class Class_801EADD8 {
public:
    Class_801EADD8();
    virtual ~Class_801EADD8();
    void fn_801EAE44(Vec3_801DE1E0 *pMin, Vec3_801DE1E0 *pMax);
    void fn_801EAE7C(Vec3_801DE1E0 *pPoint);
    void fn_801EAEB4(Vec3_801DE1E0 *pPoint);
    void fn_801EAF60(float (*m)[4], Class_801EADD8 *pOut);
    void fn_801EB134(int a, int b, int c);

    Vec3_801DE1E0 mMin;
    Vec3_801DE1E0 mMax;
};

Class_801EADD8::Class_801EADD8()
{
    Vec3_801DE1E0 *pMax = &mMax;

    mMin.x = mMin.y = mMin.z = 0.0f;
    pMax->x = pMax->y = pMax->z = 0.0f;
}

Class_801EADD8::~Class_801EADD8()
{
}

void Class_801EADD8::fn_801EAE44(Vec3_801DE1E0 *pMin, Vec3_801DE1E0 *pMax)
{
    mMin = *pMin;
    mMax = *pMax;
}

void Class_801EADD8::fn_801EAE7C(Vec3_801DE1E0 *pPoint)
{
    mMin = *pPoint;
    mMax = *pPoint;
}

void Class_801EADD8::fn_801EAEB4(Vec3_801DE1E0 *pPoint)
{
    mMin.x = pPoint->x <= mMin.x ? pPoint->x : mMin.x;
    mMin.y = pPoint->y <= mMin.y ? pPoint->y : mMin.y;
    mMin.z = pPoint->z <= mMin.z ? pPoint->z : mMin.z;
    mMax.x = pPoint->x >= mMax.x ? pPoint->x : mMax.x;
    mMax.y = pPoint->y >= mMax.y ? pPoint->y : mMax.y;
    mMax.z = pPoint->z >= mMax.z ? pPoint->z : mMax.z;
}

void Class_801EADD8::fn_801EAF60(float (*m)[4], Class_801EADD8 *pOut)
{
    Vec3_801DE1E0 axisX;
    Vec3_801DE1E0 axisY;
    Vec3_801DE1E0 axisZ;
    Vec3_801DE1E0 corner;
    Vec3_801DE1E0 point;
    float sizeX;
    float sizeY;
    float sizeZ;

    fn_801D04C4();
    fn_801D06D4(m[0]);
    fn_80227CC0(&corner, &mMin);
    fn_801D0544();
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
    fn_80227264(&axisX, &axisX, sizeX);
    fn_80227264(&axisY, &axisY, sizeY);
    fn_80227264(&axisZ, &axisZ, sizeZ);
    pOut->fn_801EAE7C(&corner);
    fn_8022765C(&point, &corner, &axisX);
    pOut->fn_801EAEB4(&point);
    fn_8022765C(&point, &point, &axisY);
    pOut->fn_801EAEB4(&point);
    fn_8022765C(&point, &corner, &axisY);
    pOut->fn_801EAEB4(&point);
    fn_8022765C(&corner, &corner, &axisZ);
    pOut->fn_801EAEB4(&corner);
    fn_8022765C(&point, &corner, &axisX);
    pOut->fn_801EAEB4(&point);
    fn_8022765C(&point, &point, &axisY);
    pOut->fn_801EAEB4(&point);
    fn_8022765C(&point, &corner, &axisY);
    pOut->fn_801EAEB4(&point);
}

void Class_801EADD8::fn_801EB134(int a, int b, int c)
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
    fn_80227264(&axisX, &axisX, sizeX);
    fn_80227264(&axisY, &axisY, sizeY);
    fn_80227264(&axisZ, &axisZ, sizeZ);
    corner = mMin;
    corners[0] = mMin;
    fn_8022765C(&point, &corner, &axisX);
    corners[1] = point;
    fn_8022765C(&point, &point, &axisY);
    corners[2] = point;
    fn_8022765C(&point, &corner, &axisY);
    corners[3] = point;
    fn_8022765C(&corner, &corner, &axisZ);
    corners[4] = corner;
    fn_8022765C(&point, &corner, &axisX);
    corners[5] = point;
    fn_8022765C(&point, &point, &axisY);
    corners[6] = point;
    fn_8022765C(&point, &corner, &axisY);
    corners[7] = point;
    fn_801E736C(&corners[0], &corners[1], a, b, c);
    fn_801E736C(&corners[1], &corners[2], a, b, c);
    fn_801E736C(&corners[2], &corners[3], a, b, c);
    fn_801E736C(&corners[3], &corners[0], a, b, c);
    fn_801E736C(&corners[4], &corners[5], a, b, c);
    fn_801E736C(&corners[5], &corners[6], a, b, c);
    fn_801E736C(&corners[6], &corners[7], a, b, c);
    fn_801E736C(&corners[7], &corners[4], a, b, c);
    fn_801E736C(&corners[0], &corners[4], a, b, c);
    fn_801E736C(&corners[1], &corners[5], a, b, c);
    fn_801E736C(&corners[2], &corners[6], a, b, c);
    fn_801E736C(&corners[3], &corners[7], a, b, c);
}
