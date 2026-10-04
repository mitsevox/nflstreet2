#ifndef GAME_CU_80181330_H
#define GAME_CU_80181330_H

/* 44-byte list entry. */
struct Entry_80182CC8 {
    int mId;
    int mUnknown4;
    char mName[22];
    unsigned char mUnknown30;
    int mUnknown32;
    int mUnknown36;
    unsigned char mUnknown40;
    unsigned char mUnknown41;
};

/* Text argument record reached through Arg_8018399C::pParams. */
struct Params_80005284 {
    int mUnknown0;
    int mLength;
    char *mpText;
};

/* One argument or result slot of the message handler fn_8018399C. Text
   arguments are passed on to the Class_802A6BB0 entries by value. */
union Arg_8018399C {
    int i;
    float f;
    int *pi;
    float *pf;
    Params_80005284 *pParams;
};

/* Vtable 0x802A6BB0: ten entries, each an empty function except the seventh,
   which returns 0. */
class Class_802A6BB0 {
public:
    virtual void vfn_01(int a, int *pResult);
    virtual void vfn_02(int a, int b, int c);
    virtual void vfn_03(int a, int *pB, int *pC);
    virtual void vfn_04(int a, int b, int c);
    virtual void vfn_05(int a, int b, Arg_8018399C text);
    virtual void vfn_06(int a, int b, int c, int *pD, int *pE, Arg_8018399C textF,
                        Arg_8018399C textG, Arg_8018399C textH);
    virtual int vfn_07(int a, int b, Arg_8018399C text);
    virtual void vfn_08(int a, int b, int c);
    virtual void vfn_09(int a, int *pResult, Arg_8018399C text);
    virtual void vfn_10(int a, Arg_8018399C text);
};

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
