#ifndef GAME_CU_8018EC68_H
#define GAME_CU_8018EC68_H

/* Row of table 'VETS' filled by fn_8018EC68 (0x64 bytes). */
struct VetsRow_8018EC68 {
    char mIuve[64];
    short mQrxe;
    short mPewr;
    short mPdwr;
    short mCswr;
    int mDive;
    int mItes;
    unsigned char mNets;
    unsigned char mDroe;
    char mCsis;
    char mCsos;
    int mPes[4];
};

/* src/game/cu_8018EC68.cpp */
extern "C" {
int fn_8018EDF0(int dive, int droe, VetsRow_8018EC68 *pRow);
int fn_8018EE44(int dive);
int fn_8018EE78(void);
int fn_8018EEAC(void);
int fn_8018EEF0(void);
}

#endif
