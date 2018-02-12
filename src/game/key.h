/// Key (header)
/// (c) 2018 Jani Nykänen

#ifndef __KEY__
#define __KEY__

#include "../engine/sprite.h"
#include "../engine/assets.h"

#include "obase.h"

/// Key game object
EXTENDS_GAME_OBJECT 

    // Member variables
    float floatTimer;
    bool flying;
    float speedMul;

AS ( KEY );

/// Initialize keys
/// < ass Assets
void key_init(ASSET_PACK* ass);

/// Create a new key
/// < x X coordinate (in grid)
/// < y Y coordinate (in grid)
/// > A new key
KEY key_create(int x, int y);

#endif // __KEY__