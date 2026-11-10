#ifndef GAME_STEV_TABLE_H
#define GAME_STEV_TABLE_H

/* Row of table 'VETS' filled by StevReadRow (0x64 bytes). */
struct StevRow_t {
    char mIuve[64];
    unsigned short mQrxe;
    unsigned short mPewr;
    unsigned short mPdwr;
    unsigned short mCswr;
    int mDive;
    int mItes;
    unsigned char mNets;
    unsigned char mDroe;
    char mCsis;
    char mCsos;
    int mPes[4];
};

/* src/game/StevTable.cpp */
extern "C" {
int StevGetRow(int dive, int droe, StevRow_t *pRow);
int StevCountDiveRows(int dive);
int StevCountRows(void);
int StevClose(void);
int StevOpen(void);
}

#endif
