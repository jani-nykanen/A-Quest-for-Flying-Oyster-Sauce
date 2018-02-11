/// Boulder (header)
/// (c) 2018 Jani Nykänen

#ifndef __BOULDER__
#define __BOULDER__

#include "../engine/sprite.h"
#include "../engine/assets.h"

#include "obase.h"

/// Boulder game object
EXTENDS_GAME_OBJECT 

    // Members
    bool moving;
    bool falling;

    float gravity;

AS ( BOULDER );

/// Initialize boulders
/// < ass Assets
void boulder_init(ASSET_PACK* ass);

/// Create a new boulder
/// < x X coordinate (in grid)
/// < y Y coordinate (in grid)
/// > A new boulder
BOULDER boulder_create(int x, int y);

#endif // __BOULDER__