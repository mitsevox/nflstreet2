/* Commentary triggers for single plays: a catch, an interception, a wall hurdle and a failed one, a
   stiff arm, a juke or spin, a thrown pass, a stripped ball and a fumble. Each picks the commentary
   bank of the team concerned and names the player involved. */

#include "engine/spchevnt.h"

extern "C" {
int SpchIGGetTeamPlayer(int side);
void SpchIGGetPlayerCategory(int *pResult, int value);
int fn_80178308(void);
int fn_80178320(void);
}

extern "C" void SpchIGSayCatch(int value)
{
    int result;

    SpchIGGetPlayerCategory(&result, value);
    if (fn_80178308() == 0) {
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2023), 1, result);
    } else {
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4023), 1, result);
    }
}

extern "C" void SpchIGSayInterception(int value)
{
    int result;

    SpchIGGetPlayerCategory(&result, value);
    if (fn_80178320() == 0) {
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2024), 1, result);
    } else {
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4024), 1, result);
    }
}

extern "C" void SpchIGSayWallHurdle(int value)
{
    int result;

    SpchIGGetPlayerCategory(&result, value);
    if (fn_80178308() == 0) {
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2025), 1, result);
    } else {
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4025), 1, result);
    }
}

extern "C" void SpchIGSayStiffArm(int value)
{
    int result;

    if (fn_80178308() == 0) {
        SpchIGGetPlayerCategory(&result, value);
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2026), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, value);
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4026), 1, result);
    }
}

extern "C" void SpchIGSayJukeSpin(int value)
{
    int result;

    if (fn_80178308() == 0) {
        SpchIGGetPlayerCategory(&result, value);
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2027), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, value);
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4027), 1, result);
    }
}

extern "C" void SpchIGSayWallHurdleMiss(int value)
{
    int result;

    if (fn_80178308() == 0) {
        SpchIGGetPlayerCategory(&result, value);
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2028), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, value);
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4028), 1, result);
    }
}

extern "C" void SpchIGSayPassThrown(int)
{
    int result;

    if (fn_80178320() == 0) {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(0));
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2029), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(1));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4029), 1, result);
    }
}

extern "C" void SpchIGSayBallStrip(int)
{
    int result;

    if (fn_80178320() == 0) {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(0));
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x202A), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(1));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x402A), 1, result);
    }
}

extern "C" void SpchIGSayFumble(void)
{
    int result;

    if (fn_80178308() == 0) {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(0));
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x201B), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(1));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x401B), 1, result);
    }
}
