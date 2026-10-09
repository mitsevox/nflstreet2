extern "C" {
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
unsigned int fn_801C3180(const char *pText);
}

// Formats value in decimal with a comma between each group of three digits,
// writing at most size - 1 characters and a terminator to pOut.
extern "C" void fn_8017F49C(int value, char *pOut, int size)
{
    char digits[20];
    int length;
    int lead;
    int i;
    int count;

    fn_801C2D88(digits, sizeof(digits), "%d", value);
    length = fn_801C3180(digits);
    lead = length % 3;
    count = 0;
    for (i = 0; i < length; i++) {
        if (i != 0 && i % 3 == lead) {
            pOut[count++] = ',';
        }
        pOut[count++] = digits[i];
        if (count == size - 1) {
            break;
        }
    }
    pOut[count] = 0;
}
