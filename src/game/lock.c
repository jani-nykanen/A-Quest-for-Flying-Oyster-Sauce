/// Lock (source)
/// (c) 2018 Jani Nykänen

#include "lock.h"

#include "../engine/graphics.h"
#include "../engine/sample.h"

#include "../vpad.h"

#include "stage.h"
#include "player.h"
#include "status.h"

#include "stdio.h"
#include "math.h"

// Lock bitmap
static BITMAP* bmpLock;

// Sound effects
static SAMPLE* sOpen;


// Update lock location to collision map
static void lock_update_location(LOCK* lock)
{
    stage_set_collision_tile(lock->x,lock->y,1);
}



// Boulder-player collision
static void lock_player_collision(void* o, void* p)
{
    const float DELTA = 0.1f;

    PLAYER* pl = (PLAYER*)p;
    LOCK* lock = (LOCK*)o;

    if(lock->opening || !lock->exist) return;
   
    VEC2 stick = vpad_get_stick();

    if(!pl->moving && pl->y == lock->y && abs(pl->x-lock->x) == 1 
       && fabs(stick.x) > DELTA)
    {
        if(status_get_key_count() > 0)
        {
            status_remove_key();
            lock->opening = true;
            lock->preventMovement = true; 
            stage_set_tile(lock->x,lock->y,0);

            play_sample(sOpen,0.60f);
        }
    }
}


// Update lock
static void lock_update(void* o, float tm)
{
    LOCK* lock = (LOCK*)o;
    lock->preventMovement = false;
    if(!lock->exist) return;

    if(lock->opening)
    {
        spr_animate(&lock->spr,0,0,6,6,tm);
        lock->preventMovement = true;
        if(lock->spr.frame == 6)
        {
            lock->exist = false;
            stage_set_collision_tile(lock->x,lock->y,0);
        }
        return;
    }

    lock_update_location(lock);
}


// Draw lock
static void lock_draw(void* o)
{
    LOCK* lock = (LOCK*)o;
    if(lock->exist == false) return;

    if(lock->opening)
    {
        spr_draw(&lock->spr,bmpLock,lock->vpos.x,lock->vpos.y,0);
    }
}


// Reset lock
static void lock_reset(void* o)
{
    LOCK* lock = (LOCK*)o;
    
    lock->opening = false;
    lock->spr.frame = 0;
}


// Initialize
void lock_init(ASSET_PACK* ass)
{
    // Get assets
    bmpLock = (BITMAP*)get_asset(ass,"lock");
    sOpen = (SAMPLE*)get_asset(ass,"openLock");
}


// Create a new lock
LOCK lock_create(int x, int y)
{
    LOCK b;

    b.x = x;
    b.y = y;
    b.vpos = vec2(x*16.0f,y*16.0f);
    b.spr = create_sprite(16,16);
    b.onDraw = lock_draw;
    b.onUpdate = lock_update;
    b.onPlayerCollision = lock_player_collision;
    b.onReset = lock_reset;
    b.exist = true;
    b.opening = false;
    b.preventMovement = false;

    stage_set_collision_tile(b.x,b.y,1);

    return b;
}
