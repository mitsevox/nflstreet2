#ifndef ENGINE_T3DB_COLS_H
#define ENGINE_T3DB_COLS_H

/* Column list element passed to fn_801F9718 (src/engine/t3db.c); a list ends at mCol == -1. */
typedef struct TDbCol_801F9718 {
    int mUnk0;
    int mUnk4;
    int mCol;
    int mIdx;
} TDbCol_801F9718;

/* Column description filled by fn_801F9AB8 (src/engine/t3db.c). */
typedef struct TDbColInfo_801F9AB8 {
    int mType;
    int mUnk4;
    int mCol;
    int mSize;
} TDbColInfo_801F9AB8;

#endif
