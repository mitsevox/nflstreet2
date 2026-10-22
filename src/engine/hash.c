extern unsigned int strlen(const char *s);
extern int fn_801C1F54(int c);

int fn_801F34C0(char *pString, int multiplier)
{
    int hash = 0;
    int scale;
    int i;

    scale = 1;
    for (i = strlen(pString) - 1; i >= 0; i--) {
        hash += fn_801C1F54(pString[i]) * scale;
        scale *= multiplier;
    }
    return hash;
}
