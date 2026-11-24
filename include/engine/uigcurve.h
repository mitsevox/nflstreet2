#ifndef ENGINE_UIGCURVE_H
#define ENGINE_UIGCURVE_H

#include "types.h"

struct UIGNode_t;
struct UIGCurvePoint_t;

typedef union UIGCurveArg_t {
    Int32 i;
    Float32 f;
    void *p;
    Int16 s[2];
} UIGCurveArg_t;

#ifdef __cplusplus
extern "C" {
#endif
void UIGCurveObjAction(struct UIGNode_t *pNode, Uint32 msg, int nArgs, UIGCurveArg_t *pArgs);
void UIGCurveBuildStrip(int numPoints, struct UIGCurvePoint_t *pPoints, float *pWidths,
                       struct UIGCurvePoint_t *pOut, int numOut);
struct UIGCurvePoint_t UIGCurveGetPoint(struct UIGCurvePoint_t *pPoints, int unused, int index);
#ifdef __cplusplus
}
#endif
#endif
