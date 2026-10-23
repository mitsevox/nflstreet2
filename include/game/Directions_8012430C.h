#ifndef GAME_DIRECTIONS_8012430C_H
#define GAME_DIRECTIONS_8012430C_H

/* Eight per-direction costs, one per 45-degree sector, cleared and filled by
   fn_8012430C/fn_80124374 through the callback table lbl_8029F584. Indexed
   loads and stores name the record base first (lfsx f1,r3,r4 at
   0x801242F0), the form ProDG emits for an array member, not for a bare
   float pointer. */
struct Directions_8012430C {
    float mCost[8];
};

#endif
