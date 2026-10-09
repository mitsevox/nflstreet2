#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/fn_801FCE10.h"

extern "C" {
int fn_80178308(void);
int fn_80178320(void);
Object_8003DEC4 *fn_8003DEE4(int value);
void fn_8009CF30(void *pDst, Pose_80041930 *pPose);
}

extern "C" Object_80039F5C *fn_8003AC84(int id)
{
    Object_80039F5C *pResult = 0;
    int team = fn_80178308();
    unsigned int i;

    for (i = 0; i < 7; i++) {
        Object_80039F5C *p = fn_80039F5C((unsigned char)team, i);
        if (id == p->mUnknown2908) {
            pResult = p;
            break;
        }
    }
    if (pResult == 0) {
        team = fn_80178320();
        for (i = 0; i < 7; i++) {
            Object_80039F5C *p = fn_80039F5C((unsigned char)team, i);
            if (id == p->mUnknown2908) {
                pResult = p;
                break;
            }
        }
    }
    return pResult;
}

extern "C" Object_80039F5C *fn_8003AD2C(int id)
{
    Object_80039F5C *pResult = 0;
    int value;
    int status;
    int code = 0;

    status = fn_801FCE10(0, "use 'EMAG' select 'DIGP' into \x85 from 'YALP' where 'DIOP' = \x82\n", &value, id);
    if (status != 0 && status != 23) {
        code = status;
    }
    if (status != 23) {
        Object_8003DEC4 *pObject = fn_8003DEE4(value);
        if (pObject != 0) {
            int team = fn_80178308();
            unsigned int i;

            for (i = 0; i < 7; i++) {
                Object_80039F5C *p = fn_80039F5C((unsigned char)team, i);
                if (p != 0 && p->mpUnknown4 == (Block_80170E64 *)pObject) {
                    pResult = p;
                    break;
                }
            }
            if (pResult == 0) {
                team = fn_80178320();
                for (i = 0; i < 7; i++) {
                    Object_80039F5C *p = fn_80039F5C((unsigned char)team, i);
                    if (p != 0 && p->mpUnknown4 == (Block_80170E64 *)pObject) {
                        pResult = p;
                        break;
                    }
                }
            }
        }
    }
    return pResult;
}

extern "C" void fn_8003AE24(Object_80039F5C *p)
{
    Object_8003DEC4 *pObject = fn_8003DEE4(p->mUnknown2908);

    if (pObject == 0) {
        pObject = fn_8003DEC4((p->mId >> 8 & 0xFF) * 7 + (p->mId >> 16 & 0xFF));
    }
    p->mpUnknown4 = (Block_80170E64 *)pObject;
    fn_8009CF30(&p->mUnknown16, &pObject->mUnknown44);
    fn_8009CF30(&p->mUnknown108, &pObject->mUnknown44);
    fn_8009CF30(&p->mUnknown200, &pObject->mUnknown44);
}
