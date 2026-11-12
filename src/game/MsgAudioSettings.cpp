/* Audio settings screen: reads and writes the game setting behind each row and,
   when the player accepts, rebuilds the music playlist and starts the next song. */

#include "game/OptionsScreenMsg.h"
#include "game/OptionsScreen.h"
#include "game/GameOptions.h"
#include "game/fn_80072AA8.h"

extern "C" {
void MsgAudioSettingsApply(void)
{
    fn_80072AA8();
    fn_80072F90();
}

void MsgAudioSettingsSetValue(unsigned int index, int value)
{
    int id = OptionsScreenGetOptionId(index);

    if (id != 24) {
        GameOptionsSet(id, value);
    }
}

int MsgAudioSettingsGetValue(unsigned int index)
{
    int result = 0;
    int id = OptionsScreenGetOptionId(index);

    if (id != 24) {
        result = GameOptionsGet(id);
    }
    return result;
}

void MsgAudioSettingsClose(void) {}
void MsgAudioSettingsOpen(void) {}

int MsgAudioSettingsHandleMessage(unsigned int id, OptionsScreenMsg_t *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgAudioSettingsOpen();
        break;
    case 0x80000002:
        MsgAudioSettingsClose();
        break;
    case 0x80000003:
        *pResult = MsgAudioSettingsGetValue(pBlock->mUnknown0);
        break;
    case 0x80000005:
        MsgAudioSettingsSetValue(pBlock->mUnknown0, pBlock->mUnknown4);
        break;
    case 0x80000004:
        MsgAudioSettingsApply();
        break;
    default:
        return 0;
    }
    return 1;
}
}
