#ifndef GAME_CU_80047E28_H
#define GAME_CU_80047E28_H

/* Model ids written by fn_8015F6E8. */
struct Ids_8015F6E8 {
    int mUnknown0;
    int mUnknown4;
};

/* Field accessors of the player records lbl_803078E8, defined in
   src/game/cu_80047E28.cpp. */
extern "C" {
void fn_80049124(int player);
void fn_800496A0(unsigned int mode, int index, int unused, int id);
int fn_80049888(int index);
int fn_800499A8(int index);
int fn_800499E8(int index);
void fn_80049B30(int index, int value);
void fn_80049B48(int index, int value);
void fn_80049B60(int index, int value);
void fn_80049B78(int index, int value);
void fn_80049B90(int index, int value);
void fn_80049BA8(int index, int value);
unsigned char fn_80049BC0(int index);
void fn_80049BD8(int index, int value);
void fn_80049BF0(int index, int value);
void fn_80049C20(int index, int value);
unsigned char fn_80049C38(int index);
void fn_80049C50(int index, int player);
void fn_80049D34(int index, unsigned int value);
void fn_80049D50(int index, unsigned int value);
void fn_80049D6C(int index, unsigned int which, int value);
void fn_80049E00(int index, const char *pName, Ids_8015F6E8 *pIds);
unsigned char fn_80049EC8(int index);
unsigned char fn_80049EE0(int index);
unsigned char fn_80049EF8(int index);
}

#endif
