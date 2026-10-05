#ifndef GAME_CLASS_802A56E8_H
#define GAME_CLASS_802A56E8_H

/* Scrimmage rule set with vtable 0x802A56E8, defined in cu_80176F18; the
   current rule object is held in its state block and called through the
   fn_80178xxx wrappers. Arguments named team are 0 or 1. */
class Class_802A56E8 {
public:
    virtual int vfn_01();
    virtual int vfn_02();
    virtual void vfn_03(int team);
    virtual int vfn_04(int team);
    virtual int vfn_05(int team);
    virtual int vfn_06();
    virtual int vfn_07(int team);
    virtual int vfn_08();
    virtual int vfn_09();
    virtual void vfn_10();
    virtual void vfn_11(int team);
    virtual int vfn_12();
    virtual int vfn_13();
    virtual int vfn_14();
    virtual int vfn_15();
    virtual int vfn_16() { return 0; }
    virtual int vfn_17(int team) { return 0; }
    virtual int vfn_18(int team) { return 0; }
    virtual void vfn_19();
    virtual void vfn_20(int flip);
    virtual int vfn_21();
};

#endif
