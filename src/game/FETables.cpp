/* Game database helpers for the front end: the tutorial lesson table (title,
   description, status), and the pose and tattoo tables of create-a-player. */

#include "game/Key_8007A334.h"
#include "game/Object_8007A334.h"

extern "C" {
int fn_8007A934(Object_8007A334 *pObject, int key);

int LessonTableSeek(Object_8007A334 *pObject, int a, int *pResult)
{
    return fn_8007A7F4(pObject, 0x4449564D, a, 0, pResult);
}

int LessonTableGetCILM(Object_8007A334 *pObject)
{
    return fn_8007A934(pObject, 0x43494C4D);
}

int LessonTableGetCISM(Object_8007A334 *pObject)
{
    return fn_8007A934(pObject, 0x4349534D);
}

int LessonTableGetDIRM(Object_8007A334 *pObject)
{
    return fn_8007A934(pObject, 0x4449524D);
}

void LessonTableGetTitle(Object_8007A334 *pObject, char *pData, int size)
{
    fn_8007AA3C(pObject, 0x5449544D, (int)pData, size);
}

void LessonTableGetDescription(Object_8007A334 *pObject, char *pData, int size)
{
    fn_8007AA3C(pObject, 0x4353444D, (int)pData, size);
}

void PoseTableOpen(Object_8007A334 *pObject)
{
    Key_8007A334 keys[2];

    keys[0].Set(0x54425753, 0x524F5753, 0);
    keys[1].Set(-1, -1, 3);
    fn_8007A334(pObject, 0x54425753, -1, keys, 0, 0x54415453);
}

void PoseTableClose(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

void PoseTableSeek(Object_8007A334 *pCursor, int value, int *pResult)
{
    fn_8007A7F4(pCursor, 0x554E5753, value, 0, pResult);
}

void PoseTableGetName(Object_8007A334 *pCursor, char *pBuffer, int size)
{
    fn_8007AA3C(pCursor, 0x414E5753, (int)pBuffer, size);
}

int PoseTableGetNumber(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x554E5753);
}

void TattooTableOpen(Object_8007A334 *pCursor, int type)
{
    Object_80023BBC arg;
    Key_8007A334 keys[2];

    arg.Set(6, 0x4F5441544C544154LL, 3, type);
    keys[0].Set(0x4F544154, 0x524F5454, 0);
    keys[1].Set(-1, -1, 3);
    fn_8007A334(pCursor, 0x4F544154, -1, keys, &arg, 0x54415453);
}

void TattooTableClose(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

void TattooTableGetName(Object_8007A334 *pCursor, char *pBuffer, int size)
{
    fn_8007AA3C(pCursor, 0x4E544154, (int)pBuffer, size);
}

int TattooTableGetId(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x49544154);
}
}
