#include "game/Object_8015C244.h"

extern "C" {
void fn_8003F66C(void *p);
void fn_8003F6B0(void *p);
void fn_8003F6B4(void *p, float (*pData)[3], int a);
void fn_8003F6C8(void *p, unsigned char a, unsigned char b, unsigned char c);
void fn_8003F6D8(void *p, float value);
void fn_8003F6E0(void *p, float value);
void fn_8003F6E8(void *p, float value);
int fn_801784C4(void);

void fn_8015A248(Object_8015C244 *p, float *pOut)
{
    Object_80039F5C *pObject = p->mpUnknown208;

    pOut[0] = pObject->mMotion.mPos.mX;
    pOut[1] = pObject->mMotion.mPos.mY;
    p->mUnknown68 = pOut[0];
    p->mUnknown72 = pOut[1];
    if (fn_801784C4()) {
        pOut[1] = -pOut[1];
        pOut[0] = -pOut[0];
    }
}

void fn_8015A2B4(Object_8015C244 *p)
{
    p->mpUnknown208 = 0;
    fn_8003F66C(p->mUnknown20);
    fn_8003F6B4(p->mUnknown20, p->mUnknown88, 10);
    fn_8003F6D8(p->mUnknown20, 0.1f);
    fn_8003F6C8(p->mUnknown20, 0x80, 0x80, 0);
    fn_8003F6E0(p->mUnknown20, 4.0f);
    fn_8003F6E8(p->mUnknown20, 1.0f);
    p->mUnknown80 = 0;
    p->mUnknown81 = 0;
    p->mUnknown84 = 10;
}

void fn_8015A354(Object_8015C244 *p)
{
    fn_8003F6B0(p->mUnknown20);
    p->mpUnknown208 = 0;
    p->mUnknown80 = 0;
    p->mUnknown81 = 0;
    p->mUnknown84 = 10;
}
}

#ifdef DECOMP_COMPARE
#include "game/Object_8015C244.h"
#include "game/fn_80177FE0.h"
#include "game/State_803EB098.h"
#include "game/fn_8016871C.h"
#include "game/fn_80163E94.h"
#include "game/fn_80178D18.h"
#include "game/fn_80227638.h"
#include "game/fn_802270D4.h"
#include "game/fn_800F06F4.h"

