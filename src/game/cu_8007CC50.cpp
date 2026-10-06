#include "game/Object_8007A334.h"
#include "game/Key_8007A334.h"

extern "C" {

void fn_8007CC50(Object_8007A334 *pObject)
{
    Key_8007A334 keys[2];

    keys[0].Set(0x52494148, 0x524F5248, 0);
    keys[1].Set(-1, -1, 3);
    fn_8007A334(pObject, 0x52494148, -1, keys, 0, 0x54415453);
}

void fn_8007CCC4(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

void fn_8007CCE4(Object_8007A334 *pObject, int id, int *pResult)
{
    fn_8007A7F4(pObject, 0x52414850, id, 0, pResult);
}

void fn_8007CD1C(Object_8007A334 *pObject, char *pBuffer, int size)
{
    fn_8007AA3C(pObject, 0x4D4E5248, (int)pBuffer, size);
}

int fn_8007CD50(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x52414850);
}

int fn_8007CD78(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x444D5248);
}

}
