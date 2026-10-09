#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include <string.h>

extern "C" {

extern const int lbl_80293968[];
char *fn_801C2F88(char *pDest, const char *pSource, unsigned int count);
char *fn_801C32CC(char *pText);

static int lbl_802D69E0[4] = { 0x31544753, 0x32544753, 0x33544753, 0x34544753 };

int fn_800808F8(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x44494750);
}

int fn_80080920(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x44494F50);
}

int fn_80080948(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x44494754);
}

int fn_80080970(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x49544754);
}

void fn_80080998(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x49544754, value);
}

int fn_800809C4(Object_8008044C *pObject, int a, int *pResult)
{
    return fn_8007A7F4((Object_8007A334 *)pObject, 0x44494750, a, 0, pResult);
}

int fn_800809FC(Object_8008044C *pObject, int a, int *pResult)
{
    return fn_8007A7F4((Object_8007A334 *)pObject, 0x44494F50, a, 0, pResult);
}

void fn_80080A34(Object_8008044C *pObject, char *pBuffer, int size)
{
    fn_8007AA3C((Object_8007A334 *)pObject, 0x414E4650, (int)pBuffer, size);
}

void fn_80080A68(Object_8008044C *pObject, char *pBuffer, int size)
{
    fn_8007AA3C((Object_8007A334 *)pObject, 0x414E4C50, (int)pBuffer, size);
}

/* Nickname, or the upper-case last name when the nickname is empty. */
void fn_80080A9C(Object_8008044C *pObject, char *pBuffer, int size)
{
    fn_8007AA3C((Object_8007A334 *)pObject, 0x4E4B4E50, (int)pBuffer, size);
    if (strlen(pBuffer) == 0) {
        fn_80080A68(pObject, pBuffer, size);
        fn_801C32CC(pBuffer);
    }
}

/* "F. Last": the first initial (leading spaces skipped), then the last name. */
void fn_80080B08(Object_8008044C *pObject, char *pBuffer, int size)
{
    char first[16];
    char last[16];
    char *pFirst;
    int length;
    unsigned int lastLength;
    unsigned int total;

    fn_80080A34(pObject, first, 12);
    pFirst = first;
    while (*pFirst == ' ') pFirst++;
    length = strlen(pFirst);
    fn_80080A68(pObject, last, 15);
    lastLength = strlen(last);
    if (length) {
        pBuffer[0] = *pFirst;
        pBuffer[1] = '.';
        pBuffer[2] = ' ';
        length = 3;
    }
    if (lastLength) {
        strcpy(pBuffer + length, last);
    } else if (length) {
        length--;
    }
    total = length + lastLength;
    if (total > size) total = size;
    pBuffer[total] = 0;
}

/* "First Last". */
void fn_80080BEC(Object_8008044C *pObject, char *pBuffer, int size)
{
    char first[16];
    char last[16];
    int length;
    unsigned int lastLength;
    unsigned int total;

    fn_80080A34(pObject, first, 12);
    length = strlen(first);
    fn_80080A68(pObject, last, 15);
    lastLength = strlen(last);
    if (length) {
        strcpy(pBuffer, first);
        pBuffer[length] = ' ';
        length++;
    }
    if (lastLength) {
        strcpy(pBuffer + length, last);
    } else if (length) {
        length--;
    }
    total = length + lastLength;
    if (total > size) total = size;
    pBuffer[total] = 0;
}

int fn_80080CB0(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x59545250);
}

int fn_80080CD8(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x4C494C50) != 0;
}

int fn_80080D10(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x50585350);
}

/* Upper-case letters of the last name followed by the first name, other
   characters removed. Returns 0 with an empty buffer when fn_80080CB0 is
   non-zero. */
int fn_80080D38(Object_8008044C *pObject, char *pBuffer, int size)
{
    char first[16];
    char *pDest;
    char *pSource;
    int result = 1;

    if (fn_80080CB0(pObject) == 0) {
        pBuffer[0] = 0;
        fn_80080A68(pObject, pBuffer, 15);
        fn_80080A34(pObject, first, 12);
        fn_801C2F88(pBuffer, first, size);
        fn_801C32CC(pBuffer);
        pDest = pBuffer;
        for (pSource = pBuffer; *pSource; pSource++) {
            while ((*pSource < 'A' || *pSource > 'Z') && *pSource) pSource++;
            *pDest++ = *pSource;
        }
        *pDest = 0;
    } else {
        pBuffer[0] = 0;
        result = 0;
    }
    return result;
}

int fn_80080E20(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x54425950);
}

int fn_80080E48(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x58454C50);
}

int fn_80080E70(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x54484C50);
}

int fn_80080E98(Object_8008044C *pObject)
{
    int value = fn_8007A98C(pObject, 0x52414850);
    if (value == 63) value = 0;
    return value;
}

int fn_80080ECC(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x4F504250);
}

void fn_80080EF4(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x4F504250, value);
}


int fn_80080F20(void *pObject)
{
    return fn_8007A98C(pObject, 0x4E535050);
}

int fn_80080F48(void *pObject, int index)
{
    return fn_8007A98C(pObject, lbl_802D69E0[index]);
}

void fn_80080F78(void *pObject, int value)
{
    fn_8007ABA4(pObject, 0x4E535050, value);
}

void fn_80080FA4(void *pObject, int index, int value)
{
    fn_8007ABA4(pObject, lbl_802D69E0[index], value);
}

void fn_80080FD4(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x52414850, value);
}

void fn_80081000(Object_8007A334 *pObject, int index)
{
    fn_8007ABA4(pObject, 0x54425950, index);
    fn_8007AA90(pObject, 0x544C4650, lbl_80293968[index]);
}

void fn_8008105C(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x494B5350, value);
}

void fn_80081088(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x58454C50, value);
}

void fn_800810B4(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x31414850, value);
}

int fn_800810E0(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x31414850);
}

void fn_80081108(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x43484650, value);
}

int fn_80081134(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x43484650);
}

void fn_8008115C(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x54475750, value - 160);
}

int fn_80081188(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x54475750) + 160;
}

void fn_800811B4(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x54474850, value);
}

int fn_800811E0(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x54474850);
}

int fn_80081208(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x4E414850);
}

void fn_80081230(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x4E414850, value);
}

int fn_8008125C(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x4E454A50);
}

void fn_80081284(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x4E454A50, value);
}
}
