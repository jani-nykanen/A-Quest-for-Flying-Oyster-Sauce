/// Game object base (header)
/// (c) 2018 Jani Nykänen

#ifndef __GOBJ_BASE__
#define __GOBJ_BASE__

#include "../engine/vector.h"
#include "../engine/sprite.h"

#include "stdbool.h"

#define EXTENDS_GAME_OBJECT typedef struct\
{\
int x;\
int y;\
VEC2 vpos;\
SPRITE spr;\
bool exist;\
void (*onUpdate) (void*,float);\
void (*onDraw) (void*);\
void (*onPlayerCollision)(void*,void*);\

#define AS(name) }name;

EXTENDS_GAME_OBJECT AS (OBJECT);

/// Update object
/// < o Object
/// < tm Timem mul.
void object_update(OBJECT* o, float tm);

/// Object-player collision
/// < o Object
/// < p Player
void object_player_collision(OBJECT* o, OBJECT* p);

/// Draw object
/// < o Object
void object_draw(OBJECT* o);


#endif // __GOBJ_BASE__