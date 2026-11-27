/* Route arrows: the arrows drawn on the field that show each player's route from his play
   commands (runs, cuts, blocks and zones) while the play is chosen or previewed. A pool of 27
   arrow objects is kept in the game object list and handed out per shown player. */

#include "game/RouteArrow.h"

extern "C" {
void ArrowInit(void *p);
void ArrowShutdown(void *p);
void ArrowSetPointBuffer(void *p, float (*pData)[3], int a);
void ArrowSetColor(void *p, unsigned char a, unsigned char b, unsigned char c);
void ArrowSetWidth(void *p, float value);
void ArrowSetEndWidth(void *p, float value);
void ArrowSetEndBrightness(void *p, float value);
int ScrmIsFieldFlipped(void);

void RouteArrowStartAtPlayer(RouteArrow_t *p, float *pOut)
{
    Object_80039F5C *pObject = p->mpPlayer;

    pOut[0] = pObject->mMotion.mPos.mX;
    pOut[1] = pObject->mMotion.mPos.mY;
    p->mStartX = pOut[0];
    p->mStartY = pOut[1];
    if (ScrmIsFieldFlipped()) {
        pOut[1] = -pOut[1];
        pOut[0] = -pOut[0];
    }
}

void RouteArrowInit(RouteArrow_t *p)
{
    p->mpPlayer = 0;
    ArrowInit(p->mArrow);
    ArrowSetPointBuffer(p->mArrow, p->mPoints, 10);
    ArrowSetWidth(p->mArrow, 0.1f);
    ArrowSetColor(p->mArrow, 0x80, 0x80, 0);
    ArrowSetEndWidth(p->mArrow, 4.0f);
    ArrowSetEndBrightness(p->mArrow, 1.0f);
    p->mbShown = 0;
    p->mbFlip = 0;
    p->mPendingTurn = 10;
}

void RouteArrowShutdown(RouteArrow_t *p)
{
    ArrowShutdown(p->mArrow);
    p->mpPlayer = 0;
    p->mbShown = 0;
    p->mbFlip = 0;
    p->mPendingTurn = 10;
}
}

#include "game/RouteArrow.h"
#include "game/ScrmGetBallSpot.h"
#include "game/State_803EB098.h"
#include "game/PlayBookGetPlay.h"
#include "game/PlaySet.h"
#include "game/ScrmGetTeamPlayerCount.h"
#include "game/Vec2Add.h"
#include "game/Vec3Magnitude.h"
#include "game/fn_800F06F4.h"

static int _RouteArrow_iObjList;
static unsigned int _RouteArrow_uNumShown;
static unsigned char _RouteArrow_bEnabled;
static RouteArrow_t *_RouteArrow_apArrows[27];

