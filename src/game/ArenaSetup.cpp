extern "C" {
void fn_800246C0(void);
void fn_80024820(void);
}

static unsigned char sInitialized = 0;

extern "C" void fn_80025E00(void)
{
    sInitialized = 1;
    fn_800246C0();
}

extern "C" void fn_80025E28(void)
{
    fn_80024820();
    sInitialized = 0;
}
