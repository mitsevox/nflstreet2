// Turns four characters of text into a database tag (byte order reversed).
extern "C" {
unsigned int DbTextToTag(unsigned int *pValue);
}

extern "C" unsigned int DbTextToTag(unsigned int *pValue)
{
    unsigned int value = *pValue;

    return (value << 24) | ((value & 0xFF00) << 8) | ((value >> 8) & 0xFF00) | (value >> 24);
}
