#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/fn_801FCE10.h"

struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    unsigned char mUnknown12;
    char mUnknown13;
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    char mUnknown18[2];
};

struct Table_8015005C {
    Entry_8015005C mEntries[5];
    char mUnknown100[17];
    unsigned char mUnknown117;
    unsigned char mCount;
    char mUnknown119[6];
    unsigned char mUnknown125;
};

struct Object_8015005C {
    char mUnknown0[36];
    Table_8015005C *mpUnknown36;
};

class Class_802A2918 : public Class_80148A58 {
public:
    Object_8015005C *mpUnknown1C;
};

struct Info_80152940 {
    Info_80152940() : mpObject(0), mUnknown4(0), mUnknown12(0), mUnknown16(0), mUnknown20(0xFF) {}

    Object_80039F5C *mpObject;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
};

extern "C" {
extern const char lbl_802A0F24[];
extern const char lbl_802A0F34[];
extern const char lbl_802A0F74[];

int fn_80188030(int index);
int fn_80187A78(unsigned char index, char *pText, int count);
int fn_80187400(int kind, int key, int first, int last);
void fn_80152940(Class_802A2918 *p, int index, Info_80152940 *pInfo);

void fn_80152400(Class_802A2918 *p, int value, int *list, int *ids)
{
    unsigned char i;

    for (i = 0; i < 7 && list[i] != 32767; i++) {
        ids[i] = ids[i + 7] = list[i];
    }
}

void fn_80152448(Class_802A2918 *p, int value, int *list, int *ids, int a, int b)
{
    p->vfn_10(value, list, ids);
}

void fn_8015247C(Class_802A2918 *p)
{
    for (unsigned short i = 0; i <= 3; i++) {
        if (p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown12 == 255) {
            continue;
        }
        char name[32];
        if (!fn_80187A78(fn_80188030(p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown12), name, 31)) {
            continue;
        }
        QueryResult result;
        QueryCursor cursor;
        unsigned int score = 0;
        int key = 0;
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        fn_801FCE10(&result, "use 'EVAS' declare \x8a fastcursor for select 'SJSH' into \x85 and 'KPSH' into \x82 from 'BJSH' order by 'SJSH' asc and 'KPSH' asc\n",
                    &cursor, &score, &key);
        cursor.mUnknown4 = 0;
        fn_801FCE10(0, lbl_802A0F24, &cursor);
        if (cursor.mUnknown0) {
            fn_801FCFA0(&cursor);
        }
        Info_80152940 info;
        fn_80152940(p, i, &info);
        if (score < (unsigned int)info.mUnknown8) {
            int id = 0;
            int status = fn_801FCE10(0, lbl_802A0F34, &id, name);
            if (status == 23) {
                id = fn_80187400(0x52435348, 0x4B505348, 0, 255);
                if (id == -1) {
                    continue;
                }
                fn_801FCE10(0, lbl_802A0F74, id, name);
            }
            if (id != -1) {
                fn_801FCE10(&result, "use 'EVAS' update 'BJSH' set 'SJSH' = \x85 and 'UBJH' = \x82 where 'KPSH' = \x82\n",
                            info.mUnknown8, id, key);
            }
        }
    }
}
}
