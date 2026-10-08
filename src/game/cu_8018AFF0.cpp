extern "C" {
unsigned int fn_8018AFF0(unsigned int *pValue);
}

extern "C" unsigned int fn_8018AFF0(unsigned int *pValue)
{
    unsigned int value = *pValue;

    return (value << 24) | ((value & 0xFF00) << 8) | ((value >> 8) & 0xFF00) | (value >> 24);
}
