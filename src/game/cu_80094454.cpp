extern "C" int fn_80091C84(int index, float *pOut);

extern "C" float fn_80094454(int index)
{
    float value = 0.0f;

    fn_80091C84(index, &value);
    return value;
}
