/// Player (source)
/// (c) 2018 Jani Nykänen

#include "player.h"

#include "../engine/graphics.h"

#include "../vpad.h"

#include "stage.h"

#include "math.h"
#include "stdio.h"

// Global player constants
static float PL_SPEED = 0.75f;
static float PL_GRAVITY_MAX = 4.0f;
static float PL_GRAVITY_DELTA = 0.1f;

// Player bitmap
static BITMAP* bmpPlayer;


// Get gravity
static bool pl_get_gravity(PLAYER* pl)
{
    pl->checkGravity = false;

    if(pl->moving) return false;

    int* colMap = stage_get_collision_map();
    POINT dim = stage_get_map_size();

    int y = pl->y;
    
    int id = colMap[y*dim.x + pl->x];
    if(pl->y == dim.y-1 || id == 2) return false;
    id = colMap[(++y)*dim.x + pl->x];
    if(id > 0 && id != 2) return false;

    for(; y < dim.y; ++ y)
    {
        id = colMap[y*dim.x + pl->x];
        if(id > 0 && id != 2)
        {
            break;
            
        }
        else if(id == 2)
        {
            y --;
            break;
        }
    }

    pl->y = y-1;
    pl->target.y = pl->y*16.0f;
    pl->target.x = pl->x*16.0f;
    pl->moving = true;
    pl->moveVertical = false;
    pl->falling = true;
    pl->gravity = 0.0f;

    return true;
}


// Control
static void pl_control(PLAYER* pl)
{
    const float DELTA = 0.1f;

    if(pl->moving) return;
    if(pl->checkGravity && pl_get_gravity(pl)) return;

    pl->falling = false;

    VEC2 stick = vpad_get_stick();
    int oldx = pl->x;
    int oldy = pl->y;
    int d = 0;

    // Get movement direction
    if(fabs(stick.x) > DELTA)
    {
        d = (stick.x > 0.0f ? 1 : -1);
        pl->x += d;
        pl->dir = d == 1 ? 0 : 1;
        pl->moving = true;
        pl->moveVertical = false;
    }
    else if(fabs(stick.y) > DELTA)
    {
        d = (stick.y > 0.0f ? 1 : -1);
        pl->y += d;
        pl->moving = true;
        pl->moveVertical = true;
    }


    // Check if it's possible to move
    if(pl->moving)
    {
        int* colMap = stage_get_collision_map();
        int id = colMap[pl->y * 16 + pl->x];

        if( (id > 0 && id != 2) 
            || (pl->moveVertical && (id != 2 && pl->y <= oldy) ) )
        {
            pl->moving = false;
            pl->x = oldx;
            pl->y = oldy;
        }
        else
        {
            pl->target.y = pl->y*16.0f;
            pl->target.x = pl->x*16.0f;
        }
    }
}


// Coordinate movement
static void pl_move_coord(PLAYER* pl, float tm, float* coord,  float* target, float speed)
{
    if(*target > *coord)
    {
        *coord += speed * tm;
        if(*coord >= *target)
        {
            pl->moving = false;
        }
    }
    else if(*target < *coord)
    {
        *coord -= speed * tm;
        if(*coord  <= *target)
        {
            pl->moving = false;
        }
    }

    if(!pl->moving)
    {
        *coord = *target;
        pl->checkGravity = true;
        pl_control(pl);
    }
}


// Move
static void pl_move(PLAYER* pl, float tm)
{
    if(!pl->moving) return;

    // "Coordinate" movement
    pl_move_coord(pl,tm,&pl->vpos.x,&pl->target.x, PL_SPEED);
    pl_move_coord(pl,tm,&pl->vpos.y,&pl->target.y, pl->falling ? pl->gravity : PL_SPEED);

    // Gravity
    if(pl->falling)
    {
        if(pl->gravity < PL_GRAVITY_MAX)
        {
            pl->gravity += PL_GRAVITY_DELTA * tm;
            if(pl->gravity > PL_GRAVITY_MAX)
            {
                pl->gravity = PL_GRAVITY_MAX;
            }
        }
    }
}


// Animate player
static void pl_animate(PLAYER* pl, float tm)
{
    // Standing
    if(!pl->moving)
    {
        int* colMap = stage_get_collision_map();
        POINT dim = stage_get_map_size();

        if(colMap[pl->y * dim.x + pl->x] == 2 && colMap[(pl->y+1)*dim.x + pl->x] != 1)
        {
            spr_animate(&pl->spr,3,0,0,0,tm);
        }
        else
        {
            spr_animate(&pl->spr,0,0,3,10,tm);
        }
    }
    // Falling
    else if(pl->falling)
    {
        int frame = pl->gravity > 0.5f ? 8 : 7;
        spr_animate(&pl->spr,2,frame,frame,0,tm);
    }
    // Moving "normally"
    else
    {
        if(pl->moveVertical)
            spr_animate(&pl->spr,3,0,7,4,tm);
        else
            spr_animate(&pl->spr,1,0,5,5,tm);
    }
}


// Initialize player
void pl_init(ASSET_PACK* ass)
{
    bmpPlayer = (BITMAP*)get_asset(ass,"player");
}


// Create a new player
PLAYER pl_create(int x, int y)
{
    PLAYER pl;
    pl.x = x;
    pl.y = y;
    pl.vpos.x = 16.0f*x;
    pl.vpos.y = 16.0f*y;
    pl.spr = create_sprite(24,24);

    pl.moving = false;
    pl.moveVertical = false;
    pl.target = pl.vpos;
    pl.delta = vec2(0,0);
    pl.dir = 0;
    pl.checkGravity = false;
    pl.falling = false;
    pl.gravity = 0.0f;

    return pl;
}


// Update player
void pl_update(PLAYER* pl, float tm)
{
    pl_control(pl);
    pl_move(pl,tm);
    pl_animate(pl,tm);
}


// Draw player
void pl_draw(PLAYER* pl)
{
    spr_draw(&pl->spr,bmpPlayer,(int)round(pl->vpos.x) - 4,(int)round(pl->vpos.y) -4 + 1,pl->dir);
}
