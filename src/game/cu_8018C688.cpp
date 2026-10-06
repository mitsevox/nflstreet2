#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/fn_801FCE10.h"

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int handle);
void fn_8018DF20(Object_8007A334 *pCursor, int index);
void fn_8018DF78(Object_8007A334 *pCursor);

float lbl_802EAEF4[10] = {
    0.16f, 0.12f, 0.10f, 0.14f, 0.20f, 0.0f, 0.06f, 0.08f, 0.0f, 0.0f
};
float lbl_802EAF1C[10] = {
    0.12f, 0.0f, 0.0f, 0.0f, 0.11f, 0.26f, 0.0f, 0.0f, 0.23f, 0.23f
};
float lbl_802EAF44[10] = {
    0.27f, 0.10f, 0.06f, 0.12f, 0.28f, 0.18f, 0.05f, 0.06f, 0.14f, 0.14f
};

void fn_8018C688(int *pValues, float *pFirst, float *pSecond, float *pThird)
{
    float firstWeight = 0.0f;
    float secondWeight = 0.0f;
    float thirdWeight = 0.0f;
    *pFirst = 0.0f;
    *pSecond = 0.0f;
    *pThird = 0.0f;
    for (int i = 0; i < 10; i++) {
        *pFirst += pValues[i] * lbl_802EAEF4[i];
        firstWeight += lbl_802EAEF4[i];
        *pSecond += pValues[i] * lbl_802EAF1C[i];
        secondWeight += lbl_802EAF1C[i];
        *pThird += pValues[i] * lbl_802EAF44[i];
        thirdWeight += lbl_802EAF44[i];
    }
    *pFirst /= firstWeight;
    *pSecond /= secondWeight;
    *pThird /= thirdWeight;
}

void fn_8018C7B8(int index, int *pFirst, int *pSecond, int *pThird)
{
    Object_8007A334 cursor;
    fn_8018DF20(&cursor, index);
    int count = fn_8007A410(&cursor);
    float firstTotal = 0.0f;
    float secondTotal = 0.0f;
    float thirdTotal = 0.0f;
    if (fn_8007A444(&cursor)) {
        do {
            int values[10];
            float first;
            float second;
            float third;
            fn_80081788((Object_8008044C *)&cursor, values);
            fn_8018C688(values, &first, &second, &third);
            firstTotal += first;
            secondTotal += second;
            thirdTotal += third;
        } while (fn_8007A510(&cursor));
    }
    double first = firstTotal * 1.6 / count;
    if (first >= 1.0) {
        *pFirst = (int)(first <= 99.0 ? first : 99.0);
    } else {
        *pFirst = 1;
    }
    double second = secondTotal * 1.6 / count;
    if (second >= 1.0) {
        *pSecond = (int)(second <= 99.0 ? second : 99.0);
    } else {
        *pSecond = 1;
    }
    double third = thirdTotal * 1.6 / count;
    if (third >= 1.0) {
        *pThird = (int)(third <= 99.0 ? third : 99.0);
    } else {
        *pThird = 1;
    }
    fn_8018DF78(&cursor);
}

void fn_8018CA14(int index)
{
    int handle = fn_8022F3D4(fn_8022F358(index));
    int first;
    int second;
    int third;
    QueryResult result;
    fn_8018C7B8(index, &first, &second, &third);
    fn_801FCE10(&result,
        "use \x8c update 'MTRC' set 'FORT' = \x82 and 'EDRT' = \x82 and 'VORT' = \x82\n",
        handle, first, second, third);
}
}
