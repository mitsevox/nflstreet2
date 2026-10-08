#ifndef GAME_CLASS_80297CE8_H
#define GAME_CLASS_80297CE8_H

/* Polymorphic class with vtable 0x80297CE8 in the cu_8008E978 candidate range.
   Only the entries that its users override or call carry signatures; the
   rest are placeholders. */
class Class_80297CE8 {
public:
    virtual ~Class_80297CE8() {}
    virtual void vfn_02();
    virtual void vfn_03();
    virtual void vfn_04(float dt);
    virtual void vfn_05(float dt);
    virtual void vfn_06(float dt);
    virtual void vfn_07();
    virtual unsigned char vfn_08() { return 1; }
    virtual void vfn_09();
    virtual void vfn_10();
    virtual void vfn_11();
    virtual int vfn_12();
};

/* .sdata word whose initial value is the object at 0x803EC914, the .sbss word
   in which 0x800CF100 stores this vtable. */
extern Class_80297CE8 *lbl_803EABA4;

#endif
