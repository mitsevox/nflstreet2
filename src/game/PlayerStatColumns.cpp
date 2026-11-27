/* Player statistics columns: the categories of the player statistics screen (passing, rushing,
   receiving, blocking, defensive, kicking, punting and the two returns) and the header and flags
   of each of their 84 columns. On the GameCube no code reads them: the screen that used them was
   discarded by the linker, and only the tables and two literals of a discarded helper remain. */
#include "game/PlayerStatColumns.h"

extern "C" int sprintf(char *pOut, const char *pFormat, ...);

// FAKEMATCH: discarded file-static stand-in; its literals "01234567" and "%d" are the
// unreferenced first 16 bytes of this file's .rodata
static inline void _PlayerStatFormatValue(char *pText, int value)
{
    if (value < 0) {
        sprintf(pText, "01234567");
    } else {
        sprintf(pText, "%d", value);
    }
}

const PlayerStatCategory_t gPlayerStatCategories[9] = {
    { 0, "Passing", 11 },
    { 1, "Rushing", 10 },
    { 2, "Receiving", 9 },
    { 4, "Blocking", 2 },
    { 5, "Defensive", 14 },
    { 6, "Kicking", 19 },
    { 7, "Punting", 9 },
    { 8, "Kick return", 5 },
    { 8, "Punt return", 5 },
};

const PlayerStatColumn_t gPlayerStatCatColumns[84] = {
    /* Passing */
    { "\nRating", 1, 1, 1, 1 },
    { "\nYds", 1, 0, 0, 1 },
    { "\nTD", 1, 0, 0, 1 },
    { "\nInt", 0, 0, 1, 1 },
    { "\nComp", 1, 0, 0, 1 },
    { "\nAtt", 1, 0, 0, 1 },
    { "\nComp%", 1, 0, 1, 1 },
    { "\nAvg", 1, 1, 1, 1 },
    { "Yds /\nGame", 1, 1, 0, 1 },
    { "\nSack", 0, 0, 1, 0 },
    { "\nLong", 1, 0, 0, 0 },
    /* Rushing */
    { "\nYds", 1, 0, 0, 1 },
    { "\nTD", 1, 0, 0, 1 },
    { "\nAtt", 1, 0, 0, 1 },
    { "\nAvg", 1, 1, 1, 1 },
    { "Yds /\nGame", 1, 1, 0, 1 },
    { "\nFumb", 0, 0, 0, 0 },
    { "\nBTK", 1, 0, 0, 0 },
    { "After\n1st Hit", 1, 0, 0, 0 },
    { "20+\nYds", 1, 0, 0, 0 },
    { "\nLong", 1, 0, 0, 0 },
    /* Receiving */
    { "\nRec", 1, 0, 0, 1 },
    { "\nYds", 1, 0, 0, 1 },
    { "\nAvg", 1, 1, 1, 1 },
    { "\nTD", 1, 0, 0, 1 },
    { "Yds /\nGame", 1, 1, 0, 1 },
    { "\nYAC", 1, 0, 0, 0 },
    { "YAC\nAvg", 1, 1, 1, 0 },
    { "\nDrops", 0, 0, 1, 0 },
    { "\nLong", 1, 0, 0, 0 },
    /* Blocking */
    { "Pan-\ncake", 1, 0, 0, 0 },
    { "\nSack", 0, 0, 0, 0 },
    /* Defensive */
    { "\nTack", 1, 0, 0, 0 },
    { "Tack\nLoss", 1, 0, 0, 0 },
    { "\nSack", 1, 0, 0, 1 },
    { "\nInt", 1, 0, 0, 1 },
    { "Int\nYds", 1, 0, 0, 1 },
    { "Int\nAvg", 1, 1, 0, 1 },
    { "Int\nLong", 1, 0, 0, 0 },
    { "Pass\nDefl", 1, 0, 0, 0 },
    { "\nFF", 1, 0, 0, 1 },
    { "Fumb\nRec", 1, 0, 0, 1 },
    { "Fumb\nYds", 1, 0, 0, 0 },
    { "\nBlock", 1, 0, 0, 0 },
    { "\nSafety", 1, 0, 0, 0 },
    { "Def\nTD", 1, 0, 0, 0 },
    /* Kicking */
    { "\nFGM", 1, 0, 0, 1 },
    { "\nFGA", 1, 0, 0, 1 },
    { "\nFG%", 1, 0, 0, 1 },
    { "FG\nLong", 1, 0, 0, 0 },
    { "FG\nBlock", 0, 0, 0, 1 },
    { "\nXPM", 1, 0, 0, 1 },
    { "\nXPA", 1, 0, 0, 1 },
    { "\nXP%", 1, 0, 0, 1 },
    { "XP\nBlock", 0, 0, 0, 0 },
    { "FGM\n17-29", 1, 0, 0, 0 },
    { "FGA\n17-29", 1, 0, 0, 0 },
    { "FGM\n30-39", 1, 0, 0, 0 },
    { "FGA\n30-39", 1, 0, 0, 0 },
    { "FGM\n40-49", 1, 0, 0, 0 },
    { "FGA\n40-49", 1, 0, 0, 0 },
    { "FGM\n50+", 1, 0, 0, 0 },
    { "FGA\n50+", 1, 0, 0, 0 },
    { "\nNo.", 1, 0, 0, 0 },
    { "\nTB", 1, 0, 0, 0 },
    /* Punting */
    { "\nAvg", 1, 1, 0, 1 },
    { "\nNo.", 1, 0, 0, 1 },
    { "\nYds", 1, 0, 0, 1 },
    { "Net\nYds", 1, 0, 0, 0 },
    { "Net\nAvg", 1, 1, 0, 0 },
    { "\nBlock", 0, 0, 0, 1 },
    { "In\n20", 1, 0, 0, 1 },
    { "\nTB", 0, 0, 0, 0 },
    { "\nLong", 1, 0, 0, 0 },
    /* Kick return */
    { "\nAvg", 1, 1, 1, 1 },
    { "\nKR", 1, 0, 0, 1 },
    { "\nYds", 1, 0, 0, 1 },
    { "\nTD", 1, 0, 0, 0 },
    { "\nLong", 1, 0, 0, 0 },
    /* Punt return */
    { "\nAvg", 1, 1, 1, 1 },
    { "\nPR", 1, 0, 0, 1 },
    { "\nYds", 1, 0, 0, 1 },
    { "\nTD", 1, 0, 0, 0 },
    { "\nLong", 1, 0, 0, 0 },
};
