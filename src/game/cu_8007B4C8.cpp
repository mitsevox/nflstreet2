#include <string.h>

#include "game/fn_801FCE10.h"
#include "game/Object_8007A334.h"
#include "game/QueryStatus.h"

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int a);
}

static Object_8007A334 lbl_8030B968;

extern "C" {
static void fn_8007B4C8(Object_8007A334 *pObject)
{
    fn_8007A308(pObject, 0x52564E45, 0x44495645);
}

static void fn_8007B4F8(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

int fn_8007B518(int index, int id)
{
    int value;
    int result = fn_801FCE10(0, "use \x8c select 'KLNE' into \x82 from 'NEKL' where 'DIVE' = \x85\n",
                             fn_8022F3D4(fn_8022F358(index)), &value, id);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        return value == 1;
    }
    return 0;
}

void fn_8007B5A8(int index, int id, int value)
{
    fn_801FCE10(0, "use \x8c update 'NEKL' set 'KLNE' = \x82 where 'DIVE' = \x85\n",
                fn_8022F3D4(fn_8022F358(index)), value, id);
}

void fn_8007B5FC(int index)
{
    fn_8007B5A8(index, 10, 0);
    fn_8007B5A8(index, 11, 0);
}

void fn_8007B640(int index)
{
    fn_8007B5A8(index, 10, 1);
    fn_8007B5A8(index, 11, 1);
}

/* Selects the row whose 'DIVE' column equals id; the accessors below read
   that row until fn_8007B6D4 releases it. */
void fn_8007B684(int id)
{
    fn_8007B4C8(&lbl_8030B968);
    fn_8007A7F4(&lbl_8030B968, 0x44495645, id, 0, 0);
}

void fn_8007B6D4(void)
{
    fn_8007B4F8(&lbl_8030B968);
}

void fn_8007B6FC(int *pA, int *pB)
{
    *pA = fn_8007A98C(&lbl_8030B968, 0x43495045);
    *pB = fn_8007A98C(&lbl_8030B968, 0x32435045);
}

int fn_8007B754(void)
{
    return fn_8007A98C(&lbl_8030B968, 0x4C545645);
}

float fn_8007B784(void)
{
    return fn_8007A9E4(&lbl_8030B968, 0x4C505645);
}

float fn_8007B7B4(void)
{
    return fn_8007A9E4(&lbl_8030B968, 0x46505645);
}

float fn_8007B7E4(void)
{
    return fn_8007A9E4(&lbl_8030B968, 0x44575645);
}

float fn_8007B814(void)
{
    return fn_8007A9E4(&lbl_8030B968, 0x4C575645);
}

int fn_8007B844(void)
{
    return fn_8007A98C(&lbl_8030B968, 0x53445645);
}

float fn_8007B874(void)
{
    return fn_8007A9E4(&lbl_8030B968, 0x44455645);
}

void fn_8007B8A4(char *pDest, int count)
{
    char buffer[33];

    buffer[0] = 0;
    fn_8007AA3C(&lbl_8030B968, 0x49554E45, (int)buffer, sizeof(buffer));
    strncpy(pDest, buffer, count);
}

void fn_8007B904(int a, int b)
{
    fn_8007AA3C(&lbl_8030B968, 0x4F4C5645, a, b);
}

void fn_8007B93C(int a, int b)
{
    fn_8007AA3C(&lbl_8030B968, 0x45445645, a, b);
}

int fn_8007B974(void)
{
    return fn_8007A98C(&lbl_8030B968, 0x46564E45) == 1;
}
}
