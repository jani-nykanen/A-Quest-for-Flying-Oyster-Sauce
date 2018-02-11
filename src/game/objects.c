/// Game objects (source)
/// (c) 2018 Jani Nykänen

#include "objects.h"

#include "../engine/graphics.h"

#include "boulder.h"
#include "key.h"
#include "star.h"
#include "player.h"

// Max amount of objects
#define MAX_OBJ 64

// Objects
static OBJECT* objects[MAX_OBJ];
// Object count
static int objCount =0;

// Player object
static PLAYER player;


// Initialize objects
void obj_init(ASSET_PACK* ass)
{
    // Initialize game object types
    boulder_init(ass);
    key_init(ass);
    star_init(ass);
    pl_init(ass);

    // Set default values
    objCount = 0;
}


// Update objects
void obj_update(float tm)
{
    // Update game objects
    int i = 0;
    for(; i < objCount; ++ i)
    {
        object_update(objects[i],tm);
        object_player_collision(objects[i],(OBJECT*)&player);
    }

    // Update player
    pl_update(&player,tm);
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
    if(id == 10)
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

}