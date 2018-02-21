/// Game objects (source)
/// (c) 2018 Jani Nykänen

#include "objects.h"

#include "../engine/graphics.h"

#include "boulder.h"
#include "key.h"
#include "star.h"
#include "player.h"
#include "lock.h"
#include "enemy.h"
#include "coin.h"
#include "stage.h"

// Max amount of objects
#define MAX_OBJ 64

// Objects
static OBJECT* objects[MAX_OBJ];
// Object count
static int objCount =0;

// Player object
static PLAYER player;

// Can move
static bool canMove;


// Reset
void obj_reset()
{
    int i = 0;
    for(; i < objCount; ++ i)
    {
        object_reset(objects[i]);
    }
    pl_reset(&player);
}


// Initialize objects
void obj_init(ASSET_PACK* ass)
{
    // Initialize game object types
    boulder_init(ass);
    key_init(ass);
    star_init(ass);
    lock_init(ass);
    pl_init(ass);
    enemy_init(ass);
    coin_init(ass);

    // Set default values
    objCount = 0;
    canMove = true;
}


// Update objects
void obj_update(float tm)
{
    // Update game objects
    int i = 0;
    canMove = true;
    
    for(; i < objCount; ++ i)
    {
        object_update(objects[i],tm);
        object_player_collision(objects[i],(OBJECT*)&player);

        if(objects[i]->preventMovement)
            canMove = false;
    }

    // Update player
    pl_update(&player,tm);
    stage_player_elec_collision((void*)&player);
}


// Draw objects
void obj_draw()
{
    // Draw game objects
    int i = 0;
    for(; i < objCount; ++ i)
    {
        object_draw(objects[i]);
    }

    // Draw player
    pl_draw(&player);
}


// Add an object
void obj_add(int id, int x, int y)
{
    int oldCount = objCount;

    // TODO: Error checking
    if(id == 19 || id == 26)
    {
        objects[objCount ++] = (OBJECT*) malloc(sizeof(COIN));
        *((COIN*)objects[objCount -1]) = coin_create(x,y,id == 26 ? 1 : 0);
    }
    else if(id >= 11 && id <= 16)
    {
        objects[objCount ++] = (OBJECT*) malloc(sizeof(ENEMY));
        *((ENEMY*)objects[objCount -1]) = enemy_create(x,y,id-11);
    }
    else if(id == 10)
    {
        objects[objCount ++] = (OBJECT*) malloc(sizeof(BOULDER));
        *((BOULDER*)objects[objCount -1]) = boulder_create(x,y);
    }
    else if(id == 9)
    {
        objects[objCount ++] = (OBJECT*) malloc(sizeof(STAR));
        *((STAR*)objects[objCount -1]) = star_create(x,y);
    }
    else if(id == 8)
    {
        objects[objCount ++] = (OBJECT*) malloc(sizeof(KEY));
        *((KEY*)objects[objCount -1]) = key_create(x,y);
    }
    else if(id == 7)
    {
        player = pl_create(x,y);
    }
    else if(id == 6)
    {
        objects[objCount ++] = (OBJECT*) malloc(sizeof(LOCK));
        *((LOCK*)objects[objCount -1]) = lock_create(x,y);
    }

    // If new object was created, set start position
    if(oldCount < objCount)
    {
        objects[objCount -1]->startPos = point(x,y);
    }

}


// Can move
bool obj_can_move()
{
    return canMove;
}


// Clear objects
void obj_clear()
{
    int i = 0;
    for(; i < objCount; ++ i)
    {
        free(objects[i]);
    }
    objCount = 0;
}