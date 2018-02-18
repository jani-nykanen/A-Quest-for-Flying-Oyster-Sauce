/// Enemy (header)
/// (c) 2018 Jani Nykänen

#ifndef __ENEMY__
#define __ENEMY__

#include "../engine/sprite.h"
#include "../engine/assets.h"

#include "obase.h"

/// Enemy game object
EXTENDS_GAME_OBJECT 

    // Members
    // ...
    int id;
    bool moving;
    int dir;
    int sprDir;
    bool falling;
    float gravity;

AS ( ENEMY );

/// Initialize enemies
/// < ass Assets
void enemy_init(ASSET_PACK* ass);

/// Create a new enemy
/// < x X coordinate (in grid)
/// < y Y coordinate (in grid)
/// < id Enemy id
/// > A new enemy
ENEMY enemy_create(int x, int y, int id);

#endif // __ENEMY__