struct Vec_801E850C {
    float x;
    float y;
    float z;
};

/* Rigid body (defined in another file). */
struct Body_801E850C {
    char mUnknown00[0x44];
    float mUnknown44;
    char mUnknown48[0x64 - 0x48];
    Vec_801E850C mUnknown64;
    char mUnknown70[0x88 - 0x70];
    float mUnknown88[4][4];
    float mUnknownC8[4][4];
};

extern "C" {
void fn_801D04C4(void);
void fn_801D0544(void);
void fn_801D06D4(float (*m)[4]);
float fn_802270D4(Vec_801E850C *pV);
void fn_80227264(Vec_801E850C *pOut, Vec_801E850C *pV, float scale);
void fn_8022765C(Vec_801E850C *pOut, Vec_801E850C *pA, Vec_801E850C *pB);
void fn_802276B4(Vec_801E850C *pOut, Vec_801E850C *pA, Vec_801E850C *pB);
float fn_80227704(Vec_801E850C *pA, Vec_801E850C *pB);
void fn_802277DC(Vec_801E850C *pOut, Vec_801E850C *pA, Vec_801E850C *pB);
void fn_80227C2C(Vec_801E850C *pOut, Vec_801E850C *pIn);
void fn_80227CC0(Vec_801E850C *pOut, Vec_801E850C *pIn);
void fn_801E987C(Body_801E850C *pBody);
void fn_801E9D64(Body_801E850C *pBody, Vec_801E850C *pImpulse, Vec_801E850C *pPoint);
void fn_801E9E18(Body_801E850C *pBody, Vec_801E850C *pPoint, Vec_801E850C *pVel);
}

/* Constraint interface. */
class Class_801E850C {
public:
    virtual void vfn_01() = 0;
};

/* Point-to-point joint between two bodies. */
class Class_801E8478 : public Class_801E850C {
public:
    Class_801E8478(Body_801E850C *pBodyA, Body_801E850C *pBodyB, Vec_801E850C *pAnchorA,
                   Vec_801E850C *pAnchorB);
    virtual void vfn_01();
    virtual ~Class_801E8478();

    Body_801E850C *mpBodyA;
    Vec_801E850C mAnchorA;
    Body_801E850C *mpBodyB;
    Vec_801E850C mAnchorB;
};

Class_801E8478::Class_801E8478(Body_801E850C *pBodyA, Body_801E850C *pBodyB,
                               Vec_801E850C *pAnchorA, Vec_801E850C *pAnchorB)
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
    Vec_801E850C pointA;
    Vec_801E850C pointB;
    Vec_801E850C velA;
    Vec_801E850C velB;
    Vec_801E850C error;
    Vec_801E850C delta;
    Vec_801E850C normal;
    Vec_801E850C armA;
    Vec_801E850C armB;
    Vec_801E850C crossA;
    Vec_801E850C crossB;
    Vec_801E850C turnA;
    Vec_801E850C turnB;
    Vec_801E850C impulse;
    float (*pMatrixA)[4];
    float (*pMatrixB)[4];
    float (*pInertiaA)[4];
    float (*pInertiaB)[4];
    float length;
    float massA;
    float massB;
    float dotA;

    fn_801D04C4();
    pMatrixA = mpBodyA->mUnknown88;
    pMatrixB = mpBodyB->mUnknown88;
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
        fn_802276B4(&armA, &pointA, &mpBodyA->mUnknown64);
        fn_802276B4(&armB, &pointB, &mpBodyB->mUnknown64);
        pInertiaA = mpBodyA->mUnknownC8;
        pInertiaB = mpBodyB->mUnknownC8;
        fn_802277DC(&crossA, &armA, &normal);
        fn_802277DC(&crossB, &armB, &normal);
        fn_801D06D4(pInertiaA);
        fn_80227C2C(&turnA, &crossA);
        fn_801D06D4(pInertiaB);
        fn_80227C2C(&turnB, &crossB);
        fn_802277DC(&crossA, &turnA, &armA);
        fn_802277DC(&crossB, &turnB, &armB);
        massA = mpBodyA->mUnknown44;
        massB = mpBodyB->mUnknown44;
        dotA = fn_80227704(&normal, &crossA);
        fn_80227264(&impulse, &normal, length / (massA + massB + dotA + fn_80227704(&normal, &crossB)));
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
