// Looks up a font from the front-end resource list.
extern "C" {
void *UIGLibraryGetGlobal(int index);
int UIGFontGetFont(void *pList, int type, short id, int b);

int UISGetFont(int id, int b)
{
    return UIGFontGetFont(UIGLibraryGetGlobal(1), 2, id, b);
}
}
