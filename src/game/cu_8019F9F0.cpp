/* Object passed to the per-object handlers; +0x68 selects its handler set. */
struct Object_8019FA8C {
    char mUnknown0[0x68];
    int mUnknown68;
};

struct HandlerSet_802F2714 {
    void (*mpUnknown0)(int index);
    void (*mpUnknown4)(int index);
    void (*mpUnknown8)(Object_8019FA8C *pObject);
    void (*mpUnknownC)(Object_8019FA8C *pObject);
    void (*mpUnknown10)(Object_8019FA8C *pObject);
    void (*mpUnknown14)(int index);
    void (*mpUnknown18)(int index);
    void (*mpUnknown1C)(Object_8019FA8C *pObject);
};

extern "C" {
void fn_8019F508(int index);
void fn_8019F5D8(int index);
void fn_8019F678(Object_8019FA8C *pObject);
void fn_8019F69C(Object_8019FA8C *pObject);
void fn_8019F6A8(Object_8019FA8C *pObject);
void fn_8019F6CC(int index);
void fn_8019F82C(int index);
void fn_8019F874(Object_8019FA8C *pObject);
}

static HandlerSet_802F2714 lbl_802F2714[] = {
    { fn_8019F508, fn_8019F5D8, fn_8019F678, fn_8019F69C, fn_8019F6A8, fn_8019F6CC, fn_8019F82C, fn_8019F874 },
};

extern "C" {
void fn_8019F9F0(void)
{
    unsigned int i;

    for (i = 0; i < sizeof(lbl_802F2714) / sizeof(lbl_802F2714[0]); i++) {
        lbl_802F2714[i].mpUnknown0(i);
    }
}

void fn_8019FA3C(void)
{
    unsigned int i;

    for (i = 0; i < sizeof(lbl_802F2714) / sizeof(lbl_802F2714[0]); i++) {
        lbl_802F2714[i].mpUnknown4(i);
    }
}

void fn_8019FA8C(Object_8019FA8C *pObject)
{
    lbl_802F2714[pObject->mUnknown68].mpUnknown8(pObject);
}

void fn_8019FAC8(Object_8019FA8C *pObject)
{
    lbl_802F2714[pObject->mUnknown68].mpUnknownC(pObject);
}

void fn_8019FB04(Object_8019FA8C *pObject)
{
    lbl_802F2714[pObject->mUnknown68].mpUnknown10(pObject);
}

void fn_8019FB40(Object_8019FA8C *pObject)
{
    lbl_802F2714[pObject->mUnknown68].mpUnknown1C(pObject);
}

void fn_8019FB7C(int index)
{
    lbl_802F2714[index].mpUnknown14(index);
}

void fn_8019FBB4(int index)
{
    lbl_802F2714[index].mpUnknown18(index);
}
}
