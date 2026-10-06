struct Object_8018A910 {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    float mUnknown10;
};

extern "C" {
static void (*lbl_803EB6A8)(int, float, float, float, float) = 0;

void fn_8018A908(void (*pCallback)(int, float, float, float, float))
{
    lbl_803EB6A8 = pCallback;
}

void fn_8018A910(Object_8018A910 *pObject, unsigned int code, int a, int *pValue)
{
    switch (code) {
    case 0:
        pObject->mUnknown0 = *pValue;
        break;
    case 0xFFFFFFFE:
        if (lbl_803EB6A8 != 0) {
            lbl_803EB6A8(pObject->mUnknown0, pObject->mUnknown8, pObject->mUnknown4, pObject->mUnknownC,
                         pObject->mUnknown10);
        }
        break;
    }
}
}
