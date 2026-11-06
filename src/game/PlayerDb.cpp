/* Player records in the game database: read and write the columns of a player row
   (ids, team, names, appearance, height and weight) through an open player cursor, and
   build the short, full and letters-only forms of a player's name. */

#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include <string.h>

extern "C" {

extern const int lbl_80293968[];
char *fn_801C2F88(char *pDest, const char *pSource, unsigned int count);
char *fn_801C32CC(char *pText);

static int _PlayerDb_aSgtColumns[4] = { 0x31544753, 0x32544753, 0x33544753, 0x34544753 };

int PlayerDbGetId(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x44494750);
}

int PlayerDbGetOriginalId(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x44494F50);
}

int PlayerDbGetTeamId(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x44494754);
}

int PlayerDbGetTeamIndex(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x49544754);
}

void PlayerDbSetTeamIndex(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x49544754, value);
}

int PlayerDbSeekId(Object_8008044C *pObject, int a, int *pResult)
{
    return DbCursorFindInt((DbCursor *)pObject, 0x44494750, a, 0, pResult);
}

int PlayerDbSeekOriginalId(Object_8008044C *pObject, int a, int *pResult)
{
    return DbCursorFindInt((DbCursor *)pObject, 0x44494F50, a, 0, pResult);
}

void PlayerDbGetFirstName(Object_8008044C *pObject, char *pBuffer, int size)
{
    fn_8007AA3C((DbCursor *)pObject, 0x414E4650, (int)pBuffer, size);
}

void PlayerDbGetLastName(Object_8008044C *pObject, char *pBuffer, int size)
{
    fn_8007AA3C((DbCursor *)pObject, 0x414E4C50, (int)pBuffer, size);
}

/* The 0x4E4B4E50 text, or the upper-cased PlayerDbGetLastName text when it is empty. */
void PlayerDbGetNickname(Object_8008044C *pObject, char *pBuffer, int size)
{
    fn_8007AA3C((DbCursor *)pObject, 0x4E4B4E50, (int)pBuffer, size);
    if (strlen(pBuffer) == 0) {
        PlayerDbGetLastName(pObject, pBuffer, size);
        fn_801C32CC(pBuffer);
    }
}

/* The first non-space character of the PlayerDbGetFirstName text and ". ", then the
   PlayerDbGetLastName text, ending at size. */
void PlayerDbGetShortName(Object_8008044C *pObject, char *pBuffer, int size)
{
    char first[16];
    char last[16];
    char *pFirst;
    int length;
    unsigned int lastLength;
    unsigned int total;

    PlayerDbGetFirstName(pObject, first, 12);
    pFirst = first;
    while (*pFirst == ' ') pFirst++;
    length = strlen(pFirst);
    PlayerDbGetLastName(pObject, last, 15);
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

/* The PlayerDbGetFirstName text, a space, then the PlayerDbGetLastName text, ending at size. */
void PlayerDbGetFullName(Object_8008044C *pObject, char *pBuffer, int size)
{
    char first[16];
    char last[16];
    int length;
    unsigned int lastLength;
    unsigned int total;

    PlayerDbGetFirstName(pObject, first, 12);
    length = strlen(first);
    PlayerDbGetLastName(pObject, last, 15);
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

int PlayerDbGetPrty(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x59545250);
}

int PlayerDbHasPlil(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x4C494C50) != 0;
}

int PlayerDbGetPortraitId(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x50585350);
}

/* Only the A-Z bytes of the upper-cased PlayerDbGetLastName text followed by the
   PlayerDbGetFirstName text. Returns 0 with an empty buffer when PlayerDbGetPrty is
   non-zero. */
int PlayerDbGetNameKey(Object_8008044C *pObject, char *pBuffer, int size)
{
    char first[16];
    char *pDest;
    char *pSource;
    int result = 1;

    if (PlayerDbGetPrty(pObject) == 0) {
        pBuffer[0] = 0;
        PlayerDbGetLastName(pObject, pBuffer, 15);
        PlayerDbGetFirstName(pObject, first, 12);
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

int PlayerDbGetPybt(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x54425950);
}

int PlayerDbGetPlex(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x58454C50);
}

int PlayerDbGetPlht(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x54484C50);
}

int PlayerDbGetHairStyle(Object_8008044C *pObject)
{
    int value = DbCursorGetInt(pObject, 0x52414850);
    if (value == 63) value = 0;
    return value;
}

int PlayerDbGetPbpo(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x4F504250);
}

void PlayerDbSetPbpo(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x4F504250, value);
}

int PlayerDbGetPpsn(void *pObject)
{
    return DbCursorGetInt(pObject, 0x4E535050);
}

int PlayerDbGetSgt(void *pObject, int index)
{
    return DbCursorGetInt(pObject, _PlayerDb_aSgtColumns[index]);
}

void PlayerDbSetPpsn(void *pObject, int value)
{
    fn_8007ABA4(pObject, 0x4E535050, value);
}

void PlayerDbSetSgt(void *pObject, int index, int value)
{
    fn_8007ABA4(pObject, _PlayerDb_aSgtColumns[index], value);
}

void PlayerDbSetHairStyle(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x52414850, value);
}

void PlayerDbSetPybt(DbCursor *pObject, int index)
{
    fn_8007ABA4(pObject, 0x54425950, index);
    fn_8007AA90(pObject, 0x544C4650, lbl_80293968[index]);
}

void PlayerDbSetSkinTone(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x494B5350, value);
}

void PlayerDbSetPlex(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x58454C50, value);
}

void PlayerDbSetHairColor(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x31414850, value);
}

int PlayerDbGetHairColor(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x31414850);
}

void PlayerDbSetFacialHairColor(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x43484650, value);
}

int PlayerDbGetFacialHairColor(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x43484650);
}

void PlayerDbSetWeight(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x54475750, value - 160);
}

int PlayerDbGetWeight(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x54475750) + 160;
}

void PlayerDbSetHeight(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x54474850, value);
}

int PlayerDbGetHeight(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x54474850);
}

int PlayerDbGetPhan(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x4E414850);
}

void PlayerDbSetPhan(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x4E414850, value);
}

int PlayerDbGetPjen(Object_8008044C *pObject)
{
    return DbCursorGetInt(pObject, 0x4E454A50);
}

void PlayerDbSetPjen(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x4E454A50, value);
}
}
