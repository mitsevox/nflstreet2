class Class_802A1DC8 {
public:
    virtual void vfn_01();
    virtual void vfn_02();
    virtual void vfn_03();
    virtual void vfn_04(float value);
    virtual void vfn_05();
    virtual void vfn_06();
    virtual void vfn_07();
    virtual void vfn_08();
    virtual void vfn_09();
    virtual void vfn_10();
    virtual void vfn_11(float value);
};

extern "C" {
int fn_80054568(void);
void fn_800AD910(int a, float b);

void fn_80150710(Class_802A1DC8 *p, float value)
{
    if (fn_80054568()) {
        p->vfn_11(value);
    }
}

void fn_80150820(Class_802A1DC8 *p)
{
}

void fn_80150824(Class_802A1DC8 *p, float value)
{
    fn_800AD910(2, value);
}
}
