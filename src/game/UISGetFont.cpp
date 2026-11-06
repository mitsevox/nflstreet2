// Looks up a font from the front-end resource list.
extern "C" {
void *fn_8021EA44(int index);
int fn_8022601C(void *pList, int type, short id, int b);

int UISGetFont(int id, int b)
{
    return fn_8022601C(fn_8021EA44(1), 2, id, b);
}
}
