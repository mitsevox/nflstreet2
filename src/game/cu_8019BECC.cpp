#include "game/Object_80039F5C.h"
#include "game/Pair_8017055C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include <dolphin/mtx.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXVert.h>

/* A trail of points drawn as a flat ribbon with an end piece selected by
   mType. The width and brightness are interpolated along the trail. */
struct Trail_8019CBC0 {
    unsigned int mCount;
    int mUnknown4;
    Vector_80039F5C *mpPoints;
    int mType;
    float mRadiusX;
    float mRadiusY;
    int mAngleOffset;
    float mWidth;
    unsigned char mColor[3];
    float mEndWidth;
    float mEndBrightness;
    unsigned char mDashed;
};

/* Fan vertex of fn_8019C8C0; the 2D calls build its first two members. */
struct Vertex_8019C8C0 {
    Pair_8017055C mXY;
    float mZ;
    float mW;
};

extern "C" {
int fn_801CFC14(int angle, float *pFirst, float *pSecond);
float fn_801CFF54(float value);
void fn_801D0F80(Mtx44 m);
void fn_80210388(void);
void fn_80210BD8(int a);
void fn_80210CC4(float a, float b);
void fn_802271F0(Vector_80039F5C *pOut, Vector_80039F5C *pV);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_80227538(Pair_8017055C *pOut, int angle, float length);
int fn_802275D8(Vector_80039F5C *pA, Vector_80039F5C *pB, float epsilon);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_80227930(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB, float t);
int fn_80236EC0(int a);
void fn_8024CB90(int a, int b);
void fn_8024D418(void);
void fn_8024D450(int a, int b, int c, int d, int e);
void fn_8024DCE4(int a, int b, int c, int d, int e, int f);
void fn_8024DF64(int a);
void fn_8024FC48(int a);
void fn_8024FC84(int a, int b, int c, int d, int e, int f, int g);
void fn_80251604(int a, int b);
void fn_80251A58(int a, int b, int c, int d, int e);
void fn_80251B28(int a, int b, int c, int d);
void fn_80251CC4(int a);
void fn_8025251C(Mtx44 m, int a);
void fn_802525BC(int a);

float fn_8019BECC(Trail_8019CBC0 *pTrail, unsigned int index)
{
    return pTrail->mWidth * ((pTrail->mEndWidth - 1.0f) * index / pTrail->mCount + 1.0f);
}

void fn_8019BF38(Trail_8019CBC0 *pTrail, unsigned int index, unsigned char *pColor)
{
    float brightness = (pTrail->mEndBrightness - 1.0f) * index / pTrail->mCount + 1.0f;

    pColor[0] = (float)pTrail->mColor[0] * brightness;
    pColor[1] = (float)pTrail->mColor[1] * brightness;
    pColor[2] = (float)pTrail->mColor[2] * brightness;
}

/* Draws one quad of the ribbon at height 0 in the given colour. */
static inline void DrawQuad(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC,
                            Vector_80039F5C *pD, unsigned char *pColor)
{
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(pA->mX, pA->mY, 0.0f);
    GXColor4u8(pColor[0], pColor[1], pColor[2], 200);
    GXPosition3f32(pB->mX, pB->mY, 0.0f);
    GXColor4u8(pColor[0], pColor[1], pColor[2], 200);
    GXPosition3f32(pC->mX, pC->mY, 0.0f);
    GXColor4u8(pColor[0], pColor[1], pColor[2], 200);
    GXPosition3f32(pD->mX, pD->mY, 0.0f);
    GXColor4u8(pColor[0], pColor[1], pColor[2], 200);
}

/* Draws the ribbon segment from point index - 1 to point index, joined to
   the segment drawn before it through pLeft and pRight. */
int fn_8019C044(int unused, Trail_8019CBC0 *pTrail, unsigned int index, Vector_80039F5C *pLeft,
                Vector_80039F5C *pRight)
{
    Vector_80039F5C left1;
    Vector_80039F5C left0;
    Vector_80039F5C right1;
    Vector_80039F5C right0;
    Vector_80039F5C a1;
    Vector_80039F5C a0;
    Vector_80039F5C b1;
    Vector_80039F5C b0;
    Vector_80039F5C side;
    Vector_80039F5C side0;
    Vector_80039F5C side1;
    unsigned char color[3];
    float width0;
    float width1;
    float x;
    unsigned char i;

    width0 = fn_8019BECC(pTrail, index - 1);
    width1 = fn_8019BECC(pTrail, index);
    fn_802276B4(&side, &pTrail->mpPoints[index], &pTrail->mpPoints[index - 1]);
    x = side.mX;
    side.mX = side.mY;
    side.mY = -x;
    side.mZ = 0.0f;
    fn_802271F0(&side, &side);
    fn_80227264(&side0, &side, width0);
    fn_80227264(&side1, &side, width1);
    fn_8022765C(&left0, &pTrail->mpPoints[index - 1], &side0);
    fn_802276B4(&right0, &pTrail->mpPoints[index - 1], &side0);
    fn_8022765C(&left1, &pTrail->mpPoints[index], &side1);
    fn_802276B4(&right1, &pTrail->mpPoints[index], &side1);
    fn_8019BF38(pTrail, index - 1, color);
    if (pTrail->mDashed) {
        for (i = 0; i < 15; i++) {
            fn_80227930(&a0, &left1, &left0, (i * 2) / 29.0f);
            fn_80227930(&b0, &right1, &right0, (i * 2) / 29.0f);
            fn_80227930(&a1, &left1, &left0, (i * 2 + 1) / 29.0f);
            fn_80227930(&b1, &right1, &right0, (i * 2 + 1) / 29.0f);
            DrawQuad(&a1, &a0, &b0, &b1, color);
        }
    } else {
        DrawQuad(&left1, &left0, &right0, &right1, color);
    }
    if (index < pTrail->mCount - 1) {
        DrawQuad(&left1, pLeft, pRight, &right1, color);
    }
    pLeft->mX = left0.mX;
    pLeft->mY = left0.mY;
    pLeft->mZ = left0.mZ;
    pRight->mX = right0.mX;
    pRight->mY = right0.mY;
    pRight->mZ = right0.mZ;
    return 0;
}

/* Arrow head at point index. */
int fn_8019C4F4(int unused, Trail_8019CBC0 *pTrail, unsigned int index)
{
    Vector_80039F5C tip;
    Vector_80039F5C left;
    Vector_80039F5C right;
    Vector_80039F5C direction;
    Vector_80039F5C forward;
    unsigned char color[3];
    float width;
    float t;
    Vector_80039F5C *pPoints;

    width = fn_8019BECC(pTrail, index);
    fn_8019BF38(pTrail, index - 1, color);
    fn_802276B4(&direction, &pTrail->mpPoints[index], &pTrail->mpPoints[index - 1]);
    fn_802271F0(&direction, &direction);
    width *= 3.0f;
    fn_80227264(&forward, &direction, width);
    t = direction.mX;
    direction.mX = direction.mY;
    direction.mY = -t;
    direction.mZ = 0.0f;
    fn_802271F0(&direction, &direction);
    fn_80227264(&direction, &direction, width);
    fn_8022765C(&tip, &pTrail->mpPoints[index], &forward);
    fn_8022765C(&left, &pTrail->mpPoints[index], &direction);
    fn_802276B4(&right, &pTrail->mpPoints[index], &direction);
    pPoints = pTrail->mpPoints;
    DrawQuad(&left, &tip, &right, &pPoints[index], color);
    return 0;
}

/* Square end at point index. */
int fn_8019C6D8(int unused, Trail_8019CBC0 *pTrail, unsigned int index)
{
    Vector_80039F5C corner0;
    Vector_80039F5C corner1;
    Vector_80039F5C corner2;
    Vector_80039F5C corner3;
    Vector_80039F5C base;
    Vector_80039F5C direction;
    Vector_80039F5C side;
    unsigned char color[3];
    float width;

    width = fn_8019BECC(pTrail, index);
    fn_8019BF38(pTrail, index - 1, color);
    fn_802276B4(&direction, &pTrail->mpPoints[index], &pTrail->mpPoints[index - 1]);
    fn_802271F0(&direction, &direction);
    fn_80227264(&direction, &direction, width + width);
    fn_802276B4(&base, &pTrail->mpPoints[index], &direction);
    side.mX = -direction.mY;
    side.mY = direction.mX;
    side.mZ = 0.0f;
    fn_8022765C(&corner1, &base, &side);
    fn_8022765C(&corner0, &pTrail->mpPoints[index], &side);
    side.mX = direction.mY;
    side.mY = -direction.mX;
    side.mZ = 0.0f;
    fn_8022765C(&corner3, &base, &side);
    fn_8022765C(&corner2, &pTrail->mpPoints[index], &side);
    DrawQuad(&corner0, &corner1, &corner3, &corner2, color);
    return 0;
}

/* Ellipse of radii mRadiusX and mRadiusY around point index, drawn as a
   fan of 30 vertices. */
int fn_8019C8C0(int unused, Trail_8019CBC0 *pTrail, unsigned int index)
{
    Vertex_8019C8C0 vertex;
    unsigned char color[3];
    Pair_8017055C center;
    float first;
    float second;
    float angle;
    float steps;
    float radius;
    float a;
    float b;
    int offset;
    int phase;

    fn_8019BF38(pTrail, index - 1, color);
    fn_8019BECC(pTrail, index);
    center.mX = pTrail->mpPoints[index].mX;
    center.mY = pTrail->mpPoints[index].mY;
    a = pTrail->mRadiusX;
    b = pTrail->mRadiusY;
    offset = pTrail->mAngleOffset;
    vertex.mZ = 0.0f;
    vertex.mW = 1.0f;
    steps = 28.0f;
    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 30);
    vertex.mXY.mX = center.mX;
    vertex.mXY.mY = center.mY;
    GXPosition3f32(vertex.mXY.mX, vertex.mXY.mY, vertex.mZ);
    GXColor4u8(color[0], color[1], color[2], 50);
    for (angle = 0.0f; angle <= steps; angle += 1.0f) {
        phase = angle * 360.0f / steps * (16777216.0f / 360.0f);
        fn_801CFC14(phase, &first, &second);
        radius = b * a * fn_801CFF54(a * a * second * second + b * b * first * first);
        fn_80227538(&vertex.mXY, phase + offset, radius);
        fn_80227638(&vertex.mXY, &vertex.mXY, &center);
        GXPosition3f32(vertex.mXY.mX, vertex.mXY.mY, vertex.mZ);
        GXColor4u8(color[0], color[1], color[2], 50);
    }
    return 0;
}

