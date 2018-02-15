//// Star (header)
/// (c) 2018 Jani Nykänen

#ifndef __STAR__
#define __STAR__

#include "../engine/sprite.h"
#include "../engine/assets.h"

#include "obase.h"

/// Key game object
EXTENDS_GAME_OBJECT 

    // Member variables
    float floatTimer;
    bool collected;

AS ( STAR );

/// Initialize stars
/// < ass Assets
void star_init(ASSET_PACK* ass);

/// Create a new star
/// < x X coordinate (in grid)
/// < y Y coordinate (in grid)
/// > A new star
STAR star_create(int x, int y);

#endif // __STAR__