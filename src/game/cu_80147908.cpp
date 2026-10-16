static inline float Lerp(float from, float to, float t)
{
    return from * (1.0f - t) + to * t;
}

extern "C" void fn_80147908(unsigned int from, unsigned int to, unsigned int *pColor, float *pValue, float t,
                            float fromValue, float toValue)
{
    unsigned int fromRed = (from >> 16) & 0xFF;
    unsigned int fromGreen = (from >> 8) & 0xFF;
    unsigned int fromBlue = from & 0xFF;
    unsigned int toRed = (to >> 16) & 0xFF;
    unsigned int toGreen = (to >> 8) & 0xFF;
    unsigned int toBlue = to & 0xFF;
    unsigned int red;
    unsigned int green;
    unsigned int blue;

    *pValue = Lerp(fromValue, toValue, t);
    red = (unsigned int)Lerp(fromRed, toRed, t);
    green = (unsigned int)Lerp(fromGreen, toGreen, t);
    blue = (unsigned int)Lerp(fromBlue, toBlue, t);
    *pColor = (red << 16) + (green << 8) + blue;
}