/* Drops each point that lies on the point before it. */
void fn_8019CAC4(Trail_8019CBC0 *pTrail)
{
    unsigned int i;
    unsigned int j;
    unsigned int removed = 0;

    for (i = 0; i < pTrail->mCount - removed - 1; i++) {
        if (fn_802275D8(&pTrail->mpPoints[i], &pTrail->mpPoints[i + 1], 1e-7f)) {
            for (j = i + 1; j < pTrail->mCount - removed - 1; j++) {
                pTrail->mpPoints[j].mX = pTrail->mpPoints[j + 1].mX;
                pTrail->mpPoints[j].mY = pTrail->mpPoints[j + 1].mY;
                pTrail->mpPoints[j].mZ = pTrail->mpPoints[j + 1].mZ;
            }
            removed++;
        }
    }
    pTrail->mCount -= removed;
}

void fn_8019CBC0(Trail_8019CBC0 *pTrail)
{
    Vector_80039F5C left;
    Vector_80039F5C right;
    Mtx44 view;
    unsigned int i;
    int state;

    if (pTrail->mCount == 0) {
        return;
    }
    fn_80210388();
    fn_8019CAC4(pTrail);
    fn_8024D418();
    fn_8024CB90(9, 1);
    fn_8024CB90(11, 1);
    fn_8024D450(0, 9, 1, 4, 0);
    fn_8024D450(0, 11, 1, 5, 0);
    fn_80251CC4(1);
    fn_80251B28(0, 0xFF, 0xFF, 4);
    fn_80251604(0, 4);
    fn_8024FC48(1);
    fn_8024FC84(4, 0, 0, 1, 1, 2, 1);
    fn_8024DF64(1);
    fn_8024DCE4(0, 0, 4, 60, 0, 125);
    fn_801D0F80(view);
    fn_802525BC(0);
    fn_8025251C(view, 0);
    GXSetZCompLoc(GX_TRUE);
    fn_80251A58(7, 0, 0, 7, 0);
    GXSetCullMode(GX_CULL_NONE);
    if (pTrail->mType == 3) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    } else {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        fn_80210CC4(0.01f, 0.01f);
    }
    fn_80210BD8(2);
    state = fn_80236EC0(0);
    if (pTrail->mType == 0) {
        fn_8019C4F4(0, pTrail, pTrail->mCount - 1);
    } else if (pTrail->mType == 1) {
        fn_8019C6D8(0, pTrail, pTrail->mCount - 1);
    } else if (pTrail->mType == 2) {
        fn_8019C8C0(0, pTrail, pTrail->mCount - 1);
    } else if (pTrail->mType == 3) {
        fn_8019C4F4(0, pTrail, pTrail->mCount - 1);
    }
    for (i = pTrail->mCount - 1; i != 0; i--) {
        fn_8019C044(0, pTrail, i, &left, &right);
    }
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    fn_80210CC4(0.0f, 1.0f);
    fn_80210BD8(1);
    fn_80236EC0(state);
}
}
