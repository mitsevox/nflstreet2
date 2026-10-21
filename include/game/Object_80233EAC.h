#ifndef GAME_OBJECT_80233EAC_H
#define GAME_OBJECT_80233EAC_H

typedef struct Skeleton_80041930 Skeleton_80041930;

/* Per-level model record (0x34 bytes) embedded at +0x1C of ModelLod_802DF190;
   fn_8023417C returns its address. */
typedef struct Object_8023417C {
    char mUnknown0[0x18];
    void *mpUnknown18;
    int mUnknown1C;
    char mUnknown20[0x14];
} Object_8023417C;

/* One level of detail of a model description (0x50 bytes). A list of them
   ends with an entry whose id is 0xFFFF. Ids above 50000 name models of the
   roster archive and are stored there as id - 50000. fn_80233EAC stores the
   loaded data at +0x18 and points +0x10 at the record at +0x1C (0 when the
   level has no model). */
typedef struct ModelLod_802DF190 {
    float mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned int mId;
    Object_8023417C *mpUnknown10;
    char mUnknown14[4];
    void *mpUnknown18;
    Object_8023417C mUnknown1C;
} ModelLod_802DF190;

/* Model slot filled by fn_80233EAC: name, a, data or archive, level count
   and the level-of-detail list it was given. */
typedef struct Object_80233EAC {
    const char *mpUnknown0;
    int mUnknown4;
    void *mpUnknown8;
    int mUnknownC;
    ModelLod_802DF190 *mpUnknown10;
} Object_80233EAC;

#ifdef __cplusplus
extern "C" {
#endif
void fn_80233FCC(Object_80233EAC *pObject);
int fn_80234144(Object_80233EAC *pObject, void *p);
Object_8023417C *fn_8023417C(Object_80233EAC *pObject, int a);
void fn_80233EAC(Object_80233EAC *pObject, ModelLod_802DF190 *pLods, const char *pName, int a,
                 void *pArchive, Skeleton_80041930 *pSkeleton, void **ppData, int c);
#ifdef __cplusplus
}
#endif

#endif
