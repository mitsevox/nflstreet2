extern "C" void fn_801A105C(float x, float y, void *p, unsigned char value);

struct Record_80365574 {
    int mUnknown0[17];
    float mUnknown44;
    float mUnknown48;
    void *mUnknown4C;
    unsigned char mUnknown50;
};

static Record_80365574 lbl_80365574[16];
static int lbl_803ECBFC;

extern "C" void fn_801A133C(float x, float y, void *p, unsigned char value)
{
    Record_80365574 *pRecord = &lbl_80365574[lbl_803ECBFC++];

    pRecord->mUnknown44 = x;
    pRecord->mUnknown48 = y;
    pRecord->mUnknown4C = p;
    pRecord->mUnknown50 = value;
    fn_801A105C(x, y, p, value);
}

extern "C" void fn_801A139C(void)
{
    lbl_803ECBFC = 0;
}
