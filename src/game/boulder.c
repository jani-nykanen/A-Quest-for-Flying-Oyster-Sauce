/// Boulder (source)
/// (c) 2018 Jani Nykänen

#include "boulder.h"

#include "../engine/graphics.h"

#include "../vpad.h"

#include "stage.h"
#include "player.h"

#include "stdio.h"
#include "math.h"

// Boulder bitmap
static BITMAP* bmpBoulder;


// Update boulder location to collision map
static void b_update_location(BOULDER* b)
{
    if(!stage_is_lava(b->x,b->y))
        stage_set_collision_tile(b->x,b->y,1);
}


// Get gravity
static void b_get_gravity(BOULDER* b)
{
    b->falling = false;
    b->gravity = 0.0f;

    int oldy = b->y;
    while(!stage_is_solid(b->x,b->y+1))
    {
        ++b->y;
    }

    if(b->y != oldy)
    {
        b->falling = true;
        stage_set_collision_tile(b->x,oldy,0);
    }
}


// Fall
static void b_fall(BOULDER* b, float tm)
{
    const float GRAV_MAX = 4.0f;
    const float GRAV_SPEED = 0.2f;

    float target = b->y*16.0f;

    if(b->vpos.y < target)
    {
        b->gravity += GRAV_SPEED * tm;
        if(b->gravity > GRAV_MAX)
        {
            b->gravity = GRAV_MAX;
        }
        b->vpos.y += b->gravity * tm;

        if(b->vpos.y >= target)
        {
            b->vpos.y = target;
            b->falling = false;

            // If touch lava, turn into rock
            if(stage_is_lava(b->x,b->y))
            {
                b->exist = false;
                stage_set_collision_tile(b->x,b->y,1);
                stage_set_tile(b->x,b->y,5);
                return;
            }
        }
    }
}


// Move boulder
static void b_move(BOULDER* b,PLAYER* pl)
{
    int pdir = pl->x < b->x ? 1 : -1;
    b->vpos.x = pl->vpos.x + pdir*16.0f;

    if(!pl->moving)
    {
        b->moving = false;
        b_get_gravity(b);
        b->vpos.x = b->x * 16.0f;
    }
}


// Boulder-player collision
static void boulder_player_collision(void* o, void* p)
{
    const float DELTA = 0.1f;

    PLAYER* pl = (PLAYER*)p;
    BOULDER* b = (BOULDER*)o;

    if(!b->exist) return;
    if(b->moving)
    {
        b_move(b,pl);
        return;
    }

    VEC2 stick = vpad_get_stick();

    if(!pl->moving && pl->y == b->y && abs(pl->x-b->x) == 1 
       && fabs(stick.x) > DELTA)
    {
        int dir = stick.x > 0.0f ? 1 : -1;
        int pdir = pl->x > b->x ? -1 : 1;
        if(dir != pdir) return;

        if(!stage_is_solid(b->x+dir,b->y))
        {
            stage_set_collision_tile(b->x,b->y,0);
            b->x += dir;
            pl->pushing = true;
            b->moving = true;
        }
    }
}


// Update boulder
static void boulder_update(void* o, float tm)
{
    BOULDER* b = (BOULDER*)o;

    if(!b->exist) return;
    if(b->falling)
    {
        b_fall(b,tm);
    }

    spr_animate(&b->spr,0,0,0,0,tm);

    b_update_location(b);
}


// Draw boulder
static void boulder_draw(void* o)
{
    BOULDER* b = (BOULDER*)o;
    if(b->exist == false) return;

    spr_draw(&b->spr,bmpBoulder,(int)round(b->vpos.x),(int)round(b->vpos.y) +1,0);
}


// Initialize
void boulder_init(ASSET_PACK* ass)
{
    bmpBoulder = (BITMAP*)get_asset(ass,"boulder");
}


// Create a new boulder
BOULDER boulder_create(int x, int y)
{
    BOULDER b;

    b.x = x;
    b.y = y;
    b.vpos = vec2(x*16.0f,y*16.0f);
    b.spr = create_sprite(16,16);
    b.onDraw = boulder_draw;
    b.onUpdate = boulder_update;
    b.onPlayerCollision = boulder_player_collision;
    b.exist = true;
    b.moving = false;
    b.falling = false;
    b.gravity = 0.0f;

    return b;
}
