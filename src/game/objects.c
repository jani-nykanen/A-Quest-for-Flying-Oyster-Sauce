/// Game objects (source)
/// (c) 2018 Jani Nykänen

#include "objects.h"

#include "../engine/graphics.h"

#include "boulder.h"
#include "key.h"

// Max amount of objects
#define MAX_OBJ 64
// Single type max
#define MAX_SINGLE_TYPE 32

// Objects
static OBJECT* objects[MAX_OBJ];
// Object count
static int objCount =0;


// Initialize objects
void obj_init(ASSET_PACK* ass)
{
    // Initialize game object types
    boulder_init(ass);
    key_init(ass);

    // Set default values
    objCount = 0;
}


// Update objects
void obj_update(float tm)
{
    int i = 0;
    for(; i < objCount; ++ i)
    {
        object_update(objects[i],tm);
    }
}


// Draw objects
void obj_draw()
{
    int i = 0;
    for(; i < objCount; ++ i)
    {
        object_draw(objects[i]);
    }
}


// Add an object
void obj_add(int id, int x, int y)
{
    if(id == 10)
    {
        objects[objCount ++] = (OBJECT*) malloc(sizeof(BOULDER));
        *((BOULDER*)objects[objCount -1]) = boulder_create(x,y);
    }
    else if(id == 8)
    {
        objects[objCount ++] = (OBJECT*) malloc(sizeof(KEY));
        *((KEY*)objects[objCount -1]) = key_create(x,y);
    }

}