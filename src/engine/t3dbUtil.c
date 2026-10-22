typedef struct T3dbField_8020CCBC {
    int mUnknown0;
    unsigned int mHigh;
    unsigned int mLow;
    int mUnknownC;
} T3dbField_8020CCBC;

void fn_8020CCBC(T3dbField_8020CCBC *pFields, unsigned long long *pOut)
{
    unsigned char i = 0;

    do {
        pOut[i] = ((unsigned long long)pFields[i].mHigh << 32) | pFields[i].mLow;
    } while (pFields[i++].mLow != -1);
}
