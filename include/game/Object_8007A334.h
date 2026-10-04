#ifndef GAME_OBJECT_8007A334_H
#define GAME_OBJECT_8007A334_H

struct Object_8007A334;

extern "C" {
int fn_801FA228(int handle, int a, int b, void *pRecord);
}

/* Argument of fn_8007A334 and fn_8007A3C4. The constructor sets the same
   values fn_8007A3C4 stores at its end. */
struct Object_8007A334 {
    Object_8007A334() : mUnknown0(0), mUnknown4(0), mUnknown8(-1), mUnknown12(-1), mUnknown16(-1) {}
    ~Object_8007A334() {}
    void Read(void *pRecord) { fn_801FA228(mUnknown0, 0, 0, pRecord); }

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    char mUnknown20[24];
};

extern "C" {
void fn_8007A334(Object_8007A334 *pObject, int a, int b, void *c, void *d, int e);
void fn_8007A3C4(Object_8007A334 *pObject);
int fn_8007A410(Object_8007A334 *pObject);
int fn_8007A444(Object_8007A334 *pObject);
int fn_8007A510(Object_8007A334 *pObject);
int fn_8007A600(Object_8007A334 *pObject, int a);
int fn_8007A7F4(Object_8007A334 *pObject, int a, int b, int c, int *pResult);
int fn_8007A894(Object_8007A334 *pObject, int a, int b, int c, int *pResult);
int fn_8007A98C(void *pObject, int a);
void fn_8007AA3C(Object_8007A334 *pObject, int a, int b, int c);
int fn_8007ABA4(void *pObject, int a, int b);
void fn_8007EEFC(Object_8007A334 *pObject);
void fn_8007F064(Object_8007A334 *pObject);
void fn_8007F094(Object_8007A334 *pObject, char *pBuffer, int size);
int fn_8007F0C8(Object_8007A334 *pObject);
void fn_8007F0F4(Object_8007A334 *pObject, int a, int *pResult);
}

#endif
