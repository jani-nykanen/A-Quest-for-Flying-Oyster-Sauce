/// Coin (header)
/// (c) 2018 Jani Nykänen

#ifndef __COIN__
#define __COIN__

#include "../engine/sprite.h"
#include "../engine/assets.h"

#include "obase.h"

/// Key game object
EXTENDS_GAME_OBJECT 

    // Member variables
    float floatTimer;
    bool dying;
    int type;

AS ( COIN );

/// Initialize coins
/// < ass Assets
void coin_init(ASSET_PACK* ass);

/// Create a new coin
/// < x X coordinate (in grid)
/// < y Y coordinate (in grid)
/// < type Type
/// > A new coin
COIN coin_create(int x, int y, int type);

#endif // __COIN__