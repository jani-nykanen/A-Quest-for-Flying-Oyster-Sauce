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
    int dir;

    bool moving;
    bool checkGravity;
    bool falling;
    bool climbing;
    bool jumping;
    bool bouncing;
    bool pushing;
    bool startedMoving;
    bool dying;

    int deathMode;

    VEC2 target;
    VEC2 delta;
    
    float gravity;
    float speed;

AS ( PLAYER );

/// Initialize player
/// < ass Assets
void pl_init(ASSET_PACK* ass);

/// Reset player
/// < pl Player to reset
void pl_reset(PLAYER* pl);

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