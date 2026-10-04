#include "game/Class_8018FD64.h"

extern "C" {
int fn_8022EF8C(int a, int b);
int fn_8022EFBC(int a, int b);
}

class Class_8002373C {
public:
    Class_8002373C();
    virtual ~Class_8002373C();
    void fn_80023820(int a, int b, int c);

private:
    Class_8018FD64 mUnknown0;
};

Class_8002373C::Class_8002373C()
{
    fn_8022EF8C(0x54415453, 0x4B414D46);
    mUnknown0.fn_8018FDEC(0x4B414D46, 0x44494D46, 0, 0, 0x54415453);
}

Class_8002373C::~Class_8002373C()
{
    mUnknown0.fn_8018FE10();
    fn_8022EFBC(0x54415453, 0x4B414D46);
}

void Class_8002373C::fn_80023820(int a, int b, int c)
{
    mUnknown0.fn_8018FF54(0x44494D46, a, 0, 0);
    mUnknown0.fn_8018FFE4(0x43444D46, b, c);
}
