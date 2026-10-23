#ifndef GAME_CLASS_80297C60_H
#define GAME_CLASS_80297C60_H

/* Polymorphic class with vtable 0x80297C60; its members are defined in
   cu_8008E978 and their signatures follow those bodies and their callers. */
class Class_80297C60 {
public:
    virtual void vfn_01();
    virtual void vfn_02();
    virtual void vfn_03(float dt);
    virtual void vfn_04(float dt);
    virtual void vfn_05();
    virtual void vfn_06();
    virtual void vfn_07();
    virtual void vfn_08();
    virtual int vfn_09(char *pText);
    virtual void vfn_10(float dt);
    virtual int vfn_11(float dt);
    virtual int vfn_12(float dt);
    virtual int vfn_13(int busy);
    virtual void vfn_14(float dt);
    virtual void vfn_15();
};

/* .sdata word whose initial value is the object at 0x803EC90C, the .sbss word
   in which 0x800CF100 stores this vtable. */
extern Class_80297C60 *lbl_803EAB84;

#endif
