/// Lock (header)
/// (c) 2018 Jani Nykänen

#ifndef __LOCK__
#define __LOCK__

#include "../engine/sprite.h"
#include "../engine/assets.h"

#include "obase.h"

/// Lock game object
EXTENDS_GAME_OBJECT 

    // Members
    bool opening;

AS ( LOCK );

/// Initialize locks
/// < ass Assets
void lock_init(ASSET_PACK* ass);

/// Create a new lock
/// < x X coordinate (in grid)
/// < y Y coordinate (in grid)
/// > A new lock
LOCK lock_create(int x, int y);

#endif // __LOCK__