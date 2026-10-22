typedef struct Quat_801EB488 {
    float x;
    float y;
    float z;
    float w;
} Quat_801EB488;

double fabs(double x);
float fn_80260B1C(float x);
float fn_801CFF54(float x);
float fn_801EB4EC(Quat_801EB488 *q);
void fn_801EB56C(Quat_801EB488 *pOut, Quat_801EB488 *q, float scale);

void fn_801EB488(Quat_801EB488 *q)
{
    q->x = q->y = q->z = 0.0f;
    q->w = 1.0f;
}

float fn_801EB4AC(Quat_801EB488 *q)
{
    return fn_80260B1C(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
}

float fn_801EB4EC(Quat_801EB488 *q)
{
    return fn_801CFF54(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
}

void fn_801EB52C(Quat_801EB488 *pOut, Quat_801EB488 *q)
{
    fn_801EB56C(pOut, q, fn_801EB4EC(q));
}

void fn_801EB56C(Quat_801EB488 *pOut, Quat_801EB488 *q, float scale)
{
    pOut->x = q->x * scale;
    pOut->y = q->y * scale;
    pOut->z = q->z * scale;
    pOut->w = q->w * scale;
}

int fn_801EB5A0(Quat_801EB488 *pA, Quat_801EB488 *pB, float epsilon)
{
    float dx = fabs(pA->x - pB->x);
    float dy = fabs(pA->y - pB->y);
    float dz = fabs(pA->z - pB->z);
    float dw = fabs(pA->w - pB->w);
    int equal = 0;

    if (!(dx >= epsilon) && !(dy >= epsilon) && !(dz >= epsilon)) {
        equal = dw < epsilon;
    }
    return equal;
}

void fn_801EB61C(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB)
{
    pOut->x = pA->x - pB->x;
    pOut->y = pA->y - pB->y;
    pOut->z = pA->z - pB->z;
    pOut->w = pA->w - pB->w;
}

void fn_801EB660(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB)
{
    Quat_801EB488 q;

    q.x = pA->w * pB->x + pA->x * pB->w + pA->y * pB->z - pA->z * pB->y;
    q.y = pA->w * pB->y + pA->y * pB->w + pA->z * pB->x - pA->x * pB->z;
    q.z = pA->w * pB->z + pA->z * pB->w + pA->x * pB->y - pA->y * pB->x;
    q.w = pA->w * pB->w - pA->x * pB->x - pA->y * pB->y - pA->z * pB->z;
    pOut->x = q.x;
    pOut->y = q.y;
    pOut->z = q.z;
    pOut->w = q.w;
}

void fn_801EB700(Quat_801EB488 *pOut, Quat_801EB488 *q)
{
    fn_801EB56C(pOut, q, 1.0f / (q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z));
    pOut->x = -q->x;
    pOut->y = -q->y;
    pOut->z = -q->z;
}

float fn_801EB780(Quat_801EB488 *pA, Quat_801EB488 *pB)
{
    return pA->x * pB->x + pA->y * pB->y + pA->z * pB->z + pA->w * pB->w;
}

float fn_801EB7B4(Quat_801EB488 *pA, Quat_801EB488 *pB)
{
    return fn_801EB780(pA, pB) * (fn_801EB4EC(pA) * fn_801EB4EC(pB));
}
