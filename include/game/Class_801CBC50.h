#ifndef GAME_CLASS_801CBC50_H
#define GAME_CLASS_801CBC50_H

class Class_801CBC50 {
public:
    Class_801CBC50();
    virtual ~Class_801CBC50();
    virtual int fn_80032340() = 0;
    virtual void *fn_80032348(int index) = 0;
    virtual void fn_800323AC() = 0;

    int fn_801CBD80(int a, int b);
    int fn_801CBE24(int a);
    int fn_801CBE9C(int a);
    int fn_801CBEC8(int a);
    int fn_801CBEF4(int a, int b);

private:
    char mUnknown0[220];
};

class Class_803067B0 : public Class_801CBC50 {
public:
    virtual ~Class_803067B0() {}
    virtual int fn_80032340();
    virtual void *fn_80032348(int index);
    virtual void fn_800323AC();
};
extern Class_803067B0 lbl_803067B0;

#endif
