#ifndef GAME_VECTOR_80039F5C_H
#define GAME_VECTOR_80039F5C_H

/* Three-float point or direction. Kept apart from game/Object_80039F5C.h so that headers which
   only need the vector do not take that header's declarations. */
struct Vector_80039F5C {
    float mX;
    float mY;
    float mZ;
};

#endif
