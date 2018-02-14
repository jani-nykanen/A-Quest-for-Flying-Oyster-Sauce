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
static float ENEMY_SPEED_DEFAULT = 0.75f;

// Enemy bitmap
static BITMAP* bmpEnemy;


// Move
static void enemy_move(ENEMY* e, float tm)
{
    bool horizontal = e->id == 0 || e->id == 2;

    e->preventMovement = true;

/*
    if(stage_is_solid(e->x,e->y))
    {
        e->moving = false;
        if(horizontal)
            e->x -= e->dir;
        else
            e->y -= e->dir;
        return;
    }
*/
    float target = (horizontal ? e->x : e->y) * 16.0f;

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
            if(stage_is_solid(e->x+e->dir,e->y))
            {
                e->dir *= -1;
                if(stage_is_solid(e->x+e->dir,e->y))
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
    b.onDraw = enemy_draw;
    b.onUpdate = enemy_update;
    b.onPlayerCollision = enemy_player_collision;
    b.exist = true;
    b.preventMovement = false;
    b.moving = false;
    b.dir = x % 2 == 0 ? 1 : -1;
    b.sprDir = 0;

    stage_set_collision_tile(b.x,b.y,1);

    return b;
}
