#ifndef GAME_CLASS_80148A58_H
#define GAME_CLASS_80148A58_H

/* Object returned by fn_80148A58; its vtable pointer is at offset 0x18,
   after 24 bytes of data. Only the vtable slots called through are given
   signatures; the others are placeholders. */
class Class_80148A58 {
public:
    virtual void vfn_01();
    virtual void vfn_02();
    virtual void vfn_03();
    virtual unsigned int vfn_04(int team);
    virtual int vfn_05(int team);
    virtual unsigned int vfn_06();
    virtual void vfn_07(int a, int b);
    virtual int vfn_08(int a);
    virtual void vfn_09();
    virtual void vfn_10(int value, int *list, int *ids);
    virtual void vfn_11(int value, int *list, int *ids, int a, int b);
    virtual void vfn_12();
    virtual int vfn_13();
    virtual void vfn_14();
    virtual void vfn_15();
    virtual void vfn_16();
    virtual void vfn_17();
    virtual void vfn_18();
    virtual void vfn_19();
    virtual void vfn_20();
    virtual void vfn_21();
    virtual int vfn_22(int a);

    int mUnknown0;
    int mUnknown4;
    char mUnknown8[16];
};

extern "C" Class_80148A58 *fn_80148A58(void);

#endif
