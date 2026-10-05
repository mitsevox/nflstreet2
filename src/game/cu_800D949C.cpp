struct Object_800DAC78
{
    char mUnknown0[4];
    float mUnknown4;
};

extern "C" void fn_800DAC78(Object_800DAC78 *p, float a, float b)
{
    p->mUnknown4 = (a - b) / a;
}
