/// Game objects (header)
/// (c) 2018 Jani Nykänen

#ifndef __GAME_OBJECTS__
#define __GAME_OBJECTS__

#include "../engine/assets.h"

#include "stdbool.h"

/// Reset game objects
void obj_reset();

/// Initialize objects
/// < ass Asset pack
void obj_init(ASSET_PACK* ass);

/// Update objects
/// < tm Time mul.
void obj_update(float tm);

/// Draw objects
void obj_draw();

/// Add an object
/// < id Type identifier
/// < x X coordinate (in grid)
/// < y Y coordinate (in grid)
void obj_add(int id, int x, int y);

/// Get if the obstacles have stopped moving/acting
/// > True or false
bool obj_can_move();

#endif // __GAME_OBJECTS__