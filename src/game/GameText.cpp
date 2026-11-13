/* Text and small shared state for the game's screens: team and player names, scores, downs and
   clocks, player ages, heights and weights read from the database and formatted for display, the
   "Please wait..." busy dialog, the controller-to-player table, the memory card names, and the
   flags behind the boot prompt and the pending system reset. */

#include <stdio.h>
#include <string.h>
#include "game/Entry_80219044.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_801C3284.h"
#include "game/fn_801FCE10.h"

/* The cached database row of the last player looked up by GameTextLoadPlayer. */
struct GameTextPlayer_t {
    unsigned short mId;
    int mUnknown4;
    unsigned char mUnknown8;
    int mUnknownC;
    unsigned short mUnknown10;
    unsigned short mUnknown12;
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    char mUnknown16[12];
    char mUnknown22[18];
};

/* The cached names of the last team looked up by GameTextLoadTeam. */
struct GameTextTeam_t {
    unsigned short mId;
    unsigned char mUnknown2[10];
    char mName[16];
    char mShortName[8];
    char mDisplayName[20];
};

extern "C" {
extern void *gUISSub2Info;
extern const char *gPlayerPositionAbbrevs[];

static GameTextPlayer_t _GameText_sPlayer = {0x7FFF};
static GameTextTeam_t _GameText_sTeam = {0x3FF};
static char _GameText_szPlayResult[64] = "---- Play Result char8_t * ----";
static const char *_GameText_apPositionAbbrev[] = {
    "LB", "OL", "DB", "RB", "DL", "QB", "HB", "FB", "WR", "TE", "LT", "LG", "C", "RG", "RT", "LE",
    "RE", "DT", "LOLB", "MLB", "ROLB", "CB", "FS", "SS", "K", "P", "KR", "PR", "KOS", "LS", "3DB", 0,
};
static int _GameText_aPadPlayers[10] = {10};

static int _GameText_iLastPlayer = 0;
static int _GameText_iUnused0 = 0;
static int _GameText_iUnused1 = 0;
static int _GameText_iUnused2 = 0;
static int _GameText_iUnused3 = 0;
static unsigned char _GameText_bUnused0 = 0;
static int _GameText_iUnused4 = 0;
static int _GameText_iUnused5 = 1;
static int _GameText_iUnused6 = 0;
static int _GameText_iSelectedTeam = 0x3FF;
static unsigned int _GameText_nBusyDialogs = 0;
static unsigned char _GameText_bDialogSaved = 0;
static unsigned char _GameText_bDialogArgA = 0;
static unsigned char _GameText_bDialogArgB = 0;
static unsigned char _GameText_bSavedArgA = 0;
static unsigned char _GameText_bSavedArgB = 0;
static unsigned char _GameText_bUnused1 = 0;
static unsigned char _GameText_bBootFinished = 0;
static unsigned char _GameText_bSetupActive = 0;
static unsigned char _GameText_bUnused2 = 0;
static unsigned char _GameText_bResetRequested = 0;
static int _GameText_iResetParam = 0;
static unsigned char _GameText_bPauseState = 0;
static char _GameText_szEmpty[] = "";

static Entry_80219044 *_GameText_apDialogEntries[3];
static Entry_80219044 _GameText_aDialogEntries[3];
static char _GameText_szDialogText[256];
static char _GameText_szSavedDialogText[256];
static char _GameText_aszNames[3][129];

int fn_801F95C8(void);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int MsgGameGetPlayerPortrait(int id);
void *fn_8021EA44(int index);
int fn_8021E72C(void *pObject, int a, int b);
int fn_8022E558(void);
int fn_8022E560(void);
int fn_80219044(void *p, int a, int b, int c, Entry_80219044 **ppEntries);
void fn_8021956C(void *p, int a, int b, int c);
void FileDebugProcess(void);
void SndgUpdate(int a);
void UISGamePresentFrame(void);
void FESndUpdate(int a);
void GameTextShowBusyDialog(int show, const char *pText, int a, int b);

void fn_801F87FC(int a);
int GameModeTypeIsSpecial(void);
void MsgNameEntryGetName(char *pDest, int length);
int fn_801C2D88(char *pDest, int length, const char *pFormat, ...);
int fn_80177F70(void);
float fn_80178298(void);
Point_8017886C fn_80177FE0(void);
float fn_80178A2C(void);
int RoundToNearestInt(float value);
unsigned int fn_8009D990(int index);
int fn_8022C8F0(unsigned int low, unsigned int high);
unsigned short GameTextPickRandomTeam(int type);
unsigned char CurrentIdIsSet(void);
unsigned short TeamRecordFindIndex(int team);

void GameTextLoadPlayer(int id, unsigned char reload)
{
    int position = 0;
    if (id != _GameText_sPlayer.mId && id != 0x7FFF) {
        _GameText_sPlayer.mUnknown4 = 0;
        _GameText_sPlayer.mUnknown8 = 0;
        _GameText_sPlayer.mUnknownC = 0;
        _GameText_sPlayer.mUnknown10 = 0;
        _GameText_sPlayer.mUnknown12 = 0;
        _GameText_sPlayer.mUnknown14 = 0;
        int result = fn_801FCE10(0, "select 'SOPP' into \x82 and 'NEJP' into \x80 and 'PXSP' into \x82 and "
                                    "'DIGT' into \x81 and COL_PLYR_YEARSPRO into \x81 and 'OHFP' into \x80 and "
                                    "'ANFP' into \x88 and 'ANLP' into \x88 from 'YALP' where 'DIGP' = \x82\n",
                                 &position, &_GameText_sPlayer.mUnknown8, &_GameText_sPlayer.mUnknownC,
                                 &_GameText_sPlayer.mUnknown10, &_GameText_sPlayer.mUnknown12, &_GameText_sPlayer.mUnknown14,
                                 _GameText_sPlayer.mUnknown16, _GameText_sPlayer.mUnknown22, id);
        _GameText_sPlayer.mUnknown4 = position;
        if (result == 0) {
            _GameText_sPlayer.mId = id;
        }
    } else if (reload == 1 && id != 0x7FFF) {
        fn_801FCE10(0, "select 'NEJP' into \x80 from 'YALP' where 'DIGP' = \x82\n", &_GameText_sPlayer.mUnknown8, id);
    }
}

void GameTextLoadTeam(int id)
{
    char text[24];
    char shortText[16];
    char displayText[24];
    int type = -1;
    int database = fn_801F95C8();
    int result = fn_801FCE10(0, "use \x8c select 'PYTT' into \x82 from 'MAET' where 'DIGT' = \x82\n",
                            database, &type, id);
    if ((result == 0 && id != _GameText_sTeam.mId && (unsigned short)id != 0x3FF
         && (unsigned short)id != 0x3F7 && id != 0x3F9) || type == 5) {
        if (fn_801FCE10(0, "use \x8c select 'ANLT' into \x88 and 'ANST' into \x88 and 'ANDT' into \x88 from 'MAET' where 'DIGT' = \x82\n",
                        database, text, shortText, displayText, id) == 0) {
            if (type == 5 || type == 18) {
                _GameText_sTeam.mId = id;
            } else {
                _GameText_sTeam.mId = id;
            }
        }
        strcpy(_GameText_sTeam.mName, text);
        strcpy(_GameText_sTeam.mShortName, shortText);
        strcpy(_GameText_sTeam.mDisplayName, displayText);
    } else if (result == 23 || id == 0x3F9) {
        _GameText_sTeam.mId = 0x3FF;
    }
}

void GameTextReset(void)
{
    if (_GameText_aPadPlayers[0] == 10) {
        for (int i = 9; i >= 0; --i) {
            _GameText_aPadPlayers[i] = i;
        }
    }
    _GameText_sPlayer.mId = 0x7FFF;
    _GameText_sTeam.mId = 0x3FF;
}

void GameTextSetBootFinished(unsigned char value)
{
    _GameText_bBootFinished = value;
}

unsigned char GameTextGetBootFinished(void)
{
    return _GameText_bBootFinished;
}

int GameTextGetTeamFont(int team)
{
    int font;
    fn_801FCE10(0, "use 'TATS' select COL_TEAM_FONT_LARGE into \x82 from 'MAET' where 'DIGT' = \x82\n", &font, team);
    return 0;
}

int GameTextFindTeamByCity(int city)
{
    int team = 0;
    if (city != 3) {
        fn_801FCE10(0, "select 'DIGT' into \x85 from 'MAET' where 'DIGC' = \x85 and 'DIGD' = \x83\n", &team, city, 31);
    }
    return team;
}

int GameTextGetAwayTeam(void)
{
    return fn_8022E560();
}

int GameTextGetHomeTeam(void)
{
    return fn_8022E558();
}

void GameTextFormatScore(int team, char *pText, int length)
{
    int score = 0;
    char text[4];
    if (fn_8022E560() == team) {
        fn_801FCE10(0, "select 'CSAG' into \x82 from 'FNIG'\n", &score);
    } else {
        fn_801FCE10(0, "select 'CSHG' into \x82 from 'FNIG'\n", &score);
    }
    sprintf(text, "%d", score);
    fn_801C2EF0(pText, text, length);
}

void GameTextGetTeamDisplayName(int id, char *pText, int size)
{
    if (id != 0x3FF) {
        GameTextLoadTeam(id);
        fn_801C2EF0(pText, _GameText_sTeam.mDisplayName, size);
    } else {
        fn_801C2EF0(pText, "", size);
    }
}

void GameTextFormatTeamRecord(int team, char *pText)
{
    int wins = 0;
    int losses = 0;
    int ties = 0;
    fn_801FCE10(0, "select COL_TEAM_SEASWINS into \x82 and COL_TEAM_SEASLOSSES into \x82 and COL_TEAM_SEASTIES "
                   "into \x82 from 'MAET' where 'DIGT' = \x82\n",
                &wins, &losses, &ties, team);
    sprintf(pText, "(%d - %d - %d)", wins, losses, ties);
}

int GameTextGetQuarter(void)
{
    int quarter = 0;
    fn_801FCE10(0, "select 'RTQG' into \x82 from 'FNIG'\n", &quarter);
    return quarter + 1;
}

void GameTextFormatDown(char *pText)
{
    switch (fn_80177F70()) {
    case 0:
    case 6:
        sprintf(pText, " ");
        break;
    case 1:
        sprintf(pText, "1st");
        break;
    case 2:
        sprintf(pText, "2nd");
        break;
    case 3:
        sprintf(pText, "3rd");
        break;
    case 4:
        sprintf(pText, "4th");
        break;
    case 5:
        sprintf(pText, "5th");
        break;
    }
}

void GameTextFormatDistance(char *pText)
{
    switch (fn_80177F70()) {
    case 0:
    case 6:
        sprintf(pText, "%s", "--");
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5: {
        float distance = fn_80178298() - fn_80177FE0().mY;
        signed char yards = RoundToNearestInt(distance);
        if (!(distance < fn_80178A2C())) {
            sprintf(pText, "Goal");
        } else if (distance < 1.0f) {
            sprintf(pText, "Inches");
        } else {
            sprintf(pText, "%2d", yards < 0 ? -yards : yards);
        }
        break;
    }
    }
}

void GameTextFormatYardsToGo(char *pText)
{
    int down = fn_80177F70();
    sprintf(pText, "%s", "  ");
    if (down > 0 && down <= 5) {
        signed char yards = RoundToNearestInt(fn_80178298() - fn_80177FE0().mY);
        if (yards == 0) {
            yards = 1;
        }
        sprintf(pText, "%2d", yards < 0 ? -yards : yards);
    }
}

int GameTextFormatBallOn(char *pText)
{
    signed char yards = RoundToNearestInt(fn_80177FE0().mY);
    int side;
    if (yards < 0) {
        yards += (int)fn_80178A2C();
        side = 0;
    } else {
        yards = (int)(fn_80178A2C() - (float)yards);
        side = 1;
    }
    sprintf(pText, "%2d", yards);
    return side;
}

int GameTextFormatDownAndDistance(char *pText)
{
    float scrimmage = fn_80178298();
    Point_8017886C marker = fn_80177FE0();
    int down = fn_80177F70();
    const char *pLabel = 0;
    const char *pDown = 0;
    signed char yards = RoundToNearestInt(scrimmage - marker.mY);
    switch (down) {
    case 0:
        pLabel = "Kickoff";
        break;
    case 1:
        pDown = "1st";
        break;
    case 2:
        pDown = "2nd";
        break;
    case 3:
        pDown = "3rd";
        break;
    case 4:
        pDown = "4th";
        break;
    case 5:
        pDown = "5th";
        break;
    case 6:
        pLabel = "Extra Point";
        break;
    }
    if (pDown == 0) {
        sprintf(pText, "%s", pLabel);
        return 0;
    }
    signed char line = RoundToNearestInt(marker.mY);
    int side;
    if (line == 0) {
        line = (int)fn_80178A2C();
        side = 0;
    } else if (line < 0) {
        line += (int)fn_80178A2C();
        side = -1;
    } else {
        line = (int)(fn_80178A2C() - (float)line);
        side = 1;
    }
    if (!(scrimmage < fn_80178A2C())) {
        sprintf(pText, "%s and Goal on %d", pDown, line);
    } else if (yards > 0) {
        sprintf(pText, "%s and %d on %d", pDown, yards, line);
    } else {
        sprintf(pText, "%s and inches on %d", pDown, line);
    }
    return side;
}

void GameTextFormatGameClock(char *pText, int length)
{
    char text[8];
    unsigned int seconds = fn_8009D990(1);
    sprintf(text, "%d:%02d", (unsigned char)(seconds / 60), (unsigned char)(seconds % 60));
    fn_801C2EF0(pText, text, length);
}

void GameTextFormatPlayClock(char *pText, int length)
{
    char text[8];
    if (fn_80177F70() == 0) {
        sprintf(pText, " ");
        return;
    }
    sprintf(text, ":%02d", fn_8009D990(0));
    fn_801C2EF0(pText, text, length);
}

void GameTextGetUnknownName(char *pText)
{
    strcpy(pText, "????");
}

int GameTextGetPlayerTeam(int id)
{
    int team = 0x3FF;
    if (id >= 0 && id != 0x7FFF) {
        GameTextLoadPlayer(id, 0);
        team = _GameText_sPlayer.mUnknown10;
        if (team == 0x3F6) {
            fn_801FCE10(0, "select 'DIOT' into \x82 from TBL_RETIRE where 'DIGP' = \x82\n", &team, id);
        }
        if (team == 0x3F7) {
            fn_801FCE10(0, "select COL_DRAFT_PLYRDRAFTTEAMID into \x82 from TBL_DRAFT_PLAYER where 'DIGP' = \x82\n",
                        &team, id);
        }
    }
    return team;
}

unsigned short GameTextGetEditTeam(unsigned short fallback, int base)
{
    int team = 0x3FF;
    if (CurrentIdIsSet()) {
        fn_801FCE10(0, "select 'DIGT' into \x82 from 'DIED'\n", &team);
        if (team != 0x3FF) {
            unsigned short index = TeamRecordFindIndex(team);
            if (index != 0xFFFF) {
                return index + base;
            }
        }
    }
    return fallback;
}

void GameTextFormatPlayerName(const char *pFirst, const char *pLast, char *pText, unsigned int length)
{
    if (length > 18) {
        length = 18;
    }
    int whole = 0;
    if (strcmp(pLast, "No") == 0 || strcmp(pLast, "NO") == 0) {
        for (const char **p = _GameText_apPositionAbbrev; *p != 0; ++p) {
            if (strcmp(pFirst, *p) == 0) {
                whole = 1;
                break;
            }
        }
    }
    if (whole) {
        fn_801C2EF0(pText, pFirst, length);
        if (strlen(pText) < length) {
            strcat(pText, " ");
        }
    } else {
        pText[0] = pFirst[0];
        pText[1] = '.';
        pText[2] = 0;
    }
    fn_801C2EF0(pText + strlen(pText), pLast, length - strlen(pText));
}

void GameTextQueuePlayerPortraits(void)
{
    void *pList = fn_8021EA44(1);
    for (unsigned char team = 0; team < 2; ++team) {
        for (unsigned char index = 0; index < 7; ++index) {
            Object_80039F5C *p = PlyrGet(team, index);
            if (p->mUnknown9[2] != 0) {
                int id = MsgGameGetPlayerPortrait(p->mUnknown2908);
                if (id > 630) {
                    fn_8021E72C(pList, 10, id);
                }
            }
            if ((unsigned char)(index % 10) == 9) {
                FESndUpdate(1);
            }
        }
    }
}

void GameTextSetLastPlayer(int value)
{
    _GameText_iLastPlayer = value;
}

void GameTextFormatTenths(int value, char *pText)
{
    if (value >= 0) {
        sprintf(pText, "%d.%d", value / 10, value % 10);
    } else {
        value = -value;
        sprintf(pText, "-%d.%d", value / 10, value % 10);
    }
}

void GameTextGetMatchupTeams(int *pHome, int *pAway)
{
    int team = 0;
    fn_801FCE10(0, "select 'HDQO' into \x82 from 'TPOS'\n", &team);
    if (team == 0) {
        team = GameTextPickRandomTeam(team);
    }
    *pHome = team;
    fn_801FCE10(0, "select 'ADQO' into \x82 from 'TPOS'\n", &team);
    if (team == 0) {
        team = GameTextPickRandomTeam(team);
    }
    *pAway = team;
}

unsigned short GameTextPickRandomTeam(int type)
{
    QueryResult result;
    QueryCursor cursor;
    unsigned short team = 0;
    int status;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (type == 21) {
        status = fn_801FCE10(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGT' into \x81 from 'MAET'\n",
                             &cursor, &team);
    } else {
        status = fn_801FCE10(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGT' into \x81 from 'MAET' "
                                      "where 'PYTT' = \x82\n",
                             &cursor, &team, type);
    }
    if (status == 0) {
        cursor.mUnknown4 = fn_8022C8F0(0, result.mUnknown0 - 1);
        fn_801FCE10(0, "fetch from \x8a\n", &cursor);
    }
    if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    return team;
}

void GameTextShowPleaseWait(int show)
{
    GameTextShowBusyDialog(show, "Please wait...", 1, 1);
}

void GameTextShowBusyDialog(int show, const char *pText, int a, int b)
{
    if (show != 0) {
        if (_GameText_nBusyDialogs < 0xFFFFFFFFU) {
            ++_GameText_nBusyDialogs;
        }
        if (_GameText_nBusyDialogs == 1) {
            fn_801C3284(_GameText_szDialogText, pText, 255);
            _GameText_bDialogArgA = a;
            _GameText_bDialogArgB = b;
            _GameText_aDialogEntries[0].mUnknown0 = 0;
            _GameText_aDialogEntries[0].mpText = _GameText_szEmpty;
            _GameText_aDialogEntries[0].mLength = strlen(_GameText_szEmpty) + 1;
            _GameText_aDialogEntries[1].mUnknown0 = 0;
            _GameText_aDialogEntries[1].mpText = _GameText_szDialogText;
            _GameText_aDialogEntries[1].mLength = 255;
            _GameText_aDialogEntries[2].mUnknown0 = 0;
            _GameText_aDialogEntries[2].mpText = _GameText_szEmpty;
            _GameText_aDialogEntries[2].mLength = strlen(_GameText_szEmpty) + 1;
            _GameText_apDialogEntries[0] = &_GameText_aDialogEntries[0];
            _GameText_apDialogEntries[1] = &_GameText_aDialogEntries[1];
            _GameText_apDialogEntries[2] = &_GameText_aDialogEntries[2];
            fn_80219044(gUISSub2Info, 1, 3, 3, _GameText_apDialogEntries);
            FileDebugProcess();
            SndgUpdate(1);
            UISGamePresentFrame();
        }
    } else {
        if (_GameText_nBusyDialogs != 0) {
            --_GameText_nBusyDialogs;
            if (_GameText_nBusyDialogs != 0) {
                return;
            }
        }
        fn_8021956C(gUISSub2Info, 1, 3, 1);
    }
}

int GameTextFormatControllerPort(char *pText, int length, unsigned int port)
{
    char text[8];
    if (port >= 8) {
        port &= 7;
    }
    sprintf(text, "%d", port + 1);
    if (text[0] == 'M') {
        fn_801C2D88(pText, length, "multitap (for PlayStation\xb1" "2) in controller port %s", text + 1);
        return 2;
    }
    fn_801C2D88(pText, length, "controller in controller port %s", text);
    return 1;
}

int GameTextFormatPlayerAge(int id, char *pText)
{
    char text[] = "<string>";
    int age = 0;
    if (id != 0x7FFF) {
        fn_801FCE10(0, "select 'EGAP' into \x82 from 'YALP' where 'DIGP' = \x82\n", &age, id);
        sprintf(text, "%d", age);
    } else {
        strcpy(text, " ");
    }
    strcpy(pText, text);
    return age;
}

int GameTextFormatPlayerWeight(int id, char *pText)
{
    char text[16] = "<EmptyString>";
    int weight = 0;
    if (id != 0x7FFF) {
        fn_801FCE10(0, "select 'TGWP' into \x82 from 'YALP' where 'DIGP' = \x82\n", &weight, id);
        weight += 160;
        sprintf(text, "%d", weight);
    } else {
        strcpy(text, " ");
    }
    strcpy(pText, text);
    return weight;
}

int GameTextFormatPlayerHeight(int id, char *pText)
{
    char text[16] = "<EmptyString>";
    unsigned int height = 0;
    if (id != 0x7FFF) {
        fn_801FCE10(0, "select 'TGHP' into \x82 from 'YALP' where 'DIGP' = \x82\n", &height, id);
        sprintf(text, "%d'%d\"", height / 12, height % 12);
    } else {
        strcpy(text, " ");
    }
    strcpy(pText, text);
    return height;
}

int GameTextFormatPlayerYearsPro(int id, char *pText)
{
    int years = 0;
    char text[] = "<string>";
    if (id != 0x7FFF) {
        fn_801FCE10(0, "select COL_PLYR_YEARSPRO into \x82 from 'YALP' where 'DIGP' = \x82\n", &years, id);
        if (years > 0) {
            sprintf(text, "%d", years);
        } else {
            strcpy(text, "R");
        }
    } else {
        strcpy(text, " ");
    }
    strcpy(pText, text);
    return years;
}

int GameTextGetMemCardNames(char *pText0, int length0, char *pText1, int length1,
                char *pText2, int length2, char *pText3, int length3)
{
    fn_801C3284(pText0, "NGC", length0);
    fn_801C3284(pText1, "Memory Card", length1);
    fn_801C3284(pText2, "Memory Card", length2);
    fn_801C3284(pText3, "Memory Card Slot", length3);
    return 2;
}

void GameTextGetControllerNames(int port, char *pPort, char *pSocket, char *pSocketLower,
                                char *pController, char *pControllerLower)
{
    char socket[] = "Controller Socket";
    char socketLower[] = "Controller Socket";
    char controller[] = "Controller";
    char controllerLower[] = "Controller";
    if (port >= 8) {
        port %= 8;
    }
    pPort[0] = '1' + port;
    pPort[1] = 0;
    strcpy(pSocket, socket);
    strcpy(pSocketLower, socketLower);
    strcpy(pController, controller);
    strcpy(pControllerLower, controllerLower);
}

int GameTextGetSeasonYear(void)
{
    int year;
    int week;
    fn_801FCE10(0, "select COL_SEAS_YEAR into \x82 from TBL_SEASON_INFO\n", &year);
    fn_801FCE10(0, "select COL_SEAS_WEEKTYPE into \x82 from TBL_SEASON_INFO\n", &week);
    return 0x3FF;
}

int GameTextShowRosterFill(int player, int team, int stage)
{
    char text[256];
    char teamName[16];
    char last[12];
    char first[12];
    char position[4];
    int slot;
    SndgUpdate(1);
    switch (stage) {
    case 0:
        if (_GameText_nBusyDialogs != 0) {
            _GameText_bDialogSaved = 1;
            fn_801C3284(_GameText_szSavedDialogText, _GameText_szDialogText, 254);
            _GameText_bSavedArgA = _GameText_bDialogArgA;
            _GameText_bSavedArgB = _GameText_bDialogArgB;
        }
        break;
    case 1: {
        int found = fn_801FCE10(0, "select 'ANDT' into \x88 from 'MAET' where ('DIGT' = \x82)\n", teamName, team);
        first[0] = 0;
        last[0] = 0;
        slot = 31;
        if (found == 0
            && fn_801FCE10(0, "select 'ANFP' into \x88 and 'ANLP' into \x88 and 'SOPP' into \x82 from 'YALP' "
                              "where ('DIGP' = \x82)\n",
                           first, last, &slot, player) == 0) {
            sprintf(position, gPlayerPositionAbbrevs[slot]);
            sprintf(text, "Filling Team Rosters\n%s signed %s %c.%s", teamName, position, first[0], last);
        } else {
            sprintf(text, "Filling team rosters");
        }
        if (_GameText_nBusyDialogs != 0 && --_GameText_nBusyDialogs == 0) {
            fn_8021956C(gUISSub2Info, 1, 3, 1);
        }
        GameTextShowBusyDialog(1, text, _GameText_bSavedArgA, 2);
        break;
    }
    case 2:
        if (_GameText_nBusyDialogs != 0 && --_GameText_nBusyDialogs == 0) {
            fn_8021956C(gUISSub2Info, 1, 3, 1);
        }
        if (_GameText_bDialogSaved == 1) {
            GameTextShowBusyDialog(1, _GameText_szSavedDialogText, _GameText_bSavedArgA, _GameText_bSavedArgB);
            _GameText_szSavedDialogText[0] = 0;
            _GameText_bSavedArgA = 0;
            _GameText_bSavedArgB = 0;
            _GameText_bDialogSaved = 0;
        }
        break;
    }
    return 0;
}

void GameTextRequestReset(void)
{
    _GameText_bResetRequested = 1;
}

void GameTextServiceReset(void)
{
    if (_GameText_bResetRequested == 1) {
        fn_801F87FC(1);
    }
    _GameText_bResetRequested = 0;
}

void GameTextSetPauseState(int value)
{
    _GameText_bPauseState = value;
}

int GameTextGetTeamPlaybook(int team, unsigned char offense)
{
    unsigned int playbook = 0;
    int result = 0;
    if (offense == 1) {
        fn_801FCE10(0, "select COL_TEAM_OFFPLAYBOOK into \x85 from 'MAET' where 'DIGT' = \x82\n", &playbook, team);
        if (playbook >= 1) {
            playbook = 0;
        }
    } else {
        fn_801FCE10(0, "select COL_TEAM_DEFPLAYBOOK into \x85 from 'MAET' where 'DIGT' = \x82\n", &playbook, team);
        playbook = 0;
    }
    fn_801FCE10(0, "select 'DROB' into \x85 from 'BALP' where 'DIGB' = \x82 and 'FFOB' = \x85\n", &result, playbook,
                offense);
    return result;
}

void GameTextGetSelectedTeamName(char *pText, int length)
{
    char name[17] = {0};
    if (_GameText_iSelectedTeam != 0x3FF) {
        if (fn_801FCE10(0, "select 'ANLT' into \x88 from 'MAET' where 'DIGT' = \x85\n", name, _GameText_iSelectedTeam) == 0) {
            fn_801C3284(pText, name, length);
        }
    } else {
        fn_801C3284(pText, "", 0);
    }
}

void GameTextSetPadPlayer(int index, int value)
{
    _GameText_aPadPlayers[index] = value;
}

int GameTextGetPadPlayer(int index)
{
    return _GameText_aPadPlayers[index];
}

int GameTextFindPlayerPad(int value)
{
    for (int i = 0; i < 10; ++i) {
        if (_GameText_aPadPlayers[i] == value) {
            return i;
        }
    }
    return -1;
}

void GameTextSetSetupActive(unsigned char value)
{
    if (GameModeTypeIsSpecial() == 0) {
        _GameText_bSetupActive = value;
    }
}

void GameTextGetEnteredName(char *pText, int length)
{
    MsgNameEntryGetName(pText, length);
}

void GameTextFormatWithCommas(int value, char *pText, int length)
{
    char previous[32];
    int negative = value < 0;
    value = value < 0 ? -value : value;
    pText[0] = 0;
    while (value != 0) {
        int remaining = value / 1000;
        unsigned short group = value % 1000;
        value = remaining;
        if (remaining == 0) {
            if (strlen(pText) != 0) {
                strcpy(previous, pText);
                sprintf(pText, "%d,%s", group, previous);
            } else {
                sprintf(pText, "%d", group);
            }
        } else if (strlen(pText) != 0) {
            strcpy(previous, pText);
            sprintf(pText, "%03d,%s", group, previous);
        } else {
            sprintf(pText, "%03d", group);
        }
    }
    if (strlen(pText) == 0) {
        sprintf(pText, "0");
    }
    if (negative) {
        strcpy(previous, pText);
        sprintf(pText, "-%s", previous);
    }
}

void GameTextFormatInitialAndName(Object_80039F5C *p, char *pText, int length)
{
    signed char initial = p->mUnknown2927[0];
    if (initial == 0 || initial == ' ') {
        fn_801C2D88(pText, length, "%s", p->mUnknown2927 + 21);
    } else {
        fn_801C2D88(pText, length, "%c. %s", initial, p->mUnknown2927 + 21);
    }
}
}
