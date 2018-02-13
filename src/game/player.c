/// Player (source)
/// (c) 2018 Jani Nykänen

#include "player.h"

#include "../engine/graphics.h"

#include "../vpad.h"

#include "stage.h"
#include "objects.h"
#include "status.h"

#include "math.h"
#include "stdio.h"

// Global player constants
static float PL_SPEED_DEFAULT = 0.75f;
static float PL_JUMP_SPEED = 0.80f;
static float PL_GRAVITY_MAX = 4.0f;
static float PL_GRAVITY_DELTA = 0.1f;
static const float STICK_DELTA = 0.1f;

// Player bitmap
static BITMAP* bmpPlayer;


// Get gravity
static bool pl_get_gravity(PLAYER* pl)
{
    pl->checkGravity = false;

    if(pl->moving) return false;

    POINT dim = stage_get_map_size();
    int y = pl->y;
    
    if(pl->y == dim.y-1 || stage_is_vine(pl->x,pl->y)) return false;
    if(stage_is_solid(pl->x,++y)) return false;

    int oldx = pl->x;
    int oldy = pl->y;

    for(; y < dim.y; ++ y)
    {
        if(stage_is_solid(pl->x,y))
        {
            break;
            
        }
        else if(stage_is_vine(pl->x,pl->y))
        {
            y --;
            break;
        }
    }

    pl->y = y-1;
    pl->target.y = pl->y*16.0f;
    pl->target.x = pl->x*16.0f;
    pl->moving = true;
    pl->climbing = false;
    pl->falling = true;

    stage_set_collision_tile(oldx,oldy,0);
    stage_set_collision_tile(pl->x,pl->y,1);

    return true;
}


// Bounce
static void pl_bounce(PLAYER* pl)
{
    VEC2 stick = vpad_get_stick();

    // Direction
    if(fabs(stick.x) > STICK_DELTA)
    {
        pl->dir = stick.x > 0.0f ? 0 : 1;
    }

    // If jump button released, start jumping
    if(pl->spr.frame >= 2 && (vpad_get_button(0) == RELEASED || vpad_get_button(0) == UP))
    {
        int d = pl->dir == 0 ? 1 : -1;

        int oldx = pl->x;
        int oldy = pl->y;

        pl->bouncing = false;
        pl->jumping = true;

        pl->speed = PL_JUMP_SPEED;
        if(stage_is_solid(pl->x+d,pl->y))
        {
            if(!stage_is_solid(pl->x,pl->y-1) && !stage_is_solid(pl->x+d,pl->y-1))
            {
                -- pl->y;
                pl->x += d;
                pl->gravity = -2.1f;
                pl->speed *= 0.625f;
            }
            else
            {
                pl->jumping = false;
                return;
            }
        }
        else
        {
            if(stage_is_solid(pl->x,pl->y-1))
            {
                pl->x += d;
                pl->gravity = -1.0f;
            }
            else if(stage_is_solid(pl->x+d,pl->y-1))
            {
                pl->x += d;
                pl->gravity = -1.0f;
            }
            else if(stage_is_solid(pl->x+d*2,pl->y) || stage_is_solid(pl->x+d*2,pl->y-1))
            {
                if(stage_is_solid(pl->x+d*2,pl->y-1))
                {
                    pl->x += d;
                    pl->gravity = -1.625f;
                    pl->speed *= 0.625f;
                }
                else
                {
                    pl->gravity = -2.1f;
                    pl->x += d * 2;
                    -- pl->y;
                    pl->speed *= 1.25f;
                }
            }
            else
            {
                pl->x += d * 2;
                pl->speed *= 1.30f;
                pl->gravity = -1.5f;
            }
        }
        pl->moving = true;

        pl->target.x = pl->x * 16.0f;
        pl->target.y = pl->y * 16.0f;
        
        stage_set_collision_tile(oldx,oldy,0);
        stage_set_collision_tile(pl->x,pl->y,1);
        status_add_turn();
    }
}


