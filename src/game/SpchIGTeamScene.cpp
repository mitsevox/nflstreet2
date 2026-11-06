/* Speech for scripted scenes: when a scene asks a player to say a line to another player, this
   starts that line for the right team, remembers who is speaking so the speech system can find him,
   and stops or releases the line when the scene moves on. */

#include "engine/spchevnt.h"

extern "C" {
void SpchIGStopChannel(int index);
void SpchIGPurgeChannel(int index);
void SpchIGGetPlayerCategory(int *pResult, int value);
void SpchIGGetTargetCategory(int *pResult, int value);
}

static int _SpchIG_iTeamSceneSpeaker0 = 0;
static int _SpchIG_iTeamSceneSpeaker1 = 0;

extern "C" void SpchIGSayTeamSceneLine(int a, int b, int c, int index)
{
    int result1;
    int result2;

    switch (index) {
    case 0:
        _SpchIG_iTeamSceneSpeaker0 = b;
        SpchIGPurgeChannel(0);
        SpchIGGetPlayerCategory(&result1, b);
        SpchIGGetTargetCategory(&result2, c);
        lbl_803EBB10(fn_801AE5D4(2, 0, 0x401E), 3, a, result1, result2);
        break;
    case 1:
        _SpchIG_iTeamSceneSpeaker1 = b;
        SpchIGPurgeChannel(1);
        SpchIGGetPlayerCategory(&result1, b);
        SpchIGGetTargetCategory(&result2, c);
        lbl_803EBB10(fn_801AE5D4(1, 0, 0x201E), 3, a, result1, result2);
        break;
    }
}

extern "C" void SpchIGStopTeamSceneLine(int index)
{
    switch (index) {
    case 0:
        SpchIGStopChannel(0);
        break;
    case 1:
        SpchIGStopChannel(1);
        break;
    }
}

extern "C" void SpchIGEndTeamSceneLine(int index)
{
    switch (index) {
    case 0:
        SpchIGPurgeChannel(0);
        _SpchIG_iTeamSceneSpeaker0 = 0;
        break;
    case 1:
        SpchIGPurgeChannel(1);
        _SpchIG_iTeamSceneSpeaker1 = 0;
        break;
    }
}

extern "C" int SpchIGGetTeamSceneSpeaker(int index)
{
    int value = 0;

    switch (index) {
    case 0:
        value = _SpchIG_iTeamSceneSpeaker0;
        break;
    case 1:
        value = _SpchIG_iTeamSceneSpeaker1;
        break;
    }
    return value;
}
