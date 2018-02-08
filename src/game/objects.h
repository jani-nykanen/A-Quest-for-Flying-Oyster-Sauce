/// Game objects (header)
/// (c) 2018 Jani Nykänen

#ifndef __GAME_OBJECTS__
#define __GAME_OBJECTS__

#include "../engine/assets.h"

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

#endif // __GAME_OBJECTS__