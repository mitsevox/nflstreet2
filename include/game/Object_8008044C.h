#ifndef GAME_OBJECT_8008044C_H
#define GAME_OBJECT_8008044C_H

struct Object_8008044C {
    Object_8008044C() : mUnknown0(0), mUnknown4(0), mUnknown8(-1), mUnknown12(-1), mUnknown16(-1) {}
    ~Object_8008044C() {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    char mUnknown20[24];
};

extern "C" {
void fn_8008044C(Object_8008044C *pObject, void *pDesc, int tag);
void fn_8008056C(Object_8008044C *pObject);
int fn_80080948(Object_8008044C *pObject);
int fn_800809C4(Object_8008044C *pObject, int a, int *pResult);
int fn_80080D38(Object_8008044C *pObject, char *pBuffer, int size);
void fn_80080E20(Object_8008044C *pObject);
int fn_800811E0(Object_8008044C *pObject);
int fn_80080ECC(Object_8008044C *pObject);
void fn_80081788(Object_8008044C *pObject, int *pValues);
}

#endif
