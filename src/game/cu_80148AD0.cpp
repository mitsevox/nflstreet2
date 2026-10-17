#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/cu_8003E214.h"
#include "game/cu_80067C10.h"
#include "game/fn_8009D990.h"
#include "game/fn_800B65A0.h"

extern "C" {
int fn_80178AE0(void);
int fn_8022B414(int handle, unsigned int tag, int *pValue);
void fn_80148D20(Record_8003E214 *pRecords, int *pValues,
                 Object_8007A334 *pQuery);
void fn_80148DFC(Record_8003E214 *pRecords, int count, int *pExcluded,
                 int *pId, int *pCategory);

int fn_80148AD0(Class_80148A58 *)
{
    return 14;
}

unsigned int fn_80148AD8(Class_80148A58 *, int)
{
    return 7;
}

int fn_80148AE0(Class_80148A58 *, int)
{
    return 7;
}

unsigned int fn_80148AE8(Class_80148A58 *)
{
    return 7;
}

int fn_80148AF0(Class_80148A58 *, int)
{
    return 0;
}

void fn_80148AF8(Class_80148A58 *p)
{
    if (p->mState.mCount && p->mState.mpRecords) {
        fn_8003EBC4(fn_80148D20);
        fn_8003EBE4(fn_80148DFC);
    }
}

void fn_80148B44(Class_80148A58 *, int value, int *pList, int *pIds)
{
    fn_8003E8FC(value, pList, pIds);
}

void fn_80148B70(Class_80148A58 *, int value, int *pList, int *pIds,
                 int, int)
{
    fn_8003E8FC(value, pList, pIds);
}

int fn_80148B9C(Class_80148A58 *)
{
    unsigned char team = (unsigned char)fn_80178AE0();
    int result = 0;
    if (team != 2) {
        result = fn_800B65A0(team) != 255;
    }
    return result;
}

void fn_80148BF0(Class_80148A58 *p)
{
    int value = (int)fn_8009D990(1);
    if (value != p->mState.mCachedValue && value >= 0) {
        p->mState.mCachedValue = value;
        if (value <= 10) {
            fn_80067D4C(20, 0);
        }
    }
}

int fn_80148C4C(Class_80148A58 *p)
{
    unsigned int index = 0;
    while (index < p->mState.mCount && p->mState.mpRecords[index].mUnknown2C) {
        ++index;
    }
    return index == p->mState.mCount ? 0 : index;
}

int fn_80148CA0(Class_80148A58 *, int team, unsigned int tag)
{
    int value = 0;
    int result = 0;
    for (unsigned char index = 0; index <= 6; ++index) {
        Object_80039F5C *p = fn_80039F5C((unsigned char)team, index);
        if (p->mUnknown9[2]) {
            fn_8022B414(p->mUnknown2908, tag, &value);
            result += value;
        }
    }
    return result;
}
}
