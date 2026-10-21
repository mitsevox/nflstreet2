#include "game/Class_80148A58.h"
#include "game/cu_8003E214.h"
#include "game/fn_802372EC.h"

extern "C" {
int fn_801486A0(void);
int fn_80183950(void);
void *fn_801C2030(void *dst, const void *src, unsigned int n);

void fn_80148D20(Record_8003E214 *pRecord, int *pValues, Object_8007A334 *)
{
    Class_80148A58 *p = fn_80148A58();
    unsigned int i;
    unsigned int j;

    for (j = 0; j < 14; j++) {
        pRecord->values[j] = 0;
    }
    for (i = 0; i < p->mState.mCount; i++) {
        pRecord->values[p->mState.mpRecords[i].mUnknown0] = 0;
        for (j = 0; j < 10; j++) {
            pRecord->values[p->mState.mpRecords[i].mUnknown0] +=
                p->mState.mpRecords[i].mUnknown4[j] * pValues[j];
            p->mState.mpRecords[i].mUnknown2C = 0;
        }
    }
}

void fn_80148DFC(Record_8003E214 *pRecords, int count, int *, int *pId, int *pCategory)
{
    Class_80148A58 *p = fn_80148A58();
    int index = p->vfn_23(pRecords, count);
    unsigned int values[4];
    int ids[4];
    int categories[4];
    unsigned int found;
    unsigned int i;
    unsigned char k;

    for (unsigned char m = 0; m <= 3; m++) {
        ids[m] = 32767;
        values[m] = 0;
        categories[m] = 0;
    }
    found = 0;
    for (i = 0; i < count; i++) {
        if (!pRecords[i].excluded) {
            for (k = 0; k <= 3; k++) {
                if (pRecords[i].values[p->mState.mpRecords[index].mUnknown0] > values[k]) {
                    found++;
                    fn_801C2030(&values[k] + 1, &values[k], (3 - k) * 4);
                    fn_801C2030(&ids[k] + 1, &ids[k], (3 - k) * 4);
                    fn_801C2030(&categories[k] + 1, &categories[k], (3 - k) * 4);
                    ids[k] = pRecords[i].id;
                    values[k] = pRecords[i].values[p->mState.mpRecords[index].mUnknown0];
                    categories[k] = p->mState.mpRecords[index].mUnknown0;
                    *pCategory = categories[k];
                    p->mState.mpRecords[index].mUnknown2C = 1;
                    break;
                }
            }
        }
    }
    *pId = ids[0];
    *pCategory = categories[0];
    if (!fn_80183950() && *pCategory) {
        switch (fn_801486A0()) {
        case 0:
        case 1:
        case 2: {
            unsigned int n = found;
            if (n > 4) {
                n = 4;
            }
            unsigned int pick = fn_802372EC(0, n);
            *pId = ids[pick];
            *pCategory = categories[pick];
            break;
        }
        }
    }
}
}
