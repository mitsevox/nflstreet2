#ifndef GAME_UISMODEL_H
#define GAME_UISMODEL_H

#include "game/Object_80039F5C.h"

struct UISModelDesc_t {
    short mUnknown00;
    short mUnknown02;
    Vector_80039F5C mUnknown04;
    Vector_80039F5C mUnknown10;
    Vector_80039F5C mUnknown1C;
    Vector_80039F5C mUnknown28;
};

struct UISModelRender_t {
    unsigned char mUnknown00[88];
    void *mpUnknown58;
};

struct UISModel_t {
    unsigned char mUnknown00[4];
    float mUnknown04;
    float mUnknown08;
    float mUnknown0C;
    unsigned char mUnknown10[4];
    int mUnknown14;
    unsigned char mUnknown18[48];
    UISModelRender_t mUnknown48;
    unsigned char mUnknownA4[244];
    unsigned int mUnknown198;
    Vector_80039F5C mUnknown19C;
    int mUnknown1A8;
    int mUnknown1AC;
    int mUnknown1B0;
    Vector_80039F5C mUnknown1B4;
    Vector_80039F5C mUnknown1C0;
    short mUnknown1CC;
    short mUnknown1CE;
    float mUnknown1D0;
    unsigned char mUnknown1D4;
    unsigned char mUnknown1D5[3];
    short mUnknown1D8;
    short mUnknown1DA;
    short mUnknown1DC;
    short mUnknown1DE;
    unsigned char mUnknown1E0[4];
    int mUnknown1E4;
};

extern "C" {
void UISModelBind(UISModel_t *pObject, UISModelDesc_t *pDesc);
void UISModelInit(UISModel_t *pObject, UISModelDesc_t *pDesc);
void UISModelFree(UISModel_t *pObject);
int UISModelDraw(UISModel_t *pObject, int value);
void UISModelCopyTexture(UISModel_t *pObject, void *pData, int index, int component);
void UISModelApplyTextures(UISModel_t *pObject, void *pData);
int UISModelUpdateTextures(UISModel_t *pObject);
int UISModelRegister(void *pHandle, int count);
void UISModelUnregister(void);
void UISModelDrawReady(UISModel_t *pObject, int value);
void UISModelSetDrawMode(UISModel_t *pObject, unsigned char value);
}

#endif
