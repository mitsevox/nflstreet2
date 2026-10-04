#include "game/Object_8007A334.h"

extern "C" {
void fn_8022DBF4(int value);
void fn_8022DC38(int value);
int fn_8022E558(void);
int fn_8022E560(void);
}

static int sColumnTags[3] = { 0x47544847, 0x47544147, 0x47545047 };
static Object_8007A334 sCursor;
static ColumnValue_802D6424 sRecord[4];
static unsigned char sInitialized = 0;

extern "C" {

void fn_8007CA28(void);

void fn_8007C9D4(void)
{
    fn_8007A334(&sCursor, 0x464E4947, 0x554E5547, 0, 0, 0x454D4147);
    fn_8007CA28();
    sInitialized = 1;
}

/* Reads the current values of all columns into sRecord. */
void fn_8007CA28(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        sRecord[i].mTableTag = 0x464E4947;
        sRecord[i].mColumnTag = sColumnTags[i];
    }
    ColumnValue_802D6424 *pEnd = &sRecord[3];
    pEnd->mValue = 0;
    pEnd->mColumnTag = -1;
    pEnd->mTableTag = -1;
    sCursor.Read(sRecord);
}

void fn_8007CAB4(void)
{
    fn_8007A3C4(&sCursor);
    sInitialized = 0;
}

unsigned char fn_8007CAE4(void)
{
    return sInitialized;
}

void fn_8007CAEC(int index, int value)
{
    if (index == 0) {
        fn_8022DBF4(value);
    } else if (index == 1) {
        fn_8022DC38(value);
    } else {
        fn_8007AA90(&sCursor, sColumnTags[index], value);
        sRecord[index].mValue = value;
    }
}

int fn_8007CB6C(int index)
{
    if (index == 0) {
        return fn_8022E558();
    } else if (index == 1) {
        return fn_8022E560();
    }
    return sRecord[index].mValue;
}
}
