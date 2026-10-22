extern const unsigned char lbl_802AEF10[];

#define CTYPE(c) ((lbl_802AEF10 + 1)[(unsigned char)(c)])

int fn_801C1F54(int c)
{
    if (CTYPE(c) & 2) {
        c -= 'a' - 'A';
    }
    return c;
}

int fn_801C1F74(int c)
{
    if (CTYPE(c) & 1) {
        c += 'a' - 'A';
    }
    return c;
}
