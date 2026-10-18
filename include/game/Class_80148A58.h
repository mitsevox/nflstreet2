#ifndef GAME_CLASS_80148A58_H
#define GAME_CLASS_80148A58_H

/* Object returned by fn_80148A58; its vtable pointer is at offset 0x18,
   after 24 bytes of data. Only the vtable slots called through are given
   signatures; the others are placeholders. */
struct Object_80039F5C;
struct Record_8003E214;

struct Record_80148C4C {
    int mUnknown0;
    int mUnknown4[10];
    unsigned char mUnknown2C;
    char mUnknown2D[3];
};

struct State_80148A58 {
    unsigned int mCount;
    int mCachedValue;
    Record_80148C4C *mpRecords;
    unsigned char mUnknownC;
    char mUnknownD[3];
};

class Class_80148A58 {
public:
    virtual void vfn_01();
    virtual void vfn_02();
    virtual int vfn_03();
    virtual unsigned int vfn_04(int team);
    virtual int vfn_05(int team);
    virtual unsigned int vfn_06();
    virtual void vfn_07(int a, int b);
    virtual int vfn_08(int a);
    virtual float *vfn_09(int a);
    virtual void vfn_10(int value, int *list, int *ids);
    virtual void vfn_11(int value, int *list, int *ids, int a, int b);
    virtual void vfn_12();
    virtual int vfn_13();
    virtual void vfn_14();
    virtual void vfn_15();
    virtual void vfn_16(const int *pKinds);
    virtual void vfn_17(const int *pKinds);
    virtual void vfn_18(int a, unsigned char index, char *pText, unsigned char length);
    virtual void vfn_19(int team, int column, char *pText, int length);
    virtual void vfn_20(int team, int index, int kind, char *pFirst, int firstLength,
                        char *pSecond, int secondLength);
    virtual void vfn_21();
    virtual int vfn_22(int a);

    virtual int vfn_23(Record_8003E214 *pRecords, int count);
    virtual int vfn_24(int team, unsigned int tag);
    virtual unsigned char vfn_25(int team, int index);
    virtual int vfn_26(int team, int index, Object_80039F5C *pPlayer, int kind);
    virtual int vfn_27(int team, int index, int value);
    virtual unsigned char vfn_28(int index);
    virtual const char *vfn_29(int kind);
    virtual int vfn_30(int kind, int team, int index, Object_80039F5C *pPlayer);
    virtual int vfn_31(int kind, int team, int index, Object_80039F5C *pPlayer,
                       int threshold, int mode);
    virtual int vfn_32(int team, int kind);
    virtual int vfn_33(int kind, int team);
    virtual int vfn_34(int kind, int team, int threshold, int mode);

    Class_80148A58();

    int mUnknown0;
    int mUnknown4;
    union {
        char mUnknown8[16];
        State_80148A58 mState;
    };
};

extern "C" Class_80148A58 *fn_80148A58(void);

#endif
