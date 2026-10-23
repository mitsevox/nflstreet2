#ifndef GAME_DIRECTIONS_8012430C_H
#define GAME_DIRECTIONS_8012430C_H

/* Eight per-direction costs, one per 45-degree sector, cleared and filled by
   fn_8012430C/fn_80124374 through the callback table lbl_8029F584. */
struct Directions_8012430C {
    float mCost[8];
};

#endif
