/*
 * View clipping for the TM renderer. Keeps a copy of the current projection and
 * local-to-camera matrices, projects points and bounding boxes through them into clip
 * space, and returns the six-plane clip codes the renderer uses to skip models that lie
 * wholly off screen (and to know which ones cross an edge). It can also collect the
 * screen extent of the projected points and their average depth.
 */
#include "engine/tmlib.h"

extern void fn_801D0424(void *pDst, void *pSrc);
extern void fn_801D04C4(void);
extern void fn_801D0544(void);
extern void fn_801D0664(void *pMtx);
extern void fn_801D06D4(void *pMtx);
extern void fn_801D1288(int mode, void *pMtx);

static f32 _TMClip_ZeroVec[3] = { 0.0f, 0.0f, 0.0f };
static Mtx44 _TMClip_Projection;
static Mtx44 _TMClip_LocalToCamera;

static inline void _TMClipExpandXformRow(TMClipExtent_t *pBox, f32 (*pMtx)[4], f32 (*pOut)[3], int r)
{
    f32 y0 = pMtx[r][1] * pBox->mMin[1];
    f32 z0 = pMtx[r][2] * pBox->mMin[2];
    f32 x0 = pMtx[r][0] * pBox->mMin[0];
    f32 w = pMtx[r][3];
    f32 x1 = pMtx[r][0] * pBox->mMax[0];
    f32 y1 = pMtx[r][1] * pBox->mMax[1];
    f32 z1 = pMtx[r][2] * pBox->mMax[2];
    f32 t;

    t = y0 + z0 + w;
    pOut[0][r] = x0 + t;
    pOut[1][r] = x1 + t;
    t = y1 + z0 + w;
    pOut[2][r] = x0 + t;
    pOut[3][r] = x1 + t;
    t = y0 + z1 + w;
    pOut[4][r] = x0 + t;
    pOut[5][r] = x1 + t;
    t = y1 + z1 + w;
    pOut[6][r] = x0 + t;
    pOut[7][r] = x1 + t;
}

/* Transforms the eight corners of a box by a 3x4 matrix. */
static void _TMClipExpandXformBBox(TMClipExtent_t *pBox, f32 (*pMtx)[4], f32 (*pOut)[3])
{
    _TMClipExpandXformRow(pBox, pMtx, pOut, 0);
    _TMClipExpandXformRow(pBox, pMtx, pOut, 1);
    _TMClipExpandXformRow(pBox, pMtx, pOut, 2);
}

/* Applies the projection's non-zero terms to a camera-space point. */
static inline void _TMClipProjectPoint(f32 *pClip, f32 (*pMtx)[4], f32 *pPos)
{
    pClip[0] = pMtx[0][0] * pPos[0] + pMtx[0][2] * pPos[2];
    pClip[1] = pMtx[1][1] * pPos[1] + pMtx[1][2] * pPos[2];
    pClip[2] = pMtx[2][2] * pPos[2] + pMtx[2][3];
    pClip[3] = pMtx[3][2] * pPos[2];
}

/* The six-bit clip code of a clip-space point: one bit per plane it lies outside. */
static inline unsigned int _TMClipOutcode(f32 *pClip)
{
    unsigned int code;

    code = 0;
    if (!(pClip[0] >= -pClip[3])) {
        code = 2;
    } else if (!(pClip[0] <= pClip[3])) {
        code = 1;
    }
    if (!(pClip[1] >= -pClip[3])) {
        code |= 8;
    } else if (!(pClip[1] <= pClip[3])) {
        code |= 4;
    }
    if (!(pClip[2] >= -pClip[3])) {
        code |= 0x20;
    } else if (!(pClip[2] <= pClip[3])) {
        code |= 0x10;
    }
    return code;
}

static inline void _TMClipExtentAddVec(TMClipExtent_t *pExtent, f32 *pPos)
{
    if (!(pPos[0] >= pExtent->mMin[0])) {
        pExtent->mMin[0] = pPos[0];
    }
    if (!(pPos[0] <= pExtent->mMax[0])) {
        pExtent->mMax[0] = pPos[0];
    }
    if (!(pPos[1] >= pExtent->mMin[1])) {
        pExtent->mMin[1] = pPos[1];
    }
    if (!(pPos[1] <= pExtent->mMax[1])) {
        pExtent->mMax[1] = pPos[1];
    }
    if (!(pPos[2] >= pExtent->mMin[2])) {
        pExtent->mMin[2] = pPos[2];
    }
    if (!(pPos[2] <= pExtent->mMax[2])) {
        pExtent->mMax[2] = pPos[2];
    }
}

