/* Forwards unrecoverable disc errors to the registered fatal-message handler. */

#include "__dvd.h"

static void (*FatalFunc)(void);


static char JapaneseFatalMessage[] =
    "\n"
    "\n"
    "\n"
    "\203G\203\211\201[\202\252\224\255\220\266\202\265\202\334\202\265\202\275\201B\n"
    "\n"
    "\226{\221\314\202\314\203p\203\217\201[\203{\203^\203\223\202\360\211\237\202\265\202\304\223d\214\271\202\360OFF\202\311\202\265\201A\n"
    "\226{\221\314\202\314\216\346\210\265\220\340\226\276\217\221\202\314\216w\216\246\202\311\217]\202\301\202\304\202\255\202\276\202\263\202\242\201B";

static char EnglishFatalMessage[] =
    "\n"
    "\n"
    "\n"
    "An error has occurred.\n"
    "Turn the power off and refer to the\n"
    "Nintendo GameCube Instruction Booklet\n"
    "for further instructions.";

static char EnglishEuropeanFatalMessage[] =
    "\n"
    "\n"
    "\n"
    "An error has occurred.\n"
    "Turn the power off and refer to the\n"
    "Nintendo GameCube\231 Instruction Booklet\n"
    "for further instructions.";

static char GermanFatalMessage[] =
    "\n"
    "\n"
    "\n"
    "Ein Fehler ist aufgetreten.\n"
    "Bitte schalten Sie den NINTENDO GAMECUBE\n"
    "aus und lesen Sie die Bedienungsanleitung,\n"
    "um weitere Informationen zu erhalten.";

static char FrenchFatalMessage[] =
    "\n"
    "\n"
    "\n"
    "Une erreur est survenue.\n"
    "Eteignez la console et r\351f\351rez-vous au\n"
    "manuel d'instructions NINTENDO GAMECUBE\n"
    "pour de plus amples informations.";

static char SpanishFatalMessage[] =
    "\n"
    "\n"
    "\n"
    "Se ha producido un error.\n"
    "Apaga la consola y consulta el manual\n"
    "de instrucciones de NINTENDO GAMECUBE\n"
    "para obtener m\341s informaci\363n.";

static char ItalianFatalMessage[] =
    "\n"
    "\n"
    "\n"
    "Si \350 verificato un errore.\n"
    "Spegni (OFF) e controlla il manuale\n"
    "d'istruzioni del NINTENDO GAMECUBE\n"
    "per ulteriori indicazioni.";

static char DutchFatalMessage[] =
    "\n"
    "\n"
    "\n"
    "Er is een fout opgetreden.\n"
    "Zet de NINTENDO GAMECUBE uit en\n"
    "raadpleeg de handleiding van de\n"
    "Nintendo GameCube voor nadere\n"
    "instructies.";

const char *Japanese = JapaneseFatalMessage;
const char *English = EnglishFatalMessage;

void __DVDPrintFatalMessage(void) {
    if (FatalFunc) {
        FatalFunc();
    }
}
