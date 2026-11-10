// Front-end held object: the switch that lets a button press pick a screen
// object, and the object last picked.
extern "C" {
void UISHeldObjSet(int value);
unsigned char UISHeldObjEnable(unsigned char value);
unsigned char UISHeldObjIsEnabled(void);
}

static unsigned char _UISHeldObj_bEnabled = 0;
static int _UISHeldObj_pObject = 0;

extern "C" void UISHeldObjSet(int value)
{
    _UISHeldObj_pObject = value;
}

extern "C" unsigned char UISHeldObjEnable(unsigned char value)
{
    unsigned char previous = _UISHeldObj_bEnabled;

    _UISHeldObj_bEnabled = value;
    return previous;
}

extern "C" unsigned char UISHeldObjIsEnabled(void)
{
    return _UISHeldObj_bEnabled;
}
