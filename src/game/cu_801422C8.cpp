struct Camera_801422C8 {
    char mPad00[0xDC];
    void (*mUnknownDC)(Camera_801422C8 *pCamera, int msg);
};

static unsigned char lbl_803EB1F8 = 0;

extern "C" {
void fn_80142A64(Camera_801422C8 *pCamera, int msg);

void fn_801422C8(Camera_801422C8 *pCamera)
{
    pCamera->mUnknownDC = fn_80142A64;
    lbl_803EB1F8 = 1;
}

void fn_801422E0(Camera_801422C8 *pCamera)
{
    lbl_803EB1F8 = 0;
}
}