// Control
static void pl_control(PLAYER* pl)
{
    if(!obj_can_move() || pl->moving || pl->jumping) return;
    if(pl->checkGravity && pl_get_gravity(pl)) return;

    pl->falling = false;
    pl->gravity = 0.0f;

    VEC2 stick = vpad_get_stick();
    int oldx = pl->x;
    int oldy = pl->y;
    int d = 0;

    // Jump button pressed
    if(!pl->bouncing && vpad_get_button(0) == PRESSED)
    {   
        pl->bouncing = true;
        pl->spr.count = 0.0f;
        pl->spr.frame = 0;
        pl->spr.row = 2;
    }

    // Bounce
    if(pl->bouncing)
    {
        pl_bounce(pl);
        return;
    }

    // Get movement direction
    if(fabs(stick.x) > STICK_DELTA)
    {
        d = (stick.x > 0.0f ? 1 : -1);
        pl->x += d;
        pl->dir = d == 1 ? 0 : 1;
        pl->moving = true;
        pl->climbing = false;
    }
    else if(fabs(stick.y) > STICK_DELTA)
    {
        d = (stick.y > 0.0f ? 1 : -1);
        pl->y += d;
        pl->moving = true;
        pl->climbing = true;
    }

    // Check if it's possible to move
    if(pl->moving)
    {
        if( stage_is_solid(pl->x,pl->y) 
            || (pl->climbing && (!stage_is_vine(pl->x,pl->y) && pl->y <= oldy) ) )
        {
            pl->moving = false;
            pl->x = oldx;
            pl->y = oldy;
        }
        else
        {
            pl->target.y = pl->y*16.0f;
            pl->target.x = pl->x*16.0f;

            pl->speed = PL_SPEED_DEFAULT;

            stage_set_collision_tile(oldx,oldy,0);
            stage_set_collision_tile(pl->x,pl->y,1);
            status_add_turn();
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
        pl->speed = PL_SPEED_DEFAULT;

        if(!pl->jumping)
            pl_control(pl);
        pl->jumping = false;
        pl->pushing = false;
    }
}


// Move
static void pl_move(PLAYER* pl, float tm)
{
    if(!pl->moving) return;

    // "Coordinate" movement
    pl_move_coord(pl,tm,&pl->vpos.x,&pl->target.x, pl->speed);
    if(!pl->jumping)
    {
        pl_move_coord(pl,tm,&pl->vpos.y,&pl->target.y, pl->falling ? pl->gravity : PL_SPEED_DEFAULT);
    }

    // Gravity
    if(pl->falling || pl->jumping)
    {
        if(pl->gravity < PL_GRAVITY_MAX)
        {
            pl->gravity += PL_GRAVITY_DELTA * tm;
            if(pl->gravity > PL_GRAVITY_MAX)
            {
                pl->gravity = PL_GRAVITY_MAX;
            }
        }

        if(pl->jumping)
        {
            pl->vpos.y += pl->gravity * tm;
        }
    }
}


// Animate player
static void pl_animate(PLAYER* pl, float tm)
{
    // Bouncing
    if(pl->bouncing)
    {
        if(pl->spr.frame < 2)
        {
            spr_animate(&pl->spr,2,0,2,8,tm);
        }
    }
    // Jumping
    else if(pl->jumping)
    {
        if(pl->spr.frame < 7)
        {
            spr_animate(&pl->spr,2,2,7,6,tm);
        }
    }
    // Standing
    else if(!pl->moving)
    {
        if(stage_is_vine(pl->x,pl->y) && !stage_is_solid(pl->x,pl->y +1))
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
        if(pl->climbing)
            spr_animate(&pl->spr,3,0,7,4,tm);
        else
        {
            if(pl->pushing)
                spr_animate(&pl->spr,4,0,3,6,tm);
            else
                spr_animate(&pl->spr,1,0,5,5,tm);
        }
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
    pl.climbing = false;
    pl.target = pl.vpos;
    pl.delta = vec2(0,0);
    pl.dir = 0;
    pl.checkGravity = false;
    pl.falling = false;
    pl.climbing = false;
    pl.gravity = 0.0f;
    pl.jumping = false;
    pl.bouncing = false;
    pl.pushing = false;
    pl.speed = PL_SPEED_DEFAULT;

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
