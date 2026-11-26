#ifndef GAME_SCRMPLAYRESULT_H
#define GAME_SCRMPLAYRESULT_H

extern "C" int MathArcTan2(float y, float x);

/* Position on the field: mX across, mY along it. */
struct FieldPoint_t {
    float mX;
    float mY;

    /* Angle of the point seen from the origin. */
    int Heading() const { return MathArcTan2(mY, mX); }
};

/* The object whose address ScrmGetPlayResult returns; ScrmStatEndPlay receives one
   for the play just finished. Only the accessed fields are declared. */
struct ScrmPlayResult_t {
    int mUnknown00;
    int mUnknown04;
    FieldPoint_t mUnknown08;
    float mUnknown10;
    float mUnknown14;
    int mUnknown18;
    unsigned char mUnknown1C;
    signed char mUnknown1D;
};

extern "C" ScrmPlayResult_t *ScrmGetPlayResult(void);

#endif
