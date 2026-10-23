#ifndef GAME_CLASS_80297B50_H
#define GAME_CLASS_80297B50_H

/* Polymorphic class with vtable 0x80297B50; its members are defined in
   cu_8008E978 and their signatures follow those bodies and their callers. */
class Class_80297B50 {
public:
    virtual void vfn_01();
    virtual void vfn_02();
    virtual void vfn_03();
    virtual void vfn_04(float dt);
    virtual void vfn_05();
    virtual int vfn_06();
};

/* .sdata word whose initial value is the object at 0x803EC908, the .sbss word
   in which 0x800CF100 stores this vtable. */
extern Class_80297B50 *lbl_803EAB38;

#endif
