/* Player database text: the names, database column ids and display kinds of the player record's
   fields, the position and position-group abbreviations, the play-style names of each position,
   the character widths used to fit a name into a text box, and the helpers that read a player's
   row and format it for the roster and player screens. On the GameCube only the roster-slot
   abbreviation formatter is called; the linker discarded the other helpers, whose query strings
   stay in this file's read-only data. */
#include <string.h>
#include "game/TDbCompilePerformOp.h"

extern "C" {
int sprintf(char *pBuffer, const char *pFormat, ...);
extern int lbl_803EB4C8;
}

/* Text boxes: the fitted copy of a name and the three shown strings. */
static char _PlayerDbText_szFitted[76] = "The Users String";
static char _PlayerDbText_szText0[76] = "The Users String";
static char _PlayerDbText_szText1[76] = " ";
static char _PlayerDbText_szText2[76] = " ";

/* Player record fields: short name, database column id (-1: none) and display kind. */
static const char *_PlayerDbText_apFieldNames[102] = {
    "POS", "FNAME", "LNAME", "COLL", "GRYR", "PORT", "AGE", "HGT",
    "WGT", "HCOL", "YPRO", "HAND", "TEND", "OVR", "INJ", "SAL",
    "ACC", "AGI", "JMP", "BTK", "CAR", "CTH", "KR", "PRET",
    "KAC", "KPW", "", "PBK", "PPW", "RBK", "STA", "STR",
    "TAK", "THA", "THP", "JMP", "SPD", "TGH", "IMP", "SKIN",
    "HEAD", "VIS", "EYE", "FACE", "JNUM", "SLV", "JNME", "LANK",
    "RANK", "MUSC", "FMSK", "NPAD", "BRTE", "TSLV", "TLEL", "TLH",
    "TLW", "TRE", "TRE", "TRW", "GSLV", "GLE", "GRE", "GLW",
    "GLH", "GRH", "GRW", "SHOE", "EMO", "CEL", "TEAM", "BODY",
    "FLAK", "PID", "PORG", "FSHP", "SSHP", "MTHPC", "LTHI", "RTHI",
    "HSSP", "STMP", "STUP", "STFP", "SAMP", "SAFP", "SGMP", "SGFP",
    "SGQP", "SHMP", "SHFP", "SCMP", "SCFP", "SSLP", "SPTP", "SSTP",
    "SSWP", "SHCP", "STQP", "FSHP", "CONT", "JTYP",
};
static int _PlayerDbText_aFieldColumns[102] = {
    0x534F5050, 0x414E4650, 0x414E4C50, -1, -1, 0x50585350,
    0x45474150, 0x54474850, 0x54475750, -1, -1, 0x4E414850,
    -1, 0x52564F50, -1, -1, -1, 0x49474150,
    0x4B544250, 0x4B544250, -1, 0x48544350, -1, -1,
    -1, -1, -1, -1, -1, -1,
    -1, -1, 0x4B415450, -1, -1, -1,
    0x44505350, -1, -1, 0x494B5350, 0x44454850, 0x53495650,
    -1, -1, 0x4E454A50, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,
    -1, -1, -1, 0x4C454350, 0x44494754, -1,
    -1, 0x44494750, 0x44494F50, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,
};
static short _PlayerDbText_asFieldKinds[102] = {
    0, 1, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
static unsigned char _PlayerDbText_abFieldFlags[102] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* Position abbreviations by position number, by roster slot, by depth-chart group, with the
   special-teams positions, and by position group. */
static const char *_PlayerDbText_apPositionNames[22] = {
    "QB", "HB", "FB", "WR", "TE", "LT", "LG", "C",
    "RG", "RT", "LE", "RE", "DT", "LOLB", "MLB", "ROLB",
    "CB", "FS", "SS", "K", "P", "ALL",
};
static const char *_PlayerDbText_apSlotAbbrevs[14] = {
    "QB", "RB", "WR", "WR", "OL", "OL", "OL", "DL",
    "DL", "LB", "LB", "DB", "DB", "DB",
};
static const char *_PlayerDbText_apDepthNames[18] = {
    "QB", "HB", "FB", "WR", "TE", "T", "G", "C",
    "DE", "DT", "OLB", "MLB", "CB", "FS", "SS", "K",
    "P", "ALL",
};
const char *gPlayerPositionAbbrevs[26] = {
    "QB", "HB", "FB", "WR", "TE", "LT", "LG", "C",
    "RG", "RT", "LE", "RE", "DT", "LOLB", "MLB", "ROLB",
    "CB", "FS", "SS", "K", "P", "KR", "PR", "KOS",
    "LS", "3DRB",
};
static const char *_PlayerDbText_apGroupNames[11] = {
    "QB", "RB", "WR", "TE", "OL", "DL", "LB", "DB",
    "K", "PTOTAL", 0,
};

/* The two play styles of each position number: below 10, from 20. */
static const char *_PlayerDbText_aapPlayStyles[21][2] = {
    { "Pocket", "Scrambling" }, { "Power", "Speed" }, { "Blocking", "Receiving" },
    { "Speed", "Possession" }, { "Blocking", "Receiving" }, { "Pass Blocking", "Run Blocking" },
    { "Pass Blocking", "Run Blocking" }, { "Pass Blocking", "Run Blocking" },
    { "Pass Blocking", "Run Blocking" }, { "Pass Blocking", "Run Blocking" },
    { "Pass Rushing", "Run Stopping" }, { "Pass Rushing", "Run Stopping" },
    { "Pass Rushing", "Run Stopping" }, { "Run Stopping", "Coverage" },
    { "Run Stopping", "Coverage" }, { "Run Stopping", "Coverage" }, { "Hard Hitting", "Coverage" },
    { "Coverage", "Hard Hitting" }, { "Coverage", "Hard Hitting" }, { "Accurate", "Power" },
    { "Accurate", "Power" },
};

/* Text widths of the characters ' ' to DEL. */
static short _PlayerDbText_asCharWidths[96] = {
    5, 99, 99, 99, 99, 99, 10, 3, 99, 99, 99, 99, 99, 5, 3, 99,
    7, 4, 7, 7, 8, 7, 7, 7, 8, 7, 99, 99, 99, 99, 99, 99,
    99, 10, 9, 8, 9, 8, 8, 8, 9, 3, 7, 10, 8, 11, 10, 9,
    9, 9, 9, 8, 8, 9, 9, 13, 9, 9, 8, 99, 99, 99, 99, 99,
    99, 6, 7, 7, 7, 7, 6, 7, 7, 3, 3, 7, 3, 12, 7, 7,
    7, 6, 5, 7, 5, 7, 8, 12, 8, 8, 7, 99, 99, 99, 99, 0,
};

extern "C" {
void PlayerDbTextFormatField(char *pText, int field, int value);

/* Discarded by the GameCube linker; body from the Xbox counterpart 0x152400. */
unsigned char PlayerDbTextIsJerseyFree(int team, short jersey)
{
    QueryCursor cursor;
    QueryResult result;
    unsigned char bFree = 0;
    int status;

    status = TDbCompilePerformOp(&cursor, "declare \x8a cursor for select * from 'YALP' where 'DIGT' = \x82 and 'NEJP' = \x82\n",
                                 &result, team, jersey);
    if (status == 0 || status == 23 || status == 21 || status == 20) {
        if (result.mUnknown0 == 0) {
            bFree = 1;
        }
        TDbSQLDestroyCursor(&cursor);
    }
    return bFree;
}

/* Discarded by the GameCube linker; body from the Xbox counterpart 0x1524F0. */
int PlayerDbTextFitText(char *pText)
{
    int width = lbl_803EB4C8 * 6;
    int length;
    int count;
    int i;

    if (width < 54) {
        width = 54;
    }
    length = strlen(pText);
    count = 0;
    while (count < length) {
        if (width < 3) {
            break;
        }
        _PlayerDbText_szFitted[count] = pText[count];
        width -= _PlayerDbText_asCharWidths[pText[count] - ' '];
        count++;
    }
    if (width < 3) {
        count--;
    }
    for (i = count; i < lbl_803EB4C8; i++) {
        _PlayerDbText_szFitted[i] = ' ';
    }
    _PlayerDbText_szFitted[i] = 0;
    sprintf(pText, "%s", _PlayerDbText_szFitted);
    return count;
}

void PositionAbbrevFormat(int slot, char *pText)
{
    sprintf(pText, _PlayerDbText_apSlotAbbrevs[slot]);
}

/* Discarded by the GameCube linker: the default play-style text that the Xbox counterpart
   0x152690 copies inline at its start. */
// FAKEMATCH: the Xbox 0x152690 initializes its local buffer with this literal; that natural form
// (char szStyle[40] = "Pocket Passer "; in PlayerDbTextGetPlayStyle) places the string after the
// other literals, so this helper stands in only to emit it at 0x802A5CAC.
void PlayerDbTextGetDefaultPlayStyle(char *pText)
{
    strcpy(pText, "Pocket Passer ");
}

/* Discarded by the GameCube linker; body from the Xbox counterpart 0x1527A0. */
void PlayerDbTextFormatPlayStyle(char *pText, int position, int rating)
{
    if (rating < 0) {
        rating = 0;
    } else if (rating > 29) {
        rating = 29;
    }
    switch (rating / 10) {
    case 0:
        sprintf(pText, _PlayerDbText_aapPlayStyles[position][0]);
        break;
    case 1:
        sprintf(pText, "Balanced");
        break;
    case 2:
        sprintf(pText, _PlayerDbText_aapPlayStyles[position][1]);
        break;
    default:
        sprintf(pText, "INVALID!");
        break;
    }
}

/* Discarded by the GameCube linker; body from the Xbox counterpart 0x152810. The Xbox version returns
   the position passed through a conversion helper with no identified GameCube counterpart; the raw
   position is returned here. */
int PlayerDbTextGetPosition(int player)
{
    int position = 0;

    TDbCompilePerformOp(0, "select 'SOPP' into \x82 from 'YALP' where 'DIGP' = \x82\n", &position, player);
    return position;
}

/* Discarded by the GameCube linker; body from the Xbox counterpart 0x152840. */
int PlayerDbTextReadField(char *pText, int field, int player)
{
    int value = 0;
    int status = 0;
    char szValue[16];

    switch (_PlayerDbText_asFieldKinds[field]) {
    case 0:
        status = TDbCompilePerformOp(0, "select \x8c into \x82 from 'YALP' where 'DIGP' = \x82\n",
                                     _PlayerDbText_aFieldColumns[field], &value, player);
        PlayerDbTextFormatField(pText, field, value);
        if (field == 12) {
            int tendency = 0;
            int position = 0;

            TDbCompilePerformOp(0, "select 'NETP' into \x82 from 'YALP' where 'DIGP' = \x82\n", &tendency, player);
            TDbCompilePerformOp(0, "select 'SOPP' into \x82 from 'YALP' where 'DIGP' = \x82\n", &position, player);
            PlayerDbTextFormatPlayStyle(pText, position, tendency);
        }
        return value;
    case 1:
        if (field == 1) {
            status = TDbCompilePerformOp(0, "select \x8c into \x88 from 'YALP' where 'DIGP' = \x82\n",
                                         _PlayerDbText_aFieldColumns[field], szValue, player);
            strncpy(pText, szValue, 12);
        } else if (field == 2) {
            status = TDbCompilePerformOp(0, "select \x8c into \x88 from 'YALP' where 'DIGP' = \x82\n",
                                         _PlayerDbText_aFieldColumns[field], szValue, player);
            strncpy(pText, szValue, 15);
        }
        break;
    }
    return status;
}

/* Discarded by the GameCube linker; body from the Xbox counterpart 0x1529D0. */
void PlayerDbTextFormatField(char *pText, int field, int value)
{
    sprintf(pText, "%d", value);
    if (_PlayerDbText_asFieldKinds[field] != 0) {
        return;
    }
    switch (field) {
    case 10:
        if (value == 0) {
            sprintf(pText, "Rookie");
        }
        break;
    case 8:
        sprintf(pText, "%d", value + 160);
        break;
    case 0:
        sprintf(pText, _PlayerDbText_apPositionNames[value]);
        break;
    case 6:
        sprintf(pText, "%d", value);
        break;
    case 11:
        if (value != 0) {
            sprintf(pText, "Left");
        } else {
            sprintf(pText, "Right");
        }
        break;
    }
}

/* Discarded by the GameCube linker: the jersey-number query that follows the field formatter. */
int PlayerDbTextGetJersey(int player)
{
    int jersey = 0;

    TDbCompilePerformOp(0, "select 'NEJP' into \x82 from 'YALP' where 'DIGP' = \x82\n", &jersey, player);
    return jersey;
}

/* Discarded by the GameCube linker; body from the Xbox counterpart 0x152690. */
int PlayerDbTextGetPlayStyle(int player, char *pText)
{
    char szStyle[40];
    char szPosition[12];
    int position = 0;
    int tendency;

    PlayerDbTextGetDefaultPlayStyle(szStyle);
    TDbCompilePerformOp(0, "select \x8c into \x82 from 'YALP' where 'DIGP' = \x82\n",
                        _PlayerDbText_aFieldColumns[0], &position, player);
    sprintf(szPosition, "%d", position);
    if (_PlayerDbText_asFieldKinds[0] == 0) {
        sprintf(szPosition, _PlayerDbText_apPositionNames[position]);
    }
    tendency = PlayerDbTextReadField(szStyle, 12, player);
    PlayerDbTextFormatPlayStyle(pText, position, tendency);
    return tendency;
}

/* Discarded by the GameCube linker; body from the Xbox counterpart 0x152AA0. */
short PlayerDbTextFindFreeJersey(int team, int bUp, short jersey, short low, short high)
{
    QueryCursor cursor;
    QueryResult result;
    short start = jersey;
    int step = bUp ? 1 : -1;
    int status;

    do {
        status = TDbCompilePerformOp(&cursor, "declare \x8a cursor for select * from 'YALP' where 'DIGT' = \x82 and 'NEJP' = \x82\n",
                                     &result, team, jersey);
        if (status == 0 || status == 23 || status == 21 || status == 20) {
            unsigned char bFree = result.mUnknown0 == 0;

            TDbSQLDestroyCursor(&cursor);
            if (bFree) {
                return jersey;
            }
        }
        jersey += step;
        if (jersey < low) {
            jersey = high;
        } else if (jersey > high) {
            jersey = low;
        }
    } while (jersey != start);
    return -1;
}

/* Discarded by the GameCube linker; body from the Xbox counterpart 0x152B50. */
void PlayerDbTextSetTexts(const char *pText0, const char *pText1, const char *pText2)
{
    sprintf(_PlayerDbText_szText0, "%s", pText0);
    sprintf(_PlayerDbText_szText1, "%s", pText1);
    sprintf(_PlayerDbText_szText2, "%s", pText2);
}
}
