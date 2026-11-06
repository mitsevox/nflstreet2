#include "game/Ball.h"
#include "game/Object_8017886C.h"

extern "C" {
unsigned char fn_8016B7C4(Point_8017886C *pTo);
float fn_8016B938(void);
}

/* Scales *pValue down once BallGetLandingPoint gives the ball's spot: to 85% when
   fn_8016B7C4 accepts that spot, then by a quarter of twice the
   fn_8016B938 factor (capped at 1). */
extern "C" void fn_8009F5A4(unsigned int *pValue)
{
    float scale = 0.25f;
    Ball_t *pBall;
    Vector_80039F5C spot;

    pBall = BallGetCurrent();
    if (pBall != 0 && BallGetLandingPoint(pBall, &spot) != 0) {
        float factor;
        float value;

        if (fn_8016B7C4((Point_8017886C *)&spot) != 0) {
            *pValue = *pValue * 85 / 100;
        }
        factor = fn_8016B938() * 2.0f;
        if (factor > 1.0f) {
            factor = 1.0f;
        }
        value = *pValue;
        *pValue = (unsigned int)(value - value * factor * scale);
    }
}
