extern "C" {
void *fn_8021EA44(int index);
int fn_8022601C(void *pList, int type, short id, int b);

int fn_8018AD34(int id, int b)
{
    return fn_8022601C(fn_8021EA44(1), 2, id, b);
}
}
