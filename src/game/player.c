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
// static float PL_GRAVITY = 0.1f;

// Player bitmap
static BITMAP* bmpPlayer;


// Control
static void pl_control(PLAYER* pl)
{
    const float DELTA = 0.1f;

    VEC2 stick = vpad_get_stick();

    if(pl->moving) return;

    int oldx = pl->x;
    int oldy = pl->y;

    int d;
    if(fabs(stick.x) > DELTA)
    {
        d = (stick.x > 0.0f ? 1 : -1);
        pl->x += (stick.x > 0.0f ? 1 : -1);
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

    if(pl->moving)
    {
        int* colMap = stage_get_collision_map();
        int id = colMap[pl->y * 16 + pl->x];
        if(id > 0 && id != 2)
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


// Move
static void pl_move(PLAYER* pl, float tm)
{
    if(!pl->moving) return;

    // TODO: Single method for these

    // Horizontal movement
    if(pl->target.x > pl->vpos.x)
    {
        pl->vpos.x += PL_SPEED * tm;
        if(pl->vpos.x >= pl->target.x)
        {
            pl->vpos.x = pl->target.x;
            pl->moving = false;
            pl_control(pl);
        }
    }
    else if(pl->target.x < pl->vpos.x)
    {
        pl->vpos.x -= PL_SPEED * tm;
        if(pl->vpos.x <= pl->target.x)
        {
            pl->vpos.x = pl->target.x;
            pl->moving = false;
            pl_control(pl);
        }
    }

    // Vertical movement
    if(pl->target.y > pl->vpos.y)
    {
        pl->vpos.y += PL_SPEED * tm;
        if(pl->vpos.y >= pl->target.y)
        {
            pl->vpos.y = pl->target.y;
            pl->moving = false;
            pl_control(pl);
        }
    }
    else if(pl->target.y < pl->vpos.y)
    {
        pl->vpos.y -= PL_SPEED * tm;
        if(pl->vpos.y <= pl->target.y)
        {
            pl->vpos.y = pl->target.y;
            pl->moving = false;
            pl_control(pl);
        }
    }

}


// Animate player
static void pl_animate(PLAYER* pl, float tm)
{
    if(!pl->moving)
        spr_animate(&pl->spr,0,0,3,10,tm);
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
