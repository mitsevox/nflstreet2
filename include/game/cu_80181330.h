#ifndef GAME_CU_80181330_H
#define GAME_CU_80181330_H

/* Classes whose implementations lie in 0x80181330-0x8018422C. Virtual
   functions are named vfn_NN after their vtable entry. */

/* 44-byte list entry. */
struct Entry_80182CC8 {
    int mId;
    int mUnknown4;
    char mName[22];
    unsigned char mUnknown30;
    int mUnknown32;
    int mUnknown36;
    unsigned char mUnknown40;
};

/* Argument of the last two entries of the Class_802A6BB0 vtable. */
struct Params_80005284 {
    int mUnknown0;
    int mLength;
    char *mpText;
};

/* Vtable 0x802A6BB0: ten entries, each an empty function except the seventh,
   which returns 0. */
class Class_802A6BB0 {
public:
    virtual void vfn_01(int a, int *pResult);
    virtual void vfn_02(int a, int b, int c);
    virtual void vfn_03();
    virtual void vfn_04();
    virtual void vfn_05();
    virtual void vfn_06();
    virtual int vfn_07();
    virtual void vfn_08();
    virtual void vfn_09(int a, int *pResult, Params_80005284 **ppParams);
    virtual void vfn_10(int a, Params_80005284 **ppParams);
};

/* Common base of Class_802A6B60 and Class_800055D8, named after its sixth
   entry 0x80184190; no vtable of its own is present in the target. */
class Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pValue) = 0;
    virtual int vfn_02(int a, int b, void **ppResult) = 0;
    virtual void vfn_03(int index) = 0;
    virtual void vfn_04(int index, int *pId) = 0;
    virtual void vfn_05(int index, Entry_80182CC8 *pEntry) = 0;
    virtual Class_802A6BB0 *vfn_06();
};

/* Vtable 0x802A6B60: a list of Entry_80182CC8 records supplied by the last
   two entries. */
class Class_802A6B60 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pValue);
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual void vfn_03(int id);
    virtual void vfn_04(int index, int *pId);
    virtual void vfn_05(int index, Entry_80182CC8 *pEntry);
    virtual int vfn_07() = 0;
    virtual Entry_80182CC8 *vfn_08() = 0;
};

#endif
