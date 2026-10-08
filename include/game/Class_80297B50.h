#ifndef GAME_CLASS_80297B50_H
#define GAME_CLASS_80297B50_H

/* Polymorphic class with vtable 0x80297B50 in the cu_8008E978 candidate range.
   Only the entries that its users override or call carry signatures; the
   rest are placeholders. */
class Class_80297B50 {
public:
    virtual void vfn_01();
    virtual void vfn_02();
    virtual void vfn_03();
    virtual void vfn_04(float dt);
    virtual void vfn_05();
    virtual void vfn_06();
};

/* .sdata word whose initial value is the object at 0x803EC908, the .sbss word
   in which 0x800CF100 stores this vtable. */
extern Class_80297B50 *lbl_803EAB38;

#endif
