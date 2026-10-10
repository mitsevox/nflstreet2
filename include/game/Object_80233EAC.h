#ifndef GAME_OBJECT_80233EAC_H
#define GAME_OBJECT_80233EAC_H

struct Skeleton_80041930;

/* One level of detail of a model description (0x50 bytes). A list of them
   ends with an entry whose id is 0xFFFF. Ids above 50000 name models of the
   roster archive and are stored there as id - 50000. */
struct ModelLod_802DF190 {
    float mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned int mId;
    int mUnknown10;
    char mUnknown14[60];
};

/* Model slot filled by fn_80233EAC; it keeps the level-of-detail list it was
   given at +0x10. */
struct Object_80233EAC {
    int mUnknown0[4];
    ModelLod_802DF190 *mpUnknown10;
};

struct Object_8023417C {
    char mUnknown0[0x18];
    void *mpUnknown18;
};

extern "C" {
void fn_80233FCC(Object_80233EAC *pObject);
int fn_80234144(Object_80233EAC *pObject, void *p);
Object_8023417C *fn_8023417C(Object_80233EAC *pObject, int a);
void fn_80233EAC(Object_80233EAC *pObject, ModelLod_802DF190 *pLods, const char *pName, int a,
                 void *pArchive, Skeleton_80041930 *pSkeleton, void **ppData, int c);
}

#endif
