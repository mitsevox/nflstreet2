#include "game/Object_8007A334.h"
#include "game/fn_801FCE10.h"

extern "C" {
int fn_801F967C(int handle, int table);
int fn_801F9980(int handle, int *pTable);
int fn_8022F384(int a);
int fn_8022F4BC(void);
void fn_8007E514(Object_8007A334 *pObject, signed char a);
void fn_8007E56C(Object_8007A334 *pObject);
int fn_8007E58C(Object_8007A334 *pObject);
int fn_8007E5B4(Object_8007A334 *pObject);
}

static int lbl_802D6778[8] = { 0x4F474F4C, 0x524F474C, 0, 0, -1, -1, 3, 0 };
static int lbl_803EC868;

extern "C" {

void fn_8007EEFC(Object_8007A334 *pObject)
{
    Object_8007A334 cursor;
    QueryResult result;
    Object_80023BBC arg;
    unsigned char a;

    a = fn_8022F384(fn_8022F4BC());
    fn_801F9980(0x54415453, &lbl_803EC868);
    fn_801FCE10(&result, "use \x8c select into \x8c * from 'OGOL'\n", 0x54415453, lbl_803EC868);
    fn_8007E514(&cursor, a);
    if (fn_8007A444(&cursor)) {
        do {
            if (fn_8007E5B4(&cursor) == 0) {
                int id = fn_8007E58C(&cursor);
                fn_801FCE10(0, "use \x8c update \x8c set 'KLGL' = 0 where 'LGLT' = \x82\n", 0x54415453,
                            lbl_803EC868, id);
            }
        } while (fn_8007A510(&cursor));
    }
    fn_8007E56C(&cursor);

    unsigned int table = lbl_803EC868;
    unsigned long long column = 0x4B4C474C;
    arg.Set(6, ((unsigned long long)table << 32) | column, 3);
    arg.mUnknown16.mValue.mInt = 0;
    fn_8007A334(pObject, lbl_803EC868, -1, lbl_802D6778, &arg, 0x54415453);
}

void fn_8007F064(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
    fn_801F967C(0x54415453, lbl_803EC868);
}

void fn_8007F094(Object_8007A334 *pObject, char *pBuffer, int size)
{
    fn_8007AA3C(pObject, 0x4D4E474C, (int)pBuffer, size);
}

int fn_8007F0C8(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x4C474C54) + 45;
}

void fn_8007F0F4(Object_8007A334 *pObject, int a, int *pResult)
{
    fn_8007A7F4(pObject, 0x4C474C54, a - 45, 0, pResult);
}

}
