// Front-end view object: a screen object that, when drawn, passes its index and
// rectangle to a draw function the game registers (the player model in menus).
struct UISViewObj_t {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    float mUnknown10;
};

extern "C" {
static void (*_UISViewObj_pDrawFunc)(int, float, float, float, float) = 0;

void UISViewObjSetDrawFunc(void (*pCallback)(int, float, float, float, float))
{
    _UISViewObj_pDrawFunc = pCallback;
}

void UISViewObjAction(UISViewObj_t *pObject, unsigned int code, int a, int *pValue)
{
    switch (code) {
    case 0:
        pObject->mUnknown0 = *pValue;
        break;
    case 0xFFFFFFFE:
        if (_UISViewObj_pDrawFunc != 0) {
            _UISViewObj_pDrawFunc(pObject->mUnknown0, pObject->mUnknown8, pObject->mUnknown4, pObject->mUnknownC,
                         pObject->mUnknown10);
        }
        break;
    }
}
}
