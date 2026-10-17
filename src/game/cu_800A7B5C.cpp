#include "game/Object_80039F5C.h"
#include "game/Object_8007A334.h"
#include "game/Object_800785C0.h"
#include "game/Block_800A70F4.h"
#include "game/cu_80067C10.h"

struct Record_8007C84C;

extern "C" {
int fn_8007C7E8(Object_8007A334 *pCursor, int key, int *pResult);
void fn_8007C84C(Object_8007A334 *pCursor, Record_8007C84C *pOut);
void fn_800A6658(int team);
void fn_800A6CB0(int id);
void fn_800A6DA4(void);
int fn_800A6590(int value);
int fn_800A8408(int team);
void fn_800AE7F0(int index, int team, Object_80039F5C *p);
void fn_8017DE54(int a, float t, int b, int direct);
void fn_8017DF6C(int a, int b);
void fn_8017E328(int a, int b);
int fn_80025708(void);
float fn_800D3F2C(int team);
int fn_80177F70(void);
int fn_80178308(void);

extern Block_800A70F4 *lbl_803EC954[2];
extern int lbl_803EC95C;
extern unsigned char lbl_803EAA50;
extern int lbl_802D7EFC[][3];
}

extern "C" void fn_800A7B5C(void)
{
    Object_8007A334 cursor;
    int row;
    int quiet = 0;
    unsigned char team;

    for (team = 0; team <= 1; team++) {
        if ((lbl_803EC954[team]->mUnknown6C == 0 && fn_800D3F2C(team) >= 0.5f) ||
            (lbl_803EC954[team]->mUnknown6C == 1 && fn_800D3F2C(team) >= 1.0f)) {
            Block_800A70F4 *pBlock = lbl_803EC954[team];

            if (pBlock->mUnknown6C == 0) {
                pBlock->mUnknown5C++;
            } else if (pBlock->mUnknown6C == 1) {
                pBlock->mUnknown60++;
            }
            if (fn_80177F70() != 6) {
                fn_80178308();
            }
            fn_8007A308(&cursor, 'KRBG', 'DIBG');
            fn_800A6658(team);
            if (team == fn_80178308()) {
                fn_8007C7E8(&cursor, 0, &row);
            } else {
                fn_8007C7E8(&cursor, 1, &row);
            }
            fn_8007C84C(&cursor, (Record_8007C84C *)lbl_803EC954[team]);
            fn_8007A3C4(&cursor);
            lbl_803EC954[team]->mUnknown10 = 10000;
            if (lbl_803EC95C == -1) {
                fn_800A6DA4();
                fn_800A6CB0(lbl_802D7EFC[lbl_803EAA50][0]);
            }
            if (fn_800D3F2C(team) >= 1.0f) {
                lbl_803EC954[team]->mUnknown6C = 2;
                fn_8017DF6C(team, 2);
            } else {
                lbl_803EC954[team]->mUnknown6C = 1;
                fn_8017DF6C(team, 1);
                if (fn_800D3F2C(team) >= 0.5f) {
                    fn_8017E328(team, 2);
                }
            }
            lbl_803EC954[team]->mUnknown58 = 1.0f;
            lbl_803EC954[team]->mUnknown64 = 0;
            fn_8017DE54(team, fn_800D3F2C(team), 0, 0);
            fn_800AE7F0(fn_800A6590(fn_800A8408(team)), team, 0);
            if (fn_80025708() != 0 &&
                ((team == 0 && fn_800785C0()->mUnknown1C3 != 0) ||
                 (team == 1 && fn_800785C0()->mUnknown1C2 != 0))) {
                quiet = 1;
            }
            if (!quiet) {
                if (lbl_803EC954[team]->mUnknown6C == 1) {
                    fn_80067DB8(22, 0, team, 0, 0);
                } else if (lbl_803EC954[team]->mUnknown6C == 2) {
                    fn_80067DB8(23, 0, team, 0, 0);
                }
            }
        }
    }
}

extern "C" {
int fn_80178BA4(int team);
int fn_80178BE4(int team);
int fn_800A8444(int team);
}

extern "C" unsigned char fn_800A82FC(int team)
{
    unsigned char result = 0;
    int a = fn_80178BA4(team);
    int b = fn_80178BE4(team);
    int state = lbl_803EC954[team]->mUnknown6C;

    if (state == 2) {
        if (fn_80177F70() != 6 || a != 0 || b != 0) {
            result = 1;
        }
    } else if (state == 1) {
        if (b != 0 || a != 0 ||
            (fn_800A8444(team == 0) && fn_80177F70() != 6 && fn_800D3F2C(team) < 0.75f)) {
            result = 1;
        }
    }
    lbl_803EC954[team]->mUnknown64 = result;
    return result;
}
