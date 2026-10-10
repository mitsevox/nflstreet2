extern "C" {

/* pOut[i] = pB[i] + (pA[i] - pB[i]) * weight, with a 4.12 fixed-point
   weight; pOut may be pA. */
void fn_801A679C(short *pOut, short *pA, short *pB, int weight, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        short delta = pA[i] - pB[i];
        short step = delta * weight >> 12;

        pOut[i] = pB[i] + step;
    }
}

/* As fn_801A679C, with each pA[i] first scaled by pScale[i] (1.15 fixed
   point) and offset by pOffset[i]. */
void fn_801A67DC(short *pOut, short *pA, short *pB, int weight, int count, short *pOffset,
                 short *pScale)
{
    int i;

    for (i = 0; i < count; i++) {
        int offset = pOffset[i];
        short value = (pA[i] * pScale[i] >> 15) + offset;
        short delta = value - pB[i];
        short step = delta * weight >> 12;

        pOut[i] = pB[i] + step;
    }
}

/* pOut[i] = pOffset[i] + pA[i] * pScale[i], with a 1.15 fixed-point scale;
   pOut may be pA. */
void fn_801A6838(short *pOut, short *pA, int count, short *pOffset, short *pScale)
{
    int i;

    for (i = 0; i < count; i++) {
        pOut[i] = pOffset[i] + (pA[i] * pScale[i] >> 15);
    }
}
}
