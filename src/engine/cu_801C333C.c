extern const unsigned char lbl_802AEF10[];

#define CTYPE(c) ((lbl_802AEF10 + 1)[(unsigned char)(c)])

int fn_801C333C(const char *pString)
{
    int value = 0;
    int negative = 0;

    while (CTYPE(*pString) & 8) {
        pString++;
    }
    if (*pString == '+') {
        pString++;
    } else if (*pString == '-') {
        negative = 1;
        pString++;
    }
    while (CTYPE(*pString) & 4) {
        value *= 10;
        value += *pString++ - '0';
    }
    return negative ? -value : value;
}
