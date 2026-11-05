#ifndef GAME_PLAYERLOOK_H
#define GAME_PLAYERLOOK_H

/* Model ids written by fn_8015F6E8. */
struct PlayerHeadIds_t {
    int mUnknown0;
    int mUnknown4;
};

/* Field accessors of the player records lbl_803078E8, defined in
   src/game/PlayerLook.cpp. */
extern "C" {
void PlayerLookApply(int player);
void PlayerLookLoadForPlayer(unsigned int mode, int index, int unused, int id);
int PlayerLookGetHatModel(int index);
int PlayerLookGetSlot1Model(int index);
int PlayerLookGetAccessoryModel(int index);
void PlayerLookSetSkin(int index, int value);
void PlayerLookSetFace(int index, int value);
void PlayerLookSetBrow(int index, int value);
void PlayerLookSetHeadType(int index, int value);
void PlayerLookSetHair(int index, int value);
void PlayerLookSetBodyType(int index, int value);
unsigned char PlayerLookGetBodyType(int index);
void PlayerLookSetFaceFlag(int index, int value);
void PlayerLookSetNumber(int index, int value);
void PlayerLookSetPlex(int index, int value);
unsigned char PlayerLookGetPlex(int index);
void PlayerLookApplyHeadDecal(int index, int player);
void PlayerLookSetHairColor(int index, unsigned int value);
void PlayerLookSetFacialHairColor(int index, unsigned int value);
void PlayerLookSetPartVariant(int index, unsigned int which, int value);
void PlayerLookGetHeadIds(int index, const char *pName, PlayerHeadIds_t *pIds);
unsigned char PlayerLookGetSkin(int index);
unsigned char PlayerLookGetFace(int index);
unsigned char PlayerLookGetBrow(int index);
}

#endif
