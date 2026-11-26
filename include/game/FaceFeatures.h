#ifndef GAME_FACEFEATURES_H
#define GAME_FACEFEATURES_H

struct FMCAPPORTValues;
struct Object_8008044C;

/* 40-byte block filled by PlayerDbGetFaceFeatures and read by FaceMorphIsAllowed. */
struct FaceFeatures_t {
    int mUnknown0[10];
};

extern "C" {
void FaceMorphBuildWeights(FaceFeatures_t *pBlock, FMCAPPORTValues *pValues);
int FaceMorphIsAllowed(FaceFeatures_t *pBlock);
void PlayerLookSetFeatures(int index, FaceFeatures_t *pBlock);
void PlayerLookGetFeatures(int index, FaceFeatures_t *pBlock);
void PlayerDbGetFaceFeatures(Object_8008044C *pObject, FaceFeatures_t *pBlock);
void PlayerDbSetFaceFeatures(Object_8008044C *pObject, FaceFeatures_t *pBlock);
}

#endif
