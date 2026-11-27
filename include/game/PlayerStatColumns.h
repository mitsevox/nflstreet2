#ifndef GAME_PLAYERSTATCOLUMNS_H
#define GAME_PLAYERSTATCOLUMNS_H

/* One category of the player statistics screen and how many columns of gPlayerStatCatColumns it
   takes, in table order. */
typedef struct PlayerStatCategory_t {
    int mGroup;
    const char *mpName;
    unsigned char mNumColumns;
} PlayerStatCategory_t;

/* One column of the player statistics screen: its two-line header and four flags. */
typedef struct PlayerStatColumn_t {
    const char *mpHeader;
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA;
} PlayerStatColumn_t;

extern const PlayerStatCategory_t gPlayerStatCategories[9];
extern const PlayerStatColumn_t gPlayerStatCatColumns[84];

#endif
