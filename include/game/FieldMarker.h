#ifndef GAME_FIELDMARKER_H
#define GAME_FIELDMARKER_H

/* One beam of a marker set: drawn by FieldMarkerDrawBeams with width mUnknown0, alpha
   mUnknown4 and offset mUnknown8; mUnknownC and mUnknown10 are the time and phase that
   FieldMarkerUpdateBeams advances. */
struct FieldMarkerBeam_t {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    int mUnknown10;
};

/* A fixed spot on the field with three beams. */
struct FieldMarkerBeamSet_t {
    float mPosition[3];
    float mUnknownC;
    FieldMarkerBeam_t mUnknown10[3];
};

/* One of the small arrows drawn by FieldMarkerDrawArrows: scale mUnknownC, alpha mUnknown10
   and the fade phase mUnknown14 of FieldMarkerUpdateArrows. */
struct FieldMarkerArrow_t {
    float mPosition[3];
    float mUnknownC;
    float mUnknown10;
    int mUnknown14;
};

extern "C" {
extern FieldMarkerBeamSet_t gFieldMarkerBeamSets[15];
extern FieldMarkerArrow_t *gFieldMarkerArrows;
extern unsigned int gFieldMarkerArrowCount;
}

#endif
