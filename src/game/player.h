/// Player (header)
/// (c) 2018 Jani Nykänen

#ifndef __PLAYER__
#define __PLAYER__

#include "../engine/sprite.h"
#include "../engine/assets.h"

#include "obase.h"

/// Key game object
EXTENDS_GAME_OBJECT 

    /// Members
    /// ...

AS ( PLAYER );

/// Initialize player
/// < ass Assets
void pl_init(ASSET_PACK* ass);

/// Create a new player
/// < x X coordinate (in grid)
/// < y Y coordinate (in grid)
/// > A new player
PLAYER pl_create(int x, int y);

/// Update player
/// < pl Player object
/// < tm Time multiplier
void pl_update(PLAYER* pl, float tm);

/// Draw player
/// < pl Player object
void pl_draw(PLAYER* pl);

#endif // __PLAYER__