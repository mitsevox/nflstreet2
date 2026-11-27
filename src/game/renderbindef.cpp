// Render bin definitions: the code-less data file of the game's render bins. It names the
// sixteen bins GLIB::Init hands to the render library, in drawing order; the library fills in
// every other field when it allocates the list.
#include "engine/llrender.h"

RenderBin_t RenderBin_GameDefs[16] = {
    { "SKY" },
    { "FIELD" },
    { "DMSHADOW" },
    { "OVERLAY" },
    { "ENVIRONMENT" },
    { "COMPRESSEDENVIRONMENT" },
    { "STATIC" },
    { "WALLSHADOW" },
    { "DMSIDELINE" },
    { "GAMEBRKSCRIM" },
    { "PLAYERS" },
    { "MISC" },
    { "PARTICLES" },
    { "RAINSNOW" },
    { "UISTUDIO" },
    { "SCREENTRANS" },
};
