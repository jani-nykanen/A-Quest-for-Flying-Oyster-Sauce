/// Game object base (header)
/// (c) 2018 Jani Nykänen

#ifndef __GOBJ_BASE__
#define __GOBJ_BASE__

#include "../engine/vector.h"

#include "stdbool.h"

#define EXTENDS_GAME_OBJECT typedef struct\
{\
int x;\
int y;\
VEC2 vpos;\
bool exist;\

#define AS(name) }name;

#endif // __GOBJ_BASE__