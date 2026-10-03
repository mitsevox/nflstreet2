/* Argument of fn_8007A334 and fn_8007A3C4. The constructor sets the same
   values fn_8007A3C4 stores at its end. */
struct Object_8007A334 {
    Object_8007A334() : mUnknown0(0), mUnknown4(0), mUnknown8(-1), mUnknown12(-1), mUnknown16(-1) {}
    ~Object_8007A334() {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    char mUnknown20[24];
};

extern "C" {
void fn_8007A334(Object_8007A334 *pObject, int a, int b, int c, int d, int e);
void fn_8007A3C4(Object_8007A334 *pObject);
}

static Object_8007A334 lbl_8037DEA4;

extern "C" {
static void fn_8002306C()
{
    fn_8007A334(&lbl_8037DEA4, 0x45434146, -1, 0, 0, 0x54415453);
}

static void fn_800230B0()
{
    fn_8007A3C4(&lbl_8037DEA4);
}

void fn_800230D8()
{
    fn_8002306C();
}

void fn_800230F8()
{
    fn_800230B0();
}
}