/* Clip codes of camera-space points: the OR of all codes in bits 8-13, their AND in bits 0-5. */
static unsigned int _TMClipVertexListProj(f32 *pPoints, int numPoints, f32 (*pMtx)[4], f32 *pDepth)
{
    f32 aClip[4];
    f32 depth;
    unsigned int andCode;
    unsigned int orCode;
    unsigned int code;
    int count;

    depth = 0.0f;
    andCode = 0x3F;
    orCode = 0;
    count = numPoints;
    for (; numPoints > 0; numPoints--) {
        _TMClipProjectPoint(aClip, pMtx, pPoints);
        code = _TMClipOutcode(aClip);
        orCode |= code;
        andCode &= code;
        if (pDepth != 0) {
            depth -= aClip[3];
        }
        pPoints += 3;
    }
    if (pDepth != 0) {
        *pDepth = depth / count;
    }
    return (orCode << 8) | andCode;
}

/* As _TMClipVertexListProj, also growing the extent by each point's projected position. */
static unsigned int _TMClipVertexListProjExtent(f32 *pPoints, int numPoints, f32 (*pMtx)[4],
                                                TMClipExtent_t *pExtent, f32 *pDepth)
{
    f32 aClip[4];
    f32 aNdc[3];
    f32 depth;
    f32 inv;
    unsigned int andCode;
    unsigned int orCode;
    unsigned int code;
    int count;

    depth = 0.0f;
    andCode = 0x3F;
    orCode = 0;
    count = numPoints;
    for (; numPoints > 0; numPoints--) {
        _TMClipProjectPoint(aClip, pMtx, pPoints);
        inv = 1.0f / aClip[3];
        code = _TMClipOutcode(aClip);
        orCode |= code;
        andCode &= code;
        aNdc[0] = aClip[0] * inv;
        aNdc[1] = aClip[1] * inv;
        aNdc[2] = aClip[2] * inv;
        _TMClipExtentAddVec(pExtent, aNdc);
        if (pDepth != 0) {
            depth -= aClip[3];
        }
        pPoints += 3;
    }
    if (pDepth != 0) {
        *pDepth = depth / count;
    }
    return (orCode << 8) | andCode;
}

/* Sets the projection matrix to clip against: a copy of pMtx, or the current one. */
void TMClipProjection(void *pMtx)
{
    if (pMtx != 0) {
        fn_801D0424(_TMClip_Projection, pMtx);
    } else {
        fn_801D1288(2, _TMClip_Projection);
    }
}

/* Sets the local-to-camera matrix: a copy of pMtx, or the current one. */
void TMClipMatrix(void *pMtx)
{
    if (pMtx != 0) {
        fn_801D0424(_TMClip_LocalToCamera, pMtx);
    } else {
        fn_801D0F80(_TMClip_LocalToCamera);
    }
}

/* Builds the local-to-camera matrix from up to three matrices on a pushed matrix stack. */
void TMClipMatrixWorld(void *pMtxA, void *pMtxB, void *pMtxC)
{
    fn_801D04C4();
    if (pMtxA != 0) {
        fn_801D06D4(pMtxA);
    }
    if (pMtxB != 0) {
        fn_801D0664(pMtxB);
    }
    if (pMtxC != 0) {
        fn_801D0664(pMtxC);
    }
    fn_801D0F80(_TMClip_LocalToCamera);
    fn_801D0544();
}

/* Clip codes of local-space points through both matrices, with optional extent and depth. */
unsigned int TMClipVertexList(f32 *pPoints, int numPoints, TMClipExtent_t *pExtent, f32 *pDepth)
{
    f32 aPos[3];
    f32 aClip[4];
    f32 aNdc[3];
    f32 depth;
    f32 inv;
    unsigned int andCode;
    unsigned int orCode;
    unsigned int code;
    int count;

    depth = 0.0f;
    andCode = 0x3F;
    orCode = 0;
    if (pExtent != 0) {
        TMClipResetExtent(pExtent);
    }
    count = numPoints;
    for (; numPoints > 0; numPoints--) {
        aPos[0] = _TMClip_LocalToCamera[0][0] * pPoints[0] + _TMClip_LocalToCamera[0][1] * pPoints[1] +
                  _TMClip_LocalToCamera[0][2] * pPoints[2] + _TMClip_LocalToCamera[0][3];
        aPos[1] = _TMClip_LocalToCamera[1][0] * pPoints[0] + _TMClip_LocalToCamera[1][1] * pPoints[1] +
                  _TMClip_LocalToCamera[1][2] * pPoints[2] + _TMClip_LocalToCamera[1][3];
        aPos[2] = _TMClip_LocalToCamera[2][0] * pPoints[0] + _TMClip_LocalToCamera[2][1] * pPoints[1] +
                  _TMClip_LocalToCamera[2][2] * pPoints[2] + _TMClip_LocalToCamera[2][3];
        _TMClipProjectPoint(aClip, _TMClip_Projection, aPos);
        code = _TMClipOutcode(aClip);
        andCode &= code;
        orCode |= code;
        if (pExtent != 0) {
            inv = 1.0f / aClip[3];
            aNdc[0] = aClip[0] * inv;
            aNdc[1] = aClip[1] * inv;
            aNdc[2] = aClip[2] * inv;
            _TMClipExtentAddVec(pExtent, aNdc);
        }
        if (pDepth != 0) {
            depth -= aClip[3];
        }
        pPoints += 3;
    }
    if (pDepth != 0) {
        *pDepth = depth / count;
    }
    return (orCode << 8) | andCode;
}

