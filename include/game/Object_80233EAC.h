#ifndef GAME_OBJECT_80233EAC_H
#define GAME_OBJECT_80233EAC_H

struct Object_80233EAC {
    int mUnknown0[5];
};

struct Object_8023417C {
    char mUnknown0[0x18];
    void *mpUnknown18;
};

extern "C" {
void fn_80233FCC(Object_80233EAC *pObject);
int fn_80234144(Object_80233EAC *pObject, void *p);
Object_8023417C *fn_8023417C(Object_80233EAC *pObject, int a);
}

#endif
