#ifndef GAME_CLASS_8018FD64INLINE_H
#define GAME_CLASS_8018FD64INLINE_H

#include "game/Class_8018FD64.h"

/* Inline definition of the Class_8018FD64 constructor (the body of
   0x8018FD64: vtable 0x802AB4F8, then the Object_8007A334 constructor).
   Files that build the object as a local store those values themselves
   (0x8001F26C, 0x80052FC8, 0x8007BF9C, 0x8007C5C4, 0x8008259C and others), so
   the definition was visible there. src/game/cu_8002373C.cpp calls 0x8018FD64
   for its member, and ProDG 3.9.3 expands a visible inline constructor there
   too, so that file sees only the declaration and does not include this. */
inline Class_8018FD64::Class_8018FD64() {}

#endif