extern "C" {
void RouteArrowStartAtPlayer(RouteArrow_t *, float *);
void RouteArrowInit(RouteArrow_t *);
void RouteArrowShutdown(RouteArrow_t *);
int ScrmIsFieldFlipped(void);
int ScrmGetOffenseTeam(void);
PlayBookFormation_t *PlayBookGetFormation(int);
Record_8011F4E0 *fn_8011F4E0(void);
float fn_8011F4D4(void);
int PlayAlignHasSlots(PlayBookPlay_t *pRecord);
int fn_8011E9D8(void *);
void fn_800F0910(int, void *);
int fn_800FC014(Object_80039F5C *, void *);
Object_80039F5C *fn_800FC070(Object_80039F5C *, void *);
void fn_8009E9EC(int, int, FieldPoint_t *);
float ScrmGetSidelineX(void);
float ScrmGetEndLineY(void);
void ArrowAddPoint(void *, void *);
void ArrowSetColor(void *, unsigned char, unsigned char, unsigned char);
void ArrowReset(void *);
void ArrowSetEnd(void *, int, int, float, float);
void ArrowDraw(void *);
void Vec2FromAngle(void *, int, float);
void Vec3Add(void *, void *, void *);
void Vec2Sub(void *, void *, void *);
int MathArcTan2(float, float);
int MathAngleDiff(int, int);
void *memset(void *, int, unsigned int);
void PlayerCutGetAnimOffset(int, unsigned char, int, void *);
int PlayerCutGetMessageTurn(void *);
int ObjNewType_(int, int, int, void (*)(RouteArrow_t *), void (*)(RouteArrow_t *));
int ObjDelType(int);
void ObjSetListObjFunc(int, int, int, int (*)(RouteArrow_t *));
RouteArrow_t *ObjNewInList(int, int, int, void *);
void ObjSetPriority(int, RouteArrow_t *, int);
void ObjRemoveFromList(int, RouteArrow_t *);
void VptTrashObject(int);
void VptFlushObjectTrashSync(void);
void RouteArrowBuild(RouteArrow_t *);
int RouteArrowGetBlockCommand(RouteArrow_t *, unsigned char *);

int RouteArrowDraw(RouteArrow_t *p)
{
    if (p->mbShown && _RouteArrow_bEnabled == 1) {
        RouteArrowBuild(p);
        ArrowDraw(p->mArrow);
    }
    return 0;
}

void RouteArrowFlushTurn(RouteArrow_t *p, Vector_80039F5C *pPoint, int angle)
{
    float length = 0.0f;
    int turn = 0;
    if (p->mPendingTurn == 10) return;
    switch (p->mPendingTurn) {
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
    case 5: case 6: break;
    }
    if (length != 0.0f) {
        if (ScrmIsFieldFlipped()) turn += 0x800000;
        FieldPoint_t delta;
        Vec2FromAngle(&delta, turn, length);
        Vec2Add(pPoint, pPoint, &delta);
        ArrowAddPoint(p->mArrow, pPoint);
    }
    p->mPendingTurn = 10;
}

void RouteArrowAddSegment(RouteArrow_t *p, unsigned char *pCommand,
                 Vector_80039F5C *pPoint, float *pLength, int *pAngle)
{
    int angle;
    float length;
    if (pAngle) { angle = *pAngle; length = *pLength; }
    else { length = (float)(unsigned int)pCommand[1] * 0.125f; angle = (pCommand[2] & 0x7f) << 17; }
    RouteArrowFlushTurn(p, pPoint, angle);
    if (ScrmIsFieldFlipped()) angle += 0x800000;
    FieldPoint_t delta;
    Vec2FromAngle(&delta, angle, length);
    Vec2Add(pPoint, pPoint, &delta);
    pPoint->mX = pPoint->mX < -ScrmGetSidelineX() ? -ScrmGetSidelineX() :
                pPoint->mX > ScrmGetSidelineX() ? ScrmGetSidelineX() : pPoint->mX;
    pPoint->mY = pPoint->mY < -ScrmGetEndLineY() ? -ScrmGetEndLineY() :
                pPoint->mY > ScrmGetEndLineY() ? ScrmGetEndLineY() : pPoint->mY;
    ArrowAddPoint(p->mArrow, pPoint);
}

void RouteArrowAddToSpot(RouteArrow_t *p, unsigned char *pCommand, Vector_80039F5C *pPoint)
{
    unsigned char index = pCommand[1];
    if (pCommand[0] == 92) index += 14;
    FieldPoint_t origin;
    FieldPoint_t target;
    origin = ScrmGetBallSpot();
    fn_8009E9EC(0, index, &target);
    if (pCommand[0] == 40 && target.mY - origin.mY > 25.0f)
        target.mY = origin.mY + 25.0f;
    if (ScrmIsFieldFlipped()) { target.mY = -target.mY; target.mX = -target.mX; }
    Vec2Sub(&target, &target, pPoint);
    float length = Vec2Magnitude(&target);
    int angle = MathArcTan2(target.mY, target.mX);
    if (ScrmIsFieldFlipped()) angle = (angle + 0x800000) & 0xffffff;
    RouteArrowAddSegment(p, 0, pPoint, &length, &angle);
}

struct RouteArrowCmd_t {
    unsigned char mType;
    unsigned char mArgs[3];
};

void RouteArrowAddBlockPath(RouteArrow_t *p, unsigned char *pCommand, Vector_80039F5C *pPoint)
{
    RouteArrowCmd_t command;
    Object_80039F5C *pPlayer = p->mpPlayer;
    FieldPoint_t origin;
    origin = ScrmGetBallSpot();
    fn_8011F4E0();
    unsigned char code = fn_800FC014(pPlayer, pCommand);
    switch (code) {
    case 254:
        return;
    case 253:
        memset(&command, 0, 4);
        command.mType = 3; command.mArgs[0] = 24; command.mArgs[1] = 96;
        RouteArrowAddSegment(p, &command.mType, pPoint, 0, 0);
        return;
    case 0:
        memset(&command, 0, 4);
        command.mType = 3; command.mArgs[0] = 24; command.mArgs[1] = 32;
        RouteArrowAddSegment(p, &command.mType, pPoint, 0, 0);
        return;
    }
    Object_80039F5C *pOther = fn_800FC070(pPlayer, pCommand);
    if (pOther == PlyrGet(pOther->mIdBytes[2], 0)) {
        pOther = PlaySetGetKeyPlayer(PlayBookGetFormation(ScrmGetOffenseTeam()));
        if (pOther == PlyrGet(pOther->mIdBytes[2], 0)) {
            unsigned char i = 0;
            unsigned int count = ScrmGetTeamPlayerCount(ScrmGetOffenseTeam());
            if (i < count) do {
                Object_80039F5C *pCandidate = PlyrGet(ScrmGetOffenseTeam(), i);
                PlayBookPlay_t *pRecord = PlayBookGetPlay(ScrmGetOffenseTeam());
                void *pCommands = PlayAlignGetRoute(pRecord, ScrmGetOffenseTeam(), pCandidate->mIdBytes[1]);
                if (fn_800F06F4(0, pCommands, 18, 0xffff) != 0xffff) {
                    pOther = pCandidate;
                    break;
                }
            } while (++i < count);
        }
    }
    float dx = pPlayer->mMotion.mPos.mX - origin.mX;
    float across = pOther->mMotion.mPos.mX - pPlayer->mMotion.mPos.mX;
    float otherDx = pOther->mMotion.mPos.mX - origin.mX;
    FieldPoint_t target;
    FieldPoint_t delta;
    float length;
    int angle;
    if (__builtin_fabsf(across) < 1.5f && __builtin_fabsf(otherDx) < 4.0f) {
        target.mY = pOther->mMotion.mPos.mY;
        target.mX = 1.5f - __builtin_fabsf(across);
        if (dx < 0.5f) target.mX = -target.mX;
        target.mX += pOther->mMotion.mPos.mX;
        if (ScrmIsFieldFlipped()) { target.mX = -target.mX; target.mY = -target.mY; }
        Vec2Sub(&delta, &target, pPoint);
        length = Vec2Magnitude(&delta);
        angle = MathArcTan2(delta.mY, delta.mX);
        if (ScrmIsFieldFlipped()) angle = (angle + 0x800000) & 0xffffff;
        RouteArrowAddSegment(p, 0, pPoint, &length, &angle);
    }
    target.mX = pOther->mMotion.mPos.mX;
    target.mY = pOther->mMotion.mPos.mY;
    if (ScrmIsFieldFlipped()) { target.mX = -target.mX; target.mY = -target.mY; }
    Vec2Sub(&delta, &target, pPoint);
    length = Vec2Magnitude(&delta);
    angle = MathArcTan2(delta.mY, delta.mX);
    if (ScrmIsFieldFlipped()) angle = (angle + 0x800000) & 0xffffff;
    RouteArrowAddSegment(p, 0, pPoint, &length, &angle);
}

void RouteArrowAddStraight(RouteArrow_t *p, float distance,
                unsigned char *pCommand, Vector_80039F5C *pPoint)
{
    if (ScrmIsFieldFlipped()) distance = -distance;
    pPoint->mY += distance;
    ArrowAddPoint(p->mArrow, pPoint);
}

void RouteArrowAddHook(RouteArrow_t *p, Vector_80039F5C *pPoint)
{
    float length = 1.0f;
    if (ScrmIsFieldFlipped()) length = -1.0f;
    unsigned short index = fn_800F06F4(0, p->mpCommands, 19, 0xffff);
    int angle = index != 0xffff ? p->mpCommands[index * 4 + 2] << 17 : 0x400000;
    int turn;
    if (MathAngleDiff(angle, 0) <= 0x3fffff) turn = angle - 0x400000;
    else if (MathAngleDiff(angle, 0) > 0x400000) turn = angle + 0x400000;
    else turn = pPoint->mX < ScrmGetBallSpot().mX ? 0x800000 : 0;
    float point[3];
    Vec2FromAngle(point, turn, length);
    point[2] = 0.0f;
    Vec3Add(point, point, pPoint);
    ArrowAddPoint(p->mArrow, point);
    Vec2FromAngle(point, angle, length);
    point[2] = 0.0f;
    Vec3Add(pPoint, pPoint, point);
    ArrowAddPoint(p->mArrow, pPoint);
}

void RouteArrowAddToQuarterback(RouteArrow_t *p, Vector_80039F5C *pPoint)
{
    Object_80039F5C *pPlayer = p->mpPlayer;
    Object_80039F5C *pOther = PlyrGet(ScrmGetOffenseTeam(), 0);
    FieldPoint_t origin = ScrmGetBallSpot();
    float across = pOther->mMotion.mPos.mX - pPlayer->mMotion.mPos.mX;
    float otherDx = pOther->mMotion.mPos.mX - origin.mX;
    float dx = pPlayer->mMotion.mPos.mX - origin.mX;
    FieldPoint_t target, delta;
    float length;
    int angle;
    if (__builtin_fabsf(across) < 1.5f && __builtin_fabsf(otherDx) < 4.0f) {
        target.mY = pOther->mMotion.mPos.mY;
        target.mX = 1.5f - __builtin_fabsf(across);
        if (dx < 0.0f) target.mX = -target.mX;
        target.mX += pOther->mMotion.mPos.mX;
        if (ScrmIsFieldFlipped()) { target.mX = -target.mX; target.mY = -target.mY; }
        Vec2Sub(&delta, &target, pPoint);
        length = Vec2Magnitude(&delta);
        angle = MathArcTan2(delta.mY, delta.mX);
        if (ScrmIsFieldFlipped()) angle = (angle + 0x800000) & 0xffffff;
        RouteArrowAddSegment(p, 0, pPoint, &length, &angle);
    }
    target.mX = pOther->mMotion.mPos.mX;
    target.mY = pOther->mMotion.mPos.mY;
    if (ScrmIsFieldFlipped()) { target.mX = -target.mX; target.mY = -target.mY; }
    Vec2Sub(&delta, &target, pPoint);
    length = Vec2Magnitude(&delta);
    angle = MathArcTan2(delta.mY, delta.mX);
    if (ScrmIsFieldFlipped()) angle = (angle + 0x800000) & 0xffffff;
    RouteArrowAddSegment(p, 0, pPoint, &length, &angle);
}

void RouteArrowAddCut(RouteArrow_t *p, unsigned char *pCommand, Vector_80039F5C *pPoint)
{
    FieldPoint_t delta;
    switch (pCommand[1]) {
    case 5: case 7: case 11: {
        PlayerCutGetAnimOffset(pCommand[1], pCommand[0], 0x400000, &delta);
        float length = Vec2Magnitude(&delta) * 0.5f;
        RouteArrowCmd_t command;
        memset(&command, 0, 4);
        command.mType = 20; command.mArgs[1] = pCommand[1]; command.mArgs[0] = pCommand[0];
        int angle = PlayerCutGetMessageTurn(&command.mType);
        if (pCommand[1] != 7) {
            if (ScrmIsFieldFlipped()) Vec2FromAngle(&delta, 0xc00000, length);
            else Vec2FromAngle(&delta, 0x400000, length);
            pPoint->mX += delta.mX; pPoint->mY += delta.mY;
            ArrowAddPoint(p->mArrow, pPoint);
        }
        if (ScrmIsFieldFlipped()) Vec2FromAngle(&delta, angle + 0xc00000, length);
        else Vec2FromAngle(&delta, angle + 0x400000, length);
        pPoint->mX += delta.mX; pPoint->mY += delta.mY;
        ArrowAddPoint(p->mArrow, pPoint);
        break;
    }
    case 8:
        if (pCommand[0] == 2) {
            if (ScrmIsFieldFlipped()) Vec2FromAngle(&delta, 0x200000, 1.5f);
            else Vec2FromAngle(&delta, 0xa00000, 1.5f);
            pPoint->mX += delta.mX; pPoint->mY += delta.mY;
            ArrowAddPoint(p->mArrow, pPoint);
        } else {
            if (ScrmIsFieldFlipped()) Vec2FromAngle(&delta, 0x600000, 1.5f);
            else Vec2FromAngle(&delta, 0xe00000, 1.5f);
            pPoint->mX += delta.mX; pPoint->mY += delta.mY;
            ArrowAddPoint(p->mArrow, pPoint);
        }
        break;
    case 10:
        break;
    case 9:
        if (pCommand[0] == 2) {
            if (ScrmIsFieldFlipped()) Vec2FromAngle(&delta, 0, 1.5f);
            else Vec2FromAngle(&delta, 0x800000, 1.5f);
            pPoint->mX += delta.mX; pPoint->mY += delta.mY;
            ArrowAddPoint(p->mArrow, pPoint);
            if (ScrmIsFieldFlipped()) Vec2FromAngle(&delta, 0xa00000, 1.5f);
            else Vec2FromAngle(&delta, 0x200000, 1.5f);
            pPoint->mX += delta.mX; pPoint->mY += delta.mY;
            ArrowAddPoint(p->mArrow, pPoint);
        } else {
            if (ScrmIsFieldFlipped()) Vec2FromAngle(&delta, 0x800000, 1.5f);
            else Vec2FromAngle(&delta, 0, 1.5f);
            pPoint->mX += delta.mX; pPoint->mY += delta.mY;
            ArrowAddPoint(p->mArrow, pPoint);
            if (ScrmIsFieldFlipped()) Vec2FromAngle(&delta, 0xe00000, 1.5f);
            else Vec2FromAngle(&delta, 0x600000, 1.5f);
            pPoint->mX += delta.mX; pPoint->mY += delta.mY;
            ArrowAddPoint(p->mArrow, pPoint);
        }
        break;
    }
}

int RouteArrowAddCommand(RouteArrow_t *p, unsigned char *pCommand, Vector_80039F5C *pPoint, int hasOther)
{
    int more = 1;
    FieldPoint_t target;
    float length;
    int angle;
    switch (pCommand[0]) {
    case 30:
        RouteArrowStartAtPlayer(p, &pPoint->mX);
        more = 0;
    case 3: case 4: case 19: case 26: case 27: case 68: case 72:
        RouteArrowAddSegment(p, pCommand, pPoint, 0, 0);
        break;
    case 20: RouteArrowAddCut(p, pCommand + 1, pPoint); break;
    case 52:
        p->mPendingTurn = pCommand[1];
        if (p->mPendingTurn == 7) RouteArrowFlushTurn(p, pPoint, pCommand[2] << 17);
        else if (p->mPendingTurn == 8 || p->mPendingTurn == 9) {
            RouteArrowCmd_t command;
            memset(&command, 0, 4);
            command.mType = 3; command.mArgs[0] = 8;
            command.mArgs[1] = p->mStartX > ScrmGetBallSpot().mX ? 64 : 0;
            RouteArrowAddSegment(p, &command.mType, pPoint, 0, 0);
        }
        break;
    case 47:
        if (hasOther) RouteArrowAddHook(p, pPoint);
        else RouteArrowAddSegment(p, pCommand, pPoint, 0, 0);
        break;
    case 31:
        if (hasOther) RouteArrowAddHook(p, pPoint);
        else RouteArrowAddStraight(p, -1.0f, pCommand + 1, pPoint);
        break;
    case 33: RouteArrowAddStraight(p, 1.0f, pCommand + 1, pPoint); break;
    case 91:
        if (p->mPendingTurn == 7) break;
    case 1: {
        if (*(unsigned int *)p->mArrow > 1) break;
        FieldPoint_t point;
        point.mX = pPoint->mX;
        point.mY = pPoint->mY;
        if (ScrmIsFieldFlipped()) { point.mX = -point.mX; point.mY = -point.mY; }
        target.mX = fn_8011F4D4();
        FieldPoint_t origin = ScrmGetBallSpot();
        target.mY = origin.mY;
        Vec2Sub(&target, &target, &point);
        angle = MathArcTan2(target.mY, target.mX);
        if (MathAngleDiff(angle, 0x400000) > 0x3fffff) break;
        length = Vec2Magnitude(&target);
        RouteArrowAddSegment(p, 0, pPoint, &length, &angle);
        break;
    }
    case 90: {
        if (*(unsigned int *)p->mArrow > 1) break;
        FieldPoint_t point;
        point.mX = pPoint->mX;
        point.mY = pPoint->mY;
        if (ScrmIsFieldFlipped()) { point.mX = -point.mX; point.mY = -point.mY; }
        target.mX = fn_8011F4D4() + (signed char)pCommand[1] * 0.0625f;
        if (target.mX < ScrmGetBallSpot().mX) target.mX -= -2.0f;
        else target.mX += -2.0f;
        target.mY = ScrmGetBallSpot().mY + (signed char)pCommand[2] * 0.0625f + -2.0f;
        Vec2Sub(&target, &target, &point);
        angle = MathArcTan2(target.mY, target.mX);
        length = Vec2Magnitude(&target);
        RouteArrowAddSegment(p, 0, pPoint, &length, &angle);
        p->mbMotion = 1;
        break;
    }
    case 85:
        RouteArrowStartAtPlayer(p, &pPoint->mX);
        more = 0;
        RouteArrowAddToQuarterback(p, pPoint);
        break;
    case 40: case 92:
        RouteArrowStartAtPlayer(p, &pPoint->mX);
        RouteArrowAddToSpot(p, pCommand, pPoint);
        break;
    case 22:
        RouteArrowStartAtPlayer(p, &pPoint->mX);
        RouteArrowAddBlockPath(p, pCommand, pPoint);
        break;
    }
    return more;
}

void RouteArrowSetStyle(RouteArrow_t *p, unsigned char *pCommand, int hasOther)
{
    if (pCommand[0] == 22) RouteArrowGetBlockCommand(p, pCommand);
    switch (pCommand[0]) {
    case 1: case 2: case 3: case 4: case 6: case 27: case 68: case 91:
        if (hasOther) ArrowSetColor(p->mArrow, 250, 250, 250);
        else ArrowSetColor(p->mArrow, 224, 141, 18);
        ArrowSetEnd(p->mArrow, 0, 0, 0.0f, 0.0f);
        break;
    case 90:
        if (hasOther) ArrowSetColor(p->mArrow, 250, 250, 250);
        else ArrowSetColor(p->mArrow, 250, 250, 250);
        ArrowSetEnd(p->mArrow, 0, 0, 0.0f, 0.0f);
        break;
    case 18: case 25: case 26:
        ArrowSetColor(p->mArrow, 250, 250, 250);
        ArrowSetEnd(p->mArrow, 0, 0, 0.0f, 0.0f);
        break;
    case 19: case 20: case 21:
        if (hasOther) ArrowSetColor(p->mArrow, 250, 250, 250);
        else ArrowSetColor(p->mArrow, 250, 250, 250);
        ArrowSetEnd(p->mArrow, 0, 0, 0.0f, 0.0f);
        break;
    case 31: case 33: case 47: case 72:
        if (hasOther) ArrowSetColor(p->mArrow, 250, 250, 250);
        else ArrowSetColor(p->mArrow, 250, 250, 250);
        ArrowSetEnd(p->mArrow, 1, 0, 0.0f, 0.0f);
        break;
    case 30:
        ArrowSetColor(p->mArrow, 224, 141, 18);
        ArrowSetEnd(p->mArrow, 0, 0, 0.0f, 0.0f);
        break;
    case 40:
        ArrowSetColor(p->mArrow, 224, 141, 18);
        switch (pCommand[1]) {
        case 0: ArrowSetEnd(p->mArrow, 2, 0, 8.0f, ScrmGetSidelineX()); break;
        case 1: case 2: ArrowSetEnd(p->mArrow, 2, 0, 6.0f, ScrmGetSidelineX() * 0.5f); break;
        case 3: case 4: case 5: ArrowSetEnd(p->mArrow, 2, 0, 4.5f, ScrmGetSidelineX() * 0.333333343f); break;
        case 6: case 7: case 8: case 9: ArrowSetEnd(p->mArrow, 2, 0, 3.0f, ScrmGetSidelineX() * 0.25f); break;
        }
        break;
    case 92:
        ArrowSetColor(p->mArrow, 224, 141, 18);
        switch (pCommand[1] + 14) {
        case 14: ArrowSetEnd(p->mArrow, 2, 0, 8.0f, ScrmGetSidelineX()); break;
        case 15: case 16: ArrowSetEnd(p->mArrow, 2, 0, 6.0f, ScrmGetSidelineX() * 0.5f); break;
        case 17: case 18: case 19: ArrowSetEnd(p->mArrow, 2, 0, 4.5f, ScrmGetSidelineX() * 0.333333343f); break;
        case 20: case 21: case 22: case 23: ArrowSetEnd(p->mArrow, 2, 0, 3.0f, ScrmGetSidelineX() * 0.25f); break;
        }
        break;
    case 22:
        ArrowSetColor(p->mArrow, 250, 250, 250);
        ArrowSetEnd(p->mArrow, 4, 0, 0.0f, 0.0f);
        break;
    case 85:
        ArrowSetColor(p->mArrow, 224, 141, 18);
        ArrowSetEnd(p->mArrow, 4, 0, 0.0f, 0.0f);
        break;
    case 52:
        break;
    default:
        ArrowSetEnd(p->mArrow, 4, 0, 0.0f, 0.0f);
        break;
    }
}

void RouteArrowBuild(RouteArrow_t *p)
{
    Object_80039F5C *pPlayer = p->mpPlayer;
    RouteArrowCmd_t command;
    ArrowReset(p->mArrow);
    Vector_80039F5C point;
    point.mX = p->mStartX;
    point.mY = p->mStartY;
    point.mZ = 0.0f;
    if (ScrmIsFieldFlipped()) { point.mY = -point.mY; point.mX = -point.mX; }
    ArrowAddPoint(p->mArrow, &point);
    unsigned char *pCommand = p->mpCommands;
    int hasOther = fn_8011E9D8(pCommand);
    unsigned char more;
    do {
        command = *(RouteArrowCmd_t *)pCommand;
        command.mType &= 0x7f;
        if (p->mbFlip) fn_800F0910(0, &command.mType);
        if (command.mType) {
            more = (pCommand[0] >> 7) ^ 1;
            more &= RouteArrowAddCommand(p, &command.mType, &point, hasOther);
            pCommand += 4;
            more = pCommand[0] ? more : 0;
        } else more = 0;
    } while (more);
    RouteArrowSetStyle(p, &command.mType, hasOther);
    PlayBookPlay_t *pRecord = PlayBookGetPlay(pPlayer->mIdBytes[2]);
    if (PlayAlignHasSlots(pRecord)) {
        for (unsigned char i = 0; i <= 2; ++i) {
            // FAKEMATCH: slot byte addressed as pRecord + (i << 2) + 0x1C, not *pRecord->mUnknown1C[i]
            if (pPlayer->mIdBytes[1] == *((unsigned char *)pRecord + (i << 2) + 0x1C)) {
                int index = fn_800F06F4(0, p->mpCommands, 19, 0xffff);
                if (index == 0xffff && fn_800F06F4(0, p->mpCommands, 21, 0xffff) == index) continue;
                switch (i) {
                case 0: ArrowSetColor(p->mArrow, 205, 8, 16); break;
                case 1: ArrowSetColor(p->mArrow, 0, 169, 95); break;
                case 2: ArrowSetColor(p->mArrow, 160, 160, 160); break;
                }
            }
        }
    }
}

void RouteArrowRegisterType(void)
{
    ObjNewType_(14, sizeof(RouteArrow_t), 27, RouteArrowInit, RouteArrowShutdown);
    ObjSetListObjFunc(_RouteArrow_iObjList, 14, 0, RouteArrowDraw);
}

int RouteArrowGetBlockCommand(RouteArrow_t *p, unsigned char *pCommand)
{
    Object_80039F5C *pPlayer = p->mpPlayer;
    Record_8011F4E0 *pInfo = fn_8011F4E0();
    int code;
    if (pInfo->mUnknown4) {
        code = pInfo->mUnknown32[pPlayer->mIdBytes[1]];
        if (code == 255) code = 253;
    } else code = pCommand[1];
    switch (code) {
    case 254: return 85;
    case 253: return 2;
    // FAKEMATCH: the explicit case 22 keeps the command unchanged like the fall-through; it only
    // shapes the compare tree (the bound check after 253)
    case 22: break;
    }
    return 22;
}

void RouteArrowUnregisterType(void)
{
    VptFlushObjectTrashSync();
    ObjDelType(14);
}

RouteArrow_t *RouteArrowNew(void)
{
    RouteArrow_t *p = ObjNewInList(_RouteArrow_iObjList, 14, 0, 0);
    ObjSetPriority(_RouteArrow_iObjList, p, 3);
    return p;
}

void RouteArrowDelete(RouteArrow_t *p)
{
    if (p) {
        ObjRemoveFromList(_RouteArrow_iObjList, p);
        VptTrashObject((int)p);
    }
}

void RouteArrowSysInit(int handle)
{
    _RouteArrow_iObjList = handle;
    RouteArrowRegisterType();
    RouteArrow_t **p = _RouteArrow_apArrows;
    RouteArrow_t **pLast = p + 26;
    do { *p++ = RouteArrowNew(); } while (p <= pLast);
    _RouteArrow_uNumShown = 0;
    _RouteArrow_bEnabled = 1;
}

void RouteArrowSysShutdown(void)
{
    RouteArrow_t **p = _RouteArrow_apArrows;
    RouteArrow_t **pLast = p + 26;
    do { RouteArrowDelete(*p++); } while (p <= pLast);
    _RouteArrow_iObjList = 0;
    RouteArrowUnregisterType();
    _RouteArrow_uNumShown = 0;
}

void RouteArrowUpdateHighlights(void)
{
    for (int i = 0; i < 27; ++i) {
        RouteArrow_t *p = _RouteArrow_apArrows[i];
        if (p->mpPlayer) {
            if (p->mHighlight > 0.1f) p->mHighlight *= 0.88f;
            else p->mHighlight = 0.1f;
        }
    }
}

RouteArrow_t *RouteArrowShow(Object_80039F5C *pPlayer, FieldPoint_t *pPoint,
                            unsigned char *pCommands, unsigned char flag)
{
    RouteArrow_t *p = 0;
    for (int i = 0; i < 27; ++i) {
        if (!_RouteArrow_apArrows[i]->mpPlayer) {
            ++_RouteArrow_uNumShown;
            _RouteArrow_apArrows[i]->mbShown = 1;
            _RouteArrow_apArrows[i]->mbFlip = flag;
            _RouteArrow_apArrows[i]->mPendingTurn = 10;
            _RouteArrow_apArrows[i]->mpPlayer = pPlayer;
            *(FieldPoint_t *)&_RouteArrow_apArrows[i]->mStartX = *pPoint;
            _RouteArrow_apArrows[i]->mpCommands = pCommands;
            p = _RouteArrow_apArrows[i];
            break;
        }
    }
    p->mHighlight = 0.1f;
    return p;
}

void RouteArrowHide(RouteArrow_t *p)
{
    p->mbShown = 0;
    p->mbFlip = 0;
    p->mPendingTurn = 10;
    p->mpPlayer = 0;
    --_RouteArrow_uNumShown;
}

void RouteArrowHighlight(RouteArrow_t *p)
{
    p->mHighlight = 0.6f;
}

void RouteArrowSetEnabled(int value)
{
    _RouteArrow_bEnabled = value;
}
}
