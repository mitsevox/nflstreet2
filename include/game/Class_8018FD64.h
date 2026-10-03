#ifndef GAME_CLASS_8018FD64_H
#define GAME_CLASS_8018FD64_H

/* Class defined outside this unit. The target class is polymorphic: its
   vtable pointer is at +0 and an Object_8007A334 follows at +4, and the
   destructor, fn_8018FE10, fn_8018FF54 and fn_8018FFE4 are virtual. Only the
   48-byte size and the called members are declared; the layout is opaque. */
class Class_8018FD64 {
public:
    Class_8018FD64();
    ~Class_8018FD64();
    void fn_8018FDEC(int a, int b, void *c, int d, int e);
    void fn_8018FE10();
    int fn_8018FF54(int a, int b, int c, int *pResult);
    void fn_8018FFE4(int a, int b, int c);

private:
    char mUnknown0[48];
};

#endif
