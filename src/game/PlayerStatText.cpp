/* Player statistics text: the database column, the full name and the two-line column header of
   each of the 98 player statistics (tackles, kicking, passing, returns, receiving, rushing and the
   derived rates); the name table ends with "NULL" and the other two with a zero entry. On the
   GameCube no code reads them: the
   statistics screens that used them were discarded by the linker, and only the tables remain. */

/* Database column of each statistic (-1: none). */
int gPlayerStatColumns[99] = {
    -1, 0x61746467, 0x6C746467, 0x61746467, 0x6C626C67, 0x66666C67,
    0x72666C67, 0x79666C67, 0x74666C67, -1, 0x6B736C67, 0x61736C67,
    0x526C7367, 0x79697367, 0x6E697367, 0x74697367, -1, -1,
    0x61656B67, 0x62656B67, 0x6D656B67, 0x61666B67, -1, -1,
    0x63616B67, 0x64616B67, 0x65616B67, 0x62666B67, 0x4C666B67, 0x6D666B67,
    -1, -1, 0x636D6B67, 0x646D6B67, 0x656D6B67, 0x6B6E6B67,
    0x62746B67, -1, 0x616B7267, 0x4C6B7267, 0x746B7267, 0x796B7267,
    0x61706F67, 0x61736F67, 0x74616167, 0x6D636167, 0x63636167, 0x64706467,
    -1, -1, -1, -1, 0x6E696167, -1,
    0x4E6C6167, 0x61736167, 0x64746167, 0x61796167, -1, 0x61707267,
    0x4C707267, 0x74707267, 0x79707267, 0x74617067, 0x6C627067, 0x74707067,
    0x4E6C7067, 0x796E7067, 0x62747067, 0x61797067, 0x70326367, 0x61636367,
    0x72646367, 0x4C726367, 0x64746367, 0x61796367, 0x63796367, 0x79327567,
    0x70327567, 0x74617567, 0x74627567, 0x75667567, 0x4E6C7567, 0x64747567,
    0x61797567, 0x68797567, 0x70706370, 0x72706370, 0x63736370, 0x61726370,
    0x74646370, 0x70666370, 0x62746B67, 0x61756370, 0x6E756370, 0x616B6370,
    0x61706370, -1, 0x00000000,
};

/* Full name of each statistic. */
const char *gPlayerStatNames[99] = {
    "Knockdown", "Tack", "Tack Loss", "Tot Tack", "Pass Defl", "FF",
    "Fumb Rec", "Fumb Yds", "Fumb TD", "QB Hurry", "Sack", "Safety",
    "Int Long", "Int Yds", "Int", "Int TD", "Game", "G Start",
    "XPA", "XP Block", "XPM", "FGA", "FGA -29", "FGA 20-29",
    "FGA 30-39", "FGA 40-49", "FGA 50+", "FG Block", "FG Long", "FGM",
    "FGM -29", "FGM 20-29", "FGM 30-39", "FGM 40-49", "FGM 50+", "No.",
    "TB", "Knockdown", "KR", "KR Long", "KR TD", "KR Yds",
    "Pancake", "Sack", "Pass Att", "Pass Comp", "ConsecComp", "Pass Defl",
    "PassDrvAtt", "PassDrvComp", "PassDrvYds", "Pass Hurry", "Pass Int", "Pass KD",
    "Pass Long", "Pass Sack", "TD", "Yds", "PermLevel", "PR",
    "PR Long", "PR TD", "PR Yds", "No.", "Punt Block", "In 20",
    "Punt Long", "Net Yds", "TB", "Yds", "Rec 2Pt", "Rec",
    "Drops", "Rec Long", "TD", "Yds", "YAC", "20+ Yds",
    "Rush 2Pt", "Att", "BTK", "Rush Fumb", "Rush Long", "TD",
    "Yds", "After 1st Hit", "Comp%", "Rating", "Avg", "Avg",
    "Def TD", "FG%", "TB%", "Avg", "Net Avg", "Avg",
    "Avg", "Team", "NULL",
};

/* Two-line column header of each statistic. */
const char *gPlayerStatHeaders[99] = {
    "Knock\nDown", "\nTack", "Tack\nLoss", "Tot\nTack", "Pass\nDefl", "\nFF",
    "Fumb\nRec", "Fumb\nYds", "Fumb\nTD", "QB\nHurry", "\nSack", "\nSafety",
    "Int\nLong", "Int\nYds", "\nInt", "Int\nTD", "Game\nPlayed", "Game\nStart",
    "\nXPA", "XP\nBlock", "\nXPM", "\nFGA", "FGA\n-29", "FGA\n20-29",
    "FGA\n30-39", "FGA\n40-49", "FGA\n50+", "FG\nBlock", "FG\nLong", "\nFGM",
    "FGM\n-29", "FGM\n20-29", "FGM\n30-39", "FGM\n40-49", "FGM\n50+", "\nNo.",
    "\nTB", "Knock\nDown", "\nKR", "KR\nLong", "KR\nTD", "KR\nYds",
    "Pan-\ncake", "\nSack", "Pass\nAtt", "Pass\nComp", "Consec\nComp", "Pass\nDefl",
    "Pass\nDrvAtt", "Pass\nDrvComp", "Pass\nDrvYds", "Pass\nHurry", "Pass\nInt", "Pass\nKD",
    "Pass\nLong", "Pass\nSack", "\nTD", "\nYds", "Perm\nLevel", "\nPR",
    "PR\nLong", "PR\nTD", "PR\nYds", "\nNo.", "Punt\nBlock", "Punt\nIn 20",
    "Punt\nLong", "Net\nYds", "\nTB", "\nYds", "Rec\n2Pt", "\nRec",
    "\nDrops", "Rec\nLong", "\nTD", "\nYds", "\nYAC", "20+\nYds",
    "Rush\n2Pt", "\nAtt", "\nBTK", "Rush\nFumb", "Rush\nLong", "\nTD",
    "\nYds", "After\n1st Hit", "\nComp%", "\nRating", "\nAvg", "\nAvg",
    "Def\nTD", "\nFG%", "\nTB%", "\nAvg", "Net\nAvg", "\nAvg",
    "\nAvg", "\nTeam", 0,
};
