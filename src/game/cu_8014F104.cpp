#include "game/Class_802A2B68.h"
#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/fn_801FCE10.h"

struct Info_8014F3E4 {
    Object_80039F5C *mpUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    unsigned int mUnknown12;
    unsigned char mUnknown16;
};

extern "C" {
extern int lbl_803EB2D8;
extern const char lbl_802A0E98[];
extern const char lbl_802A0F24[];
extern const char lbl_802A0F34[];
extern const char lbl_802A0F74[];
extern const char lbl_802A1074[];

int fn_80188030(int index);
int fn_80187A78(unsigned char index, char *pText, int count);
int fn_80187400(int kind, int key, int first, int last);

Object_80039F5C *fn_8003AC84(int id);
int fn_8017F584(void);
int fn_8014FF34(Class_802A2B68 *p);
unsigned int fn_8014F474(Class_80148A58 *p, Object_80039F5C *pPlayer);

Block_8014F104 *fn_8014F104(Class_80148A58 *p)
{
    return static_cast<Class_802A2B68 *>(p)->mpUnknown1C;
}

int fn_8014F10C(Class_802A2B68 *p, int team)
{
    if (team == 0) {
        return 5;
    }
    return 1;
}

void fn_8014F120(Class_802A2B68 *p, int value, int *pList, int *pIds)
{
    for (unsigned char i = 0; i <= 6 && pList[i] != 32767; i++) {
        pIds[i] = pIds[i + 7] = pList[i];
    }
}

void fn_8014F168(Class_802A2B68 *p, int value, int *pList, int *pIds, int a, int b)
{
    p->vfn_10(value, pList, pIds);
}

void fn_8014F19C(Class_802A2B68 *p)
{
    for (unsigned short i = 0; i <= 5; i++) {
        if (p->mpUnknown1C->mpUnknown34[i].mUnknown8 == 255) {
            continue;
        }
        char name[32];
        if (!fn_80187A78(fn_80188030(p->mpUnknown1C->mpUnknown34[i].mUnknown8), name, 31)) {
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
        fn_801FCE10(&result, lbl_802A0E98, &cursor, &score, &key,
                    (unsigned char)((unsigned int)lbl_803EB2D8 / 60));
        cursor.mUnknown4 = 0;
        fn_801FCE10(0, lbl_802A0F24, &cursor);
        if (cursor.mUnknown0) {
            fn_801FCFA0(&cursor);
        }
        if (score < p->mpUnknown1C->mpUnknown34[i].mUnknown4) {
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
                fn_801FCE10(&result, lbl_802A1074,
                            p->mpUnknown1C->mpUnknown34[i].mUnknown4, id, key);
            }
        }
    }
}

int fn_8014F36C(Class_802A2B68 *p)
{
    if (fn_8017F584() == 7) {
        return fn_8014FF34(p) <= 4;
    }
    return fn_8014F104(fn_80148A58())->mpUnknown34[0].mUnknown8 != 255;
}

void fn_8014F3DC(int value)
{
    lbl_803EB2D8 = value;
}

void fn_8014F3E4(Class_80148A58 *p, int index, Info_8014F3E4 *pInfo)
{
    Record_8014F104 *pRecord = &static_cast<Class_802A2B68 *>(p)->mpUnknown1C->mpUnknown34[index];
    pInfo->mUnknown4 = pRecord->mUnknown4;
    pInfo->mUnknown8 = pRecord->mUnknown12[8];
    pInfo->mUnknown12 = pRecord->mUnknown12[0];
    pInfo->mpUnknown0 = fn_8003AC84(pRecord->mUnknown0);
    pInfo->mUnknown16 = pRecord->mUnknown8;
}

Object_80039F5C *fn_8014F448(Class_80148A58 *p)
{
    return fn_8003AC84(static_cast<Class_802A2B68 *>(p)->mpUnknown1C->mpUnknown34[0].mUnknown0);
}

unsigned int fn_8014F474(Class_80148A58 *p, Object_80039F5C *pPlayer)
{
    unsigned int i;
    for (i = 0; i <= 5; i++) {
        if (fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0 == pPlayer->mUnknown2908) {
            break;
        }
    }
    return i;
}

void fn_8014F4D8(Class_80148A58 *p, Object_80039F5C *pPlayer, int kind, int value)
{
    unsigned int index = fn_8014F474(fn_80148A58(), pPlayer);
    if (kind == 8 && value > fn_8014F104(fn_80148A58())->mpUnknown34[index].mUnknown48) {
        fn_8014F104(fn_80148A58())->mpUnknown34[index].mUnknown48 = value;
    }
    fn_8014F104(fn_80148A58())->mpUnknown34[index].mUnknown12[kind] += value;
}
}
