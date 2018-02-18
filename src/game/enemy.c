/// Enemy (source)
/// (c) 2018 Jani Nykänen

#include "enemy.h"

#include "../engine/graphics.h"

#include "../vpad.h"

#include "stage.h"
#include "player.h"
#include "status.h"

#include "stdio.h"
#include "math.h"

// Global enemy constants
static float ENEMY_SPEED_DEFAULT = 0.90f;

// Enemy bitmap
static BITMAP* bmpEnemy;



// Get gravity
static void enemy_get_gravity(ENEMY* e)
{
    e->falling = false;
    e->gravity = 0.0f;

    int oldy = e->y;
    while(!stage_is_solid(e->x,e->y+1))
    {
        ++e->y;
    }

    if(e->y != oldy)
    {
        e->preventMovement = true;
        e->falling = true;
        stage_set_collision_tile(e->x,oldy,0);
        stage_set_collision_tile(e->x,e->y,1);
    }
}


// Fall
static void enemy_fall(ENEMY* e, float tm)
{
    const float GRAV_MAX = 4.0f;
    const float GRAV_SPEED = 0.2f;

    float target = e->y*16.0f;

    if(e->vpos.y < target)
    {
        e->gravity += GRAV_SPEED * tm;
        if(e->gravity > GRAV_MAX)
        {
            e->gravity = GRAV_MAX;
        }
        e->vpos.y += e->gravity * tm;

        if(e->vpos.y >= target)
        {
            e->vpos.y = target;
            e->falling = false;
        }
    }
}


// Move
static void enemy_move(ENEMY* e, float tm)
{
    bool horizontal = e->id == 0 || e->id == 2;
    float target = (horizontal ? e->x : e->y) * 16.0f;

    e->preventMovement = true;

    if(horizontal)
        e->vpos.x += ENEMY_SPEED_DEFAULT * e->dir * tm;
    else
        e->vpos.y += ENEMY_SPEED_DEFAULT * e->dir * tm;

    bool cond1 = horizontal ? e->vpos.x > target : e->vpos.y > target;
    bool cond2 = horizontal ? e->vpos.x < target : e->vpos.y < target;

    if((e->dir == 1 && cond1) || (e->dir == -1 && cond2))
    {
        e->moving = false;

        if(horizontal)
            e->vpos.x = target;
        else
            e->vpos.y = target;

        if(e->id ==0)
        {
            enemy_get_gravity(e);
        }
    }
}


// Boulder-player collision
static void enemy_player_collision(void* o, void* p)
{
    PLAYER* pl = (PLAYER*)p;
    ENEMY* e = (ENEMY*)o;

    if(!e->exist) return;

    // If player moving, make the enemy move
    if(!e->moving && pl->startedMoving)
    {
        // Horizontal movement
        if(e->id == 0 || e->id == 2)
        {
            if(stage_is_solid(e->x+e->dir,e->y)
             || (e->id == 0 && !stage_is_solid(e->x+e->dir,e->y +1)))
            {
                e->dir *= -1;
                if(stage_is_solid(e->x+e->dir,e->y)
                || (e->id == 0 && !stage_is_solid(e->x+e->dir,e->y +1)))
                {
                    return;
                }
            }
            stage_set_collision_tile(e->x,e->y,0);
            e->x += e->dir;
        }
        // Vertical movement
        else if(e->id == 3)
        {
            if(stage_is_solid(e->x,e->y+e->dir) || stage_is_lava(e->x,e->y+e->dir))
            {
                e->dir *= -1;
                if(stage_is_solid(e->x,e->y+e->dir) || stage_is_lava(e->x,e->y+e->dir))
                {
                    return;
                }
            }
            stage_set_collision_tile(e->x,e->y,0);
            e->y += e->dir;
        }

        stage_set_collision_tile(e->x,e->y,1); 
        e->moving = true;
    }
}


// Animate
static void enemy_animate(ENEMY* e, float tm)
{
    if(!(e->id == 0 && e->moving))
        spr_animate(&e->spr,e->id,0,3,8,tm);
    else
    {
        spr_animate(&e->spr,e->id,4,7,6,tm);
        e->sprDir = e->dir == 1 ? 1 : 0;
    }
}


// Update enemy
static void enemy_update(void* o, float tm)
{
    ENEMY* e = (ENEMY*)o;
    e->preventMovement = false;
    if(!e->exist) return;

    enemy_animate(e,tm);

    // If falling, fall
    if(e->id ==0)
    {
        if(!stage_is_solid(e->x,e->y+1))
        {
            enemy_get_gravity(e);
        }

        if(e->falling)
        {
            e->preventMovement = true;
            enemy_fall(e,tm);
        }
    }

    // If moving, move
    if(e->moving)
    {
        enemy_move(e,tm);
    }
}


// Draw enemy
static void enemy_draw(void* o)
{
    ENEMY* e = (ENEMY*)o;
    if(e->exist == false) return;

    spr_draw(&e->spr,bmpEnemy,e->vpos.x-4,e->vpos.y-4 +1,e->sprDir);
    
}


// Reset
static void enemy_reset(void* o)
{
    ENEMY* e = (ENEMY*)o;
    if(e->exist == false) return;

    stage_set_collision_tile(e->x,e->y,1);
    e->moving = false;
    e->dir = e->x % 2 == 0 ? 1 : -1;
}


// Initialize
void enemy_init(ASSET_PACK* ass)
{
    bmpEnemy = (BITMAP*)get_asset(ass,"enemy");
}


// Create a new enemy
ENEMY enemy_create(int x, int y, int id)
{
    ENEMY b;

    b.x = x;
    b.y = y;
    b.id = id;
    b.vpos = vec2(x*16.0f,y*16.0f);
    b.spr = create_sprite(24,24);
    b.spr.row = id;
    b.onDraw = enemy_draw;
    b.onUpdate = enemy_update;
    b.onPlayerCollision = enemy_player_collision;
    b.onReset = enemy_reset;
    b.exist = true;
    b.preventMovement = false;
    b.moving = false;
    b.dir = x % 2 == 0 ? 1 : -1;
    b.sprDir = 0;
    b.gravity = 0.0f;
    b.falling = false;

    stage_set_collision_tile(b.x,b.y,1);

    return b;
}