/* Clip codes of camera-space points; resets and fills pExtent when it is given. */
unsigned int TMClipProjVertexList(void *pPoints, int numPoints, TMClipExtent_t *pExtent, void *pArg)
{
    unsigned int result;

    if (pExtent != 0) {
        TMClipResetExtent(pExtent);
        result = _TMClipVertexListProjExtent(pPoints, numPoints, _TMClip_Projection, pExtent, pArg);
    } else {
        result = _TMClipVertexListProj(pPoints, numPoints, _TMClip_Projection, pArg);
    }
    return result;
}

/* Projects one local-space point (the origin when pPos is null); returns its clip code. */
int TMClipVertex(f32 *pNdc, f32 *pClip, f32 *pPos)
{
    f32 aClip[4];
    f32 x;
    f32 y;
    f32 z;
    int code;

    if (pPos == 0) {
        pPos = _TMClip_ZeroVec;
    }
    if (pClip == 0) {
        pClip = aClip;
    }
    x = _TMClip_LocalToCamera[0][0] * pPos[0] + _TMClip_LocalToCamera[0][1] * pPos[1] + _TMClip_LocalToCamera[0][2] * pPos[2] + _TMClip_LocalToCamera[0][3];
    y = _TMClip_LocalToCamera[1][0] * pPos[0] + _TMClip_LocalToCamera[1][1] * pPos[1] + _TMClip_LocalToCamera[1][2] * pPos[2] + _TMClip_LocalToCamera[1][3];
    z = _TMClip_LocalToCamera[2][0] * pPos[0] + _TMClip_LocalToCamera[2][1] * pPos[1] + _TMClip_LocalToCamera[2][2] * pPos[2] + _TMClip_LocalToCamera[2][3];
    pClip[0] = _TMClip_Projection[0][0] * x + _TMClip_Projection[0][2] * z;
    pClip[1] = _TMClip_Projection[1][1] * y + _TMClip_Projection[1][2] * z;
    pClip[2] = _TMClip_Projection[2][2] * z + _TMClip_Projection[2][3];
    pClip[3] = _TMClip_Projection[3][2] * z;
    if (pNdc != 0) {
        f32 inv = 1.0f / pClip[3];

        pNdc[0] = pClip[0] * inv;
        pNdc[1] = pClip[1] * inv;
        pNdc[2] = pClip[2] * inv;
    }
    code = 0;
    if (!(pClip[0] >= -pClip[3])) {
        code = 2;
    } else if (!(pClip[0] <= pClip[3])) {
        code = 1;
    }
    if (!(pClip[1] >= -pClip[3])) {
        code |= 8;
    } else if (!(pClip[1] <= pClip[3])) {
        code |= 4;
    }
    if (!(pClip[2] >= -pClip[3])) {
        code |= 0x20;
    } else if (!(pClip[2] <= pClip[3])) {
        code |= 0x10;
    }
    return code;
}

/* Clip codes of a local-space box, by its eight corners. */
unsigned int TMClipBBox(TMClipExtent_t *pBox, TMClipExtent_t *pExtent, void *pArg)
{
    u8 aPoints[0x60];

    _TMClipExpandXformBBox(pBox, _TMClip_LocalToCamera, (f32 (*)[3])aPoints);
    return TMClipProjVertexList(aPoints, 8, pExtent, pArg);
}

/* Empties an extent: minimum at +FLT_MAX, maximum at -FLT_MAX. */
void TMClipResetExtent(TMClipExtent_t *pExtent)
{
    pExtent->mMin[2] = 3.4028235e38f;
    pExtent->mMin[1] = 3.4028235e38f;
    pExtent->mMin[0] = 3.4028235e38f;
    pExtent->mMax[2] = -3.4028235e38f;
    pExtent->mMax[1] = -3.4028235e38f;
    pExtent->mMax[0] = -3.4028235e38f;
}

/* Grows an extent to include the point (x, y, z). */
void TMClipExtentAddPoint(TMClipExtent_t *pExtent, float x, float y, float z)
{
    if (!(x >= pExtent->mMin[0])) {
        pExtent->mMin[0] = x;
    }
    if (!(x <= pExtent->mMax[0])) {
        pExtent->mMax[0] = x;
    }
    if (!(y >= pExtent->mMin[1])) {
        pExtent->mMin[1] = y;
    }
    if (!(y <= pExtent->mMax[1])) {
        pExtent->mMax[1] = y;
    }
    if (!(z >= pExtent->mMin[2])) {
        pExtent->mMin[2] = z;
    }
    if (!(z <= pExtent->mMax[2])) {
        pExtent->mMax[2] = z;
    }
}
