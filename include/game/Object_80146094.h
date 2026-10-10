#ifndef GAME_OBJECT_80146094_H
#define GAME_OBJECT_80146094_H

/* Four-float record copied whole from the table lbl_802DD68C. */
struct Color_802DD68C {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
};

/* Three floats copied whole between the point slots of Trail_80146FDC. */
struct Point_80146FDC {
    float x;
    float y;
    float z;
};

/* One of the four 0x8C-byte point histories at the start of
   Object_80146094. Each update fills mSource[0]/mSource[1] through
   fn_80146F74 from the matrix indices mIndex[0]/mIndex[1] and stores one
   of them into the eight-entry ring mPoints at mHead. */
struct Trail_80146FDC {
    Point_80146FDC mPoints[8];
    Point_80146FDC mSource[2];
    int mHead;
    unsigned int mCount;
    int mToggle;
    int mIndex[2];
};

/* 0xB4-byte record copied whole from the object at +0x5C. */
struct Block_801470F0 {
    int mUnknown[45];
};

/* 0x36-byte record copied whole from the object at +0x248. */
struct Half_801470F0 {
    short mUnknown[27];
};

/* Block at +0x1444 of Object_8003DEC4 (0x5AC bytes, to the end of the
   object). */
struct Object_80146094 {
    Trail_80146FDC mTrails[4];
    float mUnknown230;
    unsigned int mUnknown234;
    int mUnknown238;
    unsigned char mUnknown23C;
    Color_802DD68C mUnknown240;
    Color_802DD68C mUnknown250;
    float mUnknown260[2][4][4];
    Block_801470F0 mUnknown2E0[2];
    Point_80146FDC mUnknown448[2];
    int mUnknown460[2];
    Half_801470F0 mUnknown468[2];
    float mUnknown4D4[2][4][4];
    int mUnknown554;
    unsigned int mUnknown558;
    int mUnknown55C;
    unsigned char mUnknown560;
    float mUnknown564;
    unsigned char mUnknown568;
    float mUnknown56C;
    float mUnknown570;
    float mUnknown574;
    char mPad578[0x57C - 0x578];
    unsigned char mUnknown57C;
    float mUnknown580;
    float mUnknown584;
    float mUnknown588;
    char mPad58C[0x590 - 0x58C];
    float mUnknown590;
    float mUnknown594;
    float mUnknown598;
    char mPad59C[0x5A0 - 0x59C];
    unsigned int mUnknown5A0;
    int mUnknown5A4;
    unsigned int mUnknown5A8;
};

#endif
