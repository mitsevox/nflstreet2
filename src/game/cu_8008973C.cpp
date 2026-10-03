struct Record_802D6C40 {
    int mUnknown0[37];
    unsigned char mUnknown94;
};

static Record_802D6C40 lbl_802D6C40[4] = {0};

extern "C" unsigned char fn_8008973C(int index)
{
    return lbl_802D6C40[index].mUnknown94;
}

extern "C" void fn_80089754(void)
{
    unsigned int i;

    for (i = 0; i < 4; i++) {
        lbl_802D6C40[i].mUnknown94 = 0;
    }
}
