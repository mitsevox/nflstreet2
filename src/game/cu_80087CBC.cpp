#include <stdio.h>

#include "game/Object_8007A334.h"
#include "game/fn_800670B4.h"
#include "game/fn_801FCE10.h"

extern "C" {
int fn_8007A934(Object_8007A334 *pObject, int key);
int fn_80168ED0(int a);
int fn_801C302C(const char *s1, const char *s2, int n);

void fn_80087CBC(Object_8007A334 *pCursor);
void fn_80087CFC(Object_8007A334 *pCursor);
int fn_80087D1C(Object_8007A334 *pCursor, int key);
unsigned char fn_80087D50(Object_8007A334 *pCursor);
int fn_80087D7C(Object_8007A334 *pCursor);
unsigned char fn_80087DA4(Object_8007A334 *pCursor, int column);
}

static int lbl_802D6C14[4] = {
    0x55445541, 0x44445541, 0x4C445541, 0x52445541
};

extern "C" {

void fn_80087CBC(Object_8007A334 *pCursor)
{
    fn_8007A334(pCursor, 0x49445541, 0x4F464C50, 0, 0, 0x54415453);
}

void fn_80087CFC(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

int fn_80087D1C(Object_8007A334 *pCursor, int key)
{
    return fn_8007A894(pCursor, 0x4F464C50, key, 0, 0);
}

unsigned char fn_80087D50(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x4F494650);
}

int fn_80087D7C(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x44494250);
}

unsigned char fn_80087DA4(Object_8007A334 *pCursor, int column)
{
    Object_800670B4 object;
    Record_80067338 record;
    char text[8];
    int handle;
    int match = 0;
    int tag;
    int mode;
    int value;
    unsigned short count;
    unsigned char i;

    if (fn_80087D50(pCursor)) {
        value = fn_80087D7C(pCursor);
        tag = 0x31544250;
        mode = 1;
        match = value == fn_80168ED0(1);
    } else {
        value = fn_80087D7C(pCursor);
        tag = 0x31444250;
        mode = 11;
        if (value == fn_80168ED0(0)) {
            match = 1;
        }
    }
    if (match) {
        signed char number = fn_8007A934(pCursor, lbl_802D6C14[column]);

        sprintf(text, "%02d", number);
        fn_800670B4(tag, mode, 0, &object);
        fn_801FCE10(0, "use \x8c select 'TSBP' into \x85 from 'TSBP' where '_dro' = \x85 and 'MFBP' = \x85\n",
                    tag, &handle, 1, object.mUnknown0);
        count = fn_800672BC(tag, handle);
        for (i = 0; i < count; i++) {
            fn_80067338(tag, handle, i, &record);
            if (fn_801C302C(record.mUnknown1F0, text, 2) == 0) {
                break;
            }
        }
    } else {
        i = 0;
    }
    return i;
}

}