extern "C" {
extern unsigned char lbl_803ECA68;
extern unsigned int lbl_803ECA64;

extern int lbl_803ECA60;
extern Object_8015C244 *lbl_8031C02C[27];
void fn_8015A248(Object_8015C244 *, float *);
void fn_8015A2B4(Object_8015C244 *);
void fn_8015A354(Object_8015C244 *);
int fn_801784C4(void);
int fn_80178308(void);
Object_800670B4 *fn_80168708(int);
Record_8011F4E0 *fn_8011F4E0(void);
float fn_8011F4D4(void);
int fn_801650DC(void);
int fn_8011E9D8(void *);
void fn_800F0910(int, void *);
unsigned char fn_800FC014(Object_80039F5C *, void *);
Object_80039F5C *fn_800FC070(Object_80039F5C *, void *);
void fn_8009E9EC(int, int, Point_8017886C *);
float fn_80178A08(void);
float fn_80178A44(void);
void fn_8003F6F0(void *, void *);
void fn_8003F6C8(void *, unsigned char, unsigned char, unsigned char);
void fn_8003F744(void *);
void fn_8003F754(void *, int, int, float, float);
void fn_8019CBC0(void *);
void fn_80227538(void *, int, float);
void fn_8022765C(void *, void *, void *);
void fn_80227690(void *, void *, void *);
int fn_801CFE40(float, float);
int fn_801CFFD0(int, int);
void *fn_801C1F94(void *, int, unsigned int);
void fn_8012CB98(int, int, int, void *);
int fn_8012CB50(void *);
int fn_801DCF0C(int, int, int, void (*)(Object_8015C244 *), void (*)(Object_8015C244 *));
void fn_801DCF8C(int);
void fn_801DD0C8(int, int, int, int (*)(Object_8015C244 *));
Object_8015C244 *fn_801DD268(int, int, int, void *);
void fn_801DD3AC(int, Object_8015C244 *, int);
void fn_801DD320(int, Object_8015C244 *);
void fn_80228D58(int);
void fn_80228E18(void);
void fn_8015BCAC(Object_8015C244 *);
int fn_8015BF28(Object_8015C244 *, unsigned char *);

int fn_8015A39C(Object_8015C244 *p)
{
    if (p->mUnknown80 && lbl_803ECA68 == 1) {
        fn_8015BCAC(p);
        fn_8019CBC0(p->mUnknown20);
    }
    return 0;
}

void fn_8015A3EC(Object_8015C244 *p, Vector_80039F5C *pPoint, int angle)
{
    float length = 0.0f;
    int turn = 0;
    if (p->mUnknown84 == 10) return;
    switch (p->mUnknown84) {
    case 0: case 2:
        turn = (unsigned int)(angle - 0x400001) <= 0x7ffffe ? 0x800000 : 0;
        length = 1.0f;
        break;
    case 3:
        turn = (unsigned int)(angle - 0x400001) > 0x7ffffe ? 0x800000 : 0;
        length = 1.0f;
        break;
    case 1: case 4: turn = 0xc00000; length = 0.5f; break;
    case 7:
        turn = (unsigned int)(angle - 0x400001) <= 0x7ffffe ? 0x800000 : 0;
        length = 4.0f;
        break;
    case 8: turn = 0xc00000; length = 1.5f; break;
    case 9: turn = 0xc00000; length = 3.0f; break;
    }
    if (length != 0.0f) {
        if (fn_801784C4()) turn += 0x800000;
        Point_8017886C delta;
        fn_80227538(&delta, turn, length);
        fn_80227638(pPoint, pPoint, &delta);
        fn_8003F6F0(p->mUnknown20, pPoint);
    }
    p->mUnknown84 = 10;
}

void fn_8015A588(Object_8015C244 *p, unsigned char *pCommand,
                 Vector_80039F5C *pPoint, float *pLength, int *pAngle)
{
    int angle;
    float length;
    if (pAngle) { angle = *pAngle; length = *pLength; }
    else { length = (float)(unsigned int)pCommand[1] * 0.125f; angle = (pCommand[2] & 0x7f) << 17; }
    fn_8015A3EC(p, pPoint, angle);
    if (fn_801784C4()) angle += 0x800000;
    Point_8017886C delta;
    fn_80227538(&delta, angle, length);
    fn_80227638(pPoint, pPoint, &delta);
    pPoint->mX = pPoint->mX < -fn_80178A08() ? -fn_80178A08() :
                pPoint->mX > fn_80178A08() ? fn_80178A08() : pPoint->mX;
    pPoint->mY = pPoint->mY < -fn_80178A44() ? -fn_80178A44() :
                pPoint->mY > fn_80178A44() ? fn_80178A44() : pPoint->mY;
    fn_8003F6F0(p->mUnknown20, pPoint);
}

void fn_8015A6E0(Object_8015C244 *p, unsigned char *pCommand, Vector_80039F5C *pPoint)
{
    unsigned char index = pCommand[1];
    if (pCommand[0] == 92) index += 14;
    Point_8017886C origin = fn_80177FE0();
    Point_8017886C target;
    fn_8009E9EC(0, index, &target);
    if (pCommand[0] == 40 && target.mY - origin.mY > 25.0f)
        target.mY = origin.mY + 25.0f;
    if (fn_801784C4()) { target.mY = -target.mY; target.mX = -target.mX; }
    fn_80227690(&target, &target, pPoint);
    float length = fn_802270A4(&target);
    int angle = fn_801CFE40(target.mY, target.mX);
    if (fn_801784C4()) angle = (angle + 0x800000) & 0xffffff;
    fn_8015A588(p, 0, pPoint, &length, &angle);
}

void fn_8015A818(Object_8015C244 *p, unsigned char *pCommand, Vector_80039F5C *pPoint)
{
    Object_80039F5C *pPlayer = p->mpUnknown208;
    Point_8017886C origin = fn_80177FE0();
    fn_8011F4E0();
    unsigned char code = fn_800FC014(pPlayer, pCommand);
    if (code == 254) return;
    if (code == 253 || code == 0) {
        unsigned char command[4];
        fn_801C1F94(command, 0, 4);
        command[0] = 3; command[1] = 24; command[2] = code == 253 ? 96 : 32;
        fn_8015A588(p, command, pPoint, 0, 0);
        return;
    }
    Object_80039F5C *pOther = fn_800FC070(pPlayer, pCommand);
    if (pOther == fn_80039F5C(pOther->mIdBytes[2], 0)) {
        pOther = fn_8016444C(fn_80168708(fn_80178308()));
        if (pOther == fn_80039F5C(pOther->mIdBytes[2], 0)) {
            unsigned int count = fn_80178D18(fn_80178308());
            for (unsigned char i = 0; i < count; ++i) {
                Object_80039F5C *pCandidate = fn_80039F5C(fn_80178308(), i);
                Record_80067338 *pRecord = fn_8016871C(fn_80178308());
                void *pCommands = fn_80164EC8(pRecord, fn_80178308(), pCandidate->mIdBytes[1]);
                if (fn_800F06F4(0, pCommands, 18, 0xffff) != 0xffff) {
                    pOther = pCandidate;
                    break;
                }
            }
        }
    }
    float dx = pPlayer->mMotion.mPos.mX - origin.mX;
    float across = pOther->mMotion.mPos.mX - pPlayer->mMotion.mPos.mX;
    float otherDx = pOther->mMotion.mPos.mX - origin.mX;
    if (__builtin_fabsf(across) < 1.5f && __builtin_fabsf(otherDx) < 4.0f) {
        Point_8017886C target;
        target.mY = pOther->mMotion.mPos.mY;
        target.mX = 1.5f - __builtin_fabsf(across);
        if (dx < 0.5f) target.mX = -target.mX;
        target.mX += pOther->mMotion.mPos.mX;
        if (fn_801784C4()) { target.mX = -target.mX; target.mY = -target.mY; }
        Point_8017886C delta;
        fn_80227690(&delta, &target, pPoint);
        float length = fn_802270A4(&delta);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        if (fn_801784C4()) angle = (angle + 0x800000) & 0xffffff;
        fn_8015A588(p, 0, pPoint, &length, &angle);
    }
    Point_8017886C target;
    target.mX = pOther->mMotion.mPos.mX;
    target.mY = pOther->mMotion.mPos.mY;
    if (fn_801784C4()) { target.mX = -target.mX; target.mY = -target.mY; }
    Point_8017886C delta;
    fn_80227690(&delta, &target, pPoint);
    float length = fn_802270A4(&delta);
    int angle = fn_801CFE40(delta.mY, delta.mX);
    if (fn_801784C4()) angle = (angle + 0x800000) & 0xffffff;
    fn_8015A588(p, 0, pPoint, &length, &angle);
}

void fn_8015AB84(Object_8015C244 *p, float distance,
                unsigned char *pCommand, Vector_80039F5C *pPoint)
{
    if (fn_801784C4()) distance = -distance;
    pPoint->mY += distance;
    fn_8003F6F0(p->mUnknown20, pPoint);
}

void fn_8015ABE4(Object_8015C244 *p, Vector_80039F5C *pPoint)
{
    float length = 1.0f;
    if (fn_801784C4()) length = -1.0f;
    unsigned short index = fn_800F06F4(0, p->mpUnknown76, 19, 0xffff);
    int angle = index != 0xffff ? p->mpUnknown76[index * 4 + 2] << 17 : 0x400000;
    int turn;
    if (fn_801CFFD0(angle, 0) <= 0x3fffff) turn = angle - 0x400000;
    else if (fn_801CFFD0(angle, 0) > 0x400000) turn = angle + 0x400000;
    else turn = pPoint->mX < fn_80177FE0().mX ? 0x800000 : 0;
    float point[3];
    fn_80227538(point, turn, length);
    point[2] = 0.0f;
    fn_8022765C(point, point, pPoint);
    fn_8003F6F0(p->mUnknown20, point);
    fn_80227538(point, angle, length);
    point[2] = 0.0f;
    fn_8022765C(pPoint, pPoint, point);
    fn_8003F6F0(p->mUnknown20, pPoint);
}

void fn_8015AD50(Object_8015C244 *p, Vector_80039F5C *pPoint)
{
    Object_80039F5C *pPlayer = p->mpUnknown208;
    Object_80039F5C *pOther = fn_80039F5C(fn_80178308(), 0);
    Point_8017886C origin = fn_80177FE0();
    float across = pOther->mMotion.mPos.mX - pPlayer->mMotion.mPos.mX;
    float dx = pPlayer->mMotion.mPos.mX - origin.mX;
    float otherDx = pOther->mMotion.mPos.mX - origin.mX;
    if (__builtin_fabsf(across) < 1.5f && __builtin_fabsf(otherDx) < 4.0f) {
        Point_8017886C target;
        target.mY = pOther->mMotion.mPos.mY;
        target.mX = 1.5f - __builtin_fabsf(across);
        if (dx < 0.0f) target.mX = -target.mX;
        target.mX += pOther->mMotion.mPos.mX;
        if (fn_801784C4()) { target.mX = -target.mX; target.mY = -target.mY; }
        Point_8017886C delta;
        fn_80227690(&delta, &target, pPoint);
        float length = fn_802270A4(&delta);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        if (fn_801784C4()) angle = (angle + 0x800000) & 0xffffff;
        fn_8015A588(p, 0, pPoint, &length, &angle);
    }
    Point_8017886C target;
    target.mX = pOther->mMotion.mPos.mX;
    target.mY = pOther->mMotion.mPos.mY;
    if (fn_801784C4()) { target.mX = -target.mX; target.mY = -target.mY; }
    Point_8017886C delta;
    fn_80227690(&delta, &target, pPoint);
    float length = fn_802270A4(&delta);
    int angle = fn_801CFE40(delta.mY, delta.mX);
    if (fn_801784C4()) angle = (angle + 0x800000) & 0xffffff;
    fn_8015A588(p, 0, pPoint, &length, &angle);
}

void fn_8015AF48(Object_8015C244 *p, unsigned char *pCommand, Vector_80039F5C *pPoint)
{
    Point_8017886C delta;
    switch (pCommand[1]) {
    case 5: case 7: case 11: {
        fn_8012CB98(pCommand[1], pCommand[0], 0x400000, &delta);
        float length = fn_802270A4(&delta) * 0.5f;
        unsigned char command[4];
        fn_801C1F94(command, 0, 4);
        command[0] = 20; command[1] = pCommand[0]; command[2] = pCommand[1];
        int angle = fn_8012CB50(command);
        if (pCommand[1] != 7) {
            fn_80227538(&delta, fn_801784C4() ? 0xc00000 : 0x400000, length);
            pPoint->mX += delta.mX; pPoint->mY += delta.mY;
            fn_8003F6F0(p->mUnknown20, pPoint);
        }
        fn_80227538(&delta, angle + (fn_801784C4() ? 0xc00000 : 0x400000), length);
        pPoint->mX += delta.mX; pPoint->mY += delta.mY;
        fn_8003F6F0(p->mUnknown20, pPoint);
        break;
    }
    case 8:
        if (pCommand[0] == 2) fn_80227538(&delta, fn_801784C4() ? 0x200000 : 0xa00000, 1.5f);
        else fn_80227538(&delta, fn_801784C4() ? 0x600000 : 0xe00000, 1.5f);
        pPoint->mX += delta.mX; pPoint->mY += delta.mY;
        fn_8003F6F0(p->mUnknown20, pPoint);
        break;
    case 9:
        if (pCommand[0] == 2) {
            fn_80227538(&delta, fn_801784C4() ? 0 : 0x800000, 1.5f);
            pPoint->mX += delta.mX; pPoint->mY += delta.mY;
            fn_8003F6F0(p->mUnknown20, pPoint);
            fn_80227538(&delta, fn_801784C4() ? 0xa00000 : 0x200000, 1.5f);
        } else {
            fn_80227538(&delta, fn_801784C4() ? 0x800000 : 0, 1.5f);
            pPoint->mX += delta.mX; pPoint->mY += delta.mY;
            fn_8003F6F0(p->mUnknown20, pPoint);
            fn_80227538(&delta, fn_801784C4() ? 0xe00000 : 0x600000, 1.5f);
        }
        pPoint->mX += delta.mX; pPoint->mY += delta.mY;
        fn_8003F6F0(p->mUnknown20, pPoint);
        break;
    }
}

int fn_8015B344(Object_8015C244 *p, unsigned char *pCommand, Vector_80039F5C *pPoint, int hasOther)
{
    int more = 1;
    switch (pCommand[0]) {
    case 30:
        fn_8015A248(p, &pPoint->mX);
        more = 0;
    case 3: case 4: case 19: case 26: case 27: case 68: case 72:
        fn_8015A588(p, pCommand, pPoint, 0, 0);
        break;
    case 20: fn_8015AF48(p, pCommand + 1, pPoint); break;
    case 52:
        p->mUnknown84 = pCommand[1];
        if (p->mUnknown84 == 7) fn_8015A3EC(p, pPoint, pCommand[2] << 17);
        else if (p->mUnknown84 == 8 || p->mUnknown84 == 9) {
            unsigned char command[4];
            fn_801C1F94(command, 0, 4);
            command[0] = 3; command[1] = 8;
            command[2] = p->mUnknown68 > fn_80177FE0().mX ? 64 : 0;
            fn_8015A588(p, command, pPoint, 0, 0);
        }
        break;
    case 47:
        if (hasOther) fn_8015ABE4(p, pPoint);
        else fn_8015A588(p, pCommand, pPoint, 0, 0);
        break;
    case 31:
        if (hasOther) fn_8015ABE4(p, pPoint);
        else fn_8015AB84(p, -1.0f, pCommand + 1, pPoint);
        break;
    case 33: fn_8015AB84(p, 1.0f, pCommand + 1, pPoint); break;
    case 91:
        if (p->mUnknown84 == 7) break;
    case 1: {
        if (*(unsigned int *)p->mUnknown20 > 1) break;
        Point_8017886C point = {pPoint->mX, pPoint->mY};
        if (fn_801784C4()) { point.mX = -point.mX; point.mY = -point.mY; }
        Point_8017886C target;
        target.mX = fn_8011F4D4();
        Point_8017886C origin = fn_80177FE0();
        target.mY = origin.mY;
        fn_80227690(&target, &target, &point);
        int angle = fn_801CFE40(target.mY, target.mX);
        if (fn_801CFFD0(angle, 0x400000) > 0x3fffff) break;
        float length = fn_802270A4(&target);
        fn_8015A588(p, 0, pPoint, &length, &angle);
        break;
    }
    case 90: {
        if (*(unsigned int *)p->mUnknown20 > 1) break;
        Point_8017886C point = {pPoint->mX, pPoint->mY};
        if (fn_801784C4()) { point.mX = -point.mX; point.mY = -point.mY; }
        Point_8017886C target;
        target.mX = fn_8011F4D4() + (signed char)pCommand[1] * 0.0625f;
        if (target.mX < fn_80177FE0().mX) target.mX -= -2.0f;
        else target.mX += -2.0f;
        target.mY = fn_80177FE0().mY + (signed char)pCommand[2] * 0.0625f + -2.0f;
        fn_80227690(&target, &target, &point);
        int angle = fn_801CFE40(target.mY, target.mX);
        float length = fn_802270A4(&target);
        fn_8015A588(p, 0, pPoint, &length, &angle);
        p->mUnknown64 = 1;
        break;
    }
    case 85:
        fn_8015A248(p, &pPoint->mX);
        more = 0;
        fn_8015AD50(p, pPoint);
        break;
    case 40: case 92:
        fn_8015A248(p, &pPoint->mX);
        fn_8015A6E0(p, pCommand, pPoint);
        break;
    case 22:
        fn_8015A248(p, &pPoint->mX);
        fn_8015A818(p, pCommand, pPoint);
        break;
    }
    return more;
}

void fn_8015B834(Object_8015C244 *p, unsigned char *pCommand, int hasOther)
{
    if (pCommand[0] == 22) fn_8015BF28(p, pCommand);
    float length = 0.0f;
    int style = 4;
    switch (pCommand[0]) {
    case 1: case 2: case 3: case 4: case 6: case 27: case 68: case 91:
        if (hasOther) fn_8003F6C8(p->mUnknown20, 250, 250, 250);
        else fn_8003F6C8(p->mUnknown20, 224, 141, 18);
        style = 0; break;
    case 90:
        if (hasOther) fn_8003F6C8(p->mUnknown20, 250, 250, 250);
        else fn_8003F6C8(p->mUnknown20, 250, 250, 250);
        style = 0; break;
    case 18: case 25: case 26:
        fn_8003F6C8(p->mUnknown20, 250, 250, 250);
        style = 0; break;
    case 19: case 20: case 21:
        if (hasOther) fn_8003F6C8(p->mUnknown20, 250, 250, 250);
        else fn_8003F6C8(p->mUnknown20, 250, 250, 250);
        style = 0; break;
    case 31: case 33: case 47: case 72:
        if (hasOther) fn_8003F6C8(p->mUnknown20, 250, 250, 250);
        else fn_8003F6C8(p->mUnknown20, 250, 250, 250);
        style = 1; break;
    case 30:
        fn_8003F6C8(p->mUnknown20, 224, 141, 18);
        style = 0; break;
    case 40: case 92: {
        fn_8003F6C8(p->mUnknown20, 224, 141, 18);
        int index = pCommand[1];
        if (pCommand[0] == 92) index += 14;
        int origin = pCommand[0] == 92 ? 14 : 0;
        switch (index - origin) {
        case 0: fn_8003F754(p->mUnknown20, 2, 0, 8.0f, fn_80178A08()); break;
        case 1: case 2: fn_8003F754(p->mUnknown20, 2, 0, 6.0f, fn_80178A08() * 0.5f); break;
        case 3: case 4: case 5: fn_8003F754(p->mUnknown20, 2, 0, 4.5f, fn_80178A08() * 0.333333343f); break;
        case 6: case 7: case 8: case 9: fn_8003F754(p->mUnknown20, 2, 0, 3.0f, fn_80178A08() * 0.25f); break;
        }
        return;
    }
    case 22: fn_8003F6C8(p->mUnknown20, 250, 250, 250); break;
    case 85: fn_8003F6C8(p->mUnknown20, 224, 141, 18); break;
    case 52: return;
    }
    fn_8003F754(p->mUnknown20, style, 0, length, length);
}

void fn_8015BCAC(Object_8015C244 *p)
{
    Object_80039F5C *pPlayer = p->mpUnknown208;
    fn_8003F744(p->mUnknown20);
    Vector_80039F5C point;
    point.mX = p->mUnknown68;
    point.mY = p->mUnknown72;
    point.mZ = 0.0f;
    if (fn_801784C4()) { point.mY = -point.mY; point.mX = -point.mX; }
    fn_8003F6F0(p->mUnknown20, &point);
    unsigned char *pCommand = p->mpUnknown76;
    int hasOther = fn_8011E9D8(pCommand);
    unsigned char command[4];
    int more;
    do {
        *(unsigned int *)command = *(unsigned int *)pCommand;
        command[0] &= 0x7f;
        if (p->mUnknown81) fn_800F0910(0, command);
        if (command[0]) {
            more = ((pCommand[0] >> 7) ^ 1) & fn_8015B344(p, command, &point, hasOther);
            pCommand += 4;
            if (!pCommand[0]) more = 0;
        } else more = 0;
    } while (more);
    fn_8015B834(p, command, hasOther);
    Record_80067338 *pRecord = fn_8016871C(pPlayer->mIdBytes[2]);
    if (fn_801650DC()) {
        for (unsigned char i = 0; i <= 2; ++i) {
            if (pPlayer->mIdBytes[1] == pRecord->mUnknown1C[i][0]) {
                unsigned short index = fn_800F06F4(0, p->mpUnknown76, 19, 0xffff);
                if (index == 0xffff && fn_800F06F4(0, p->mpUnknown76, 21, 0xffff) == index) continue;
                switch (i) {
                case 0: fn_8003F6C8(p->mUnknown20, 205, 8, 16); break;
                case 1: fn_8003F6C8(p->mUnknown20, 0, 169, 95); break;
                case 2: fn_8003F6C8(p->mUnknown20, 160, 160, 160); break;
                }
            }
        }
    }
}

void fn_8015BED4(void)
{
    fn_801DCF0C(14, sizeof(Object_8015C244), 27, fn_8015A2B4, fn_8015A354);
    fn_801DD0C8(lbl_803ECA60, 14, 0, fn_8015A39C);
}

int fn_8015BF28(Object_8015C244 *p, unsigned char *pCommand)
{
    Object_80039F5C *pPlayer = p->mpUnknown208;
    Record_8011F4E0 *pInfo = fn_8011F4E0();
    int code;
    if (pInfo->mUnknown4) {
        code = pInfo->mUnknown32[pPlayer->mIdBytes[1]];
        if (code == 255) code = 253;
    } else code = pCommand[1];
    switch (code) {
    case 253: return 2;
    case 254: return 85;
    default: return 22;
    }
}

void fn_8015BFAC(void)
{
    fn_80228E18();
    fn_801DCF8C(14);
}

Object_8015C244 *fn_8015BFD4(void)
{
    Object_8015C244 *p = fn_801DD268(lbl_803ECA60, 14, 0, 0);
    fn_801DD3AC(lbl_803ECA60, p, 3);
    return p;
}

void fn_8015C024(Object_8015C244 *p)
{
    if (p) {
        fn_801DD320(lbl_803ECA60, p);
        fn_80228D58((int)p);
    }
}

void fn_8015C064(int handle)
{
    lbl_803ECA60 = handle;
    fn_8015BED4();
    Object_8015C244 **p = lbl_8031C02C;
    Object_8015C244 **pLast = p + 26;
    do { *p++ = fn_8015BFD4(); } while (p <= pLast);
    lbl_803ECA64 = 0;
    lbl_803ECA68 = 1;
}

void fn_8015C0C0(void)
{
    Object_8015C244 **p = lbl_8031C02C;
    Object_8015C244 **pLast = p + 26;
    do { fn_8015C024(*p++); } while (p <= pLast);
    lbl_803ECA60 = 0;
    fn_8015BFAC();
    lbl_803ECA64 = 0;
}

void fn_8015C114(void)
{
    for (int i = 0; i < 27; ++i) {
        Object_8015C244 *p = lbl_8031C02C[i];
        if (p->mpUnknown208) {
            if (p->mUnknown48 > 0.1f) p->mUnknown48 *= 0.88f;
            else p->mUnknown48 = 0.1f;
        }
    }
}

Object_8015C244 *fn_8015C170(Object_80039F5C *pPlayer, Point_8017886C *pPoint,
                            unsigned char *pCommands, unsigned char flag)
{
    Object_8015C244 *p = 0;
    for (int i = 0; i < 27; ++i) {
        if (!lbl_8031C02C[i]->mpUnknown208) {
            ++lbl_803ECA64;
            lbl_8031C02C[i]->mUnknown80 = 1;
            lbl_8031C02C[i]->mUnknown81 = flag;
            lbl_8031C02C[i]->mUnknown84 = 10;
            lbl_8031C02C[i]->mpUnknown208 = pPlayer;
            __builtin_memcpy(&lbl_8031C02C[i]->mUnknown68, pPoint, sizeof(*pPoint));
            lbl_8031C02C[i]->mpUnknown76 = pCommands;
            p = lbl_8031C02C[i];
            break;
        }
    }
    p->mUnknown48 = 0.1f;
    return p;
}

void fn_8015C218(Object_8015C244 *p)
{
    p->mUnknown80 = 0;
    p->mUnknown81 = 0;
    p->mUnknown84 = 10;
    p->mpUnknown208 = 0;
    --lbl_803ECA64;
}

void fn_8015C244(Object_8015C244 *p)
{
    p->mUnknown48 = 0.6f;
}

void fn_8015C254(int value)
{
    lbl_803ECA68 = value;
}
}
#endif
