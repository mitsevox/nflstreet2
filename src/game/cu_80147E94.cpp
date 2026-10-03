typedef int (*Callback_80238234)(void *p, int value);
typedef int (*Callback1C_80238234)(void *p, void *q);

extern "C" {
void *fn_80238174(int a, void **ppData, int size, int b, unsigned int id);
void fn_802381E0(void *pHandle);
void fn_80238234(void *pHandle, Callback_80238234 pCallback10, Callback_80238234 pCallback14, Callback_80238234 pCallback18, Callback1C_80238234 pCallback1C);
}

static void *lbl_803EB298 = 0;

extern "C" {
int fn_80147E94(void *p, int value)
{
    return 0;
}

int fn_80147E9C(void *p, int value)
{
    return 0;
}

int fn_80147EA4(void *p, void *q)
{
    return 0;
}

void fn_80147EAC(void)
{
    void *pHandle = fn_80238174(0, &lbl_803EB298, 4, 0, 0x67696E74);

    fn_80238234(pHandle, fn_80147E94, fn_80147E9C, 0, fn_80147EA4);
    fn_802381E0(pHandle);
}

void *fn_80147F18(int value)
{
    if (value != 0) {
        return 0;
    }
    return lbl_803EB298;
}
}
