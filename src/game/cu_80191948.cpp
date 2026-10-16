#include <string.h>
#include <stdio.h>
#include "game/fn_8007F828.h"
#include "game/Callees_801D57E0.h"
#include "game/fn_80191948.h"

extern "C" {
int fn_801D6850(void);
int fn_801D673C(int index);
void fn_801D5764(int value, char *pText, int size);
void fn_80029BBC(int value, char *pOut, int size);
unsigned int fn_80029838(int value);
int fn_8002A824(void);
char *fn_801D6918(void);
void fn_80191868(int value, char *pOut, int size, int unused, const char *pText);
int fn_801C2D88(char *pOut, int size, const char *pFormat, ...);
void fn_80191C70(int value, int index, char *pA, char *pB, int flag, char *pC, char *pD, char *pE);
extern unsigned char lbl_803EB720;
extern const char lbl_802ABDB8[];
extern const char lbl_802ABD9C[];
extern const char lbl_802ABDBC[];

void fn_80191948(int value, Object_80191948 *pA, Object_80191948 *pB, Object_80191948 *pC)
{
    char text[32];
    char textB[32];
    char textC[32];
    char textD[32];
    int index = fn_801D671C();
    int flag = 0;
    text[0] = lbl_802ABDB8[0];
    textB[0] = lbl_802ABDB8[0];

    switch (value) {
    case 1: case 5: case 8: case 15: case 50: case 59: case 94: case 119: case 122:
        fn_801D6B24(text, 32);
        if (strcmp(text, lbl_802ABD9C) == 0) {
            fn_80029BBC(fn_801D6850(), text, 32);
        }
        break;
    case 63: {
        int key = fn_801D6850();
        if (key < 1 || key > 3) {
            flag = lbl_803EB720;
        }
    }
    case 2:
        switch (fn_801D6850()) {
        case 1:
            fn_80029BBC(fn_801D6850(), text, 32);
            break;
        case 2: case 3:
            fn_801D6B24(textC, 32);
            if (strcmp(textC, lbl_802ABD9C) == 0) {
                fn_80029BBC(fn_801D6850(), text, 32);
            } else {
                fn_80029BBC(fn_801D6850(), textD, 32);
                fn_801C2D88(text, 32, lbl_802ABDBC, textD, textC);
            }
            break;
        }
        break;
    case 4: case 9: case 10: case 17: case 19: case 23: case 51: case 93: case 98: case 99: case 114: case 117: case 123:
        fn_80029BBC(fn_801D6850(), text, 32);
        break;
    case 6: case 91: case 107: case 111: case 113: case 120:
        strcpy(text, fn_801D6918());
        break;
    case 22: case 64: case 65: case 96: case 97: case 115: case 116:
        fn_80029BBC(fn_801D6850(), text, 32);
        fn_80191868(fn_80029838(fn_801D6850()), textB, 32, 0, 0);
        break;
    case 55:
        fn_80191868(fn_8002A824(), text, 32, 0, 0);
        break;
    }
    fn_80191C70(value, index, text, textB, flag, pA->mpUnknown8, pB->mpUnknown8, pC->mpUnknown8);
}

void fn_80191C70(int value, int index, char *pA, char *pB, int flag, char *pC, char *pD, char *pE)
{
    char text[16];
    char textB[12];
    char textC[8];
    char textD[18];
    char textE[32];
    char textF[] = " Auto Save has been disabled.";

    memcpy(pC, lbl_802ABDB8, 1);
    memcpy(pD, lbl_802ABDB8, 1);
    memcpy(pE, lbl_802ABDB8, 1);
    if (fn_8007F828(12) != 1) {
        memcpy(textF, lbl_802ABDB8, 1);
    }
    int key = fn_801D673C(index);
    fn_801D5764(-1, textB, 12);
    if (strcmp(pA, "UserID") == 0) {
        strcpy(pA, "User ID");
    }
    if (index != -1) {
        fn_801D57E0(index, textC, 7);
        fn_801D5764(key, text, 12);
    } else {
        strcpy(textC, "invalid");
        strcpy(text, "invalid");
    }

    switch (value) {
    case 99:
        sprintf(pD, "No %s found on %s.", pA, textB);
        break;
    case 100:
        sprintf(pD, "The %s is incompatible with this game.", textB);
        break;
    case 101:
        sprintf(pD, "Wrong device in %s.\nPlease insert a Memory Card.", textC);
        break;
    case 102:
        sprintf(pD, "The %s is damaged and cannot be used.", textB);
        break;
    case 103:
    case 104:
        sprintf(pD, "The %s is corrupted and needs to be formatted.", textB);
        break;
    case 90:
        sprintf(pD, "No %s found.", textB);
        break;
    case 118:
        memcpy(pD, lbl_802ABDB8, 1);
        break;
    case 0:
        sprintf(pD, "Checking %s in %s.\nDo not touch %s\nor POWER Button.", text, textC, text);
        break;
    case 67:
        sprintf(pD, "Checking %s.", textC);
        break;
    case 1:
        sprintf(pD, "Loading %s from\n%s in %s.  Do\nnot touch the %s\nor POWER Button.", pA, text, textC, text);
        break;
    case 2:
        sprintf(pD, "Saving %s\nto the %s in %s. Do\nnot touch the %s\nor POWER Button.", pA, text, textC, text);
        break;
    case 17:
        sprintf(pD, "Deleting %s from\n%s in %s.\nDo not touch the %s\nor POWER Button.", pA, text, textC, text);
        break;
    case 20:
        sprintf(pD, "Formatting\n%s in %s. \nDo not touch the %s\n or POWER Button.", text, textC, text);
        break;
    case 3:
        strcpy(pC, "!");
        sprintf(pD, "Error checking %s in %s.", textB, textC);
        strcpy(pE, "|^Continue");
        break;
    case 5:
        strcpy(pC, "!");
        sprintf(pD, "Error saving %s to %s in %s.", pA, text, textC);
        strcpy(pE, "|^Continue");
        break;
    case 50:
        strcpy(pC, "!");
        sprintf(pD, "%s does not exist on %s in %s.", pA, text, textC);
        strcpy(pE, "|^Continue");
        break;
    case 15:
        strcpy(pC, "!");
        sprintf(pD, "Error deleting %s from %s in %s.", pA, text, textC);
        strcpy(pE, "|^Continue");
        break;
    case 16:
        strcpy(pC, "!");
        sprintf(pD, "Error formatting %s in %s.", textB, textC);
        strcpy(pE, "|^Continue");
        break;
    case 6:
        strcpy(pC, "!");
        strcpy(pE, "|^Continue");
        sprintf(pD, "%s failed!\nThe %s in %s was removed during use.", pA, textB, textC);
        break;
    case 111:
        strcpy(pC, "!");
        strcpy(pE, "|Continue Without Saving|^Retry");
        sprintf(pD, "%s failed!\nThe %s in %s was removed during use.%s", pA, textB, textC, textF);
        break;
    case 120:
        strcpy(pC, "!");
        sprintf(pD, "%s failed!\nThe %s in %s was removed during use.", pA, textB, textC);
        strcpy(pE, "|Continue Without Loading Any Files|^Retry");
        break;
    case 91:
        strcpy(pC, "!");
        sprintf(pD, "%s failed!\nThe %s in %s was removed during use.", pA, textB, textC);
        strcpy(pE, "|^Continue");
        break;
    case 107:
        strcpy(pC, "!");
        sprintf(pD, "%s failed!\nThe %s in %s was removed during use.", pA, textB, textC);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 113:
        strcpy(pC, "!");
        sprintf(pD, "%s failed!\nThe %s in %s was removed during use.", pA, textB, textC);
        strcpy(pE, "|^Continue");
        break;
    case 11:
        strcpy(pC, "!");
        sprintf(pD, "Save successful.");
        strcpy(pE, "|^Continue");
        break;
    case 13:
        strcpy(pC, "!");
        sprintf(pD, "Delete successful.");
        strcpy(pE, "|^Continue");
        break;
    case 12:
        strcpy(pC, "!");
        sprintf(pD, "Load successful.");
        strcpy(pE, "|^Continue");
        break;
    case 14:
        strcpy(pC, "!");
        sprintf(pD, "Format successful.");
        strcpy(pE, "|^Continue");
        break;
    case 10:
        strcpy(pC, "!");
        sprintf(pD, "Overwriting will cause previously saved information to be lost. Are you sure you want to overwrite the existing %s information? Continuing without saving will disable Auto Save.", pA);
        strcpy(pE, "|Continue Without Saving|Overwrite|^Cancel");
        break;
    case 123:
        strcpy(pC, "!");
        sprintf(pD, "Loading an %s save will cause any unsaved %s information to be lost.", pA, pA);
        strcpy(pE, "|Continue|^Cancel");
        break;
    case 119:
        strcpy(pC, "!");
        sprintf(pD, "The maximum number of loaded User IDs has been reached. You must replace %s to create or load another. Any unsaved information in %s will be lost.", pA, pA);
        strcpy(pE, "|Replace User ID|^Cancel");
        break;
    case 18:
        strcpy(pC, "!");
        strcpy(pD, "If you delete the file, saved data will be lost.\nAre you sure you want to delete?");
        strcpy(pE, "|Yes|^No");
        break;
    case 42:
        strcpy(pC, "!");
        sprintf(pD, "Formatting the %s will erase all previously saved data. Do you wish to proceed with formatting?", textB);
        strcpy(pE, "|Format|^Cancel");
        break;
    case 60:
        strcpy(pC, "!");
        sprintf(pD, "Loading will replace an existing file in memory.\nAre you sure you want to load?");
        strcpy(pE, "|Yes|^No");
        break;
    case 4:
    case 9:
        strcpy(pC, "!");
        sprintf(pD, "The NFL STREET 2 %s file on\nthe %s in %s is corrupted.  This file needs to be deleted.", pA, text, textC);
        strcpy(pE, "|Continue Without Loading|^Retry|Delete");
        break;
    case 8:
        strcpy(pC, "!");
        sprintf(pD, "The NFL STREET 2 %s file on\nthe %s in %s is corrupted.  This file needs to be deleted.%s", pA, text, textC, textF);
        strcpy(pE, "|Continue Without Saving|^Retry|Cancel|Delete");
        break;
    case 24:
        strcpy(pC, "!");
        sprintf(pD, "Wrong device in %s. Please insert a %s.", textC, textB);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 109:
        strcpy(pC, "!");
        sprintf(pD, "Save failed!\nWrong device in %s. Please insert a %s.%s", textC, textB, textF);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 26:
        strcpy(pC, "!");
        sprintf(pD, "The %s in %s is incompatible with this game.", textB, textC);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 108:
        strcpy(pC, "!");
        sprintf(pD, "Save failed!\nThe %s in %s is incompatible with this game.%s", textB, textC, textF);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 21:
        strcpy(pC, "!");
        sprintf(pD, "The %s in %s is damaged and cannot be used.", textB, textC);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 94:
        strcpy(pC, "!");
        sprintf(pD, "The %s in %s is formatted for another market.", textB, textC);
        strcpy(pE, "|^Continue");
        break;
    case 58:
    case 59:
        strcpy(pC, "!");
        sprintf(pD, "The %s in %s is corrupted and needs to be formatted.", textB, textC);
        sprintf(pE, "|Continue Without Saving|^Retry|Format %s", textB);
        break;
    case 25:
    case 33:
        strcpy(pC, "!");
        sprintf(pD, "The %s in %s is corrupted and needs to be formatted.%s", textB, textC, textF);
        sprintf(pE, "|Continue Without Saving|^Retry|Format %s", textB);
        break;
    case 112:
        strcpy(pC, "!");
        sprintf(pD, "The %s in %s is corrupted and needs to be formatted.", textB, textC);
        sprintf(pE, "|Continue Without Loading|^Retry|Format %s", textB);
        break;
    case 93:
        strcpy(pC, "!");
        sprintf(pD, "The NFL STREET 2 %s file on\nthe %s in %s is corrupted.  This file needs to be deleted.", pA, text, textC);
        strcpy(pE, "|Continue Without Loading|^Retry|Delete");
        break;
    case 52:
        strcpy(pC, "!");
        sprintf(pD, "You cannot save under this category.");
        strcpy(pE, "|^Continue");
        break;
    case 56:
        strcpy(pC, "!");
        sprintf(pD, "You exceeded the number of teams allowed. Some could not be loaded.");
        strcpy(pE, "|^Continue");
        break;
    case 57:
        strcpy(pC, "!");
        sprintf(pD, "The %s in %s is damaged and cannot be used.\nYou will not be able to save game data if you continue.", textB, textC);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 105:
    case 106:
        strcpy(pC, "!");
        sprintf(pD, "Save failed!\nThe %s in %s is damaged and cannot be used.%s", textB, textC, textF);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 92:
        strcpy(pC, "!");
        sprintf(pD, "The %s in %s is damaged and cannot be used.", textB, textC);
        strcpy(pE, "|^Continue");
        break;
    case 51:
        strcpy(pC, "!");
        sprintf(pD, "One or more NFL STREET 2 %s files on the %s in %s are corrupted.  These files need to be deleted.", pA, text, textC);
        strcpy(pE, "|Continue Without Loading Any Files|^Retry|Delete");
        break;
    case 114:
        strcpy(pC, "!");
        sprintf(pD, "The NFL STREET 2 %s file on\nthe %s in %s is corrupted.  This file needs to be deleted.", pA, text, textC);
        strcpy(pE, "|Continue|^Retry|Delete");
        break;
    case 63:
        strcpy(pC, "!");
        if (fn_801D6850() == 0) {
            if (flag == 1) {
                sprintf(pD, "Do you want to save all your files to %s?\nWARNING! Not saving may lose your current files.", textB);
            } else {
                sprintf(pD, "Do you want to save all your files to %s?", textB);
            }
        } else {
            sprintf(pD, "Do you want to save %s?  All unsaved information may be lost.", pA);
        }
        strcpy(pE, "|^Save|Continue Without Saving|Cancel");
        break;
    case 64:
    case 97:
    case 115:
    case 116:
        strcpy(pC, "!");
        sprintf(pD, "Unable to save %s.\nThere is not enough free space on the %s in %s. To save, you need 1 file and %s.%s", pA, textB, textC, pB, textF);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 19:
    case 98:
        strcpy(pC, "!");
        sprintf(pD, "Unable to save %s to \n%s in %s. The maximum number of %s saves has been reached. %s", pA, textB, textC, pA, textF);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 55:
        strcpy(pC, "!");
        sprintf(pD, "No %s could be found.  If you wish to save, please insert a %s now. ", textB, textB);
        sprintf(pD + strlen(pD), "NFL STREET 2 needs the following amount of files and blocks free to save new files:\n");
        fn_80191868(fn_80029838(1), textD, 18, 0, 0);
        sprintf(pD + strlen(pD), "Options requires 1 file and %s.\n", textD);
        fn_80191868(fn_80029838(2), textD, 18, 0, 0);
        sprintf(pD + strlen(pD), "User ID requires 1 file and %s.\n", textD);
        fn_80191868(fn_80029838(3), textD, 18, 0, 0);
        sprintf(pD + strlen(pD), "Player Export requires 1 file and %s.\n", textD);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 96:
        strcpy(pC, "!");
        sprintf(pD, "Unable to save %s.  No\n%s found in %s. To save, you need 1 file and %s.", pA, textB, textC, pB);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 65:
        strcpy(pC, "!");
        sprintf(pD, "Unable to save %s.  No %s found in Slot A. To save, you need 1 file and\n%s.%s", pA, textB, pB, textF);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 41:
        strcpy(pC, "!");
        sprintf(pD, "The %s in %s has been removed or replaced.%s", textB, textC, textF);
        strcpy(pE, "|Continue Without Saving|^Retry");
        break;
    case 62:
        strcpy(pC, "!");
        sprintf(pD, "The %s in %s does not\nhave sufficient space to save new\nNFL STREET 2 save files.\n", text, textC);
        fn_80191868(fn_80029838(1), textD, 18, 0, 0);
        sprintf(pD + strlen(pD), "Options requires 1 file and %s.\n", textD);
        fn_80191868(fn_80029838(2), textD, 18, 0, 0);
        sprintf(pD + strlen(pD), "User ID requires 1 file and %s.\n", textD);
        fn_80191868(fn_80029838(3), textD, 18, 0, 0);
        sprintf(pD + strlen(pD), "Player Export requires 1 file and %s.\n", textD);
        sprintf(pD + strlen(pD), "Existing files may be loaded and overwritten.");
        sprintf(pE, "|Continue Without Saving|^Retry|Manage %s", text);
        break;
    case 22:
        strcpy(pC, "!");
        sprintf(pD, "Insufficient space on %s in %s. %s requires 1 file and %s of free space.", text, textC, pA, pB);
        sprintf(pE, "|Continue Without Saving|^Retry");
        break;
    case 23:
    case 117:
        strcpy(pC, "!");
        sprintf(pD, "The %s you have selected is already loaded.", pA);
        strcpy(pE, "|^Continue");
        break;
    case 69:
        strcpy(pC, "!");
        sprintf(pD, "There is insufficient space on the %s in %s to save an %s.  Insert a %s with at least 1 file and %s available.", textB, textC, pA, textB, pB);
        sprintf(pE, "|^Retry|Cancel");
        break;
    case 71:
        strcpy(pC, "!");
        sprintf(pD, "No %s found on the %s in %s. In order to use %s, insert a %s with an existing %s or save one now.", pA, textB, textC, pA, textB, pA);
        strcpy(pE, "|^Retry|Save|Cancel");
        break;
    case 72:
        strcpy(pC, "!");
        sprintf(pD, "The %s previously loaded could not be found.  Either reinsert the %s in %s with the previously loaded %s or save a new %s.", pA, textB, textC, pA, pA);
        strcpy(pE, "|^Retry|Save new|Cancel");
        break;
    case 80:
        strcpy(pC, "!");
        sprintf(pD, "Saving a new %s will %s.", pA, pB);
        strcpy(pE, "|Save|^Cancel");
        break;
    case 73:
        strcpy(pC, "!");
        sprintf(pD, "The %s previously loaded was deleted.  In order to use %s, you need to save %s to a %s in %s.", pA, pA, pA, textB, textC);
        strcpy(pE, "|Save|^Cancel");
        break;
    case 78:
        strcpy(pC, "!");
        sprintf(pD, "Delete your %s from the %s in %s?", pA, textB, textC);
        strcpy(pE, "|Delete|^Cancel");
        break;
    case 79:
        strcpy(pC, "!");
        sprintf(pD, "%s failed.  No %s was found on the %s in %s.", pA, pB, textB, textC);
        strcpy(pE, "|^Continue");
        break;
    case 81:
        strcpy(pC, "!");
        sprintf(pD, "%s failed.  No %s was found in %s.", pA, textB, textC);
        strcpy(pE, "|^Continue");
        break;
    case 82:
        strcpy(pC, "!");
        sprintf(pD, "The %s found on the %s in %s is not the one previously loaded.  If you continue, you will delete the existing %s, which will %s.  Do you wish to continue?", pA, textB, textC, pA, pB);
        strcpy(pE, "|Delete|^Cancel");
        break;
    case 74:
        strcpy(pC, "!");
        sprintf(pD, "The %s found on the %s in %s is not the one previously loaded.  Please reinsert the %s with the %s originally loaded, or overwrite the %s on this %s.", pA, textB, textC, textB, pA, pA, textB);
        strcpy(pE, "|^Retry|Overwrite|Cancel");
        break;
    case 77:
        strcpy(pC, "!");
        sprintf(pD, "The %s in %s already contains an existing %s.  If you continue, you will overwrite the existing %s, which will %s.  Do you wish to continue?", textB, textC, pA, pA, pB);
        strcpy(pE, "|Overwrite|^Cancel");
        break;
    case 83:
        strcpy(pC, "!");
        sprintf(pD, "The %s only stores detailed information for 25 products.  If you save, you will overwrite the product information and accomplishments for the oldest product.  Your EA SPORTS\260 Level will not be affected by this.  Are you sure you want to overwrite?", pA);
        strcpy(pE, "|Overwrite|^Cancel");
        break;
    case 68:
        strcpy(pC, "!");
        sprintf(pD, "No %s found in %s. In order to use %s, insert a %s with an existing %s or insert a %s with at least 1 file and %s available to save a new one.", textB, textC, pA, textB, pA, textB, pB);
        strcpy(pE, "|^Retry|Cancel");
        break;
    case 70:
        strcpy(pC, "!");
        sprintf(pD, "Your %s on the %s in %s is corrupt.  Do you wish to delete it?", pA, textB, textC);
        strcpy(pE, "|Delete|^Cancel");
        break;
    case 75:
        strcpy(pC, "!");
        sprintf(pD, "Wrong device in %s.  Insert a %s with an existing %s or insert a %s with at least 1 file and %s available to save one.", textC, textB, pA, textB, pB);
        strcpy(pE, "|^Retry|Cancel");
        break;
    case 76:
        strcpy(pC, "!");
        if (flag == 1) {
            sprintf(pD, "The %s in %s is damaged and cannot be used.  Insert a %s with an existing %s or insert a %s with at least 1 file and %s available to save one.", textB, textC, textB, pA, textB, pB);
            strcpy(pE, "|^Retry|Cancel");
        } else {
            sprintf(pD, "%s failed!  The %s in %s is damaged and cannot be used.", pA, textB, textC);
            strcpy(pE, "|^Continue");
        }
        break;
    case 85:
        strcpy(pC, "!");
        sprintf(pD, "Unable to repair your %s on the %s in %s.", pA, textB, textC);
        strcpy(pE, "|^Continue");
        break;
    case 86:
        strcpy(pC, "!");
        sprintf(pD, "Repair failed.  No %s was found on the %s in %s.", pA, textB, textC);
        strcpy(pE, "|^Continue");
        break;
    case 87:
        strcpy(pC, "!");
        sprintf(pD, "Repair failed.  No %s was found in %s.", textB, textC);
        strcpy(pE, "|^Continue");
        break;
    case 88:
        strcpy(pC, "!");
        sprintf(pD, "Repair successful.");
        strcpy(pE, "|^Continue");
        break;
    case 89:
        strcpy(pC, "!");
        sprintf(pD, "Your %s on the %s in %s is damaged.  It may be repairable, but some information about your EA SPORTS\260 games may be lost.  Some EA SPORTS\260 Levels may also be lost.  Do you wish to repair it?", pA, textB, textC);
        strcpy(pE, "|Repair|Delete|^Cancel");
        break;
    case 95:
        strcpy(pC, "!");
        sprintf(pD, "Load failed.  Please check the %s in %s and try again.", text, textC);
        strcpy(pE, "|^Continue");
        break;
    case 122:
        strcpy(pC, "!");
        sprintf(pD, "Ready to Delete. Do not touch the %s or POWER Button.", text);
        strcpy(pE, "|^Continue");
        break;
    case 43:
    case 54:
    case 110:
    default:
        strcpy(textE, fn_801D6918());
        strcpy(pC, "!");
        sprintf(pD, "%s failed.  Please check the %s in %s and try again.", textE, text, textC);
        strcpy(pE, "|^Continue");
        break;
    }
}
}
