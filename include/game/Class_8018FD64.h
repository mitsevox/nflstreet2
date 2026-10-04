#ifndef GAME_CLASS_8018FD64_H
#define GAME_CLASS_8018FD64_H

#include "game/Object_8007A334.h"

/* Data-less polymorphic base of Class_8018FD64. ProDG 3.9.3 puts the vtable
   pointer of a class without a polymorphic base after its data members, so the
   pointer at +0 of Class_8018FD64 needs one. It has no destructor of its own
   (the destructor 0x8018FD94 stores no second vtable). Which of the slots it
   introduces is not established; it is written with the entries 1-17 of the
   vtable 0x802AB4F8, the slots before the destructor. */
class Class_8018FD64Base {
public:
    virtual int fn_8018FE34() = 0;
    virtual int fn_8018FE58() = 0;
    virtual int fn_8018FE7C() = 0;
    virtual int fn_8018FEA0() = 0;
    virtual int fn_8018FEC4() = 0;
    virtual int fn_8018FEE8() = 0;
    virtual int fn_8018FF0C(int a) = 0;
    virtual int fn_8018FF30(int a, int b, int c, int *pResult) = 0;
    virtual int fn_8018FF54(int a, int b, int c, int *pResult) = 0;
    virtual int fn_8018FF78(int column) = 0;
    virtual int fn_8018FF9C(int column) = 0;
    virtual float fn_8018FFC0(int column) = 0;
    virtual void fn_8018FFE4(int a, int b, int c) = 0;
    virtual int fn_80190008(int column, int value) = 0;
    virtual int fn_8019002C(int column, int value) = 0;
    virtual int fn_80190050(int column, float value) = 0;
    virtual int fn_80190074(int column, int value) = 0;
};

/* Cursor object with vtable 0x802AB4F8: the vtable pointer at +0 and an
   Object_8007A334 at +4 (48 bytes). Each virtual member passes &mObject and
   its arguments to one Object_8007A334 function (vtable entry 1 0x8018FE34 to
   entry 17 0x80190074, then the destructor 0x8018FD94 and 0x8018FE10).
   The constructor 0x8018FD64 is declared out of line here; see
   game/Class_8018FD64Inline.h for the files that expand it inline. */
class Class_8018FD64 : public Class_8018FD64Base {
public:
    Class_8018FD64();
    void fn_8018FDEC(int a, int b, void *c, void *d, int e);

    virtual int fn_8018FE34();
    virtual int fn_8018FE58();
    virtual int fn_8018FE7C();
    virtual int fn_8018FEA0();
    virtual int fn_8018FEC4();
    virtual int fn_8018FEE8();
    virtual int fn_8018FF0C(int a);
    virtual int fn_8018FF30(int a, int b, int c, int *pResult);
    virtual int fn_8018FF54(int a, int b, int c, int *pResult);
    virtual int fn_8018FF78(int column);
    virtual int fn_8018FF9C(int column);
    virtual float fn_8018FFC0(int column);
    virtual void fn_8018FFE4(int a, int b, int c);
    virtual int fn_80190008(int column, int value);
    virtual int fn_8019002C(int column, int value);
    virtual int fn_80190050(int column, float value);
    virtual int fn_80190074(int column, int value);
    virtual ~Class_8018FD64();
    virtual void fn_8018FE10();

private:
    Object_8007A334 mObject;
};

#endif
